#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "LevelSet.h"

class Item
{
public:
	Item(int);
	Item();
	int GetId();
	int GetPrice();
	int GetSlot();
	std::string GetName();
	void SetUp(int);
	sf::Texture GetContainerTexture();
	sf::Texture GetSpriteTexture();
	int slot;
	std::string name;
	LevelSet itemLevels;
	int GetMaterialLevel();
	std::string imageName;
private:
	static void SetUpItem(int,Item*);
	int materialLevel;
	sf::Texture spriteTexture;
	sf::Texture containerTexture;
	int id;
	//LevelSet stats;
	int price;
};

#endif