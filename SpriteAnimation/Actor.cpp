#include "Actor.h"
#include <iostream>
#include "SpritePanel.h"
#include "User.h"

sf::Clock Actor::elapsedTimeClock;
sf::Time Actor::elapsedTime;


Actor::Actor(int x, int y,std::string name, std::string textureName) : GameSprite(x,y,textureName){
	currentDirection = None;
	currentAnimationPos.x = 0;
	animationSprite.setTexture(Drawn::gameTexture);
	showHit = false;
	isVisible = true;
	this->name = name;
	currentAnimationPos.y = Animation::Down;
	playAnimation = true;
	movement = sf::Vector2i(0,0);
	currentAction = NoAction;
	SetZ(2);
};
Actor::Actor(){

};
void Actor::MoveOnGrid(int x,int y){
	Drawn::MoveOnGrid(x,y);
};
void Actor::Move(float x,float y){
	Drawn::Move(x,y);
};
void Actor::SetCurrentDirection(Direction a){
	currentDirection = a;
};
Actor::Direction Actor::GetCurrentDirection(){
	return currentDirection;
};
sf::Vector2i Actor::GetMovement(){
	return movement;
};
void Actor::SetMovement(sf::Vector2i a){
	movement = a;
};
bool Actor::CheckTile(int x, int y){
	if(	y >= 0
		&& x >= 0
		&& y < SpritePanel::room->roomTiles.size() 
		&& x < SpritePanel::room->roomTiles[y].size()
		&& !SpritePanel::room->roomTiles[y][x].GetOcupied())
		return true;
	else
		return false;
};
bool Actor::SetRight(){
	if(currentDirection == None){
		SetAnimation(animations["Walk"],Animation::Right);
		movement.x = 1;
		movement.y = 0;
		if(CheckTile(graphPositionA.x + 1,graphPositionA.y)){
			currentDirection = R;
			return true;
		}
		else
			return false;
	}
};
bool Actor::SetLeft(){
	if(currentDirection == None){
		SetAnimation(animations["Walk"],Animation::Left);
		movement.x = -1;
		movement.y = 0;
		if(CheckTile(graphPositionA.x - 1,graphPositionA.y)){
			currentDirection = L;
			return true;
		}
		else
			return false;
	}
};
bool Actor::SetUp(){
	if(currentDirection == None){
		SetAnimation(animations["Walk"],Animation::Up);
		movement.x = 0;
		movement.y = -1;
		if(CheckTile(graphPositionA.x,graphPositionA.y - 1)){
			currentDirection = U;
			return true;
		}
		else
			return false;
	}
};
bool Actor::SetDown(){
	if(currentDirection == None){
		SetAnimation(animations["Walk"],Animation::Down);
		movement.x = 0;
		movement.y = 1;
		if(CheckTile(graphPositionA.x,graphPositionA.y + 1)){
			currentDirection = D;
			return true;
		}
		else
			return false;

	}
};
void Actor::Update(sf::RenderTexture& panel){
	for(int b = 0; b < 2; b++){
		if(currentDirection == Finishing){
			int dir = 0;
			if(movement.x == -1 || movement.y == -1)
				dir = 0;
			if(movement.x == 1 || movement.y == 1)
				dir = 1;
			if(fmod(sprite.getPosition().x, 32) != 0 && fmod(sprite.getPosition().x,32) != 32){
				if(abs(movement.x * elapsedTime.asSeconds() * 50) > (abs((32*dir) - fmod(sprite.getPosition().x, 32))) ){
					Move(movement.x * abs((32*dir) - fmod(sprite.getPosition().x, 32)),0);
					currentDirection = None;
					break;
				}
				else
					Move((movement.x * elapsedTime.asSeconds() * 50),0);
			}
			else if(fmod(sprite.getPosition().y,32) != 0 && fmod(sprite.getPosition().y,32) != 32){
				if(abs(movement.y * elapsedTime.asSeconds() * 50) > (abs((32*dir) - fmod(sprite.getPosition().y, 32))) ){
					Move(0,movement.y * abs((32*dir) - fmod(sprite.getPosition().y, 32)));
					currentDirection = None;
					break;
				}
				else
					Move(0, (movement.y * elapsedTime.asSeconds() * 50));
			}
		}
			else if(currentDirection == U || currentDirection == D){
					Move(0, movement.y * elapsedTime.asSeconds() * 50);
					currentDirection = Finishing;
			}
			else if(currentDirection == L || currentDirection == R){
					Move(movement.x * elapsedTime.asSeconds() * 50,0);
					currentDirection = Finishing;
			}
	}
	if(isVisible){
		UpdateRoomTile();
		UpdateAnimation();
	}
}
void Actor::OnClick(){

};
void Actor::OnActionComplete(Actions){

};
void Actor::LaunchAction(Actions){

};
sf::Vector2i Actor::GetForward(){
	return movement;
};
std::string Actor::GetName(){
	return name;
};
sf::Vector2i Actor::GetBackward(){
	return sf::Vector2i(movement.x * -1,movement.y * -1);
};
sf::Vector2i Actor::GetLeft(){
	return sf::Vector2i(abs(abs(movement.x) - 1) * (movement.x - movement.y),abs(abs(movement.y) - 1) * (movement.x - movement.y));
};
sf::Vector2i Actor::GetRight(){
	return sf::Vector2i(-1 * (abs(abs(movement.x) - 1) * (movement.x - movement.y)),-1 * (abs(abs(movement.y) - 1) * (movement.x - movement.y)));
};
bool Actor::UpdateAnimation(){
	if(animationClock.getElapsedTime() > currentAnimation->timePerFrame){
		sprite.setColor(sf::Color(255,255,255,255));
		animationClock.restart();
		sprite.setTextureRect(sf::IntRect(currentAnimationPos.x * currentAnimation->width,currentAnimationPos.y * currentAnimation->width,currentAnimation->width,currentAnimation->width));
		if(showHit){
			sprite.setColor(sf::Color(255,0,0,255));
			showHit = false;
		}
		if(currentDirection != None || currentDirection == Action)
				currentAnimationPos.x++;
		if(currentAnimationPos.x == currentAnimation->numFrames){
			if(this == User::player && User::player->currentAnimation->name == "Walk")//TODO Terrible Temp Sollution.
				currentAnimationPos.x = 1;
			else
				currentAnimationPos.x = 0;
			if(currentDirection == Action)
				OnActionComplete(currentAction);
		}
		return true;
	}
	else
		return false;
};
//sf::Texture Actor::GetSpriteTexture(){

//};
void Actor::UpdateCurrentActorTexture(){ // Try just moving around 6 sprites, might be more adventagious than this.
	animationPallate.clear(sf::Color(0,0,0,0));
	for(int x = 0; x < animationSheets.size(); x++){
		animationSprite.setTextureRect(animationSheets[x]);
		animationPallate.draw(animationSprite);
	}
	animationPallate.display();
	texture = animationPallate.getTexture();
	texture.setSmooth(true);
	sprite.setTexture(texture);
};
void Actor::SetAnimation(Animation* anim, Animation::AnimDir dir){
	if(currentAnimation->name != anim->name || currentAnimationDir != dir){
		currentAnimation = anim;
		currentAnimationDir = dir;
		currentAnimationPos.x = 0;
		currentAnimationPos.y = currentAnimation->GetY(dir);
	}
}
/*
void Actor::Play(Animation*, Animation::AnimDir dir){

};
void Actor::Loop(Animation* anim, Animation::AnimDir dir){
	currentAnimation = anim;
	currentAnimationPos.x = 0;
	currentAnimationPos.y = currentAnimation->GetY(dir);
};
void Actor::StopAnimation(){
	playAnimation = false;
};
*/
sf::Texture Actor::GetActorTexture(){
	sf::RenderTexture tempRendText;
	tempRendText.create(64,64);
	tempRendText.clear(sf::Color(0,0,0,0));
	sf::Vector2f tempPos = sprite.getPosition();
	sprite.setPosition(0,0);
	for(int x = 0; x < animationSheets.size(); x++){
		sprite.setTextureRect(sf::IntRect(animationSheets[x].left,animationSheets[x].top + (animations["Walk"]->GetY(Animation::AnimDir::Down) * 64),64,64));
		tempRendText.draw(sprite);
	}
	sprite.setPosition(tempPos);
	tempRendText.display();
	return tempRendText.getTexture();
};
void Actor::AddAnimation(Animation* anim){
	animations.insert(AnimationPair(anim->name,anim));
};
sf::Texture Actor::GetTexture(){
	return texture;
};
void Actor::OnHover(){

};