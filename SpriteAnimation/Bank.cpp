#include "Bank.h"
#include "BankPanel.h"

Bank::Bank(int x, int y, std::string textureName) : GameSprite(x,y,textureName){

};
void Bank::Update(sf::RenderTexture& window){
	UpdateRoomTile();
	window.draw(sprite);
	GameSprite::Update(window);
};
void Bank::Interact(){
	Open();
};
void Bank::Start(){

};
void Bank::Open(){
	BankPanel::instance->Open();
};