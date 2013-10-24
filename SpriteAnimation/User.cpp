#include <SFML/Graphics.hpp>
#include "User.h"
#include <iostream>
#include "SpritePanel.h"
#include <iterator>
#include <vector>
#include "Attack.h"

User* User::player;

User::User(int x, int y) : Combatant(x,y,"User","User"){
	User::player = this;
	sprite.setScale(0.85f,0.65f);
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
	SetUpAttacks();
	SetUpAnimations();
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
	UpdateUnlockables("technique","weaponTypes");
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
	DrawUser(&window);
};
void User::DrawUser(sf::RenderTexture* window){
	sprite.setPosition(sprite.getPosition().x - 11.2, sprite.getPosition().y - 9.6);
	for(int x = 0; x < animationSheets.size(); x++){
		sprite.setTextureRect(sf::IntRect(animationSheets[x].left + (currentAnimationPos.x * 64),animationSheets[x].top + (currentAnimationPos.y * 64),64,64));
		window->draw(sprite);
	}
	sprite.setPosition(sprite.getPosition().x + 11.2, sprite.getPosition().y + 9.6);
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
		animationSheets.push_back(itemSpriteSheets[x][2]);
	}
};
void User::SetUpAttacks(){
	std::vector<sf::Vector2i> atkOffset;
	atkOffset.push_back(sf::Vector2i(Attack::RelativeDirection::Forward,1));
	AddAttack(new Attack("One",1.f,atkOffset,1,0,0));
	currentAttacks.push_back("One");
	atkOffset.clear();
	atkOffset.push_back(sf::Vector2i(Attack::RelativeDirection::Forward,1));
	atkOffset.push_back(sf::Vector2i(Attack::RelativeDirection::Forward,2));
	AddAttack(new Attack("Two",1.f,atkOffset,3,0,0));
	currentAttacks.push_back("Two");
	atkOffset.clear();
	atkOffset.push_back(sf::Vector2i(Attack::RelativeDirection::Forward,1));
	atkOffset.push_back(sf::Vector2i(Attack::RelativeDirection::Left,1));
	atkOffset.push_back(sf::Vector2i(Attack::RelativeDirection::Right,1));
	AddAttack(new Attack("Three",1.f,atkOffset,6,0,0));
	currentAttacks.push_back("Three");
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
		SetAnimation(animations["Slash"],currentAnimationDir);
					}
					break;

	}
};
void User::SetUpAnimations(){
	AddAnimation(new Animation("Cast",0.05,7,64,0,2,1,3));
	AddAnimation(new Animation("Stab",0.05,8,64,4,6,5,7));
	AddAnimation(new Animation("Walk",0.04,9,64,8,10,9,11));
	AddAnimation(new Animation("Slash",0.05,6,64,12,14,13,15));
	AddAnimation(new Animation("Shoot",0.05,13,64,16,18,17,19));
	AddAnimation(new Animation("Die",0.075,6,64,20,20,20,20));
};
sf::Vector2i User::GetTailPoint(){
	return tailPoint;
};
void User::ChangeEquiped(int slot, int materialLevel){
	//if(slot < itemSpriteSheets.size() && materialLevel < itemSpriteSheets[slot].size())
		animationSheets[1 + slot] = itemSpriteSheets[slot][materialLevel];
};
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
    int a = std::stoi(level.attribute("totalXP").value()) / 4;
    float tempLevel = std::pow(a,(0.4f));
    level.attribute("level").set_value((int)std::floor(tempLevel));
    level.attribute("percent").set_value((int)((tempLevel - std::stoi(level.attribute("level").value())) * 100));
    int totalXPTemp = std::stoi(level.attribute("totalXP").value());
    for (int x = std::stoi(level.attribute("level").value()); x > 0; x--)
    {
        totalXPTemp -= (10 * ((int) std::sqrt(std::pow(x, 3)))) + 100;
    } 
    level.attribute("maxXPForNextLevel").set_value(10 * ((int)std::sqrt(std::pow(std::stoi(level.attribute("level").value()), 3)))) + 100;
    level.attribute("xpPastCurrentLevel").set_value(totalXPTemp);
    level.attribute("xpToNextLevel").set_value(std::stoi(level.attribute("maxXPForNextLevel").value()) - std::stoi(level.attribute("xpPastCurrentLevel").value()));
    level.attribute("level").set_value(std::stoi(level.attribute("totalXP").value()));
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
	}
	int beginLevel = std::stoi(level.attribute("level").value());
    int a = std::stoi(level.attribute("totalXP").value()) / 4;
    float tempLevel = std::pow(a,(0.4f));
    level.attribute("level").set_value((int)std::floor(tempLevel));
    level.attribute("percent").set_value((int)((tempLevel - std::stoi(level.attribute("level").value())) * 100));
    int totalXPTemp = std::stoi(level.attribute("totalXP").value());
    for (int x = std::stoi(level.attribute("level").value()); x > 0; x--)
    {
        totalXPTemp -= (10 * ((int) std::sqrt(std::pow(x, 3)))) + 100;
    }
    level.attribute("maxXPForNextLevel").set_value(10 * ((int)std::sqrt(std::pow(std::stoi(level.attribute("level").value()), 3)))) + 100;
    level.attribute("xpPastCurrentLevel").set_value(totalXPTemp);
    level.attribute("xpToNextLevel").set_value(std::stoi(level.attribute("maxXPForNextLevel").value()) - std::stoi(level.attribute("xpPastCurrentLevel").value()));
    //level.attribute("level").set_value(std::stoi(level.attribute("totalXP").value()));
	if(std::stoi(level.attribute("level").value()) > beginLevel){
		UpdateUnlockables(levelName,subLevelName);
	}
	level.attribute("unlockXP").set_value(std::floor(4 * std::pow(std::stoi(level.find_child_by_attribute("name",level.attribute("nextUnlock").value()).attribute("level").value()), 2.5f)));
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
	level.attribute("totalXP").set_value(std::stoi(level.attribute("totalXP").value()) + add);
	subLevel.attribute("totalXP").set_value(std::stoi(level.attribute("totalXP").value()) + add);
	CalculateLevelData(levelName,subLevelString);
	doc.save_file("xml/userInfo.xml");
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
		if(tool.value() == attributeName)
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
		if(tool.value() == attributeName)
			return std::stoi(tool.value());
	}
};