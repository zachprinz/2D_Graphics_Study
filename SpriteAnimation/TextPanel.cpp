#include "TextPanel.h"
#include "Button.h"
#include "Label.h"
#include "ProgressBar.h"
#include "SlicedSpriteCreator.h"
#include "User.h"
#include <iostream>

TextPanel* TextPanel::instance;

TextPanel::TextPanel(int x,int y) : GamePanel(x,y,"Text"){
	instance = this;
	SetUp();
	height = 0;
	averageWidth = 0;
	currentDisplayedPage = -1;
	for(int x = 97; x < 123; x++){
		averageWidth += Label::fonts[0].getGlyph(x,30,false).bounds.width;
	}
	for(int x = 41; x < 133; x++){
		if(Label::fonts[0].getGlyph(x,22,false).bounds.height > height)
			height = Label::fonts[0].getGlyph(x,30,false).bounds.height;
	}
	averageWidth = averageWidth / 26.0;
	//sf::Text tempText  = sf::Text(text,Label::fonts[0],30);
	linesPerPage = (panel.getSize().y) / height;
	linesPerPage--;
	charsPerLine = (panel.getSize().x + 360) / averageWidth;
	DisplayText("Welcome to my world. I made it. It's not quite finished but you should be able to find some stuff to do. Check out you're inventory and levels to the right. Try mousing over some items or enemies to take advantage of the stats panel. After you're aquainted with everything go talk to that mysterious man hanging out up there, see what he wants.");
};
void TextPanel::SetUp(){
	GamePanel::SetUp();
	Label* textDisplay = new Label(8,0,"blank.png",Label::Fonts::Game,"Where all the text will be displayed. ");
	dynamicElements.insert(MyPair("text",textDisplay));
	((Label*)dynamicElements["text"])->GetText()->setCharacterSize(30);
	sf::Texture tempText2;
	tempText2.loadFromFile("buttonImages/minusButton.png");
	Button* previousButton = new Button(8,panel.getSize().y - 40,tempText2,"blank.png");
	previousButton->SetTarget(this);
	previousButton->SetFunction("previousButton");
	dynamicElements.insert(MyPair("previousButton",previousButton));
	tempText2.loadFromFile("buttonImages/plusButton.png");
	Button* nextButton = new Button(panel.getSize().x - 40,panel.getSize().y - 40,tempText2,"blank.png");
	nextButton->SetTarget(this);
	nextButton->SetFunction("nextButton");
	dynamicElements.insert(MyPair("nextButton",nextButton));
};
void TextPanel::DisplayText(std::string text){
	sortedText.clear();
	pages.clear();
	while(text.size() > 1){
		std::vector<std::string> lines;
		for(int x = 0; x < linesPerPage; x++){
			if(charsPerLine > text.size() || text.find_last_of(' ',charsPerLine) == std::string::npos){
				text = text + "...";
				lines.push_back(text);
				text = "";
				break;
			}
			else{
				int p = text.find_last_of(' ',charsPerLine);
				lines.push_back(text.substr(0,p));
				text = text.substr(p,text.size());
			}
		}
		sortedText.push_back(lines);
	}
	for(int x = 0; x < sortedText.size(); x++){
		std::string tempPage;
		for(int y = 0; y < sortedText[x].size(); y++){
			tempPage += sortedText[x][y] + "\n";
		}
		pages.push_back(tempPage);
	}
	SwitchPages(1);
};
void TextPanel::SwitchPages(int page){
	if(currentDisplayedPage == -1)
		Open();
	if(page != -1 || currentDisplayedPage > 0){
		currentDisplayedPage += page;
		if(currentDisplayedPage >= pages.size()){
			std::cout << "Closing Text Panel" << std::endl;
			Close();
			currentDisplayedPage = -1;
		}
		else
			((Label*)dynamicElements["text"])->SetText(pages[currentDisplayedPage]);
	}
};
void TextPanel::OnButtonEvent(std::string func){
	if(func == "nextButton")
		SwitchPages(1);
	else if(func == "previousButton")
		SwitchPages(-1);
};