#include "Item.h"
#include "SFML/Graphics.hpp"
#include "ScriptManager.h"
#include "Drawn.h"

Item::Item(std::string ida){
	id = ida;
	itemLevels = LevelSet();
	ScriptManager::CreateItem(id,this);
	materialLevel = std::stoi(id.substr(2,id.length()));
};
void Item::SetUp(int slot){
	this->slot = slot;
};
Item::Item(){

}
std::string Item::GetId(){
	return id;
};
int Item::GetPrice(){
	return price;
};
int Item::GetSlot(){
	return slot;
};
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