#include "EquipedPanel.h"
#include <iostream>
#include "Label.h"
#include "User.h"
#include "HUDPanel.h"
#include "ActionBar.h"

sf::Texture* EquipedPanel::equipedBackground;
EquipedPanel* EquipedPanel::instance;

EquipedPanel::EquipedPanel(int x,int y) : GamePanel(x,y,"Equipment"){
	SetUp();
	instance = this;
};
EquipedPanel::EquipedPanel(){

};
void EquipedPanel::AddElement(std::string,Drawn*){

};
EquipedContainer* EquipedPanel::GetSlotContainer(int slot){
	if(((EquipedContainer*)(dynamicElements[std::to_string(slot)]))->GetIsFull())
		((EquipedContainer*)(dynamicElements[std::to_string(slot)]))->Remove();
	return (EquipedContainer*)(dynamicElements[std::to_string(slot)]);
};
void EquipedPanel::Equip(Item item){
	//HUDPanel::instance->UpdateUserImage();
	GetSlotContainer(item.GetSlot())->AddItem(item);
	User::player->ChangeEquiped(&item);
	if(item.GetSlot() == 1){
		User::player->SetUpAttacks(item.GetAttackSet());
		ActionBar::instance->UpdateActionImages();
	}
};
void EquipedPanel::Remove(Item item){

};
void EquipedPanel::Remove(std::vector<Item> items){

};
bool EquipedPanel::DoesContain(Item item){
	for(MyPair x: dynamicElements){
		if(((EquipedContainer*)x.second)->GetIsFull() && !((EquipedContainer*)x.second)->Contains(item))
			return true;
	}
	return false;
};
bool EquipedPanel::DoesContain(std::vector<Item> items){
	for(int x = 0; x < items.size(); x++){
		if(!DoesContain(items[x]))
			return false;
	}
	return true;
};
EquipedContainer* EquipedPanel::FindContainerOf(Item item){
	return (EquipedContainer*)(dynamicElements[std::to_string(item.GetSlot())]);
};
void EquipedPanel::SetUp(){
	Drawn* background = new Drawn("equipedbackground.png");
	background->SetPosition(sf::Vector2f(0,35));
	staticElements.insert(MyPair("00", background));
	int slotPosX[] = {125,32,125,233,125};
	int slotPosY[] = {20,220,107,220,235};
	GamePanel::SetUp();
	std::cout << "Creating Equiped Slots...";
	for (int x = 0; x < 5; x++){
		EquipedContainer* element = new EquipedContainer(slotPosX[x],slotPosY[x],"containerbackground.png");
		AddDynamicElement(MyPair(std::to_string(x), element));
	}
	std::cout << " Done" << std::endl;

};
void EquipedPanel::UpdateStats(){

};