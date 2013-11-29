#ifndef BANK_H
#define Bank_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Item.h"
#include "GameSprite.h"

class Bank : public GameSprite
{
public:
	Bank(int x, int y, std::string);
	void Update(sf::RenderTexture&);
	void Update(GamePanel*);
	void Interact();
	void Start();
	void Open();
	//BankUIHandler bankUI
private:
};

#endif