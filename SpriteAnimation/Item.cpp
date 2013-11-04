#include "Item.h"
#include "SFML/Graphics.hpp"
#include "ScriptManager.h"
#include "Drawn.h"
#include "pugixml\pugixml.hpp"

Item::Item(int id){
	this->id = id;
	SetUpItem(id,this);
	//itemLevels = LevelSet();
	//ScriptManager::CreateItem(id,this);
	//materialLevel = std::stoi(id.substr(2,id.length()));
};
void Item::SetUpItem(int id,Item* item){ //Weapon very definetely needs to be a childclass of Item. But I'll do that later...
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("xml/itemInfo.xml");
	pugi::xml_node atlas = doc.child("ArmourList");
	pugi::xml_node itemInfo;
	for(pugi::xml_node armour = atlas.first_child(); armour; armour = armour.next_sibling()){
		if(std::stoi(armour.attribute("id").value()) == id){
			itemInfo = armour;
			break;
		}
	}
	item->itemLevels = LevelSet(itemInfo.attribute("str").as_int(),itemInfo.attribute("end").as_int(),itemInfo.attribute("speed").as_int(),itemInfo.attribute("tech").as_int(),0,0,0,0);
	item->slot = itemInfo.attribute("slot").as_int();
	item->name = itemInfo.attribute("name").value();
	item->imageName = itemInfo.attribute("image").value();
	item->SetOversized(itemInfo.attribute("oversized").as_bool());
	item->SetAnimation(itemInfo.attribute("animation").value());
	item->SetAttackSet(itemInfo.attribute("attackSet").value());
};
void Item::SetUp(int slot){
	this->slot = slot;
};
Item::Item(){

}
int Item::GetId(){
	return id;
};
int Item::GetPrice(){
	return price;
};
int Item::GetSlot(){
	return slot;
};
bool Item::GetOversized(){
	return oversized;
};
void Item::SetOversized(bool oversized){
	this->oversized = oversized;
}
void Item::SetAttackSet(std::string attackSet){
	this->attackSet = attackSet;
};
std::string Item::GetAttackSet(){
	return attackSet;
}
std::string Item::GetName(){
	return name;
};
sf::Texture Item::GetSpriteTexture(){
	return spriteTexture;
};
sf::Texture Item::GetContainerTexture(){
	return containerTexture;
};
int Item::GetMaterialLevel(){
	return materialLevel;
};
void Item::SetAnimation(std::string animation){
	this->animation = animation;
}
std::string Item::GetAnimation(){
	return animation;
}