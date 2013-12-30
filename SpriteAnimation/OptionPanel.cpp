#include "OptionPanel.h"
#include "Drawn.h"
#include "ScrollBar.h"
#include "CheckBox.h"
#include "Button.h"
#include "Game.h"

OptionPanel* OptionPanel::instance;
sf::Texture* OptionPanel::optionBackground = new sf::Texture();


OptionPanel::OptionPanel(int x, int y) : GamePanel(x,y){
	//Close();
	instance = this;
	SetUp();
};
void OptionPanel::SetUp(){
	sf::RenderWindow* window = Drawn::gameWindow;
	Drawn* background = new Drawn("equipedbackground.png");
	staticElements.insert(MyPair("00", background));
	Button* tempButton = new Button(460,730,Button::circleButtonBackground,"check.png");
	tempButton->SetTarget(this);
	tempButton->SetFunction("apply");
	dynamicElements.insert(MyPair("apply",tempButton));
	tempButton = new Button(640,730,Button::circleButtonBackground,Button::x);
	tempButton->SetTarget(this);
	tempButton->SetFunction("exit");
	dynamicElements.insert(MyPair("accept",tempButton));

	dynamicElements.insert(MyPair("fullscreen",new CheckBox(&(Game::fullscreen),262,167)));
	dynamicElements.insert(MyPair("vsync",new CheckBox(&(Game::verticleSync),262,265)));
	dynamicElements.insert(MyPair("brightness",new ScrollBar(262,317,150,&(Game::brightness))));
	
	dynamicElements.insert(MyPair("masterVolume",new ScrollBar(262,483,150,&(Game::masterVolume))));
	dynamicElements.insert(MyPair("musicVolume",new ScrollBar(262,602,150,&(Game::musicVolume))));
	dynamicElements.insert(MyPair("effectVolume",new ScrollBar(262,542,150,&(Game::effectVolume))));
	dynamicElements.insert(MyPair("mute",new CheckBox(&(Game::mute),262,657)));
};
void OptionPanel::OnButtonEvent(std::string function){
	if(function == "apply")
		Game::UpdateSettings();
	if(function == "exit")
		Close();
};