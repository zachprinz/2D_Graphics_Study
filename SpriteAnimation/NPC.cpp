#include <SFML/Graphics.hpp>
#include "User.h"
#include "NPC.h"
#include <iostream>
#include "SpritePanel.h"
#include <iterator>
#include <vector>
#include "ScriptManager.h"

NPC::NPC(int x, int y, std::string textureName,std::string name) : Actor(x,y,"NPC",textureName){
	//ScriptManager::CreateEnemy(name,this);
	SetUpAnimations();
	animationSheets.push_back(GetTextureFromAtlas(textureName));
	animationPallate.create(64,64);
	currentAnimation = animations["Walk"];
	currentAnimationDir = Animation::Down;
	SetAnimation(animations["Walk"],Animation::Down);
	sprite.setTextureRect(sf::IntRect(0,0,32,32));
	animationPallate.create(96,128);
	UpdateCurrentActorTexture();
};
void NPC::Update(sf::RenderTexture& window){
	Actor::Update(window);
	window.draw(sprite);
};
void NPC::Interact(){

};
void NPC::OnClick(){

};
void NPC::SetUpAnimations(){
	AddAnimation(new Animation("Walk",0.075,3,32,3,0,1,2));
};
