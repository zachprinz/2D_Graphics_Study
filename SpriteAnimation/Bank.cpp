#include "Bank.h"
#include "BankPanel.h"

Bank::Bank(int x, int y, std::string textureName) : GameSprite(x,y,textureName){

};
void Bank::Update(sf::RenderTexture& window){
	UpdateRoomTile();
	GameSprite::Update(window);
};
void Bank::Update(GamePanel* panel){
	UpdateRoomTile();
	GameSprite::Update(panel);
};
void Bank::Interact(){
	Open();
};
void Bank::Start(){

};
void Bank::Open(){
	BankPanel::instance->Open();
};