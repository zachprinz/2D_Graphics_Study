#ifndef LIGHTENGINE_H
#define LIGHTENGINE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "AABB.h"
#include "ShadowLine.h"
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
	sf::Vector<Hull*> hulls;
	sf::Vector<Hull*> hullsOnScreen;
	sf::Vector<Light*> lights;
	sf::Vector<Light*> lightsOnScreen;
	sf::RenderTexture lightTexture;
	sf::RenderTexture* spritePanelTexture;
	QuadTree lightTree;
	QuadTree hullTree;
	//Camera lightCamera;
	sf::RenderTexture finalTexture;
	sf::Color ambienceColor;
}

#endif