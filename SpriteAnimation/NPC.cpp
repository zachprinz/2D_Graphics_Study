#include <SFML/Graphics.hpp>
#include "User.h"
#include "NPC.h"
#include <iostream>
#include "SpritePanel.h"
#include <iterator>
#include <vector>
#include "TextPanel.h"
#include "GamePanel.h"

NPC::NPC(int x, int y, std::string textureName,std::string name) : Actor(x,y,"NPC",textureName){
	SetUpAnimations();
	this->name = name;
	animationSheets.push_back(GetTextureFromAtlas(textureName));
	currentAnimation = animations["Walk"];
	currentAnimationDir = Animation::Left;
	SetAnimation(animations["Walk"],Animation::Left);
	sprite.setTextureRect(sf::IntRect(0,0,64,64));
	UpdateRoomTile();
	UpdateAnimation();
	UpdateBoundries();
	SpritePanel::instance->AddHull(actorHull);
};
void NPC::Update(GamePanel* panel){
	UpdateEntity();
	Actor::Update(panel);
};
void NPC::UpdateEntity(){

};
void NPC::Interact(){
	MoveTowardPoint(User::player->GetGraphPositionA());
	TextPanel::instance->DisplayText(GetResponce());
	User::player->UpdateQuest(name);
};
void NPC::OnClick(){

};
void NPC::SetUpAnimations(){
	AddAnimation(new Animation("Walk",0.075,3,32,3,0,1,2,0));
};
void NPC::MoveTowardPoint(sf::Vector2i target){
	int targetAddress = SpritePanel::room->GetGridAddress(target);
	int currentAddress = SpritePanel::room->GetGridAddress(graphPositionA);
	if(targetAddress > currentAddress){
		if(targetAddress > (currentAddress + 1))
			SetDown();
		else if(targetAddress == (currentAddress + 1))
			SetRight();
	}
	else {
		if(targetAddress < (currentAddress - 1))
			SetUp();
		else if(targetAddress == (currentAddress - 1))
			SetLeft();
	}
};
std::string NPC::GetResponce(){
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("xml/npcInfo.xml");
	pugi::xml_node NPCList = doc.child("NPCList");
	for(pugi::xml_node NPC = NPCList.first_child(); NPC; NPC = NPC.next_sibling()){
		if(NPC.attribute("name").value() == name){
			std::cout << "Found the correct NPC." << std::endl;
			for(pugi::xml_node responce = NPC.first_child(); responce; responce = responce.next_sibling()){
				for(pugi::xml_node requirement = responce.first_child(); requirement; requirement = requirement.next_sibling()){
					if(User::player->GetQuestData(requirement.attribute("questName").value(),requirement.attribute("questAtrib").value()) == requirement.attribute("valueValue").value()){
						return responce.attribute("string").value();
					}
					else
						break;
				}
			}
		}
	}
	return "None found";
};