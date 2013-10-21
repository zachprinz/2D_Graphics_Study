#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "LevelSet.h"

class Item
{
public:
	Item(std::string);
	Item();
	std::string GetId();
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
private:
	int materialLevel;
	sf::Texture spriteTexture;
	sf::Texture containerTexture;
	std::string id;
	//LevelSet stats;
	int price;
};

#endif