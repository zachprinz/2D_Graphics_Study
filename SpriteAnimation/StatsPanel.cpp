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
	//mainLevelPercent = std::stof(User::player->GetUserData(currentName,
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
	((Button*)(itemMap["Image"]))->foreground->GetSprite()->setTextureRect(Drawn::GetTextureFromAtlas("itemsprites/" + item->GetId() + ".png"));
	((Button*)(itemMap["Image"]))->CenterForeground();
	currentName = item->GetName();
	dynamicElements = itemMap;
};
void StatsPanel::SetLevel(std::string levelName){
	doUpdate = true;
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("xml/userInfo.xml");
	pugi::xml_node atlas = doc.child("User").child("LevelInfo");
	pugi::xml_node level;
	std::vector<pugi::xml_node> subLevels;
	for(pugi::xml_node tool = atlas.first_child(); tool; tool = tool.next_sibling()){
		if(tool.attribute("name").value() == levelName){
			level = tool;
			std::cout << "Found the level." << std::endl;
			for(pugi::xml_node tool2 = tool.first_child(); tool2; tool2 = tool2.next_sibling()){
					std::cout << "Pushing back with a sub Level" << std::endl;
					subLevels.push_back(tool2);
			}
		}
	}
	mainLevelPercent = std::stof(level.attribute("percent").value());
	subLevelPercents[0] = std::stof(subLevels[0].attribute("percent").value());
	subLevelPercents[1] = std::stof(subLevels[1].attribute("percent").value());
	((Drawn*)(levelMap["levelHeadline"]))->GetSprite()->setTextureRect(Drawn::GetTextureFromAtlas("levelButtons/" + levelName + ".png"));//edit image path
	mainLevelPercent = std::stof(level.attribute("percent").value());
	subLevelPercents[0] = std::stof(subLevels[0].attribute("percent").value());
	subLevelPercents[1] = std::stof(subLevels[1].attribute("percent").value());
	((Label*)(levelMap["mainLevelBottomXP"]))->SetText("0");
	((Label*)(levelMap["mainLevelCurrentXP"]))->SetText(level.attribute("xpPastCurrentLevel").value());
	((Label*)(levelMap["mainLevelTopXP"]))->GetText()->setString(level.attribute("maxXPForNextLevel").value());
	((Label*)(levelMap["subLevelTitle0"]))->GetText()->setString(subLevels[0].attribute("name").value());
	((Label*)(levelMap["subLevelTitle1"]))->GetText()->setString(subLevels[1].attribute("name").value());
	((Label*)(levelMap["subLevelDescription0"]))->GetText()->setString(subLevels[0].attribute("description").value());
	((Label*)(levelMap["subLevelDescription1"]))->GetText()->setString(subLevels[1].attribute("description").value());
	((Label*)(levelMap["subLevelBottomXP0"]))->SetText("0");
	((Label*)(levelMap["subLevelBottomXP1"]))->SetText("0");
	((Label*)(levelMap["subLevelCurrentXP0"]))->SetText(subLevels[0].attribute("xpPastCurrentLevel").value());
	((Label*)(levelMap["subLevelCurrentXP1"]))->SetText(subLevels[1].attribute("xpPastCurrentLevel").value());
	((Label*)(levelMap["subLevelTopXP0"]))->SetText(subLevels[0].attribute("maxXPForNextLevel").value());
	((Label*)(levelMap["subLevelTopXP1"]))->SetText(subLevels[1].attribute("maxXPForNextLevel").value());
	currentName = levelName;
	dynamicElements = levelMap;
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
	SetUpLevelMap();
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
void StatsPanel::SetUpLevelMap(){
	sf::Texture tempText;
	tempText.loadFromFile("blank.png");
	mainLevelPercent = 1.0;
	subLevelPercents.push_back(1.0);
	subLevelPercents.push_back(1.0);
	Drawn* levelHeadline = new Drawn("blank.png");
	ProgressBar* mainLevelProgBar = new ProgressBar(8,70,350,&mainLevelPercent);
	Label* mainLevelBottomXP = new Label(8,50,"blank.png",Label::Fonts::Game,"0");
	Label* mainLevelCurrentXP = new Label(140,50,"blank.png",Label::Fonts::Game,"50");
	Label* mainLevelTopXP = new Label(320,50,"blank.png",Label::Fonts::Game,"100");
	levelMap.insert(MyPair("levelHeadline",levelHeadline));
	levelMap.insert(MyPair("mainLevelProgBar",mainLevelProgBar));
	levelMap.insert(MyPair("mainLevelBottomXP",mainLevelBottomXP));
	levelMap.insert(MyPair("mainLevelTopXP",mainLevelTopXP));
	levelMap.insert(MyPair("mainLevelCurrentXP",mainLevelCurrentXP));
	for(int x = 0; x < 2; x++){
		std::cout << "Setting Up Sub Level" << std::endl;
		Label* subLevelTitle = new Label(8,(x*150)+160,tempText,Label::Fonts::Game,"SubLevel:" + x);
		Label* subLevelDescription = new Label(8,(x*150)+180,"blank.png",Label::Fonts::Game,"SubLevel Description Text.");
		ProgressBar* subLevelProgBar = new ProgressBar(8,(150*x) + 210,350,&subLevelPercents[x]);
		Label* subLevelBottomXP = new Label(8,(x*150)+230,"blank.png",Label::Fonts::Game,"0");
		Label* subLevelCurrentXP = new Label(140,(x*150)+230,"blank.png",Label::Fonts::Game,"50");
		Label* subLevelTopXP = new Label(320,(x*150)+230,"blank.png",Label::Fonts::Game,"100");
		levelMap.insert(MyPair("subLevelTitle" + std::to_string(x),subLevelTitle));
		levelMap.insert(MyPair("subLevelDescription" + std::to_string(x),subLevelDescription));
		levelMap.insert(MyPair("subLevelProgBar" + std::to_string(x),subLevelProgBar));
		levelMap.insert(MyPair("subLevelCurrentXP" + std::to_string(x),subLevelCurrentXP));
		levelMap.insert(MyPair("subLevelBottomXP" + std::to_string(x),subLevelBottomXP));
		levelMap.insert(MyPair("subLevelTopXP" + std::to_string(x),subLevelTopXP));
	}
};
bool StatsPanel::CheckUpdate(){
	if(doUpdate || GamePanel::currentMousePanel == this || dynamicElements == levelMap){
		doUpdate = false;
		return true;
	}
	else
		return false;
};
