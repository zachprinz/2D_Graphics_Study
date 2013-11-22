#ifndef LIGHTENGINE_H
#define LIGHTENGINE_H

#include <vector>
#include "QuadTree.h"

class LightEngine{
public:
	LightEngine(AABB bounds,sf::View panelView, sf::Color ambientColor);
	void DrawLights();
	void AddLight(Light*);
	void AddHull(Hull*);
	void SetView(sf::View);
	void DebugRender(sf::RenderTexture* panel);
	void SetAmbienceColor(sf::Color);
private:
	sf::View panelView;
	AABB viewBounds;
	std::vector<Hull*> hulls;
	std::vector<Hull*> hullsOnScreen;
	std::vector<Light*> lights;
	std::vector<Light*> lightsOnScreen;
	sf::RenderTexture lightTexture;
	sf::RenderTexture* spritePanelTexture;
	QuadTree* lightTree;
	QuadTree* hullTree;
	//Camera lightCamera;
	sf::RenderTexture finalTexture;
	sf::Color ambienceColor;
};

#endif