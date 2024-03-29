#ifndef COMBATANT_H
#define COMBATANT_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Attack.h"
#include "LevelSet.h"
#include "ProgressBar.h"
#include "Projectile.h"
#include "HealthBar.h"
#include "Clock.h"

class Combatant : public Actor
{
public:
	Combatant(int,int,std::string,std::string);
	int SendDamage();
	int TakeDamage(int damage);
	int SpendEndurance(int end);
	void Die();
	int GetHealth();
	int GetEndurance();
	LevelSet levelSet;
	//LevelSet GetTotalStats();
	void OnHover();
	bool inCombat;
	void LaunchAttack(std::string);
	void TryLaunchAttack(std::string);
	void RecieveAttack(int);
	void UpdateEffectedTiles(GamePanel*);
	//void UpdateEffectedTiles();
	typedef std::map<std::string, Attack*> AttackMap;
	typedef std::pair<std::string, Attack*> AttackPair;
	AttackMap attacks;
	void AddAttack(Attack*);
	std::string nextAttack;
	std::vector<std::string> currentAttacks;
	virtual void UpdateBar(GamePanel*);
	float healthPercent;
	float endurancePercent;
	void AddHealth(int);
	std::vector<sf::Vector2i> effectedTiles;
	int nextAttackDamage;
	Drawn* tileEffect;
	int tileEffectFrameCount;
	virtual void UpdateAction(GamePanel*, bool);
	void LaunchAction(Actions action);
protected:
	virtual void Update(GamePanel*);
	void UpdateEntity();
	HealthBar* healthBar;
	int health;
	int endurance;
	//LevelSet levels;
	std::vector<Projectile*> projectiles;
	virtual void Drop();
	void CompleteAttack();
	Clock effectedTilesAnimationClock;
	Clock inCombatClock;
};

#endif