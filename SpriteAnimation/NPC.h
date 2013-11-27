#ifndef NPC_H
#define NPC_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Actor.h"
#include <string>

class NPC :  public Actor
{

public:
	NPC(int,int,std::string,std::string);
	void Update(sf::RenderTexture&);
	void Update(GamePanel*);
	void Interact();
	void OnClick();
private:
	void UpdateEntity();
	void SetUpAnimations();
	void MoveTowardPoint(sf::Vector2i);
	std::string GetResponce();
};

#endif