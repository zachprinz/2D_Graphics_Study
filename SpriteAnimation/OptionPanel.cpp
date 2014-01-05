#include "OptionPanel.h"
#include "Drawn.h"
#include "ScrollBar.h"
#include "CheckBox.h"
#include "Button.h"
#include "Game.h"

OptionPanel* OptionPanel::instance;
sf::Texture* OptionPanel::optionBackground = new sf::Texture();


OptionPanel::OptionPanel(int x, int y) : GamePanel(x,y,"OptionPanel"){
	Close();
	instance = this;
	SetUp();
};
void OptionPanel::SetUp(){
	sf::RenderWindow* window = Drawn::gameWindow;
	Drawn* background = new Drawn("options_menu.png");
	staticElements.insert(MyPair("00", background));
	Button* tempButton = new Button(570,736,SlicedSprite::SpriteStyle::WoodPanel,"Cancel");
	tempButton->SetTarget(this);
	tempButton->SetFunction("cancel");
	AddDynamicElement(MyPair("cancel",tempButton));
	tempButton = new Button(690,736, SlicedSprite::SpriteStyle::WoodPanel,"Accept");
	tempButton->SetTarget(this);
	tempButton->SetFunction("accept");
	AddDynamicElement(MyPair("accept",tempButton));
	tempButton = new Button(15,736,SlicedSprite::SpriteStyle::WoodPanel,"Main Menu");
	tempButton->SetTarget(this);
	tempButton->SetFunction("main menu");
    	AddDynamicElement(MyPair("main menu",tempButton));
	tempButton = new Button(195,736,SlicedSprite::SpriteStyle::WoodPanel,"Exit");
	tempButton->SetTarget(this);
	tempButton->SetFunction("exit");
	AddDynamicElement(MyPair("exit",tempButton));
	AddDynamicElement(MyPair("fullscreen",new CheckBox(&(Game::fullscreen),262,167)));
	AddDynamicElement(MyPair("vsync",new CheckBox(&(Game::verticleSync),262,265)));
	AddDynamicElement(MyPair("brightness",new ScrollBar(262,317,300,&(Game::brightness))));
	
	AddDynamicElement(MyPair("masterVolume",new ScrollBar(262,483,300,&(Game::masterVolume))));
	AddDynamicElement(MyPair("musicVolume",new ScrollBar(262,602,300,&(Game::musicVolume))));
	AddDynamicElement(MyPair("effectVolume",new ScrollBar(262,542,300,&(Game::effectVolume))));
	AddDynamicElement(MyPair("mute",new CheckBox(&(Game::mute),262,657)));
};
void OptionPanel::OnButtonEvent(std::string function){
	if(function == "accept"){
		Game::UpdateSettings();
		Close();
	}
	if(function == "cancel")
		Close();
	if(function == "exit")
		Drawn::gameWindow->close();
};
void OptionPanel::Open(){
    Clock::timeSpeed = 0;
    GamePanel::Open();
};
void OptionPanel::Close(){
    Clock::timeSpeed = 1.0;
    GamePanel::Close();
};