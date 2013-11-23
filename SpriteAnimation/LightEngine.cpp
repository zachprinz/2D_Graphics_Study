#include "LightEngine.h"

LightEngine::LightEngine(AABB bounds,sf::View panelView, sf::Color ambientColor){
	hullTree = new QuadTree(bounds);
	lightTree = new QuadTree(bounds);
	this->panelView = panelView;
	CalculatePanelBounds();
	ambienceColor = ambientColor;
	lightTexture.create(panelView.getSize().x,panelView.getSize().y);
	lightsSprite.setTexture(lightTexture.getTexture());
	lightsSprite.setOrigin(lightsSprite.getGlobalBounds().width / 2, lightsSprite.getGlobalBounds().height /2);
	lightsSprite.scale(1.0f,-1.0f);
	lightShader.loadFromFile("lightShader.frag",sf::Shader::Fragment);
};
void LightEngine::DrawLights(sf::RenderTexture* panel){
	hullTree->Update();
	lightTree->Update();
	lightTexture.clear(sf::Color(0,0,0,0));//ambienceColor);
	std::vector<QuadTreeObject*> lightsToDraw = lightTree->SearchRegion(viewBounds);
	for(int x = 0; x < lightsToDraw.size(); x++){
		DrawLight(lightsToDraw[x]->myLight);
	}
	lightsSprite.setTexture(lightTexture.getTexture());
	lightsSprite.setPosition(panelView.getCenter().x,panelView.getCenter().y);
	panel->draw(lightsSprite);
};
void LightEngine::DrawLight(Light* light){
	std::vector<QuadTreeObject*> intersectingHulls = hullTree->SearchRegion(light->GetBounds());
	std::vector<sf::ConvexShape> shadows;
	for(int x = 0; x < intersectingHulls.size(); x++){
		shadows.push_back(light->GetShadowPolygon(&intersectingHulls[x]->myHull->shadowLines[0],intersectingHulls[x]->myHull));
	}
	sf::CircleShape lightShape(light->radius);
	lightShape.setFillColor(sf::Color(255,255,255,255));
	lightShape.setPosition(light->GetBounds().GetLowerBound().x - panelLowerPoint.x,light->GetBounds().GetLowerBound().y - panelLowerPoint.y);//light->GetBounds().GetUpperBound().x - panelLowerPoint.x,light->GetBounds().GetUpperBound().y - panelLowerPoint.y);
	lightShader.setParameter("lightColor",light->color);
	lightShader.setParameter("centerX",lightShape.getGlobalBounds().width / 2);
	lightShader.setParameter("centerY",lightShape.getGlobalBounds().height / 2);
	lightShader.setParameter("radius",light->radius);
	lightShader.setParameter("texture", sf::Shader::CurrentTexture);
	lightTexture.draw(lightShape,&lightShader);
	for(int x = 0; x < shadows.size(); x++){
		shadows[x].setFillColor(sf::Color(0,0,0,255));
		shadows[x].setPosition(shadows[x].getPosition().x - panelLowerPoint.x -11.6,shadows[x].getPosition().y - panelLowerPoint.y + 9.2);
		lightTexture.draw(shadows[x]);
	};
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