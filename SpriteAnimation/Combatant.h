#ifndef COMBATANT_H
#define COMBATANT_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Attack.h"
#include "LevelSet.h"
#include "ProgressBar.h"

class Combatant : public Actor
{
public:
	Combatant(int,int,std::string,std::string);
	Combatant();
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

	void RecieveAttack(int);
	void UpdateEffectedTiles(GamePanel*);
	//void UpdateEffectedTiles();
	typedef std::map<std::string, Attack*> AttackMap;
	typedef std::pair<std::string, Attack*> AttackPair;
	AttackMap attacks;
	void AddAttack(Attack*);
	void TryLaunchAttack(std::string);
	std::string nextAttack;
	std::vector<std::string> currentAttacks;
	virtual void UpdateBar(sf::RenderTexture&);
	float healthPercent;
	float endurancePercent;
	void AddHealth(int);
protected:
	virtual void Update(sf::RenderTexture&);
	virtual void Update(GamePanel*);
	void UpdateEntity();
	ProgressBar healthBar;
	int health;
	int endurance;
	//LevelSet levels;
private:
	virtual void Drop();
	void CompleteAttack();
	int nextAttackDamage;
	Drawn* tileEffect;
	int tileEffectFrameCount;
	std::vector<sf::Vector2i> effectedTiles;
	sf::Clock effectedTilesAnimationClock;
	sf::Clock inCombatClock;
};

#endif