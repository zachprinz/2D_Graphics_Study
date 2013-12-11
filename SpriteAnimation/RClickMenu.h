#ifndef RCLICKMENU_H
#define RCLICKMENU_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "GuiElement.h"
#include "Button.h"
#include "Label.h"

class RClickMenu
{
public:
	static enum Options{Drop,Equip,Unequip,Deposit,Withdraw,Barter,Craft};
	static enum Orgins{TopLeft,TopRight,BottomLeft,BottomRight};
	static std::vector<Label*> OptionButtons;
	static void SetOrgin(Orgins);
	static void AddOption(int,int,int);
	static void Reset(int,int,std::string,RClickable*,GamePanel*);
	static std::vector<Label*> GetMenu();
	static void OnStart();
	static sf::Texture menuTexture;
	static void Clear();
	static bool GetIsOpen();
	static GamePanel* currentPanel;
	static RClickable* currentTarget;
	static void Update(sf::RenderTexture&);
	static void Update(GamePanel*);
	static float width;
	static bool Contains(sf::Vector2f);
	static void Close();
	static std::vector<Label*> labels;
private:
	static float GetTextWidth(std::string);
	static bool isOpen;
};

#endif