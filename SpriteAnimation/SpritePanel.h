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
#include "LTBL/Light/LightSystem.h"

class SpritePanel : public GamePanel
{
public:
	SpritePanel(int,int,sf::RenderWindow*);
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
	void SetHighObjectsVisible();
	void SetHighObjectsInvisible();
	void SetLowObjectsVisible();
	std::vector<std::string> combatants;
	void RemoveDynamicElement(std::string);
	bool CheckUpdate();
	void LoadMapAmbience();
	ltbl::LightSystem* lightSystem;
	static sf::RenderWindow* mainWindow;
	void AddLightSource(LightObject*);
	void AddLightHull(ltbl::ConvexHull*);
	void RemoveLightHull(ltbl::ConvexHull*);
	int panelHeight;
	sf::View lightView;
private:
	void SetUp();
	sf::Texture backgroundImage;
	sf::Sprite backgroundSprite2;
	std::vector<GroundItem*> spawnedItems;
};

#endif