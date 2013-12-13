#ifndef ATTACK_H
#define ATTACK_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Clock.h"

class Attack
{
public:
	Attack(std::string name,float damageMod,std::vector<sf::Vector2i> offsets,float cooldown, int animationY, int frames);
	Attack();
	std::vector<sf::Vector2i> Use(sf::Vector2i,sf::Vector2i);
	sf::Sprite hudSprite;
	sf::IntRect hudTexture;
	enum RelativeDirection {Forward,Backward,Left,Right};
	int animationY;
	int numOfFrames;
	std::string name;
	void Update();
	float damageModifier;
	sf::Vector2i GetForward(sf::Vector2i position,sf::Vector2i movement,int);
	sf::Vector2i GetBackward(sf::Vector2i position,sf::Vector2i movement,int);
	sf::Vector2i GetLeft(sf::Vector2i position,sf::Vector2i movement,int);
	sf::Vector2i GetRight(sf::Vector2i position,sf::Vector2i movement,int);
	float percentCooledDown;
	sf::Time cooldownTime;
	Clock cooldownClock;
	bool GetIsCooledDown();
private:
	bool isCooledDown;
	std::vector<sf::Vector2i> effectTileOffsets;

	sf::Time timePerFrame;
};

#endif