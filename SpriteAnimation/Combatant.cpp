#include "Combatant.h"
#include <iostream>
#include "SpritePanel.h"
#include "StatsPanel.h"
#include "User.h"

Combatant::Combatant(int x, int y,std::string name,std::string textureName) : Actor(x,y,name,textureName){
	health = 100;
	endurance = 1000;
	healthPercent = 1;
	endurancePercent = 1;
	levelSet = LevelSet();
	inCombat = false;
	healthBar = ProgressBar(&healthPercent,GetSprite());
	tileEffectTexture.loadFromFile("tileeffect.png");
	tileEffectSprite.setTexture(tileEffectTexture);
	tileEffectSprite.setTextureRect(sf::IntRect(0,0,32,32));
	inCombatClock.restart();
};
Combatant::Combatant(){

};
void Combatant::AddAttack(Attack* atk){
	attacks.insert(AttackPair(atk->name, atk));
};
int Combatant::SendDamage(){
	return 10;
};
int Combatant::TakeDamage(int damage){
	health -= damage;
	return health;
};
int Combatant::SpendEndurance(int end){
	endurance -= end;
	return endurance;
};
void Combatant::Die(){
	User::player->UpdateQuest(name);
	Drop();
	GetRoomTile()->TryRemoveOcupant(GetTag());
	SpritePanel::room->RemoveOcupant(GetTag());
	SpritePanel::instance->RemoveDynamicElement(std::to_string(GetTag()));
	isVisible = false;
	//Call Destructor: ~Combatant();
	//Drop(); Call Lua script to derive drop.
	//Drop Calls SpritePanel::instance->SpawnItem(id,x,y,SpritePanel::instance->room);
};
void Combatant::Drop(){

};
int Combatant::GetHealth(){
	return health;
};
int Combatant::GetEndurance(){
	return endurance;
};
void Combatant::Update(sf::RenderTexture& panel){
	if(inCombat && inCombatClock.getElapsedTime().asSeconds() > 5.0){
		std::cout << "Out of Combat, healing." << std::endl;
		inCombat = false;
		inCombatClock.restart();
	}
	if(inCombat == false && health < 100){
		AddHealth(1);
	}
	for(AttackPair x: attacks){
		x.second->Update();
	}
}
void Combatant::UpdateBar(sf::RenderTexture& panel){
	if(inCombat || health < 100){
		healthPercent = ((float)health) / 100.f;
		healthBar.Update(panel);
	}
};
void Combatant::LaunchAttack(std::string atkName){
	if(attacks[atkName]->GetIsCooledDown()){
		tileEffectFrameCount = 0;
		nextAttackDamage = SendDamage() * attacks[atkName]->damageModifier;
		effectedTiles = attacks[atkName]->Use(graphPositionA,movement);
	}
};
void Combatant::CompleteAttack(){
	std::cout << "Completeing Attack" << std::endl;
	for(int y = 0; y < effectedTiles.size(); y++){
		for(int x = 0; x < SpritePanel::room->roomTiles[effectedTiles[y].y][effectedTiles[y].x].ocupants.size(); x++){
			std::cout << "Found Effected Enemy" << std::endl;
			RoomTile* tempTile = &SpritePanel::room->roomTiles[effectedTiles[y].y][effectedTiles[y].x];
			if(tempTile->ocupants[x] != GetTag()){
				int tempTag = tempTile->ocupants[x];
				if(SpritePanel::room->GetOcupant(tempTag) != NULL)
					SpritePanel::room->GetOcupant(tempTag)->RecieveAttack(nextAttackDamage);
				break;
			}
		}
	}
};
void Combatant::UpdateEffectedTiles(sf::RenderTexture& panel){
	if(effectedTiles.size() > 0){
		if(effectedTilesAnimationClock.getElapsedTime() > sf::seconds(0.075)){
			effectedTilesAnimationClock.restart();
			tileEffectSprite.setTextureRect(sf::IntRect(tileEffectFrameCount * 32,0,32,32));
			tileEffectFrameCount++;
			if(tileEffectFrameCount == 3)
				CompleteAttack();
		}
		for(int x = 0; x < effectedTiles.size(); x++){
			tileEffectSprite.setPosition(effectedTiles[x].x * 32,effectedTiles[x].y * 32);
			panel.draw(tileEffectSprite);
		}
		if(tileEffectFrameCount >= (tileEffectTexture.getSize().x / 32)){
			tileEffectFrameCount = 0;
			effectedTiles.clear();
		}
	}
};
void Combatant::UpdateEffectedTiles(){
	if(effectedTiles.size() > 0){
		if(effectedTilesAnimationClock.getElapsedTime() > sf::seconds(0.075)){
			effectedTilesAnimationClock.restart();
			tileEffectSprite.setTextureRect(sf::IntRect(tileEffectFrameCount * 32,0,32,32));
			tileEffectFrameCount++;
			if(tileEffectFrameCount == 3)
				CompleteAttack();
		}
		if(tileEffectFrameCount >= (tileEffectTexture.getSize().x / 32)){
			tileEffectFrameCount = 0;
			effectedTiles.clear();
		}
	}
};
void Combatant::TryLaunchAttack(std::string tempAtkName){
	if(attacks[tempAtkName]->GetIsCooledDown()){
		nextAttack = tempAtkName;
		currentAction = Attacking;
	}
};
void Combatant::RecieveAttack(int hit){
	inCombat = true;
	inCombatClock.restart();
	std::cout << "ATTACK RECIEVED" << std::endl;
	if(health - hit > 0)
		TakeDamage(hit);
	else {
		TakeDamage(health);
		Die();
	}
	showHit = true;
	std::cout << std::to_string(health) << std::endl;
};
void Combatant::OnHover(){
	if(StatsPanel::instance->currentName != name)
		StatsPanel::instance->SetCombatant(this);
};
void Combatant::AddHealth(int add){
	std::cout << "Adding Health" << std::endl;
	if(health + add < 100)
		health += add;
	else
		health = 100;
};