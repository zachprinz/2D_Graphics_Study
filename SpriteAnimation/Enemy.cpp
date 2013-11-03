#include <SFML/Graphics.hpp>
#include "User.h"
#include "Enemy.h"
#include <iostream>
#include "SpritePanel.h"
#include <iterator>
#include <vector>
#include "Attack.h"
#include "ScriptManager.h"

Enemy::Enemy(int x, int y, std::string textureName,std::string name) : Combatant(x,y,name,textureName){
	ScriptManager::CreateEnemy(name,this);
	SetUpAttacks();
	SetUpAnimations();
	animationSheets.push_back(GetTextureFromAtlas(textureName));
	animationPallate.create(64,64);
	currentAnimation = animations["Walk"];
	currentAnimationDir = Animation::Down;
	SetAnimation(animations["Walk"],Animation::Down);
	sprite.setTextureRect(sf::IntRect(0,0,32,32));
	animationPallate.create(96,128);
	UpdateCurrentActorTexture();
	currentPatrolTargetPoint = 0;
	currentMode = Patrol;
};
void Enemy::Update(sf::RenderTexture& window){
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
						TryLaunchAttack("One");
					break;
			}
		}
	}
	Combatant::Update(window);
	Actor::Update(window);
	UpdateEffectedTiles();
	window.draw(sprite);
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
	Interact();
}
void Enemy::SetUpAnimations(){
		AddAnimation(new Animation("Walk",0.075,3,32,3,0,1,2));
};
void Enemy::SetUpAttacks(){
	std::vector<sf::Vector2i> atkOffset;
	atkOffset.push_back(sf::Vector2i(Attack::RelativeDirection::Forward,1));
	AddAttack(new Attack("One",1.f,atkOffset,1,0,0));
	currentAttacks.push_back("One");
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
	std::cout << "Drop Added: " + item << std::endl;
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