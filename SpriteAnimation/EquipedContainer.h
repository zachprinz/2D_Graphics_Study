#ifndef EQUIPEDCONTAINER_H
#define EQUIPEDCONTAINER_H

#include <vector>
#include "Container.h"
#include <SFML/Graphics.hpp>

class EquipedContainer : public Container
{
public:
	EquipedContainer(int,int,std::string,sf::Sprite*);
	EquipedContainer(int,int,std::string);
	void OnButtonEvent(std::string);
	void OnClick();
	void Remove();
};

#endif