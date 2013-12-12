#include <SFML/Graphics.hpp>
#include "User.h"
#include "Enemy.h"
#include <iostream>
#include "SpritePanel.h"
#include <iterator>
#include <vector>
#include "Attack.h"
#include "GamePanel.h"
#include "StatsPanel.h"

Enemy::Enemy(int x, int y, std::string textureName,std::string name) : Combatant(x,y,name,textureName){
	LoadFromXML();
	animationSheets.push_back(GetTextureFromAtlas(textureName));
	SetUpAttacks();
	sprite.setTextureRect(sf::IntRect(0,0,64,64));
	currentAnimation = animations["Walk"];
	currentAnimationDir = Animation::Down;
	SetAnimation(animations["Walk"],Animation::Down);
	currentPatrolTargetPoint = 0;
	currentMode = Patrol;
	UpdateAnimation();
	UpdateBoundries();
	SpritePanel::instance->AddHull(actorHull);
};
void Enemy::Update(GamePanel* panel){
	UpdateEntity();
	Combatant::Update(panel);
	UpdateEffectedTiles(SpritePanel::instance);
};
void Enemy::UpdateEntity(){
	if(currentDirection == None){
		if(currentAction != NoAction)
				LaunchAction(currentAction);
		else{
			switch(currentMode){
				case(Patrol):
					if(patrolPoints[currentPatrolTargetPoint].x == graphPositionA.x && patrolPoints[currentPatrolTargetPoint].y == graphPositionA.y){
						if(currentPatrolTargetPoint < patrolPoints.size() - 1)
							currentPatrolTargetPoint++;
						else
							currentPatrolTargetPoint = 0;
					}
					MoveTowardPoint(SpritePanel::room->GetNextTileTo(graphPositionA,patrolPoints[currentPatrolTargetPoint]));
					break;
				case(Pursue):
					if(abs(User::player->GetGraphPositionA().x - graphPositionA.x) + abs(User::player->GetGraphPositionA().y - graphPositionA.y) < 2){
						MoveTowardPoint(User::player->GetGraphPositionA());
						currentMode = AttackMode;
					}
					else
						MoveTowardPoint(SpritePanel::room->GetNextTileTo(graphPositionA,User::player->GetTailPoint()));
					break;
				case(AttackMode):
					if(abs(User::player->GetGraphPositionA().x - graphPositionA.x) + abs(User::player->GetGraphPositionA().y - graphPositionA.y) > 1){
						currentMode = Pursue;
					}
					else
						TryLaunchAttack("Simple Slash");
					break;
			}
		}
	}
};
void Enemy::AddPatrolPoint(sf::Vector2i a){
	patrolPoints.push_back(a);
};
void Enemy::MoveTowardPoint(sf::Vector2i target){
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
void Enemy::Interact(){
		std::cout << "Interacting with Enemy" << std::endl;
		currentMode = Pursue;
		inCombat = true;
		User::player->inCombat = true;
};
void Enemy::OnClick(){
	StatsPanel::instance->SetCombatant(this);
	//Interact();
}
void Enemy::SetUpAttacks(){
	attacks.clear();
	currentAttacks.clear();
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("xml/actionInfo.xml");
	pugi::xml_node atlas = doc.child("Actions");
	pugi::xml_node attackSet;
	for(pugi::xml_node tool = atlas.first_child(); tool; tool = tool.next_sibling()){
		if(((std::string)(tool.first_attribute().as_string()))==("default")){
			for(pugi::xml_node tool2 = tool.first_child(); tool2; tool2 = tool2.next_sibling()){
				//std::cout << "Setting up a new attack!" << std::endl;
				std::vector<sf::Vector2i> atkOffset;
				for(pugi::xml_node effectedTile = tool2.first_child(); effectedTile; effectedTile = effectedTile.next_sibling()){
					atkOffset.push_back(sf::Vector2i(effectedTile.attribute("direction").as_int(),effectedTile.attribute("distance").as_int()));
				}
				AddAttack(new Attack(tool2.attribute("name").value(),tool2.attribute("damageMult").as_double(),atkOffset,tool2.attribute("cooldown").as_double(),0,0));
				currentAttacks.push_back(tool2.attribute("name").value());
			}
			break;
		}
	}
};
void Enemy::OnActionComplete(Actions action){
	switch(action){
	case(Attacking):{

					}
					break;
	}
	currentDirection = None;
	currentAction = NoAction;
	SetAnimation(animations["Walk"],currentAnimationDir);
};
void Enemy::LaunchAction(Actions action){
	currentDirection = Action;
	switch(action){
	case(Attacking):{
		LaunchAttack(nextAttack);
		SetAnimation(animations["Walk"],currentAnimationDir);
					}
					break;

	}
};
void Enemy::AddDrop(int item,float chance){
	//std::cout << "Drop Added: " + item << std::endl;
	drops.push_back(item);
	dropChances.push_back(chance);
};
void Enemy::SetName(std::string name){
	this->name = name;
};
void Enemy::Drop(){
	std::cout << "Dropping" << std::endl;
	for(int x = 0; x < drops.size(); x++){
		float temp = ((float)rand()/(float)RAND_MAX);
		std::cout << "Drop Result: " + std::to_string(temp) << "Drop Percent: " + std::to_string(dropChances[x]) << std::endl;
		if(temp <= dropChances[x]){
			SpritePanel::instance->SpawnItem(drops[x],GetGraphPositionA().x,GetGraphPositionA().y,SpritePanel::instance->room);
		}
	}
};
void Enemy::LoadFromXML(){
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("xml/enemyInfo.xml");
	pugi::xml_node atlas = doc.child("enemyList");
	pugi::xml_node enemyInfo;
	for(pugi::xml_node enemy = atlas.first_child(); enemy; enemy = enemy.next_sibling()){
		if(enemy.attribute("name").as_string() == name){
			enemyInfo = enemy;
			break;
		}
	}
	for(pugi::xml_node drop = enemyInfo.first_child(); drop; drop = drop.next_sibling()){
		AddDrop(drop.attribute("id").as_int(),drop.attribute("chance").as_float());
	}
	//item->itemLevels = LevelSet(itemInfo.attribute("str").as_int(),itemInfo.attribute("end").as_int(),itemInfo.attribute("speed").as_int(),itemInfo.attribute("tech").as_int(),0,0,0,0);
};