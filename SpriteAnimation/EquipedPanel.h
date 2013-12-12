#ifndef EQUIPEDPANEL_H
#define EQUIPEDPANEL_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "GamePanel.h"
#include "EquipedContainer.h"
#include "LevelSet.h"

class EquipedPanel : public GamePanel
{
public:
	static EquipedPanel* instance;
	EquipedPanel(int,int);
	EquipedPanel();
	void AddElement(std::string,Drawn*);
	EquipedContainer* GetSlotContainer(int);
	void Equip(Item item);
	void Remove(Item item);
	void Remove(std::vector<Item> items);
	bool DoesContain(Item);
	bool DoesContain(std::vector<Item>);
	EquipedContainer* FindContainerOf(Item item);
	static sf::Texture* equipedBackground;
	void UpdateStats();
	LevelSet equipedLevels;
private:
	void SetUp();
};

#endif