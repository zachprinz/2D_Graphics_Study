#include <SFML/Graphics.hpp>
#include "User.h"
#include <iostream>
#include "SpritePanel.h"
#include <iterator>
#include <vector>
#include "Attack.h"
#include "StatsPanel.h"
#include "ActionBar.h"

User* User::player;

User::User(int x, int y) : Combatant(x,y,"User","User"){
	ResetXMLDocs();
	oversize = true;
	User::player = this;
	bank = new BankPanel(480,480);
	inventory = new InventoryPanel(320,480);
	equiped = new EquipedPanel(320,480);
	levelPanel = new LevelPanel(320,480);
	std::vector<GamePanel*> temp;
	temp.push_back(inventory);
	temp.push_back(equiped);
	temp.push_back(levelPanel);
	std::cout << "About to create Layered Panel" << std::endl;
	layered = new LayeredPanel(temp);
	layered->SetPosition(1125,445);
	SetUpImages();
	SetUpAttacks("default");
	sprite.setTextureRect(sf::IntRect(0,0,64,64));
	currentAnimation = animations["Walk"];
	currentAnimationDir = Animation::Down;
	SetAnimation(animations["Walk"],Animation::Down);
	backupKey = sf::Keyboard::F12;
	currentKey = sf::Keyboard::F12;
	wKeyPressed = false;
	aKeyPressed = false;
	dKeyPressed = false;
	sKeyPressed = false;
	cKeyPressed = false;
	Drawn::gameTexture.setRepeated(false);
	SetUpLevels();
	UpdateAnimation();
	UpdateBoundries();
};
void User::Update(sf::RenderTexture& window){
	CheckUserInput();
	if(currentDirection == None){
		if(currentAction != NoAction){
				LaunchAction(currentAction);
		}
		else{
			switch(currentKey){
			case(sf::Keyboard::A):
					tailPoint = graphPositionA;
					SetLeft();
				break;
			case(sf::Keyboard::D):
					tailPoint = graphPositionA;
					SetRight();
				break;
			case(sf::Keyboard::W):
					tailPoint = graphPositionA;
					SetUp();
				break;
			case(sf::Keyboard::S):
					tailPoint = graphPositionA;
					SetDown();
				break;
			case(sf::Keyboard::F12):
				break;
			}
		}
	}
	Combatant::Update(window);
	Actor::Update(window);
	Draw(&window);
	DrawBoundries(window);
};
void User::GetUserWeaponImage(sf::RenderTexture* window){
	if(((EquipedContainer*)equiped->dynamicElements["1"])->GetContents().GetOversized()){
		sprite.setTextureRect(sf::IntRect(animationSheets[2].left + (currentAnimationPos.x * 192),animationSheets[2].top + ((currentAnimationPos.y % 4) * 192),192,192));
		sprite.setPosition(sprite.getPosition().x - 55,sprite.getPosition().y - 40);
		window->draw(sprite);
		sprite.setPosition(sprite.getPosition().x + 55,sprite.getPosition().y + 40);
	}
	else{
		sprite.setTextureRect(sf::IntRect(animationSheets[2].left + (currentAnimationPos.x * 64),animationSheets[2].top + (currentAnimationPos.y * 64),64,64));
		window->draw(sprite);
	}
};

void User::Interact(){
	std::cout << "Ocupant Found on Tile:" + GetRoomTile(movement.x,movement.y)->ocupants.size() << std::endl;
	//for(int x = 0; x < GetRoomTile(movement.x,movement.y)->ocupants.size(); x++){
	if(GetRoomTile(movement.x,movement.y)->ocupants.size() > 0){
		if(GetRoomTile(movement.x,movement.y)->ocupants[0] != tag){
			RoomTile* tempTile = GetRoomTile(movement.x,movement.y);
			int tempTag = tempTile->ocupants[0];
			GameSprite* tempSprite = SpritePanel::room->GetOcupant(tempTag);
			std::cout << tempSprite->GetTag();
			if(tempSprite != NULL)
				tempSprite->Interact(); // TODO
			//break;
		}
	}
	//}
}
void User::SetInventory(InventoryPanel* inv){
	inventory = inv;
};
InventoryPanel* User::GetInventory(){
	return inventory;
}
void User::SetEquiped(EquipedPanel* equip){
	equiped = equip;
};
EquipedPanel* User::GetEquiped(){
	return equiped;
};
BankPanel* User::GetBank(){
	return bank;
}
LayeredPanel* User::GetLayered(){
	return layered;
};
void User::SetLevelPanel(LevelPanel* levelPanel){
	this->levelPanel = levelPanel;
};
LevelPanel* User::GetLevelPanel(){
	return levelPanel;
};
void User::SetUpImages(){
	for(int x = 0; x < 5; x++){
		std::vector<sf::IntRect> temp;
		for(int y = 0; y < 4; y++){
			temp.push_back(GetTextureFromAtlas("userspritesheets/Slot" + std::to_string(x) + "/" + std::to_string(y) + ".png"));
		}
		itemSpriteSheets.push_back(temp);
	}

	sf::IntRect tempIntRect;
	tempIntRect = GetTextureFromAtlas("userspritesheets/body/light.png");
	animationSheets.push_back(tempIntRect);
	for(int x = 0; x < 5; x++){
		if(x != 1)
			animationSheets.push_back(Drawn::GetTextureFromAtlas("userspritesheets/" + std::to_string(x) + "/default.png"));
		if(x == 1)
			animationSheets.push_back(Drawn::GetTextureFromAtlas("userspritesheets/1/default.png"));
	}
};
void User::SetUpAttacks(std::string attackSetName){
	attacks.clear();
	currentAttacks.clear();
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("xml/actionInfo.xml");
	pugi::xml_node atlas = doc.child("Actions");
	pugi::xml_node attackSet;
	for(pugi::xml_node tool = atlas.first_child(); tool; tool = tool.next_sibling()){
		if(tool.first_attribute().value() == attackSetName){
			for(pugi::xml_node tool2 = tool.first_child(); tool2; tool2 = tool2.next_sibling()){
				std::cout << "Setting up a new attack!" << std::endl;
				std::vector<sf::Vector2i> atkOffset;
				for(pugi::xml_node effectedTile = tool2.first_child(); effectedTile; effectedTile = effectedTile.next_sibling()){
					atkOffset.push_back(sf::Vector2i(effectedTile.attribute("direction").as_int(),effectedTile.attribute("distance").as_int()));
				}
				AddAttack(new Attack(tool2.attribute("name").value(),tool2.attribute("damageMult").as_double(),atkOffset,tool2.attribute("cooldown").as_double(),0,0));
				currentAttacks.push_back(tool2.attribute("name").value());
			}
			break;
		}
	}
};
bool User::GetIsAnyKeyPressed(){
			if((sf::Keyboard::isKeyPressed(sf::Keyboard::D)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::W)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::A)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::S))){
				return false;
			}
			else
				return true;
};
void User::CheckUserInput(){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::C) && User::player->GetCurrentDirection() == User::player->None){
			if(!cKeyPressed){
				cKeyPressed = true;
				Interact();
			}
		}
		else
			if(cKeyPressed){
				cKeyPressed = false;
			}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && User::player->GetCurrentDirection() == User::player->None && currentAction == NoAction){
			TryLaunchAttack(currentAttacks[0]);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && User::player->GetCurrentDirection() == User::player->None && currentAction == NoAction){
			TryLaunchAttack(currentAttacks[1]);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && User::player->GetCurrentDirection() == User::player->None && currentAction == NoAction){
			TryLaunchAttack(currentAttacks[2]);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			if(!wKeyPressed){
				SetCurrentKey(sf::Keyboard::W);
				wKeyPressed = true;
			}
		}
		else
			if(wKeyPressed){
				wKeyPressed = false;
				RemoveKey(sf::Keyboard::W);
			}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			if(!aKeyPressed){
				SetCurrentKey(sf::Keyboard::A);
				aKeyPressed = true;
			}
		}
		else
			if(aKeyPressed){
				aKeyPressed = false;
				RemoveKey(sf::Keyboard::A);
			}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			if(!sKeyPressed){
				SetCurrentKey(sf::Keyboard::S);
				sKeyPressed = true;
			}
		}
		else
			if(sKeyPressed){
				sKeyPressed = false;
				RemoveKey(sf::Keyboard::S);
			}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			if(!dKeyPressed){
				SetCurrentKey(sf::Keyboard::D);
				dKeyPressed = true;
			}
		}
		else
			if(dKeyPressed){
				dKeyPressed = false;
				RemoveKey(sf::Keyboard::D);
			}
};
void User::SetCurrentKey(sf::Keyboard::Key newKey){
	backupKey = currentKey;
	currentKey = newKey;
};
void User::RemoveKey(sf::Keyboard::Key removeKey){
	if(removeKey == backupKey){
		backupKey = sf::Keyboard::F12;
	}
	if(removeKey == currentKey){
		currentKey = backupKey;
		backupKey = sf::Keyboard::F12;
	}
}
void User::OnActionComplete(Actions action){
	switch(action){
	case(Attacking):{

					}
					break;
	}
	currentDirection = None;
	currentAction = NoAction;
	SetAnimation(animations["Walk"],currentAnimationDir);
};
void User::LaunchAction(Actions action){
	currentDirection = Action;
	switch(action){
	case(Attacking):{
		LaunchAttack(nextAttack);
		SetAnimation(animations[((EquipedContainer*)equiped->dynamicElements["1"])->GetContents().GetAnimation()],currentAnimationDir);
					}
					break;

	}
};
sf::Vector2i User::GetTailPoint(){
	return tailPoint;
};
void User::ChangeEquiped(Item* item){
	animationSheets[item->GetSlot() + 1] = Drawn::GetTextureFromAtlas("userspritesheets/" + item->imageName);
};
void User::RemoveEquipment(int slot){
	animationSheets[slot + 1] = Drawn::GetTextureFromAtlas("userspritesheets/" + std::to_string(slot) + "/default.png");
}
void User::CalculateLevelData(std::string levelName){
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("xml/userInfo.xml");
	pugi::xml_node atlas = doc.child("User").child("LevelInfo");
	pugi::xml_node level;
	for(pugi::xml_node tool = atlas.first_child(); tool; tool = tool.next_sibling()){
		if(tool.first_attribute().value() == levelName){
			level = tool;
			break;
		}
	}
	std::cout << "Calculating" << std::endl;
	int totalXPTemp = std::stoi(level.attribute("totalXP").value());
    int beginLevel = std::floor(std::pow((totalXPTemp / 4),0.4));
    level.attribute("level").set_value(beginLevel);
	int minXPForCurrentLevel = 4*(std::pow(beginLevel,2.5));
	int maxXPForCurrentLevel = 4*(std::pow(beginLevel + 1,2.5));
	int remainingXP = maxXPForCurrentLevel - totalXPTemp;
    level.attribute("maxXPForNextLevel").set_value(maxXPForCurrentLevel);
	level.attribute("xpPastCurrentLevel").set_value(totalXPTemp - minXPForCurrentLevel);
    level.attribute("xpToNextLevel").set_value(remainingXP);
	level.attribute("percent").set_value((int)(((float)totalXPTemp / ((float)maxXPForCurrentLevel))*100));
	doc.save_file("xml/userInfo.xml");
};
void User::CalculateLevelData(std::string levelName,std::string subLevelName){
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("xml/userInfo.xml");
	pugi::xml_node atlas = doc.child("User").child("LevelInfo");
	pugi::xml_node level;
	for(pugi::xml_node tool = atlas.first_child(); tool; tool = tool.next_sibling()){
		if(tool.first_attribute().value() == levelName){
			for(pugi::xml_node tool2 = tool.first_child(); tool2; tool2 = tool2.next_sibling()){
				if(tool2.first_attribute().value() == subLevelName){
					level = tool2;
					break;
				}
			}
			break;
		}
	}//40x2 + 360x = nextLevelXP
	//
	std::cout << "Calculating" << std::endl;
	int totalXPTemp = std::stoi(level.attribute("totalXP").value());
    int beginLevel = std::floor(std::pow((totalXPTemp / 4),0.4));
    level.attribute("level").set_value(beginLevel);
	int minXPForCurrentLevel = 4*(std::pow(beginLevel,2.5));
	int maxXPForCurrentLevel = 4*(std::pow(beginLevel + 1,2.5));
	int remainingXP = maxXPForCurrentLevel - totalXPTemp;
    level.attribute("maxXPForNextLevel").set_value(maxXPForCurrentLevel);
	level.attribute("xpPastCurrentLevel").set_value(totalXPTemp - minXPForCurrentLevel);
    level.attribute("xpToNextLevel").set_value(remainingXP);
	level.attribute("percent").set_value((int)(((float)totalXPTemp / ((float)maxXPForCurrentLevel))*100));
	if(std::stoi(level.attribute("level").value()) > beginLevel){
		UpdateUnlockables(levelName,subLevelName);
		StatsPanel::instance->doUpdate = true;
	}
	//level.attribute("unlockXP").set_value(std::floor(4 * std::pow(std::stoi(level.find_child_by_attribute("nextUnlock",level.attribute("nextUnlock").value()).attribute("level").value()), 2.5f)));
	doc.save_file("xml/userInfo.xml");
};
void User::UpdateUnlockables(std::string levelName, std::string subLevelName){
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("xml/userInfo.xml");
	pugi::xml_node atlas = doc.child("User").child("LevelInfo");
	pugi::xml_node level;
	for(pugi::xml_node tool = atlas.first_child(); tool; tool = tool.next_sibling()){
		if(tool.first_attribute().value() == levelName){
			for(pugi::xml_node tool2 = tool.first_child(); tool2; tool2 = tool2.next_sibling()){
				if(tool2.first_attribute().value() == subLevelName){
					level = tool2;
					break;
				}
			}
			break;
		}
	}
	for(pugi::xml_node tool = level.first_child(); tool; tool = tool.next_sibling()){
		if(std::stoi(level.attribute("level").value()) >= std::stoi(tool.attribute("level").value())){
			(doc.child("User").child("UnlockableAbilities").find_child_by_attribute("name",tool.attribute("unlock").value())).attribute("value").set_value(std::stoi(doc.child("User").child("UnlockableAbilities").find_child_by_attribute("name", tool.attribute("unlock").value()).attribute("value").value()) + std::stoi(tool.attribute("value").value()));
		}
		else {
			level.attribute("nextUnlock").set_value(tool.attribute("name").value());
			break;
		}
	}
	doc.save_file("xml/userInfo.xml");
};
void User::AddExperience(std::string levelName, std::string subLevelString, int add){
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("xml/userInfo.xml");
	pugi::xml_node atlas = doc.child("User").child("LevelInfo");
	pugi::xml_node level;
	pugi::xml_node subLevel;
	for(pugi::xml_node tool = atlas.first_child(); tool; tool = tool.next_sibling()){
		if(tool.first_attribute().value() == levelName){
			level = tool;
			for(pugi::xml_node tool2 = tool.first_child(); tool2; tool2 = tool2.next_sibling()){
				if(tool2.first_attribute().value() == subLevelString){
					subLevel = tool2;
					break;
				}
			}
			break;
		}
	}
	if(std::stoi(level.attribute("spendXP").value()) > 0){
		level.attribute("totalXP").set_value(std::stoi(level.attribute("totalXP").value()) + add);
		level.attribute("spendXP").set_value(std::stoi(level.attribute("spendXP").value()) - add);
		subLevel.attribute("totalXP").set_value(std::stoi(subLevel.attribute("totalXP").value()) + add);
	}
	doc.save_file("xml/userInfo.xml");
	CalculateLevelData(levelName);
	CalculateLevelData(levelName,subLevelString);
};
void User::AddSpendExperience(std::string levelName, int add){
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("xml/userInfo.xml");
	pugi::xml_node atlas = doc.child("User").child("LevelInfo");
	pugi::xml_node level;
	for(pugi::xml_node tool = atlas.first_child(); tool; tool = tool.next_sibling()){
		if(tool.first_attribute().value() == levelName){
			level = tool;
			break;
		}
	}
	level.attribute("spendXP").set_value(std::stoi(level.attribute("spendXP").value()) + add);
	doc.save_file("xml/userInfo.xml");
};
int User::GetUserData(std::string levelName, std::string subLevelName, std::string attributeName){
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("xml/userInfo.xml");
	pugi::xml_node atlas = doc.child("User").child("LevelInfo");
	pugi::xml_node level;
	pugi::xml_node subLevel;
	for(pugi::xml_node tool = atlas.first_child(); tool; tool = tool.next_sibling()){
		if(tool.first_attribute().value() == levelName){
			level = tool;
			for(pugi::xml_node tool2 = tool.first_child(); tool2; tool2 = tool2.next_sibling()){
				if(tool2.first_attribute().value() == subLevelName){
					subLevel = tool2;
					break;
				}
			}
			break;
		}
	}
	for(pugi::xml_attribute tool = subLevel.first_attribute(); tool; tool = tool.next_attribute()){
		if(tool.name() == attributeName)
			return std::stoi(tool.value());
	}
};

int User::GetUserData(std::string levelName,std::string attributeName){
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("xml/userInfo.xml");
	pugi::xml_node atlas = doc.child("User").child("LevelInfo");
	pugi::xml_node level;
	pugi::xml_node subLevel;
	for(pugi::xml_node tool = atlas.first_child(); tool; tool = tool.next_sibling()){
		if(tool.first_attribute().value() == levelName){
			level = tool;
			break;
		}
	}
	for(pugi::xml_attribute tool = level.first_attribute(); tool; tool = tool.next_attribute()){
		if(tool.name() == attributeName)
			return std::stoi(tool.value());
	}
};
void User::SetUpLevels(){
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("xml/userInfo.xml");
	pugi::xml_node atlas = doc.child("User").child("LevelInfo");
	pugi::xml_node level;
	pugi::xml_node subLevel;
	for(pugi::xml_node tool = atlas.first_child(); tool; tool = tool.next_sibling()){
		CalculateLevelData(tool.attribute("name").value());
			for(pugi::xml_node tool2 = tool.first_child(); tool2; tool2 = tool2.next_sibling()){
				CalculateLevelData(tool.attribute("name").value(),tool2.attribute("name").value());
				UpdateUnlockables(tool.attribute("name").value(),tool2.attribute("name").value());
			}
	}
};
std::string User::GetQuestData(std::string questName,std::string attrib){
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("xml/questInfo.xml");
	pugi::xml_node atlas = doc.child("QuestLog");
	pugi::xml_node quest;
	pugi::xml_node subLevel;
	for(pugi::xml_node tool = atlas.first_child(); tool; tool = tool.next_sibling()){
		if(tool.first_attribute().value() == questName){
			quest = tool;
			break;
		}
	}
	for(pugi::xml_attribute tool = quest.first_attribute(); tool; tool = tool.next_attribute()){
		if(tool.name() == attrib)
			return tool.value();
	}
};
void User::UpdateQuest(std::string targetName){
	std::cout << "Updateing Quest: " + targetName << std::endl;
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("xml/questInfo.xml");
	pugi::xml_node questLog = doc.child("QuestLog");
	//What is this monstrosity.... what have i DONE!?!
	//I call it... THE RAPE LOOP! A TRIPPLE FOR LOOP WITH 4 IF STATEMENTS muahahahahahah.
	for(pugi::xml_node quest = questLog.first_child(); quest; quest = quest.next_sibling()){
		for(pugi::xml_node objective = quest.first_child().first_child(); objective; objective = objective.next_sibling()){
			if(0 == ((std::string)objective.attribute("name").as_string()).compare((std::string)quest.attribute("currentObjective").as_string())){//objective.attribute("status").value() == "incomplete" && 
				std::cout << "Found the current objective." << std::endl;
				for(pugi::xml_node requirement = objective.first_child(); requirement; requirement = requirement.next_sibling()){
					if(requirement.attribute("targetName").value() == targetName){
						std::cout << "You finished a requirement (or a portion of one.)" << std::endl;
						requirement.attribute("requiredValue").set_value((std::stoi(requirement.attribute("requiredValue").value()) - 1));
						if(std::stoi(requirement.attribute("requiredValue").value()) <= 0){
							std::cout << "You ACTUALLY finished a requirement!" << std::endl;
							objective.attribute("status").set_value("complete");
							if(objective.next_sibling() != NULL)
								quest.attribute("currentObjective").set_value(objective.next_sibling().attribute("name").value());
							else{
								quest.attribute("status").set_value("complete");
								quest.attribute("currentObjective").set_value("none");
								for(pugi::xml_node reward = quest.first_child().next_sibling().first_child(); reward; reward = reward.next_sibling()){
									if(!((std::string)reward.attribute("xpLevel").value()).empty())
										User::player->AddSpendExperience(reward.attribute("xpLevel").value(),reward.attribute("xpLevelAmount").as_int());
									if(!((std::string)reward.attribute("xpSubLevel").value()).empty())
										User::player->AddExperience(reward.attribute("xpLevel").value(),reward.attribute("xpSubLevel").value(),reward.attribute("xpSubLevelAmount").as_int());
									if(!((std::string)reward.attribute("item").value()).empty())
										User::player->GetInventory()->Add(Item(reward.attribute("item").as_int()));
								}
							}
						}
					}
				}
			break;
			}
			else{
				std::cout << "Current Objective:" << (quest.attribute("currentObjective").as_string()) << ": Objective Name:" << objective.attribute("name").as_string() << ":" << std::endl;
			}
		};
	}
	doc.save_file("xml/questInfo.xml");
};
void User::ResetXMLDocs(){
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file("xml/userInfoBackup.xml");
		doc.save_file("xml/userInfo.xml");
		pugi::xml_document doc2;
		pugi::xml_parse_result result2 = doc2.load_file("xml/questInfoBackup.xml");
		doc2.save_file("xml/questInfo.xml");
};
