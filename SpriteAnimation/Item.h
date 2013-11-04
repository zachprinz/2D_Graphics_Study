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
	bool GetOversized();
	void SetOversized(bool);
	std::string GetAnimation();
	void SetAnimation(std::string);
	void SetAttackSet(std::string);
	std::string GetAttackSet();
private:
	static void SetUpItem(int,Item*);
	std::string attackSet;
	bool oversized;
	int materialLevel;
	sf::Texture spriteTexture;
	sf::Texture containerTexture;
	std::string animation;
	int id;
	//LevelSet stats;
	int price;
};

#endif