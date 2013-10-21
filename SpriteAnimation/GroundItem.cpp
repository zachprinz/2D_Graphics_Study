#include "GroundItem.h"
#include <iostream>
#include "User.h"
#include "SpritePanel.h"

GroundItem::GroundItem(int x, int y, Item myItem) : GameSprite(x,y,"itemsprites/" + myItem.GetId() + ".png"){
	item = myItem;
	SetZ(1);
	isVisible = true;
};
Item GroundItem::GetItem(){
	return item;
};
void GroundItem::Update(sf::RenderTexture& window){
		if(isVisible){
			UpdateRoomTile();
			window.draw(sprite);
		}
};
void GroundItem::PickUp(){
	User::player->GetInventory()->Add(item);
	GetRoomTile()->TryRemoveOcupant(GetTag());
	SpritePanel::room->RemoveOcupant(GetTag());
	SpritePanel::instance->RemoveDynamicElement(std::to_string(GetTag()));
	isVisible = false;
};
void GroundItem::Interact(){
	std::cout << "Interacting with Item" << std::endl;
	PickUp();
}