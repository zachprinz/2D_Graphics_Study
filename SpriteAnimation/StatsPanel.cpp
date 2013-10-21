#include "StatsPanel.h"
#include "Label.h"
#include "Button.h"
#include "SlicedSpriteCreator.h"
#include "User.h"
#include <iostream>

StatsPanel* StatsPanel::instance;

StatsPanel::StatsPanel(int x,int y) : GamePanel(x,y,"Stats") {
	SetUp();
	SetCombatant(User::player);
	instance = this;
};
void StatsPanel::UpdateElements(){
	GamePanel::UpdateElements();
};
void StatsPanel::SetItem(Item* item){
	doUpdate = true;
	((Label*)(itemMap["StrengthValue"]))->SetText(std::to_string(item->itemLevels.strength));
	((Label*)(itemMap["EndureValue"]))->SetText(std::to_string(item->itemLevels.endurance));
	((Label*)(itemMap["SpeedValue"]))->SetText(std::to_string(item->itemLevels.speed));
	((Label*)(itemMap["TechniqueValue"]))->SetText(std::to_string(item->itemLevels.technique));
	((Label*)(itemMap["WoodcuttingValue"]))->SetText(std::to_string(item->itemLevels.woodcutting));
	((Label*)(itemMap["MiningValue"]))->SetText(std::to_string(item->itemLevels.mining));
	((Label*)(itemMap["Name"]))->SetText(item->GetName());
	((Label*)(itemMap["Name"]))->CenterText();
	((Button*)(itemMap["Image"]))->foregroundSprite.setTextureRect(Drawn::GetTextureFromAtlas("itemsprites/" + item->GetId() + ".png"));
	((Button*)(itemMap["Image"]))->CenterForeground();
	currentName = item->GetName();
	dynamicElements = itemMap;
};
void StatsPanel::SetCombatant(Combatant* combatant){
	doUpdate = true;
	((Label*)(combatantMap["StrengthValue"]))->SetText(std::to_string(combatant->levelSet.strength));
	((Label*)(combatantMap["EndureValue"]))->SetText(std::to_string(combatant->levelSet.endurance));
	((Label*)(combatantMap["SpeedValue"]))->SetText(std::to_string(combatant->levelSet.speed));
	((Label*)(combatantMap["TechniqueValue"]))->SetText(std::to_string(combatant->levelSet.technique));
	((ProgressBar*)(combatantMap["HealthBar"]))->SetPercent(&combatant->healthPercent);
	((ProgressBar*)(combatantMap["EnduranceBar"]))->SetPercent(&combatant->endurancePercent);
	((Label*)(combatantMap["Name"]))->SetText(combatant->GetName());
	((Label*)(combatantMap["Name"]))->CenterText();
	((Button*)(combatantMap["Image"]))->SetForegroundSprite(combatant->GetActorTexture());
	((Button*)(combatantMap["Image"]))->CenterForeground();
	currentName = combatant->GetName();
	dynamicElements = combatantMap;
};
void StatsPanel::SetUp(){
	SetUpItemMap();
	SetUpCombatantMap();
	GamePanel::SetUp();
};
void StatsPanel::SetUpItemMap(){
	sf::Texture tempText;
	tempText.loadFromFile("blank.png");
	int labelsPosX[] = {20,185,20,185,20,185};
	int labelsPosY[] = {160,160,230,230,300,300};
	std::string labelsString[] = {"Strength","Endure","Technique","Speed","Mining","Woodcutting"};
	for (int x = 0; x < 6; x++){
		Label* element = new Label(labelsPosX[x],labelsPosY[x],tempText,Label::Fonts::Game,labelsString[x] + ":");
		Label* valueElement = new Label(labelsPosX[x] + element->GetText()->getLocalBounds().width + 15,labelsPosY[x],tempText,Label::Fonts::Game,"null");
		itemMap.insert(MyPair(std::to_string(x), element));
		itemMap.insert(MyPair(labelsString[x] + "Value",valueElement));
	}
	Button* tempButton = new Button(147.5,15,"attacktextures/background.png","attacktextures/default.png");
	tempButton->SetTarget(this);
	tempButton->SetFunction("none");
	tempButton->CenterForeground();
	itemMap.insert(MyPair("Image",tempButton));
	Label* label = new Label(127.5,110,120,SlicedSpriteCreator::GetSlicedTexture(120,30,SlicedSpriteCreator::WoodPanel),Label::Fonts::Game,"null");
	label->CenterText();
	itemMap.insert(MyPair("Name",label));
};
void StatsPanel::SetUpCombatantMap(){
	sf::Texture tempText;
	tempText.loadFromFile("blank.png");
	int labelsPosX[] = {20,185,20,185,20,20};
	int labelsPosY[] = {160,160,230,230,300,370};
	std::string labelsString[] = {"Strength","Endure","Technique","Speed","Health","Endurance"};
	for (int x = 0; x < 6; x++){
		Label* element = new Label(labelsPosX[x],labelsPosY[x],tempText,Label::Fonts::Game,labelsString[x] + ":");
		combatantMap.insert(MyPair(std::to_string(x), element));
		if(x < 4){
			Label* valueElement = new Label(labelsPosX[x] + element->GetText()->getLocalBounds().width + 15,labelsPosY[x],tempText,Label::Fonts::Game,"null");
			combatantMap.insert(MyPair(labelsString[x] + "Value",valueElement));
		}
		else{
			float tempFloat = 1;
			ProgressBar* progBar = new ProgressBar(labelsPosX[x] + element->GetText()->getLocalBounds().width + 15,labelsPosY[x], 200, &tempFloat);
			combatantMap.insert(MyPair(labelsString[x] + "Bar",progBar));
		}
	}
	Button* tempButton = new Button(147.5,15,"attacktextures/background.png","attacktextures/default.png");
	tempButton->SetTarget(this);
	tempButton->SetFunction("none");
	tempButton->CenterForeground();
	combatantMap.insert(MyPair("Image",tempButton));
	Label* label = new Label(127.5,110,120,SlicedSpriteCreator::GetSlicedTexture(120,30,SlicedSpriteCreator::WoodPanel),Label::Fonts::Game,"null");
	label->CenterText();
	combatantMap.insert(MyPair("Name",label));
};
bool StatsPanel::CheckUpdate(){
	if(doUpdate || GamePanel::currentMousePanel == this){
		doUpdate = false;
		return true;
	}
	else
		return false;
};
