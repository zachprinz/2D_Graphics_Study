#ifndef LIGHTENGINE_H
#define LIGHTENGINE_H

#include <vector>
#include "QuadTree.h"

class LightEngine{
public:
	LightEngine(AABB bounds,sf::View panelView, sf::Color ambientColor);
	void UpdateLights();
	void DrawLights(sf::RenderTexture*);
	void DrawShadows(sf::RenderTexture*);
	void AddLight(Light*);
	void AddHull(Hull*);
	void SetView(sf::View);
	void DebugRender(sf::RenderTexture* panel);
	void SetAmbienceColor(sf::Color);
	sf::Shader lightToTextureShader;
	sf::Shader shadowShader;
	sf::Shader whiteShader;
	sf::Shader subtractShader;
	void DrawHigh(sf::RenderTexture* panel);
private:
	sf::Sprite predoneLight;
	sf::Texture predoneLightTexture;

	sf::RenderTexture tempLightText;
	sf::Sprite tempLightSprite;

	sf::RenderTexture tempShadowText;
	sf::Sprite tempShadowSprite;

	void CalculatePanelBounds();
	sf::Vector2f panelLowerPoint;

	sf::Texture lightsTexture;
	sf::Sprite lightsSprite;

	sf::Texture shadowsTexture;
	sf::Sprite shadowsSprite;

	void DrawLight(Light*);
	sf::View panelView;
	AABB viewBounds;
	std::vector<Hull*> hulls;
	std::vector<Hull*> hullsOnScreen;
	std::vector<Light*> lights;
	std::vector<Light*> lightsOnScreen;
	sf::RenderTexture lightTexture;
	sf::RenderTexture shadowTexture;
	sf::RenderTexture* spritePanelTexture;
	QuadTree* lightTree;
	QuadTree* hullTree;
	sf::RenderTexture finalTexture;
	sf::Color ambienceColor;
};

#endif