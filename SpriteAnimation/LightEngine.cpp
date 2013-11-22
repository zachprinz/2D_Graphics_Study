#include "LightEngine.h"

LightEngine::LightEngine(AABB bounds,sf::View panelView, sf::Color ambientColor){
	hullTree = new QuadTree(bounds);
	lightTree = new QuadTree(bounds);
};
void LightEngine::DrawLights(){
	hullTree->Update();
	lightTree->Update();
};
void LightEngine::AddLight(Light* light){
	lightTree->AddObject(light);
};
void LightEngine::AddHull(Hull* hull){
	hullTree->AddObject(hull);
};
void LightEngine::SetView(sf::View view){
	panelView = view;
};
void LightEngine::DebugRender(sf::RenderTexture* panel){
	hullTree->DrawDebug(panel);
	//lightTree->DrawDebug(panel);
};
void LightEngine::SetAmbienceColor(sf::Color color){
	ambienceColor = color;
};