#include "EquipedContainer.h"
#include "SpritePanel.h"
#include <iostream>
#include "User.h"
#include "RClickMenu.h"

EquipedContainer::EquipedContainer(int x,int y,std::string text) : Container(x,y,text){
	rightClickOptions.push_back("Unequip");
};
void EquipedContainer::OnClick(){
	if(isFull)
		Remove();
};
void EquipedContainer::Remove(){
		User::player->GetInventory()->Add(GetContents());
		User::player->RemoveEquipment(GetContents().GetSlot());
		ClearContents();
};
void EquipedContainer::OnButtonEvent(std::string selection){
	if(selection == "Unequip")
		Remove();
};