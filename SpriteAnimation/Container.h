#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>
#include "GuiElement.h"
#include <SFML/Graphics.hpp>
#include "Item.h"

class Container : public GuiElement
{
public:
	Container(int,int,std::string);
	void SetUp();
	void AddItem(Item item);
	Item ClearContents();
	Item GetContents();
	virtual void OnClick();
	void OnHover(bool);
	void Update(GamePanel*);
	bool GetIsFull();
	bool Contains(Item item);
	virtual void OnButtonEvent(std::string);
protected:
	bool isFull;
	Item contents;
};

#endif