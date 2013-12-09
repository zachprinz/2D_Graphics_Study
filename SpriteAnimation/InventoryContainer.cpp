#include "InventoryContainer.h"
#include "SpritePanel.h"
#include <iostream>
#include "User.h"
#include "RClickMenu.h"
#include "BankPanel.h"
#include "InventoryPanel.h"

InventoryContainer::InventoryContainer(int x,int y,std::string text) : Container(x,y,text){
	AddRClickOption(RClickMenu::Options::Drop);
	AddRClickOption(RClickMenu::Options::Equip);
};
void InventoryContainer::OnClick(){
	if(isFull)
		Equip();
};
void InventoryContainer::Drop(){
	SpritePanel::instance->SpawnItem(contents.GetId(),User::player->GetGraphPositionA().x,User::player->GetGraphPositionA().y,SpritePanel::room);
	ClearContents();
};
void InventoryContainer::Barter(){

};
void InventoryContainer::Equip(){
	User::player->GetEquiped()->Equip(GetContents());
	ClearContents();
};
void InventoryContainer::Deposit(){
	BankPanel::instance->Add(contents);
	ClearContents();
};
void InventoryContainer::OnMenuSelection(std::string selection){
	if(selection == "Equip")
		Equip();
	else if(selection == "Drop")
		Drop();
	else if(selection == "Deposit")
		Deposit();
	else if(selection == "Barter")
		Barter();
};