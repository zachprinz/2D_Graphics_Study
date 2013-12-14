#include "SpritePanel.h"
#include "GroundItem.h"
#include <iostream>
#include <MapLoader.h>
#include "Enemy.h"
#include "NPC.h"
#include "User.h"
#include "Bank.h"
#include "AmbienceObject.h"
#include "LightObject.h"
#include <assert.h>

sf::Texture* SpritePanel::spritePanelBackground = new sf::Texture();
SpritePanel* SpritePanel::instance = new SpritePanel();
Room* SpritePanel::room = new Room();


SpritePanel::SpritePanel(int x, int y) : GamePanel(x,y,"Game"){
	ml = new tmx::MapLoader("maps/");
    ml->Load("testNew.tmx");
	view.reset(sf::FloatRect(0,0,1526,922));
	view.setViewport(sf::FloatRect(0,0,1.0f,1.0f));
	panel.setView(view);
	std::cout << "Creating Light Engine." << std::endl;
	lightEngine = new LightEngine(AABB(Vec2f(0,0),Vec2f(4096,4096)),view,sf::Color(47,102,111,150));
	std::cout << "Finished Creating Lighting Engine." << std::endl;
	instance = this;
	SetUp();
	LoadMapCollisions();
	LoadMapAmbience();
	LoadMapSprites();
	mapTexture.loadFromFile("maps/testMap1.png");
	mapSprite.setTexture(mapTexture);
	isZooming = false;
	currentZoom = 1;
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
	std::cout << " Loading Map Collisions... ";
	for(int x = 0; x < objLayer->objects.size(); x++){
		sf::FloatRect rect = objLayer->objects[x].GetAABB();
		int yCor = (((int)rect.top) / 32);
		int xCor = (((int)rect.left) / 32);
		int xCor2 = (((int)(rect.left + rect.width - 1)) / 32);
		int yCor2 = (((int)(rect.height + rect.top - 1)) / 32);
		//std::cout << std::to_string(xCor) << "," << std::to_string(yCor) << " " << std::to_string(xCor2) << "," << std::to_string(yCor2) << std::endl;
		for(int y = xCor; y <= xCor2; y++){
			for(int z = yCor; z <= yCor2; z++){
				room->roomTiles[z][y].SetBlocked();
			}
		}
	}
	std::cout << "Done" << std::endl;
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
			SpawnItem(std::stoi(sprites->objects[x].GetPropertyString("id")),xCor,yCor,room);
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
		if(name == "NPC"){
			NPC* npc= new NPC(xCor,yCor,sprites->objects[x].GetPropertyString("name") + ".png", sprites->objects[x].GetPropertyString("name"));
			sf::FloatRect rect = sprites->objects[x].GetAABB();
			int xCor2 = (((int)(rect.left + rect.width - 1)) / 32);
			int yCor2 = (((int)(rect.height + rect.top - 1)) / 32);
			AddElement("NPC" + std::to_string(npc->GetTag()), npc);
			room->AddOcupant(npc);
			std::cout << "Created NPC at: "  + std::to_string(npc->GetGraphPositionA().x) + "," + std::to_string(npc->GetGraphPositionA().y) << std::endl;
		}
		if(name == "Bank"){
			Bank* bank = new Bank(xCor,yCor,"bank.png");
			AddElement("bank" + std::to_string(bank->GetTag()), bank);
			room->AddOcupant(bank);
		}
		if(name == "User"){
			User* user = new User(xCor,yCor);
			room->AddOcupant(user);
		}
		if(name == "Light"){
			yCor = (((int)sprites->objects[x].GetPosition().y - (int)std::stoi(sprites->objects[x].GetPropertyString("height"))) / 32);
			LightObject* lightObj = new LightObject(xCor,yCor,&sprites->objects[x]);
			AddElement("AmbienceObject" + std::to_string(lightObj->GetTag()), lightObj);
			room->AddOcupant(lightObj);
		}
	}
}
void SpritePanel::LoadMapAmbience(){
	std::vector<tmx::MapLayer> layers = ml->GetLayers();
	tmx::MapLayer* ambienceObjects;
	for(int x = 0; x < layers.size(); x++){
		if(layers[x].name == "ambience"){
			std::cout << " Loading Map Ambience " << std::to_string(layers[x].objects.size()) << std::endl;
			ambienceObjects = &layers[x];
			break;
		}
	}

	for(int x = 0; x < ambienceObjects->objects.size(); x++){
		std::string name = ambienceObjects->objects[x].GetType();
		int xCor = (((int)ambienceObjects->objects[x].GetPosition().x) / 32);
		int yCor = (((int)ambienceObjects->objects[x].GetPosition().y - (int)std::stoi(ambienceObjects->objects[x].GetPropertyString("height"))) / 32);
		sf::Texture tempText;
		if(name == "Ambience"){
			AmbienceObject* ambObj = new AmbienceObject(xCor,yCor,&ambienceObjects->objects[x]);
			AddElement("AmbienceObject" + std::to_string(ambObj->GetTag()), ambObj);
			room->AddOcupant(ambObj);
		}
	}
};
void SpritePanel::UpdateElements(){
	UpdateZoom();
	view.setCenter(sf::Vector2f(User::player->GetSprite()->getPosition().x,User::player->GetSprite()->getPosition().y));
	panel.setView(view);
	panel.draw(mapSprite);
	//Drawn tempDrawn("aim.png");
	//tempDrawn.GetSprite()->setOrigin(320,160);
	//tempDrawn.SetPosition(User::player->GetPosition() + sf::Vector2f(16,22));
	//tempDrawn.GetSprite()->rotate(90 + ((User::player->currentAnimationPos.y % 4) * -90));
	//tempDrawn.Draw(this);
	((Combatant*)(User::player))->UpdateEffectedTiles((GamePanel*)this);
	Actor::elapsedTime = Actor::elapsedTimeClock->getElapsedTime();
	Actor::elapsedTimeClock->restart();
	GamePanel::UpdateElements();
	User::player->Update((GamePanel*)this);
	for(int x = 0; x < combatants.size(); x++){
		((Combatant*)dynamicElements[combatants[x]])->UpdateBar(this);
	}
	lightEngine->SetView(view);
	if(!isZooming)
		lightEngine->DrawLights(&panel);
	for(int x = 0; x < AmbienceObject::tags.size(); x++){
		((AmbienceObject*)dynamicElements["AmbienceObject" + AmbienceObject::tags[x]])->Update2(this); //TODO Very Laggy
	}
	User::player->UpdateBar(this);
	panel.display();
	//lightEngine->DrawHigh(&panel);
	//lightEngine->DebugRender(&panel);
}
void SpritePanel::AddElement(std::string name, Drawn* element){
	dynamicElements.insert(MyPair(name, element));
};
void SpritePanel::SetUp(){
	GamePanel::SetUp();
}
void SpritePanel::SpawnItem(int id,int x,int y,Room* room){
	Item tempItem(id);
	std::cout << tempItem.GetId() << " Spawned at: " << x << ", " << y << std::endl;
	GroundItem* tempPoints = new GroundItem(x,y,tempItem);
	room->AddOcupant(tempPoints);
	AddElement(std::to_string(tempPoints->GetTag()),tempPoints);
};
void SpritePanel::MoveCamera(float x, float y){
	view.reset(sf::FloatRect(view.getViewport().left + x,view.getViewport().top + y,512,512));
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
void SpritePanel::AddHull(Hull* hull){
	lightEngine->AddHull(hull);
};
void SpritePanel::AddLight(Light* light){
	lightEngine->AddLight(light);
};
void SpritePanel::Zoom(float time, float zoomFactor){
	if(!isZooming){
		zoomPerSecond = abs(currentZoom - zoomFactor) / time;
		zoomDirection = -1;
		targetZoom = zoomFactor;
		zoomClock.restart();
		isZooming = true;
	}
};
void SpritePanel::UpdateZoom(){
	if(isZooming){
		float zoomAmount = zoomPerSecond * zoomClock.restart().asSeconds() * zoomDirection;
		if(zoomDirection > 0){
			if(currentZoom + zoomAmount < targetZoom){
				view.zoom((1.0/currentZoom));
				view.zoom(currentZoom + zoomAmount);
				currentZoom = currentZoom + zoomAmount;
			}
			else{
				view.zoom((1.0/currentZoom));
				view.zoom(targetZoom);
				currentZoom = targetZoom;
				isZooming = false;
			}
		}
		else{
			if(currentZoom + zoomAmount > targetZoom){
				view.zoom((1.0/currentZoom));
				view.zoom(currentZoom + zoomAmount);
				currentZoom = currentZoom + zoomAmount;
			}
			else{
				view.zoom((1.0/currentZoom));
				view.zoom(targetZoom);
				currentZoom = targetZoom;
				isZooming = false;
				ReturnZoom();
				Clock::ReturnTime();
			}
		}
	}
};
void SpritePanel::ReturnZoom(){
	zoomPerSecond = abs(1 - currentZoom) / 0.5;
	zoomDirection = 1;
	targetZoom = 1;
	zoomClock.restart();
	isZooming = true;
};
sf::Vector2f SpritePanel::GetViewLowerBound(){
	//sf::Vector2f temp = sf::Vector2f(panel.getDefaultView().getSize() - view.getSize());
	return (sf::Vector2f(view.getCenter() - sf::Vector2f(panel.getDefaultView().getSize().x / 2, panel.getDefaultView().getSize().y / 2.0)));// - sf::Vector2f(temp.x / 2.0,temp.y / 2.0));
}