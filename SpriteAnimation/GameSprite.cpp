#include "GameSprite.h"
#include "Room.h"
#include <iostream>
#include "SpritePanel.h"

int GameSprite::tagCount = 0;

GameSprite::GameSprite(int x, int y,std::string textureName) : RClickable(textureName){
	graphPositionA = sf::Vector2i(x,y);
	posB = sf::Vector2f(x*32,y*32);
	SetLocation(x * 32, y * 32);
	z = 0;
	tag = tagCount;
	tagCount++;
};
GameSprite::GameSprite(){

};
void GameSprite::AdjustZToUser(){

};
int GameSprite::GetZ(){
	return z;
};
void GameSprite::SetZ(int x){
	z = x;
}
int GameSprite::GetTag(){
	return tag;
}
void GameSprite::OnHover(){

};
void GameSprite::Interact(){
	std::cout << "Not Overriden" << std::endl;
}
void GameSprite::UpdateRoomTile(){
	SpritePanel::room->roomTiles[graphPositionA.y][graphPositionA.x].TryRemoveOcupant(tag);
	SpritePanel::room->roomTiles[((posB.y) + 31)/32][((posB.x) + 31)/32].TryRemoveOcupant(tag);
	graphPositionA.x = ((int)sprite.getPosition().x) / 32;
	graphPositionA.y = ((int)sprite.getPosition().y) / 32;
	posB.x = sprite.getPosition().x;
	posB.y = sprite.getPosition().y;
	SpritePanel::room->roomTiles[graphPositionA.y][graphPositionA.x].AddOcupant(tag);
	SpritePanel::room->roomTiles[(((int)sprite.getPosition().y) + 31)/32][(((int)sprite.getPosition().x) + 31)/32].AddOcupant(tag);
}
sf::Vector2i GameSprite::GetGraphPositionA(){
	return graphPositionA;
};
void GameSprite::SetGraphPositionA(sf::Vector2i a){
	graphPositionA = a;
};
void GameSprite::SetLocation(float x,float y){
	Drawn::SetLocation(x,y);
};
void GameSprite::RecieveAttack(int x){

};
RoomTile* GameSprite::GetRoomTile(){
	return &(SpritePanel::room->roomTiles[graphPositionA.y][graphPositionA.x]);
};
RoomTile* GameSprite::GetRoomTile(int x, int y){
	return &(SpritePanel::room->roomTiles[graphPositionA.y + y][graphPositionA.x + x]);
};
void GameSprite::OnClick(){

};