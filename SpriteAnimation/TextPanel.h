#ifndef TEXTPANEL_H
#define TEXTPANEL_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "GamePanel.h"
#include "LevelSet.h"
#include "Combatant.h"
#include "Item.h"

class TextPanel : public GamePanel
{
public:
	static TextPanel* instance;
	TextPanel(int,int);
	void DisplayText(std::string);
	void OnButtonEvent(std::string);
private:
	int currentDisplayedPage;
	int linesPerPage;
	int charsPerLine;
	std::vector<std::vector<std::string>> sortedText;
	std::vector<std::string> pages;
	float averageWidth;
	float height;
	void SetUp();
	void SwitchPages(int);
};

#endif