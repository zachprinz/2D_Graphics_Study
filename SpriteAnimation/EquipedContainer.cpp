#include "EquipedContainer.h"
#include "SpritePanel.h"
#include <iostream>
#include "User.h"
#include "RClickMenu.h"

//EquipedContainer::EquipedContainer(int x,int y,std::string text,sf::Sprite* fgSprite) : Container(x,y,text,fgSprite){
//	AddRClickOption(RClickMenu::Options::Unequip);
//};
EquipedContainer::EquipedContainer(int x,int y,std::string text) : Container(x,y,text){
	AddRClickOption(RClickMenu::Options::Unequip);
};
void EquipedContainer::OnClick(){
	if(isFull)
		Remove();
};
void EquipedContainer::Remove(){
		User::player->GetInventory()->Add(GetContents());
		ClearContents();
};
void EquipedContainer::OnMenuSelection(std::string selection){
	if(selection == "Unequip")
		Remove();
};