#ifndef GROUNDITEM_H
#define GROUNDITEM_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Item.h"
#include "GameSprite.h"

class GroundItem : public GameSprite
{
public:
	GroundItem(int,int,Item myItem);
	Item GetItem();
	void Update(sf::RenderTexture&);
	void PickUp();
	void Interact();
private:
	Item item;
};

#endif