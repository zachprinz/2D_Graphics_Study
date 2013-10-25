#include "LevelPanel.h"
#include <iostream>
#include "SlicedSpriteCreator.h"
#include "Label.h"
#include "User.h"
#include "Button.h"
#include "HUDPanel.h"

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
	sf::Texture buttonTexture = SlicedSpriteCreator::GetSlicedTexture(320,60,SlicedSpriteCreator::SpriteStyle::WoodPanel);
	std::string levelNames[] = {"strength","endurance","technique","speed","mining","woodcutting","smithing","crafting"};
	for (int x = 0; x < 8; x++){
		Button* tempButton = new Button(0,x*60,buttonTexture,"levelButtons/" + levelNames[x] + ".png");
		tempButton->SetMoveOnHover(true);
		tempButton->SetHoverMovePosition(sf::Vector2i(30,x*60));
		dynamicElements.insert(MyPair(levelNames[x], tempButton));
	}
	GamePanel::SetUp();
};
bool LevelPanel::CheckUpdate(){
	if(doUpdate == true || GamePanel::currentMousePanel == this){
		doUpdate = false;
		return true;
	}
		return false;
};
void LevelPanel::OnButtonEvent(std::string message){

};
void LevelPanel::ResetButtonPositions(){
	std::cout << "Reseting Button Positions" << std::endl;
	std::string levelNames[] = {"strength","endurance","technique","speed","mining","woodcutting","smithing","crafting"};
	for(int x = 0; x < 8; x++){
		(dynamicElements[levelNames[x]])->ResetPosition();
	}
};