#ifndef DROPDOWNKMENU_H
#define DROPDOWNMENU_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "GuiElement.h"
#include "Button.h"
#include "Label.h"

class DropDownMenu : public GuiElement
{
public:
	static bool isOpen;
	DropDownMenu(int x,int y,std::vector<std::string>);
	enum Orgins{TopLeft,TopRight,BottomLeft,BottomRight};
	std::vector<Button*> buttons;
	Label* title;
	void SetOrgin(Orgins);
	void SetTarget(GuiElement*);
	void Update(GamePanel*);
	void Close();
	static DropDownMenu* instance;
	void OnClick();
private:
	GamePanel* currentPanel;
	static float GetLongestTextWidth(std::vector<std::string>);
    	static float GetTextHeight(std::vector<std::string>);
	static SlicedSprite* GetSlicedBackground(int,int,std::vector<std::string>);
};

#endif