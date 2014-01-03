#ifndef BANKCONTAINER_H
#define BANKCONTAINER_H

#include <vector>
#include "Container.h"
#include <SFML/Graphics.hpp>

class BankContainer : public Container
{
public:
	BankContainer(int,int,std::string,sf::Sprite*);
	BankContainer(int,int,std::string);
	void OnButtonEvent(std::string);
	void OnClick();
	void Withdraw();
	void Equip();
private:

};

#endif