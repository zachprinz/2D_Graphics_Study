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
private:
	static sf::Texture* spritePanelBackground;
	tmx::MapLoader* ml;
	sf::View view;
	std::vector<tmx::MapLayer*> otherLayers;
	std::vector<tmx::MapLayer*> highLayers;
	std::vector<std::string> combatants;
	void SetUp();
	LightEngine* lightEngine;
	sf::Texture mapTexture;
	sf::Sprite mapSprite;
	void LoadMapAmbience();
	void LoadMapCollisions();
	void LoadMapSprites();
	std::vector<GroundItem*> spawnedItems;
};

#endif