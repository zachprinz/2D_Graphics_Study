#include "LightEngine.h"
#include "Drawn.h"

LightEngine::LightEngine(AABB bounds,sf::View panelView, sf::Color ambientColor){
	hullTree = new QuadTree(bounds);
	lightTree = new QuadTree(bounds);
	this->panelView = panelView;
	CalculatePanelBounds();
	ambienceColor = ambientColor;
	lightTexture.create(panelView.getSize().x,panelView.getSize().y);
	lightTexture.clear(sf::Color(0,0,0,0));
	lightTexture.display();
	lightsSprite.setTexture(lightTexture.getTexture());
	lightsSprite.setOrigin(lightsSprite.getGlobalBounds().width / 2, lightsSprite.getGlobalBounds().height /2);
	lightsSprite.setPosition(512,400);
	lightsSprite.scale(1.0f,1.0f);

	lightShader.loadFromFile("lightShader.frag",sf::Shader::Fragment);
	lightShader.setParameter("texture", sf::Shader::CurrentTexture);
	lightToTextureShader.loadFromFile("lightToPanelShader.frag",sf::Shader::Fragment);
	lightToTextureShader.setParameter("texture",sf::Shader::CurrentTexture);
	shadowShader.loadFromFile("shadowShader.frag",sf::Shader::Fragment);
	shadowShader.setParameter("texture",sf::Shader::CurrentTexture);
	subtractShader.loadFromFile("subtractShader.frag",sf::Shader::Fragment);
	subtractShader.setParameter("texture",sf::Shader::CurrentTexture);
	whiteShader.loadFromFile("whiteShader.frag",sf::Shader::Fragment);
	whiteShader.setParameter("texture",sf::Shader::CurrentTexture);
	
	tempLightText.create(300,300);
	tempLightText.clear(sf::Color(0,0,0,0));
	tempLightText.display();
	tempLightSprite.setTexture(tempLightText.getTexture());

	tempShadowText.create(300,300);
	tempShadowText.display();
	tempShadowSprite.setTexture(tempShadowText.getTexture());
	
	predoneLightTexture.loadFromFile("Images/light.png");
	predoneLight.setTexture(predoneLightTexture);
};
void LightEngine::UpdateLights(sf::RenderTexture* panel){
	hullTree->Update();
	lightTree->Update();
	lightTexture.clear(sf::Color(0,0,0,180));
	std::vector<QuadTreeObject*> lightsToDraw = lightTree->SearchRegion(viewBounds);
	for(int x = 0; x < lightsToDraw.size(); x++){
		DrawLight(lightsToDraw[x]->myLight);
	}
	lightTexture.display();
	lightsSprite.setPosition(panelView.getCenter().x ,panelView.getCenter().y);
};
void LightEngine::DrawLights(sf::RenderTexture* panel){
    panel->draw(lightsSprite);
};
void LightEngine::DrawLight(Light* light){
	light->Update();
	tempLightSprite.setPosition(0,0);
	std::vector<QuadTreeObject*> intersectingHulls = hullTree->SearchRegion(light->GetBounds());
	sf::VertexArray shadows(sf::Quads,intersectingHulls.size() * 4);
	sf::Transform shadowsTransform;
    	tempLightText.clear(light->color); //TODO lags
	tempShadowText.clear(sf::Color(255,255,255,255));
	for(int x = 0; x < intersectingHulls.size(); x++){
		light->GetShadowQuad(&intersectingHulls[x]->myHull->shadowLines[0],intersectingHulls[x]->myHull,sf::Vector2f(0,0),&shadows[x*4]);
		tempShadowText.draw(*(intersectingHulls[x]->myHull->mySprite->GetSprite()));
	}
	predoneLight.setScale((light->radius * 2) / predoneLight.getGlobalBounds().width,(2*light->radius) / predoneLight.getGlobalBounds().height);
        tempShadowText.draw(shadows);
	for(int x = 0; x < intersectingHulls.size(); x++){
		sf::Vector2f tempPosition = intersectingHulls[x]->myHull->mySprite->GetSprite()->getPosition();
		intersectingHulls[x]->myHull->mySprite->GetSprite()->setPosition(tempPosition - sf::Vector2f(light->GetBounds().GetLowerBound().x + 11.2,light->GetBounds().GetLowerBound().y + 9.6));
		tempShadowText.draw(*(intersectingHulls[x]->myHull->mySprite->GetSprite()),&whiteShader);
		intersectingHulls[x]->myHull->mySprite->GetSprite()->setPosition(tempPosition);
	}
	tempShadowText.display();
	tempLightText.draw(tempShadowSprite,&subtractShader);
    	tempLightText.draw(predoneLight);
	tempLightSprite.setPosition(light->GetBounds().GetLowerBound().x - panelLowerPoint.x,light->GetBounds().GetLowerBound().y - panelLowerPoint.y);
	tempLightSprite.setTextureRect(sf::IntRect(0,0,light->radius * 2.0f,light->radius* 2.0f));
    	shadowShader.setParameter("color",light->color);
	lightTexture.draw(tempLightSprite,&shadowShader);
	tempLightText.display();
	predoneLight.setScale(1.0,1.0);
};
void LightEngine::DrawHigh(sf::RenderTexture* panel){
	lightTexture.clear(sf::Color(0,0,0,80));
	lightTexture.display();
	panel->draw(lightsSprite);
};
void LightEngine::AddLight(Light* light){
	lightTree->AddObject(light);
};
void LightEngine::AddHull(Hull* hull){
	hullTree->AddObject(hull);
};
void LightEngine::SetView(sf::View view){
	panelView = view;
	panelLowerPoint.x = panelView.getCenter().x - panelView.getSize().x/2;
	panelLowerPoint.y = panelView.getCenter().y - panelView.getSize().y/2;
	CalculatePanelBounds();
};
void LightEngine::DebugRender(sf::RenderTexture* panel){
	hullTree->DrawDebug(panel);
	lightTree->DrawDebug(panel);
};
void LightEngine::SetAmbienceColor(sf::Color color){
	ambienceColor = color;
};
void LightEngine::CalculatePanelBounds(){
	viewBounds.SetDims(Vec2f(panelView.getSize().x,panelView.getSize().y));
	viewBounds.SetCenter(Vec2f(panelView.getCenter().x,panelView.getCenter().y));
	viewBounds.CalculateBounds();
	viewBounds.CalculateCenter();
	viewBounds.CalculateHalfDims();
};