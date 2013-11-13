#include "InventoryPanel.h"
#include <iostream>
#include "SlicedSpriteCreator.h"
#include "Label.h"

InventoryPanel* InventoryPanel::instance = new InventoryPanel();

InventoryPanel::InventoryPanel(int x,int y) : GamePanel(x,y,"Inventory"){
	SetUp();
	instance = this;
};
InventoryPanel::InventoryPanel(){

};
void InventoryPanel::AddElement(std::string,Drawn*){

};
InventoryContainer* InventoryPanel::GetOpenContainer(){
	for(int x = 0; x < 24; x++){
		if(!((InventoryContainer*)(dynamicElements[std::to_string(x)]))->GetIsFull())
			return (InventoryContainer*)(dynamicElements[std::to_string(x)]);
	}
};
void InventoryPanel::Add(Item item){
	doUpdate = true;
	GetOpenContainer()->AddItem(item);
};
void InventoryPanel::Remove(Item item){

};
void InventoryPanel::Remove(std::vector<Item> items){

};
bool InventoryPanel::DoesContain(Item item){
	for(MyPair x: dynamicElements){
		if(((InventoryContainer*)x.second)->GetIsFull() && !((InventoryContainer*)x.second)->Contains(item))
			return true;
	}
	return false;
};
bool InventoryPanel::DoesContain(std::vector<Item> items){
	for(int x = 0; x < items.size(); x++){
		if(!DoesContain(items[x]))
			return false;
	}
	return true;
};
InventoryContainer* InventoryPanel::FindContainerOf(Item item){
	for(int x = 0; x < 24; x++){
		if(((InventoryContainer*)(dynamicElements[std::to_string(x)]))->GetIsFull() && !((InventoryContainer*)(dynamicElements[std::to_string(x)]))->Contains(item))
			return ((InventoryContainer*)(dynamicElements[std::to_string(x)]));
	}
};
void InventoryPanel::SetUp(){
	GamePanel::SetUp();
	std::cout << "Creating Inventory Slots...";
	for (int x = 0; x < 6; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			InventoryContainer* element = new InventoryContainer((y*80) + 8,(x*80) + 8,"containerbackground.png");
			dynamicElements.insert(MyPair(std::to_string((x*4) + y), element));
			//std::cout << std::to_string((x*4) + y) << std::endl;
		}
	}
	std::cout << " Done" << std::endl;
};
bool InventoryPanel::CheckUpdate(){
	if(doUpdate || GamePanel::currentMousePanel == this){
		doUpdate = false;
		return true;
	}
	else
		return false;
};