#include "SpritePanel.h"
#include "GroundItem.h"
#include <iostream>
#include "SlicedSpriteCreator.h"
#include <MapLoader.h>
#include "Enemy.h"
#include "User.h"
#include "Bank.h"

sf::Texture* SpritePanel::spritePanelBackground = new sf::Texture();
SpritePanel* SpritePanel::instance = new SpritePanel();
Room* SpritePanel::room = new Room();


SpritePanel::SpritePanel(int x, int y) : GamePanel(x,y,"Game"){
	ml = new tmx::MapLoader("maps/");
    ml->Load("test.tmx");
	for(int x = 0; x < ml->GetLayers().size(); x++){
		if(ml->GetLayers()[x].name == "objects2" || ml->GetLayers()[x].name == "objects3")
			highLayers.push_back(&ml->GetLayers()[x]);
		else
			otherLayers.push_back(&ml->GetLayers()[x]);
	}
	view.reset(sf::FloatRect(0,0,1024,800));
	view.setViewport(sf::FloatRect(0,0,1.0f,1.0f));
	panel.setView(view);
	drawCollision = false; //true;
	instance = this;
	createPanelLabel = false;
	SetUp();
	LoadMapCollisions();
	LoadMapSprites();
};
SpritePanel::SpritePanel(){

}
void SpritePanel::LoadMapCollisions(){
	std::vector<tmx::MapLayer> layers = ml->GetLayers();
	tmx::MapLayer* objLayer;
	for(int x = 0; x < layers.size(); x++){
		if(layers[x].name == "objects"){
			objLayer = &layers[x];
			break;
		}
	}
	std::cout << " Loading Map Collisions " << std::endl;
	for(int x = 0; x < objLayer->objects.size(); x++){
		sf::FloatRect rect = objLayer->objects[x].GetAABB();
		int yCor = (((int)rect.top) / 32);
		int xCor = (((int)rect.left) / 32);
		int xCor2 = (((int)(rect.left + rect.width - 1)) / 32);
		int yCor2 = (((int)(rect.height + rect.top - 1)) / 32);
		std::cout << std::to_string(xCor) << "," << std::to_string(yCor) << " " << std::to_string(xCor2) << "," << std::to_string(yCor2) << std::endl;
		for(int y = xCor; y <= xCor2; y++){
			for(int z = yCor; z <= yCor2; z++){
				room->roomTiles[z][y].SetBlocked();
			}
		}
	}
};
void SpritePanel::LoadMapSprites(){
	std::vector<tmx::MapLayer> layers = ml->GetLayers();
	tmx::MapLayer* sprites;
	for(int x = 0; x < layers.size(); x++){
		if(layers[x].name == "sprites"){
			std::cout << " Loading Map Sprites " << std::to_string(layers[x].objects.size()) << std::endl;
			sprites = &layers[x];
			break;
		}
	}
	for(int x = 0; x < sprites->objects.size(); x++){
		std::string name = sprites->objects[x].GetType();
		int xCor = (((int)sprites->objects[x].GetPosition().x) / 32);
		int yCor = (((int)sprites->objects[x].GetPosition().y) / 32);
		sf::Texture tempText;
		if(name == "Item"){
			SpawnItem(sprites->objects[x].GetPropertyString("id"),xCor,yCor,room);
		}
		if(name == "Enemy"){
			Enemy* enemy = new Enemy(xCor,yCor,sprites->objects[x].GetPropertyString("name") + ".png", sprites->objects[x].GetPropertyString("name"));
			sf::FloatRect rect = sprites->objects[x].GetAABB();
			int xCor2 = (((int)(rect.left + rect.width - 1)) / 32);
			int yCor2 = (((int)(rect.height + rect.top - 1)) / 32);
			enemy->AddPatrolPoint(sf::Vector2i(xCor,yCor));
			enemy->AddPatrolPoint(sf::Vector2i(xCor2,yCor));
			enemy->AddPatrolPoint(sf::Vector2i(xCor2,yCor2));
			enemy->AddPatrolPoint(sf::Vector2i(xCor,yCor2));
			AddElement("enemy" + std::to_string(enemy->GetTag()), enemy);
			combatants.push_back("enemy" + std::to_string(enemy->GetTag()));
			room->AddOcupant(enemy);
			std::cout << "Created Enemy at: "  + std::to_string(enemy->GetGraphPositionA().x) + "," + std::to_string(enemy->GetGraphPositionA().y) << std::endl;
		}
		if(name == "Bank"){
			Bank* bank = new Bank(xCor,yCor,"bank.png");
			AddElement("bank" + std::to_string(bank->GetTag()), bank);
			room->AddOcupant(bank);
		}
		if(name == "User"){
			User* user = new User(xCor,yCor);
			//AddElement("user",user);
			room->AddOcupant(user);
		}
	}
}
void SpritePanel::UpdateElements(){
	view.setCenter(sf::Vector2f(User::player->GetSprite()->getPosition().x,User::player->GetSprite()->getPosition().y));
	panel.setView(view);
	SetHighObjectsInvisible();
	ml->Draw(panel);
	((Combatant*)(User::player))->UpdateEffectedTiles(panel);
	Actor::elapsedTime = Actor::elapsedTimeClock.restart();
	GamePanel::UpdateElements();
	User::player->Update(panel);
	SetHighObjectsVisible();
	ml->Draw(panel);
	for(int x = 0; x < combatants.size(); x++){
		((Combatant*)dynamicElements[combatants[x]])->UpdateBar(panel);
	}
	User::player->UpdateBar(panel);
	SetLowObjectsVisible();
}
void SpritePanel::AddElement(std::string name, Drawn* element){
	dynamicElements.insert(MyPair(name, element));
};
void SpritePanel::SetUp(){
	GamePanel::SetUp();
}
void SpritePanel::SpawnItem(std::string id,int x,int y,Room* room){
	Item tempItem(id);
	std::cout << tempItem.GetId() << " Spawned at: " << x << ", " << y << std::endl;
	GroundItem* tempPoints = new GroundItem(x,y,tempItem);
	room->AddOcupant(tempPoints);
	AddElement(std::to_string(tempPoints->GetTag()),tempPoints);
	for(MyPair x: dynamicElements){
		std::cout << x.first << std::endl;
	}
};
void SpritePanel::MoveCamera(float x, float y){
	view.reset(sf::FloatRect(view.getViewport().left + x,view.getViewport().top + y,512,512));
};
void SpritePanel::SetHighObjectsVisible(){
	for(int x = 0; x < otherLayers.size(); x++){
		otherLayers[x]->visible = false;
	}
	for(int x = 0; x < highLayers.size(); x++){
		highLayers[x]->visible = true;
	}
};
void SpritePanel::SetHighObjectsInvisible(){
	for(int x = 0; x < highLayers.size(); x++){
		highLayers[x]->visible = false;
	}
};
void SpritePanel::SetLowObjectsVisible(){
	for(int x = 0; x < otherLayers.size(); x++){
		otherLayers[x]->visible = true;
	}
};
void SpritePanel::RemoveDynamicElement(std::string tag){
	room->RemoveOcupant(std::stoi(tag));
	for(int x = 0; x < combatants.size(); x++){
		if(combatants[x] == "enemy" + tag){
			combatants.erase(combatants.begin() + x);
			break;
		}
	}
	GamePanel::RemoveDynamicElement("enemy" + tag);
};
bool SpritePanel::CheckUpdate(){
	return true;
};