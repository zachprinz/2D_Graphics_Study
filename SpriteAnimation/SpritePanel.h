#ifndef SPRITEPANEL_H
#define SPRITEPANEL_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "GamePanel.h"
#include "GroundItem.h"
#include <MapLoader.h>
#include "Room.h"
#include "LightObject.h"
#include "AmbienceObject.h"
#include "LightEngine.h"
#include "Thor\Particles.hpp"
#include "AmbienceEngine.h"

class SpritePanel : public GamePanel
{
public:
	static SpritePanel* instance;
	SpritePanel(int,int);
	SpritePanel();
	void AddElement(std::string,Drawn*);
	void SpawnItem(int,int,int,Room*);
	void UpdateElements();
	static Room* room;
	void MoveCamera(float,float);
	void RemoveDynamicElement(std::string);
	void AddLight(Light*);
	void AddHull(Hull*);
	void Zoom(float, float);
	void ReturnZoom();
	bool isZooming;
	float currentZoom;
	sf::Vector2f GetViewLowerBound();
	void MoveCamera();
	float cameraMoveSpeed;
	sf::Clock cameraMoveClock;
	void ShakeScreen(float, float);
	AmbienceEngine* ambienceEngine;
private:
	bool isCameraCaughtUp;
	void UpdateZoom();
	static sf::Texture* spritePanelBackground;
	tmx::MapLoader* ml;
	sf::View view;
	std::vector<tmx::MapLayer*> otherLayers;
	std::vector<tmx::MapLayer*> highLayers;
	std::vector<std::string> combatants;
	void SetUp();
	sf::Texture mapTexture;
	sf::Sprite mapSprite;
	void LoadMapAmbience();
	void LoadMapCollisions();
	void LoadMapSprites();
	std::vector<GroundItem*> spawnedItems;
	float zoomPerSecond;
	float zoomDirection;
	Clock zoomClock;
	float targetZoom;
	double FindNoise();
	bool InterpolateShake();
	sf::Vector2f targetPosition;
	Clock shakeClock;
	float shakeTime;
	float shakeAmplitude;
	void MoveCameraTo(sf::Vector2f,float speed);
	bool isShaking;
	std::vector<double> shakeOffsetsY;
	std::vector<double> shakeOffsetsX;
	bool shakeOdd;
	int shakeCount;
};
#endif