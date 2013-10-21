#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "GameSprite.h"

class Actor : public GameSprite
{
public:
	Actor(int,int,std::string,std::string);
	Actor();
	void MoveOnGrid(int,int);
	void Move(float,float);
	enum Direction {None, D, L, R, U, Finishing, Action};
	enum Actions {Attacking,Choping,Mining,NoAction};
	void SetCurrentDirection(Direction);
	Direction GetCurrentDirection();
	sf::Vector2i GetMovement();
	void SetMovement(sf::Vector2i);
	virtual void OnActionComplete(Actions);
	virtual void LaunchAction(Actions);
	virtual void OnClick();
	virtual void OnHover();
	sf::Vector2i GetForward();
	sf::Vector2i GetBackward();
	sf::Vector2i GetLeft();
	sf::Vector2i GetRight();
	sf::Texture GetTexture();
	bool showHit;
	std::string GetName();

	//Animation
	typedef std::map<std::string, Animation*> AnimationMap;
	typedef std::pair<std::string, Animation*> AnimationPair;
	AnimationMap animations;
	void AddAnimation(Animation*);
	sf::Sprite animationSprite;
	sf::RenderTexture animationPallate;
	//void Play(Animation*, Animation::AnimDir);
	//void Loop(Animation*, Animation::AnimDir);
	void SetAnimation(Animation*, Animation::AnimDir);
	//void StopAnimation();
	Animation* currentAnimation;
	sf::Vector2i currentAnimationPos;
	std::vector<sf::IntRect> animationSheets;
	void UpdateCurrentActorTexture();
	sf::Clock animationClock;
	bool UpdateAnimation();
	//sf::Texture GetSpriteTexture();
	Animation::AnimDir currentAnimationDir;
	bool playAnimation;
	static sf::Clock elapsedTimeClock;
	static sf::Time elapsedTime;
	sf::Texture GetActorTexture();
protected:
	std::string name;
	bool CheckTile(int x,int y);
	virtual void Update(sf::RenderTexture&);
	Direction currentDirection;
	Actions currentAction;
	sf::Vector2i movement;
	bool SetRight();
	bool SetLeft();
	bool SetUp();
	bool SetDown();
};

#endif