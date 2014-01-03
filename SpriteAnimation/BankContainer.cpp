#include "BankContainer.h"
#include "SpritePanel.h"
#include <iostream>
#include "User.h"
#include "RClickMenu.h"

BankContainer::BankContainer(int x,int y,std::string text) : Container(x,y,text){
	rightClickOptions.push_back("Withdraw");
	rightClickOptions.push_back("Equip");
};
void BankContainer::OnClick(){
	if(isFull)
		Withdraw();
};
void BankContainer::Equip(){
	User::player->GetEquiped()->Equip(GetContents());
	ClearContents();
};
void BankContainer::Withdraw(){
	User::player->GetInventory()->Add(contents);
	ClearContents();
}
void BankContainer::OnButtonEvent(std::string selection){
	if(selection == "Equip")
		Equip();
	else if(selection == "Withdraw")
		Withdraw();
};