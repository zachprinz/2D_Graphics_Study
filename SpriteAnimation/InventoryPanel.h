#ifndef INVENTORYPANEL_H
#define INVENTORYPANEL_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "GamePanel.h"
#include "InventoryContainer.h"

class InventoryPanel : public GamePanel
{
public:
	InventoryPanel(int,int);
	InventoryPanel();
	static InventoryPanel* instance;
	void AddElement(std::string,Drawn*);
	InventoryContainer* GetOpenContainer();
	void Add(Item item);
	void Remove(Item item);
	void Remove(std::vector<Item> items);
	bool DoesContain(Item);
	bool DoesContain(std::vector<Item>);
	InventoryContainer* FindContainerOf(Item item);
	sf::Texture inventoryBackground;
private:
	void SetUp();

};

#endif