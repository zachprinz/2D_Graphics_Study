#include "Attack.h"
#include <iostream>
#include "Drawn.h"

Attack::Attack(std::string nameA,float damageMod,std::vector<sf::Vector2i> offsets, float cooldown, int animY, int frames){
	name = nameA;
	damageModifier = damageMod;
	numOfFrames = frames;
	effectTileOffsets = offsets;
	animationY = animY;
	cooldownTime = sf::seconds(cooldown);
	cooldownClock = sf::Clock();
	hudTexture = Drawn::GetTextureFromAtlas("attacktextures/" + name + ".png");
	hudSprite.setTexture(Drawn::gameTexture);
	hudSprite.setTextureRect(hudTexture);
	percentCooledDown = 1;
	isCooledDown = true;
};
Attack::Attack(){

};
std::vector<sf::Vector2i> Attack::Use(sf::Vector2i userPos,sf::Vector2i userMovement){
	std::vector<sf::Vector2i> tempTiles;
	for(int x = 0; x < effectTileOffsets.size();x++){
		switch(effectTileOffsets[x].x){
		case(Forward):
			tempTiles.push_back(GetForward(userPos,userMovement,effectTileOffsets[x].y));
			break;
		case(Backward):
			tempTiles.push_back(GetBackward(userPos,userMovement,effectTileOffsets[x].y));
			break;
		case(Left):
			tempTiles.push_back(GetLeft(userPos,userMovement,effectTileOffsets[x].y));
			break;
		case(Right):
			tempTiles.push_back(GetRight(userPos,userMovement,effectTileOffsets[x].y));
			break;
		}
	}
	std::cout << "Attack " + name + " Launched" << std::endl;
	isCooledDown = false;
	cooldownClock.restart();
	return tempTiles;
};
void Attack::Update(){
	if(!isCooledDown && cooldownClock.getElapsedTime().asSeconds() > cooldownTime.asSeconds()){
		isCooledDown = true;
		percentCooledDown = 1;
	}
	else
		if(!isCooledDown)
			percentCooledDown = cooldownClock.getElapsedTime().asSeconds() / cooldownTime.asSeconds();
};
void Attack::Update(sf::RenderTexture& panel){

};
sf::Vector2i Attack::GetForward(sf::Vector2i position,sf::Vector2i movement,int mult){
	return sf::Vector2i((movement.x * mult)+ position.x, (movement.y * mult) + position.y);
};
sf::Vector2i Attack::GetBackward(sf::Vector2i position,sf::Vector2i movement, int mult){
	return sf::Vector2i(((movement.x * -1) * mult) + position.x,((movement.y * -1) * mult) + position.y);
};
sf::Vector2i Attack::GetLeft(sf::Vector2i position,sf::Vector2i movement, int mult){
	return sf::Vector2i(((abs(abs(movement.x) - 1) * (movement.x - movement.y)) * mult) + position.x,((abs(abs(movement.y) - 1) * (movement.x - movement.y)) * mult) + position.y);
};
sf::Vector2i Attack::GetRight(sf::Vector2i position,sf::Vector2i movement, int mult){
	return sf::Vector2i(((-1 * (abs(abs(movement.x) - 1) * (movement.x - movement.y))) * mult) + position.x,((-1 * (abs(abs(movement.y) - 1) * (movement.x - movement.y))) * mult) + position.y);
};
bool Attack::GetIsCooledDown(){
	return isCooledDown;
};