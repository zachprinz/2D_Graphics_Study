#ifndef USER_H
#define USER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Combatant.h"
#include "InventoryPanel.h"
#include "EquipedPanel.h"
#include "LayeredPanel.h"
#include "BankPanel.h"
#include "LevelPanel.h"

class User :  public Combatant
{
public:
	User(int,int);
	User();
	void Update(sf::RenderTexture&);
	void Interact();
	static User* player;
	std::vector<std::vector<sf::IntRect>> itemSpriteSheets;
	std::vector<std::vector<sf::IntRect>> baseSpriteSheets;
	void SetInventory(InventoryPanel*);
	LayeredPanel* GetLayered();
	InventoryPanel* GetInventory();
	void SetEquiped(EquipedPanel*);
	EquipedPanel* GetEquiped();
	void SetLevelPanel(LevelPanel*);
	LevelPanel* GetLevelPanel();
	BankPanel* GetBank();
	bool GetIsAnyKeyPressed();
	sf::Keyboard::Key currentKey;
	sf::Keyboard::Key backupKey;
	void SetCurrentKey(sf::Keyboard::Key);
	void RemoveKey(sf::Keyboard::Key);
	void CheckUserInput();
	void OnActionComplete(Actions);
	void LaunchAction(Actions);
	sf::Vector2i tailPoint;
	sf::Vector2i GetTailPoint();
	bool wKeyPressed;
	bool aKeyPressed;
	bool dKeyPressed;
	bool sKeyPressed;
	bool cKeyPressed;
	void ChangeEquiped(int slot, int materialLevel);
	void DrawUser(sf::RenderTexture*);
	//enum Levels {Strength,Technique,Endurance,Speed,Woodcutting,Crafting,Mining,Smithing};
	//enum SubLevels {
	void AddExperience(std::string,std::string,int);
	void AddSpendExperience(std::string,int);
	void UpdateUnlockables(std::string,std::string);
	int GetUserData(std::string, std::string, std::string);
	int GetUserData(std::string, std::string);
	std::string GetQuestData(std::string,std::string);
	void UpdateQuest(std::string);
	void ResetXMLDocs();
private:
	void CalculateLevelData(std::string);
	void CalculateLevelData(std::string,std::string);
	bool oversize;
	InventoryPanel* inventory;
	LayeredPanel* layered;
	EquipedPanel* equiped;
	BankPanel* bank;
	LevelPanel* levelPanel;
	void SetUpImages();
	void SetUpAttacks();
	void SetUpAnimations();
	void SetUpLevels();
	void GetUserWeaponImage(sf::RenderTexture*);
};
#endif