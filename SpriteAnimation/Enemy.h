#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Combatant.h"
#include <string>

class Enemy :  public Combatant
{

public:
	Enemy(int,int,std::string,std::string);
	enum Mode {AttackMode,Patrol,Pursue};
	void Update(sf::RenderTexture&);
	void Update(GamePanel*);
	void AddPatrolPoint(sf::Vector2i);
	void Interact();
	void OnClick();
	void OnActionComplete(Actions);
	void LaunchAction(Actions);
	void AddDrop(int,float);
	void SetName(std::string);
	void Drop();
private:
	void UpdateEntity();
	void LoadFromXML();
	void MoveTowardPoint(sf::Vector2i);
	void SetUpAttacks();
	bool aggressive;
	Mode currentMode;
	std::vector<sf::Vector2i> patrolPoints;
	int currentPatrolTargetPoint;
	std::vector<int> drops;
	std::vector<float> dropChances;
};

#endif