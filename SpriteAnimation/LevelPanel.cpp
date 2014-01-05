#include "LevelPanel.h"
#include <iostream>
#include "Label.h"
#include "User.h"
#include "Button.h"
#include "HUDPanel.h"
#include "StatsPanel.h"

LevelPanel* LevelPanel::instance = new LevelPanel();

LevelPanel::LevelPanel(int x,int y) : GamePanel(x,y,"Levels"){
	SetUp();
	instance = this;
};
LevelPanel::LevelPanel(){

};
void LevelPanel::AddElement(std::string,Drawn*){

};
void LevelPanel::SetUp(){
	std::string levelNames[] = {"strength","endurance","technique","speed","mining","woodcutting","smithing","crafting"};
	for (int x = 0; x < 8; x++){
		Button* tempButton = new Button(0,x*60,"levelbackground.png","levelButtons/" + levelNames[x] + ".png");
		tempButton->SetTarget(this);
		tempButton->SetFunction(levelNames[x]);
		tempButton->SetMoveOnHover(true);
		tempButton->SetHoverMovePosition(sf::Vector2i(30,x*60));
		AddDynamicElement(MyPair(levelNames[x], tempButton));
	}
	GamePanel::SetUp();
};
void LevelPanel::OnButtonEvent(std::string message){
	std::cout << "Level Button Clicked, about to switch StatsPanel." << std::endl;
	StatsPanel::instance->SetLevel(message);
};
void LevelPanel::ResetButtonPositions(){
	std::cout << "Reseting Button Positions" << std::endl;
	std::string levelNames[] = {"strength","endurance","technique","speed","mining","woodcutting","smithing","crafting"};
	for(int x = 0; x < 8; x++){
		(dynamicElements[levelNames[x]])->ResetPosition();
	}
};