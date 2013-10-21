#ifndef INVENTORYCONTAINER_H
#define INVENTORYCONTAINER_H

#include <vector>
#include "Container.h"
#include <SFML/Graphics.hpp>

class InventoryContainer : public Container
{
public:
	InventoryContainer(int,int,std::string,sf::Sprite*);
	InventoryContainer(int,int,std::string);
	void OnMenuSelection(std::string);
	void OnClick();
	void Drop();
	void Barter();
	void Equip();
	void Deposit();
private:

};

#endif