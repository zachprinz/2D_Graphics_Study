#ifndef LIGHTENGINE_H
#define LIGHTENGINE_H

#include <vector>
#include "QuadTree.h"

class LightEngine{
public:
	LightEngine(AABB bounds,sf::View panelView, sf::Color ambientColor);
	void DrawLights(sf::RenderTexture*);
	void AddLight(Light*);
	void AddHull(Hull*);
	void SetView(sf::View);
	void DebugRender(sf::RenderTexture* panel);
	void SetAmbienceColor(sf::Color);
	sf::Shader lightShader;
	sf::Shader lightToTextureShader;
	sf::Shader shadowShader;
private:
	sf::RenderTexture panelLightTempText;
	sf::Sprite panelLightTempSprite;
	sf::RenderTexture tempLightText;
	sf::Sprite tempLightSprite;
	void CalculatePanelBounds();
	sf::Vector2f panelLowerPoint;
	sf::Texture lightsTexture;
	sf::Sprite lightsSprite;
	void DrawLight(Light*);
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