#include "EquipedPanel.h"
#include <iostream>
#include "SlicedSpriteCreator.h"
#include "Label.h"
#include "User.h"
#include "HUDPanel.h"
#include "ActionBar.h"

sf::Texture* EquipedPanel::equipedBackground = new sf::Texture();
EquipedPanel* EquipedPanel::instance = new EquipedPanel();

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
	doUpdate = true;
	User::player->ChangeEquiped(&item);
	if(item.GetSlot() == 1){
		User::player->SetUpAttacks(item.GetAttackSet());
		ActionBar::instance->UpdateActionImages();
	}
	//HUDPanel::instance->UpdateUserImage();
	GetSlotContainer(item.GetSlot())->AddItem(item);
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
	int slotPosX[] = {125,32,125,233,125};
	int slotPosY[] = {20,220,107,220,235};
	GamePanel::SetUp();
	std::cout << "Creating Equiped Slots...";
	for (int x = 0; x < 5; x++){
		EquipedContainer* element = new EquipedContainer(slotPosX[x],slotPosY[x],"containerbackground.png");
		dynamicElements.insert(MyPair(std::to_string(x), element));
		//std::cout << std::to_string(x) << std::endl;
	}
	std::cout << " Done" << std::endl;
	Drawn* background = new Drawn("equipedbackground.png");
	staticElements.insert(MyPair("userImage", background));
};
void EquipedPanel::UpdateStats(){

};
bool EquipedPanel::CheckUpdate(){
	//if(doUpdate == true || GamePanel::currentMousePanel == this){
	//	doUpdate = false;
		return true;
	//}
	//	return false;
};