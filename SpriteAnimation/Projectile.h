#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameSprite.h"
#include "Attack.h"

class Combatant;
class Projectile : public GameSprite
{
public:
	Projectile(Combatant* owner,int, int, Attack,int angle, float range);
	void Update(GamePanel*);
	std::vector<RoomTile*> effectedTiles;
	Attack myAttack;
	float angle;
	sf::Vector2f projectileVelocity;
	float range;
	void Destroy();
private:
	Combatant* owner;
	sf::Vector2f orginPosition;
	void Hit(RoomTile*);
	bool CheckForCollision(std::vector<RoomTile*>);
	Clock projectileClock;
};
#endif