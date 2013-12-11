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
	SpritePanel(int,int);
	SpritePanel();
	static SpritePanel* instance;
	void AddElement(std::string,Drawn*);
	static sf::Texture* spritePanelBackground;
	void SpawnItem(int,int,int,Room*);
	tmx::MapLoader* ml;
	std::vector<tmx::MapLayer*> otherLayers;
	std::vector<tmx::MapLayer*> highLayers;
	void UpdateElements();
	void LoadMapCollisions();
	void LoadMapSprites();
	static Room* room;
	sf::View view;
	void MoveCamera(float,float);
	std::vector<std::string> combatants;
	void RemoveDynamicElement(std::string);
	bool CheckUpdate();
	void LoadMapAmbience();
	LightEngine* lightEngine;
	void AddLight(Light*);
	void AddHull(Hull*);
	sf::Texture mapTexture;
	sf::Sprite mapSprite;
private:
	void SetUp();
	std::vector<GroundItem*> spawnedItems;
};

#endif