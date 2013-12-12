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
	void Update(GamePanel*);
	void PickUp();
	void Interact();
	void SetUpBoundries();
	void OnClick();
private:
	Item item;
};

#endif