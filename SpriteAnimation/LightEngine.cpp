#include "LightEngine.h"

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
	tempLightText.create(500,500);
	tempLightText.clear(sf::Color(0,0,0,0));
	tempLightText.display();
	tempLightSprite.setTexture(tempLightText.getTexture());
	panelLightTempText.create(1080,800);
	panelLightTempText.clear(sf::Color(0,0,0,0));
	panelLightTempText.display();
	panelLightTempSprite.setTexture(panelLightTempText.getTexture());
};
void LightEngine::DrawLights(sf::RenderTexture* panel){
	hullTree->Update();
	lightTree->Update();
	ambienceColor = sf::Color(0,0,0,60);
	lightTexture.clear(sf::Color(ambienceColor));
	std::vector<QuadTreeObject*> lightsToDraw = lightTree->SearchRegion(viewBounds);
	for(int x = 0; x < lightsToDraw.size(); x++){
		DrawLight(lightsToDraw[x]->myLight);
	}
	lightTexture.display();
	panelLightTempText.clear(sf::Color(0,0,0,0));
	panelLightTempText.draw(lightsSprite,&lightToTextureShader);
	panelLightTempText.display();
	panelLightTempSprite.setPosition(panelView.getCenter().x - 512,panelView.getCenter().y - 400);
	panel->draw(panelLightTempSprite);
};
void LightEngine::DrawLight(Light* light){
	std::vector<QuadTreeObject*> intersectingHulls = hullTree->SearchRegion(light->GetBounds());
	std::vector<sf::ConvexShape> shadows;
	for(int x = 0; x < intersectingHulls.size(); x++){
		shadows.push_back(light->GetShadowPolygon(&intersectingHulls[x]->myHull->shadowLines[0],intersectingHulls[x]->myHull));
	}
	sf::CircleShape lightShape(light->radius);
	lightShape.setFillColor(sf::Color(255,255,255,255));
	lightShader.setParameter("lightColor",light->color);
	lightShader.setParameter("centerX",lightShape.getRadius());
	lightShader.setParameter("centerY",lightShape.getRadius() + (500-(2*(lightShape.getRadius()))));
	lightShader.setParameter("radius",light->radius);
	tempLightText.clear(sf::Color(0,0,0,0));
	for(int x = 0; x < shadows.size(); x++){
		shadows[x].setFillColor(sf::Color(0,255,0,255));
		shadows[x].setPosition((0 - shadows[x].getLocalBounds().left) + (shadows[x].getLocalBounds().left - light->GetBounds().GetUpperBound().x) + 300 - 11.6,(0 - shadows[x].getLocalBounds().top) + (shadows[x].getLocalBounds().top - light->GetBounds().GetUpperBound().y) + 309.2);//-11.6 - light->GetBounds().GetLowerBound().x,0-shadows[x].getPosition().y - panelLowerPoint.y + 9.2 - light->GetBounds().GetLowerBound().y - panelLowerPoint.y);
		tempLightText.draw(shadows[x]);//,&shadowShader);
	};
	tempLightText.display();
	tempLightText.draw(lightShape,&lightShader);
	tempLightSprite.setPosition(light->GetBounds().GetLowerBound().x - panelLowerPoint.x,light->GetBounds().GetLowerBound().y - panelLowerPoint.y);
	lightTexture.draw(tempLightSprite);
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
	//hullTree->DrawDebug(panel);
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