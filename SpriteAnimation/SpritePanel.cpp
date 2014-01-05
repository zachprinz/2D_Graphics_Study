#include "SpritePanel.h"
#include "GroundItem.h"
#include <iostream>
#include <MapLoader.h>
#include "Enemy.h"
#include "NPC.h"
#include "User.h"
#include "AmbienceObject.h"
#include "LightObject.h"
#include "Game.h"
#include "Thor/Config.hpp"
#include "Thor\Graphics.hpp"
#include "Thor\Resources.hpp"
#include "Thor/Math.hpp"
#include <assert.h>

sf::Texture* SpritePanel::spritePanelBackground = new sf::Texture();
SpritePanel* SpritePanel::instance = new SpritePanel();
Room* SpritePanel::room = new Room();


SpritePanel::SpritePanel(int x, int y) : GamePanel(x,y,"Game"){
	panelScale = sf::Vector2f(1,1);
	cameraMoveSpeed = 0;
	isShaking = false;
	ml = new tmx::MapLoader("maps/");
	ml->Load("testNew.tmx");
	view.reset(sf::FloatRect(0,0,Game::resolution.x,Game::resolution.y));
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
	sf::Vector2f cameraOffset(100,70);
	view.setCenter(User::player->GetSprite()->getPosition() + cameraOffset);
	
	// Particle System Test //
	
	particleTexture.loadFromFile("Images\particle.png");
	particleSystem.setTexture(particleTexture);
	emitter.setEmissionRate(30);
	emitter.setParticleLifetime(sf::seconds(4));
	emitter.setParticleScale(sf::Vector2f(1,1));
	emitter.setParticlePosition(User::player->GetPosition());
	//emitter.setParticlePosition( thor::Distributions::circle(User::player->GetPosition(), 2));   // Emit particles in given circle
	particleSystem.addEmitter(emitter);
	//thor::ScaleAffector sizeAffector(sf::Vector2f(1,1));
	//particleSystem.addAffector(sizeAffector);
	//sf::Vector2f acceleration(0.f, 10.f);
	//thor::ForceAffector gravityAffector(acceleration);
	//particleSystem.addAffector(gravityAffector);
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
	panel.setView(view);
	panel.draw(mapSprite);
	((Combatant*)(User::player))->UpdateEffectedTiles((GamePanel*)this);
	Actor::elapsedTime = Actor::elapsedTimeClock->getElapsedTime();
	Actor::elapsedTimeClock->restart();
	GamePanel::UpdateElements();
	User::player->Update((GamePanel*)this);
	for(int x = 0; x < combatants.size(); x++){
		((Combatant*)dynamicElements[combatants[x]])->UpdateBar(this);
	}
	lightEngine->SetView(view);
	for(int x = 0; x < AmbienceObject::tags.size(); x++){
		((AmbienceObject*)dynamicElements["AmbienceObject" + AmbienceObject::tags[x]])->Update2(this); //TODO Very Laggy
	}
	MoveCamera();
	User::player->UpdateBar(this);
    	particleSystem.update(particleClock.restart());
	if(!isZooming){
		lightEngine->DrawLights(&panel);
		panel.draw(particleSystem);
	}
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
void SpritePanel::MoveCamera(){
	sf::Vector2f cameraOffset(100,70);
	if(!isShaking){
		if(std::abs(view.getCenter().x - (User::player->GetPosition().x + cameraOffset.x)) < 5 &&
		   std::abs(view.getCenter().y - (User::player->GetPosition().y + cameraOffset.y)) < 5){
			isCameraCaughtUp = true;
			cameraMoveSpeed = 0.0;
		}
		else{
			isCameraCaughtUp = false;
			if(cameraMoveSpeed != 100)
				cameraMoveSpeed += (100-cameraMoveSpeed) * 0.075f;
			sf::Vector2f tempVec = User::player->GetPosition() + cameraOffset - view.getCenter();
			tempVec = sf::Vector2f(std::abs(tempVec.x),std::abs(tempVec.y));
			float tempHyp = Actor::elapsedTime.asSeconds() * cameraMoveSpeed;
			if(tempHyp > std::sqrt(std::pow(tempVec.x,2.0f) + std::pow(tempVec.y,2.0f)))
				tempHyp = std::sqrt(std::pow(tempVec.x,2.0f) + std::pow(tempVec.y,2.0f));
			float tempAngle = std::atan(tempVec.y / tempVec.x);
			sf::Vector2f directionVec(1,1);
			if(view.getCenter().x > (User::player->GetPosition().x + cameraOffset.x))
				directionVec.x = -1;
			if(view.getCenter().y > (User::player->GetPosition().y + cameraOffset.y))
				directionVec.y = -1;
			sf::Vector2f moveToPoint = sf::Vector2f(directionVec.x * (std::cos(tempAngle) * tempHyp),directionVec.y * (std::sin(tempAngle) * tempHyp));
			view.setCenter(view.getCenter() + moveToPoint);
		}
	}
	if(isShaking){
		float tempAmplitude = shakeAmplitude;
		if(InterpolateShake()){
			if(shakeCount < (shakeOffsetsY.size() / 2)){
				if(!shakeOdd){
					targetPosition.y = User::player->GetPosition().y + (shakeOffsetsX[shakeOffsetsX.size() - 1 - shakeCount]);
					targetPosition.x = User::player->GetPosition().x + shakeOffsetsY[shakeCount];
				}
				else{
					targetPosition.x = User::player->GetPosition().x + shakeOffsetsX[shakeOffsetsX.size() - 1 - shakeCount];
					targetPosition.y = User::player->GetPosition().y + shakeOffsetsY[shakeCount];
					shakeCount++;
				}
				if(shakeOdd)
					shakeOdd = false;
				else
					shakeOdd = true;
				InterpolateShake();
			}
			else
				isShaking = false;
		}
	}
};
void SpritePanel::MoveCameraTo(sf::Vector2f pos,float speed){

};
void SpritePanel::ShakeScreen(float amplitude, float timeSeconds){
	if(!isShaking){
		shakeOdd = false;
		shakeCount = 0;
		isShaking = true;
		shakeAmplitude = amplitude;
		shakeTime = timeSeconds;
		shakeClock.restart();
		targetPosition = view.getCenter();
		int sampleCount = (timeSeconds) * 16;
		shakeOffsetsX = std::vector<double>();
		shakeOffsetsY = std::vector<double>();
		for(int x = 0; x < 16; x++){
			shakeOffsetsX.push_back(amplitude * FindNoise());
			shakeOffsetsY.push_back(amplitude * FindNoise());
		}
		std::sort(shakeOffsetsX.begin(), shakeOffsetsX.end());
		std::sort(shakeOffsetsY.begin(), shakeOffsetsY.end());
		for(int x = 0; x < 16 / 3; x++){
			shakeOffsetsX[abs(std::ceil((std::abs(FindNoise()) * 10.0) * 1.5))] = amplitude * FindNoise();
			shakeOffsetsY[abs(std::ceil((std::abs(FindNoise()) * 10.0) * 1.5))] = amplitude * FindNoise();
		}
		for(int x = 0; x < shakeOffsetsX.size(); x++){
			std::cout << "X: " << std::to_string(shakeOffsetsX[x]) << " Y: " << std::to_string(shakeOffsetsY[x]) << std::endl;
		}
		InterpolateShake();
	}
};
double SpritePanel::FindNoise(){
	double x = std::rand();
	int n=(int)x*57;
	n=(n<<13)^n;
	int nn=(n*(n*n*60493+19990303)+1376312589)&0x7fffffff;
	double ret = 1.0-((double)nn/1073741824.0);
	return ret;
};
bool SpritePanel::InterpolateShake(){
	float tempTime = shakeClock.restart().asSeconds();
	if(std::abs(targetPosition.x - view.getCenter().x) < 6 && std::abs(targetPosition.y - view.getCenter().y) < 6){
		return true;
	}
	if(tempTime > 0.05)
		tempTime = 0.015;
	std::cout << "Time: " << std::to_string(tempTime) << std::endl;
	sf::Vector2f delta;
	delta.x = (targetPosition.x - view.getCenter().x);
	delta.x = delta.x * (0.25 * tempTime * 5);
	delta.y = (targetPosition.y - view.getCenter().y);
	delta.y = delta.y * (0.25 * tempTime * 5);
	while(std::abs(delta.x) < (3 * (1 - (shakeCount / 16))) + 1)
		delta.x *= 2;
	while(std::abs(delta.y) < (3 * (1 - (shakeCount / 16))) + 1)
		delta.y *= 2;
	view.setCenter(view.getCenter() + delta);
	return false;
};