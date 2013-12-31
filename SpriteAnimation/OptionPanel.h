#ifndef OPTIONPANEL_H
#define OPTIONPANEL_H

#include "GamePanel.h"
#include <iostream>

class OptionPanel : public GamePanel
{
public:
	OptionPanel(int x, int y);
	void SetResolution(sf::Vector2f resolution);
	static OptionPanel* instance;
	static sf::Texture* optionBackground;
	void SetUp();
	void OnButtonEvent(std::string messages);
	void Open();
	void Close();
};
#endif