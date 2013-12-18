#include "Actor.h"
#include <iostream>
#include "SpritePanel.h"
#include "User.h"
#include "GamePanel.h"

Clock* Actor::elapsedTimeClock;
sf::Time Actor::elapsedTime;
std::vector<std::vector<std::vector<ShadowLine>>> Actor::footLines;
std::string Actor::anims[] = {"Slash","Stab","Cast","Shoot","Walk","Die"};


Actor::Actor(int x, int y,std::string name, std::string textureName) : GameSprite(x,y,textureName){
	isPaused = false;
	currentDirection = None;
	currentAnimationPos.x = 0;
	showHit = false;
	isVisible = true;
	this->name = name;
	currentAnimationPos.y = Animation::Down;
	movement = sf::Vector2i(0,0);
	currentAction = NoAction;
	boundriesResult = boundriesDoc.load_file("xml/lpcboundries.xml");
	boundriesNode = boundriesDoc.first_child();
	SetZ(2);
	SetUpAnimation();
	sprite.setScale(0.85f,0.65f);
	if(footLines.size() < 1){
		SetUpFootLines();
	}
	actorHull = new Hull(footLines[0][0][0],sprite.getPosition(),sprite.getGlobalBounds().height);
	texturePart.height = 64;
	texturePart.width = 64;
	SetRotation(0);
};
Actor::Actor(){

};
void Actor::MoveOnGrid(int x,int y){
	Drawn::MoveOnGrid(x,y);
};
void Actor::Move(float x,float y){
	Drawn::Move(x,y);
};
void Actor::SetCurrentDirection(Direction a){
	currentDirection = a;
};
Actor::Direction Actor::GetCurrentDirection(){
	return currentDirection;
};
sf::Vector2i Actor::GetMovement(){
	return movement;
};
void Actor::SetMovement(sf::Vector2i a){
	movement = a;
};
bool Actor::CheckTile(int x, int y){
	if(	y >= 0
		&& x >= 0
		&& y < SpritePanel::room->roomTiles.size() 
		&& x < SpritePanel::room->roomTiles[y].size()
		&& !SpritePanel::room->roomTiles[y][x].GetOcupied())
		return true;
	else
		return false;
};
bool Actor::SetRight(){
	if(currentDirection == None){
		SetAnimation(animations["Walk"],Animation::Right);
		movement.x = 1;
		movement.y = 0;
		if(CheckTile(graphPositionA.x + 1,graphPositionA.y)){
			currentDirection = R;
			return true;
		}
		else
			return false;
	}
};
bool Actor::SetLeft(){
	if(currentDirection == None){
		SetAnimation(animations["Walk"],Animation::Left);
		movement.x = -1;
		movement.y = 0;
		if(CheckTile(graphPositionA.x - 1,graphPositionA.y)){
			currentDirection = L;
			return true;
		}
		else
			return false;
	}
};
bool Actor::SetUp(){
	if(currentDirection == None){
		SetAnimation(animations["Walk"],Animation::Up);
		movement.x = 0;
		movement.y = -1;
		if(CheckTile(graphPositionA.x,graphPositionA.y - 1)){
			currentDirection = U;
			return true;
		}
		else
			return false;
	}
};
bool Actor::SetDown(){
	if(currentDirection == None){
		SetAnimation(animations["Walk"],Animation::Down);
		movement.x = 0;
		movement.y = 1;
		if(CheckTile(graphPositionA.x,graphPositionA.y + 1)){
			currentDirection = D;
			return true;
		}
		else
			return false;

	}
};
void Actor::Update(GamePanel* panel){
	UpdateEntity();
	if(isVisible){
		UpdateRoomTile();
		UpdateAction(panel, UpdateAnimation());
		for(int x = 0; x < boundries.size(); x++){
				boundries[x].setPosition(sf::Vector2f(GetSprite()->getPosition().x  + GetSprite()->getLocalBounds().width / 4,GetSprite()->getPosition().y  + GetSprite()->getLocalBounds().height / 4));
				boundries[x].setScale(0.85f,0.65f);
		}
	}
	GameSprite::Update(panel);
};
void Actor::UpdateEntity(){
	for(int b = 0; b < 2; b++){
		if(currentDirection == Finishing){
			int dir = 0;
			if(movement.x == -1 || movement.y == -1)
				dir = 0;
			if(movement.x == 1 || movement.y == 1)
				dir = 1;
			if(fmod(sprite.getPosition().x, 32) != 0 && fmod(sprite.getPosition().x,32) != 32){
				if(abs(movement.x * elapsedTime.asSeconds() * 50) > (abs((32*dir) - fmod(sprite.getPosition().x, 32))) ){
					Move(movement.x * abs((32*dir) - fmod(sprite.getPosition().x, 32)),0);
					currentDirection = None;
					break;
				}
				else
					Move((movement.x * elapsedTime.asSeconds() * 50),0);
			}
			else if(fmod(sprite.getPosition().y,32) != 0 && fmod(sprite.getPosition().y,32) != 32){
				if(abs(movement.y * elapsedTime.asSeconds() * 50) > (abs((32*dir) - fmod(sprite.getPosition().y, 32))) ){
					Move(0,movement.y * abs((32*dir) - fmod(sprite.getPosition().y, 32)));
					currentDirection = None;
					break;
				}
				else
					Move(0, (movement.y * elapsedTime.asSeconds() * 50));
			}
		}
			else if(currentDirection == U || currentDirection == D){
					Move(0, movement.y * elapsedTime.asSeconds() * 100);
					currentDirection = Finishing;
			}
			else if(currentDirection == L || currentDirection == R){
					Move(movement.x * elapsedTime.asSeconds() * 100,0);
					currentDirection = Finishing;
			}
	}
};
void Actor::DrawSprite(GamePanel* panel){
	sprite.setPosition(sprite.getPosition().x - 11.2, sprite.getPosition().y - 9.6);
	for(int x = 0; x < animationSheets.size(); x++){
		if(x != 2){
			sprite.setTextureRect(sf::IntRect(animationSheets[x].left + (currentAnimationPos.x * 64),animationSheets[x].top + (currentAnimationPos.y * 64),64,64));
			Draw(panel);
		}
	}
	if(this == User::player){
		if(currentAnimation == animations["Slash"] || currentAnimation == animations["Stab"] || currentAnimation == animations["Shoot"]){
			User::player->GetUserWeaponImage(panel);
		}
	}
	sprite.setPosition(sprite.getPosition().x + 11.2, sprite.getPosition().y + 9.6);
};
void Actor::OnClick(){

};
void Actor::SetUpFootLines(){
	sprite.setColor(sf::Color(255,255,255,255));
	for(int x = 0; x < animations.size(); x++){
		currentAnimation = animations[anims[x]];
		std::vector<std::vector<ShadowLine>> tempSLineVec;
		for(int y = 0; y < currentAnimation->yValues.size(); y++){
			std::vector<ShadowLine> tempSLineVec2;
			currentAnimationDir = Animation::AnimDir(y);
			currentAnimationPos.y = currentAnimation->yValues[y];
			currentAnimationPos.x = 0;
			for(int z = 0; z < currentAnimation->numFrames; z++){
				sprite.setTextureRect(sf::IntRect(Drawn::GetTextureFromAtlas("userspritesheets/body/light.png").left + currentAnimationPos.x * currentAnimation->width,Drawn::GetTextureFromAtlas("userspritesheets/body/light.png").top + currentAnimationPos.y * currentAnimation->width,currentAnimation->width,currentAnimation->width));
				tempSLineVec2.push_back(GetUpdatedFootLine());
				currentAnimationPos.x++;
			}
			tempSLineVec.push_back(tempSLineVec2);
		}
		footLines.push_back(tempSLineVec);
	}
};
void Actor::OnActionComplete(Actions){

};
void Actor::LaunchAction(Actions){

};
sf::Vector2i Actor::GetForward(){
	return movement;
};
std::string Actor::GetName(){
	return name;
};
sf::Vector2i Actor::GetBackward(){
	return sf::Vector2i(movement.x * -1,movement.y * -1);
};
sf::Vector2i Actor::GetLeft(){
	return sf::Vector2i(abs(abs(movement.x) - 1) * (movement.x - movement.y),abs(abs(movement.y) - 1) * (movement.x - movement.y));
};
sf::Vector2i Actor::GetRight(){
	return sf::Vector2i(-1 * (abs(abs(movement.x) - 1) * (movement.x - movement.y)),-1 * (abs(abs(movement.y) - 1) * (movement.x - movement.y)));
};
void Actor::SetUpAnimation(){
	AddAnimation(new Animation("Slash",0.05,6,64,12,14,13,15,0));
	AddAnimation(new Animation("Stab",0.05,8,64,4,6,5,7,1));
	AddAnimation(new Animation("Cast",0.05,7,64,0,2,1,3,2));
	AddAnimation(new Animation("Shoot",0.025,13,64,16,18,17,19,3));
	AddAnimation(new Animation("Walk",0.04,9,64,8,10,9,11,4));
	AddAnimation(new Animation("Die",0.075,6,64,20,20,20,20,5));
};
bool Actor::UpdateAnimation(){
	if(isPlaying){
		if(animationClock.getElapsedTime() > currentAnimation->timePerFrame){
			animationClock.restart();
			sprite.setColor(sf::Color(255,255,255,255));
			sprite.setTextureRect(sf::IntRect(currentAnimationPos.x * currentAnimation->width, currentAnimationPos.y * currentAnimation->width, currentAnimation->width, currentAnimation->width));
			UpdateBoundries();// TODO Lags
			if(currentDirection != None || currentDirection == Action){
				if(!isPaused)
					currentAnimationPos.x++;
			}
			if(currentAnimationPos.x == endFrame){
				if(isLooping)
					currentAnimationPos.x = startFrame;
				else{
					currentAnimationPos.x = 0;
					isPlaying = false;
					if(currentDirection == Action)
						OnActionComplete(currentAction);
				}
			}
			return true;
		}
	}
	else
		return false;
};
void Actor::UpdateAction(GamePanel* panel, bool updateAll){

};
ShadowLine Actor::GetUpdatedFootLine(){
	sf::RenderTexture tempText;
	tempText.create(sprite.getGlobalBounds().width,sprite.getGlobalBounds().height);
	tempText.clear(sf::Color(0,0,0,0));
	sf::Vector2f backupPosition = sprite.getPosition();
	sprite.setPosition(0,0);
	tempText.draw(sprite);
	sprite.setPosition(backupPosition);
	tempText.display();
	sf::Texture unsplitTexture = tempText.getTexture();
	sf::Image unsplitImage = unsplitTexture.copyToImage();
	int width = unsplitImage.getSize().x;
	int height = unsplitImage.getSize().y;
	sf::Vector2f firstPixel = sf::Vector2f(0,0);
	sf::Vector2f secondPixel = sf::Vector2f(0,0);
	for(int y = (height-1); y > 0; y--){
		for(int x = 0; x < (width/2); x++){
			if(unsplitImage.getPixel(x,y).a > 0){
				firstPixel.x = x;
				firstPixel.y = y;
				break;
			}
		}
		if(firstPixel.x != 0 && firstPixel.y != 0)
			break;
	}
	for(int y = (height-1); y > 0; y--){
		for(int x = (width/2); x < width; x++){
			if(unsplitImage.getPixel(x,y).a > 0){
				secondPixel.x = x;
				secondPixel.y = y;
				break;
			}
		}
		if(secondPixel.x != 0 && secondPixel.y != 0)
			break;
	}
	return ShadowLine(firstPixel,secondPixel);
};
void Actor::UpdateBoundries(){
	ClearBoundries();
	pugi::xml_node animationBoundsNode;
	pugi::xml_node dirBoundsNode;
	pugi::xml_node frameBoundsNode;
	for(pugi::xml_node curAnimationBoundsNode = boundriesNode.first_child(); curAnimationBoundsNode; curAnimationBoundsNode = curAnimationBoundsNode.next_sibling()){
		if(curAnimationBoundsNode.attribute("name").as_string() == currentAnimation->name){
			animationBoundsNode = curAnimationBoundsNode;
			break;
		}
	}
	for(pugi::xml_node dirBounds = animationBoundsNode.first_child(); dirBounds; dirBounds = dirBounds.next_sibling()){
		if(dirBounds.attribute("dir").as_int() == currentAnimationDir){
			dirBoundsNode = dirBounds;
			break;
		}
	}
	int x = 0;
	int curPos = currentAnimationPos.x;
	if(currentAnimation->name == "Walk")
		curPos--;
	for(pugi::xml_node frameBounds = dirBoundsNode.first_child(); frameBounds; frameBounds = frameBounds.next_sibling()){
		if(x == curPos){
			frameBoundsNode = frameBounds;
			break;
		}
		else{
			x++;
		}
	}
	for(pugi::xml_node polygon = frameBoundsNode.first_child(); polygon; polygon = polygon.next_sibling()){
		sf::ConvexShape poly;
		poly.setPointCount(polygon.attribute("numVertexes").as_int());

		pugi::xml_node vertex = polygon.first_child();
		for(int x = 0; x < polygon.attribute("numVertexes").as_int(); x++){
			if(x != 0)
				vertex = vertex.next_sibling();
			poly.setPoint(x,sf::Vector2f(vertex.attribute("x").as_int(),vertex.attribute("y").as_int()));
		}
		poly.setFillColor(sf::Color(43,119,173,170));
		GameSprite::AddBoundryPolygon(poly);
	}
	actorHull->SetLines(footLines[currentAnimation->id][currentAnimationDir][currentAnimationPos.x],GetPosition());
}
void Actor::LoopAnimation(Animation* anim, Animation::AnimDir dir){
	isPlaying = true;
	isLooping = true;
	this->startFrame = 0;
	if(anim->name == "Walk")
		this->startFrame = 1;
	this->endFrame = anim->numFrames;
	SetAnimation(anim,dir);
};
void Actor::PlayAnimation(Animation* anim, Animation::AnimDir dir){
	isPlaying = true;
	isLooping = false;
	this->startFrame = 0;
	if(anim->name == "Walk")
		this->startFrame = 1;
	this->endFrame = anim->numFrames;
	SetAnimation(anim,dir);
};
void Actor::PlayAnimation(Animation* anim, Animation::AnimDir dir,int startFrame,int endFrame){
	isPlaying = true;
	isLooping = false;
	this->startFrame = startFrame;
	this->endFrame = endFrame;
	SetAnimation(anim,dir);
};
void Actor::PauseAnimation(){
	isPaused = true;
};
void Actor::ResumeAnimation(){
	isPaused = false;
	currentAnimationPos.x++;
	animationClock.restart();
};
void Actor::SetAnimation(Animation* anim, Animation::AnimDir dir){
	animationClock.restart();
	if(currentAnimation->name != anim->name || currentAnimationDir != dir){
		currentAnimation = anim;
		currentAnimationDir = dir;
		if(anim->name == "Walk")
			currentAnimationPos.x = 1;
		else
			currentAnimationPos.x = 0;
		currentAnimationPos.y = currentAnimation->GetY(dir);
	}
}
void Actor::AddAnimation(Animation* anim){
	animations.insert(AnimationPair(anim->name,anim));
};
sf::Texture Actor::GetTexture(){
	return texture;
};
void Actor::OnHover(){

};
Hull* Actor::GetHull(){
	return actorHull;
};