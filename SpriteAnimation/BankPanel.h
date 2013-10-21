#ifndef BANKPANEL_H
#define BANKPANEL_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "ScrollingPanel.h"
#include "BankContainer.h"

class BankPanel : public ScrollingPanel
{
public:
	BankPanel(int,int);
	BankPanel();
	static BankPanel* instance;
	void AddElement(std::string,Drawn*);
	BankContainer* GetOpenContainer();
	void Add(Item item);
	void Remove(Item item);
	void Remove(std::vector<Item> items);
	void OnButtonEvent(std::string);
	bool DoesContain(Item);
	bool DoesContain(std::vector<Item>);
	BankContainer* FindContainerOf(Item item);
	static sf::Texture* bankBackground;
private:
	void SetUp();

};

#endif