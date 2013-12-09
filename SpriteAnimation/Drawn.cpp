#include <SFML/Graphics.hpp>
#include "Drawn.h"
#include "GamePanel.h"
#include <MapLoader.h>
#include "ProgressBar.h"
#include "AABB.h"
#include "SlicedSprite.h"

sf::Texture Drawn::gameTexture;
sf::VertexArray Drawn::gameArray;
sf::RenderStates Drawn::gameRenderStates;
boost::container::flat_set<Drawn*> Drawn::vertexPointers;
int Drawn::quadCount = -1;
sf::RenderTexture Drawn::otherGraphicsPanel;
sf::Sprite Drawn::otherGraphicsSprite;

Drawn::Drawn(std::string textureExtension){
	myScale = sf::Vector2f(1,1);
	additionalQuadCount = 0;
	sprite.setTexture(gameTexture);
	sprite.setTextureRect(GetTextureFromAtlas(textureExtension));
	sprite.setPosition(0,0);
	texturePart = sprite.getTextureRect();
	isMoving = false;
	isExpanding = false;
	resetScale = sf::Vector2f(1,1);
	quad = GetVertexPointer();
	for(int x = 0; x < 4; x++){
		quad[x].position = sf::Vector2f(0,0);
		quad[x].texCoords = sf::Vector2f(0,0);
	}
	z = 0;
	vertexPointers.insert(this);
};

Drawn::Drawn(SlicedSprite* sliced){
	myScale = sf::Vector2f(1,1);
	additionalQuadCount = 0;
	sprite.setTexture(gameTexture);
	sprite.setTextureRect(GetTextureFromAtlas("blank.png"));
	sprite.setPosition(0,0);
	texturePart = sprite.getTextureRect();
	isMoving = false;
	isExpanding = false;
	resetScale = sf::Vector2f(1,1);
	quad = GetVertexPointer();
	for(int x = 0; x < 4; x++){
		quad[x].position = sf::Vector2f(0,0);
		quad[x].texCoords = sf::Vector2f(0,0);
	}
	z = 0;
	vertexPointers.insert(this);
};

Drawn::Drawn(){

};

void Drawn::Draw(GamePanel* panel){
	if(sprite.getPosition() != quad[0].position){
		sf::Vector2f pos = sprite.getPosition();
		sf::Vector2f spriteScale = sprite.getScale();
		quad[0].position = pos + panel->GetPosition();
		quad[3].position = pos + sf::Vector2f(0,myScale.y * texturePart.height * spriteScale.y) + panel->GetPosition();
		quad[1].position = pos + sf::Vector2f(myScale.x * texturePart.width * spriteScale.x,0) + panel->GetPosition();
		quad[2].position = sf::Vector2f(pos.x + (myScale.x * texturePart.width * spriteScale.x),pos.y + (myScale.y * texturePart.height * spriteScale.y)) + panel->GetPosition();
	}
	sf::IntRect texRec = sprite.getTextureRect();
	if(sf::Vector2f(texRec.left,texRec.top) != quad[0].texCoords){
		quad[0].texCoords = sf::Vector2f(texRec.left,texRec.top);
		quad[1].texCoords = sf::Vector2f(texRec.left + texRec.width,texRec.top);
		quad[3].texCoords = sf::Vector2f(texRec.left,texRec.top + texRec.height);
		quad[2].texCoords = sf::Vector2f(texRec.left + texRec.width,texRec.top + texRec.height);
	}
};
void Drawn::DrawAdditional(GamePanel* panel){
	if(ViewContains(panel->GetRenderPanel().getView(),sf::IntRect(sprite.getPosition().x,sprite.getPosition().y,sprite.getTextureRect().width,sprite.getTextureRect().height))){
		sf::Vector2f pos = sprite.getPosition() - (panel->GetRenderPanel().getView().getCenter() - sf::Vector2f(panel->GetRenderPanel().getView().getSize().x / 2, panel->GetRenderPanel().getView().getSize().y / 2.0));
		if(additionalQuads.size() < (additionalQuadCount + 1))
			additionalQuads.push_back(GetVertexPointer());
		additionalQuads[additionalQuadCount][0].position = pos + panel->GetPosition();
		additionalQuads[additionalQuadCount][3].position = pos + sf::Vector2f(0,myScale.y * sprite.getGlobalBounds().height) + panel->GetPosition();
		additionalQuads[additionalQuadCount][1].position = pos + sf::Vector2f(myScale.x * sprite.getGlobalBounds().width,0) + panel->GetPosition();
		additionalQuads[additionalQuadCount][2].position = sf::Vector2f(pos.x + (myScale.x * sprite.getGlobalBounds().width),pos.y + (myScale.y * sprite.getGlobalBounds().height)) + panel->GetPosition();
		sf::IntRect texRec = sprite.getTextureRect();
		additionalQuads[additionalQuadCount][0].texCoords = sf::Vector2f(texRec.left,texRec.top);
		additionalQuads[additionalQuadCount][1].texCoords = sf::Vector2f(texRec.left + texRec.width,texRec.top);
		additionalQuads[additionalQuadCount][3].texCoords = sf::Vector2f(texRec.left,texRec.top + texRec.height);
		additionalQuads[additionalQuadCount][2].texCoords = sf::Vector2f(texRec.left + texRec.width,texRec.top + texRec.height);
		additionalQuadCount++;
	}
	else{
		if(additionalQuads.size() < (additionalQuadCount + 1))
			additionalQuads.push_back(GetVertexPointer());
		additionalQuads[additionalQuadCount][0].texCoords = sf::Vector2f(0,0);
		additionalQuads[additionalQuadCount][1].texCoords = sf::Vector2f(0,0);
		additionalQuads[additionalQuadCount][3].texCoords = sf::Vector2f(0,0);
		additionalQuads[additionalQuadCount][2].texCoords = sf::Vector2f(0,0);
		additionalQuadCount++;
	}
};
void Drawn::ClearAdditionalQuads(){
	for(int x = 0; x < additionalQuads.size(); x++){
		for(int y = 0; y < 4; y++){
			additionalQuads[x][y].texCoords = sf::Vector2f(0,0);
		}
	}
	additionalQuadCount = 0;
};
void Drawn::Destroy(){

};
sf::Vertex* Drawn::GetVertexPointer(){
	quadCount++;
	//if(quadCount >= (gameArray.getVertexCount() / 4)){
	//	gameArray.resize(gameArray.getVertexCount() + 40);
	//}
	return &gameArray[quadCount * 4];
};
void Drawn::DrawGame(sf::RenderWindow& window){
	window.draw(gameArray,gameRenderStates);
	otherGraphicsPanel.display();
	window.draw(otherGraphicsSprite);
	otherGraphicsPanel.clear(sf::Color(0,0,0,0));
};
void Drawn::SetUp(){
	gameArray.setPrimitiveType(sf::Quads);
	gameArray.resize(3500);
	gameTexture.loadFromFile("Atlas/GameAtlas.png");
	gameTexture.setSmooth(true);
	gameTexture.setRepeated(false);
	gameRenderStates.texture = &gameTexture;
	otherGraphicsPanel.create(1920,1080);
	otherGraphicsPanel.clear(sf::Color(0,0,0,0));
	otherGraphicsPanel.display();
	otherGraphicsSprite.setTexture(otherGraphicsPanel.getTexture());
};
bool Drawn::GetVisible(){
	return isVisible;
};

sf::Sprite* Drawn::GetSprite(){
	return &sprite;
};
void Drawn::SetZ(int z){
	vertexPointers.erase(this);
	this->z = z;
	vertexPointers.insert(this);
};
sf::Texture Drawn::GetSingleTexture(){
	sf::RenderTexture tempRendText;
	std::cout << "Creating a texture to return" << std::endl;
	tempRendText.create(sprite.getTextureRect().width,sprite.getTextureRect().height);
	std::cout << "Creating a texture to return2" << std::endl;
	tempRendText.clear(sf::Color(0,0,0,0));
	sf::Vector2f tempPos = sprite.getPosition();
	sprite.setPosition(0,0);
	tempRendText.draw(sprite);
	sprite.setPosition(tempPos);
	tempRendText.display();
	sf::Texture tempText = tempRendText.getTexture();
	return tempText;
};
sf::Texture Drawn::GetSingleTexture(std::string name){
	sf::RenderTexture tempRendText;
	sf::IntRect tempTextRect = GetTextureFromAtlas(name);
	tempRendText.create(tempTextRect.width,tempTextRect.height);
	tempRendText.clear(sf::Color(0,0,0,0));
	sf::Sprite tempSprite;
	tempSprite.setTexture(gameTexture);
	tempSprite.setTextureRect(tempTextRect);
	tempRendText.draw(tempSprite);
	tempRendText.display();
	sf::Texture tempText = tempRendText.getTexture();
	return tempText;
};
void Drawn::OnHover(bool hovered){

};
sf::Vector2f Drawn::GetPositionOnPanel(){
	return positionOnPanel;
};

void Drawn::Update(sf::RenderTexture& window){
		window.draw(sprite);
};
void Drawn::DrawOther(sf::Text* label,GamePanel* panel){
	sf::Vector2f tempPos = label->getPosition();
	label->setPosition(tempPos + panel->GetPosition());
	otherGraphicsPanel.draw(*label);
	label->setPosition(tempPos);
};
void Drawn::DrawOther(sf::Sprite* sprite,GamePanel* panel){
	sf::Vector2f tempPos = sprite->getPosition();
	sprite->setPosition(tempPos + panel->GetPosition());
	otherGraphicsPanel.draw(*sprite);
	sprite->setPosition(tempPos);
};
void Drawn::DrawOther(sf::RectangleShape* sprite, GamePanel* panel){
	sf::Vector2f tempPos = sprite->getPosition();
	sprite->setPosition(tempPos + panel->GetPosition());
	otherGraphicsPanel.draw(*sprite);
	sprite->setPosition(tempPos);
};
void Drawn::Update(GamePanel* panel){
	Draw(panel);
};

void Drawn::MoveOnGrid(int x,int y){

};
void Drawn::SetScale(sf::Vector2f newScale){
	myScale = newScale;
}
sf::Vector2f Drawn::GetScale(){
	return myScale;
};
sf::IntRect Drawn::GetTexturePart(){
	return sf::IntRect(texturePart.left,texturePart.top,texturePart.width * myScale.x, texturePart.height * myScale.y);
};
void Drawn::SetPosition(sf::Vector2f newPos){
	positionOnPanel = newPos;
	resetPosition = sf::Vector2i(newPos.x,newPos.y);
	sprite.setPosition(newPos.x,newPos.y);
};
sf::Vector2f Drawn::GetPosition(){
	return sprite.getPosition();
};
void Drawn::Move(float x,float y){
	positionOnPanel.x += x;
	positionOnPanel.y += y;
	sprite.move(x,y);
};
void Drawn::OnClick(){

}
void Drawn::OnRClick(sf::Vector2i){

};
sf::IntRect Drawn::GetTextureFromAtlas(std::string name){
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("Atlas/GameAtlas.xml");
	pugi::xml_node atlas = doc.child("TextureAtlas");
	sf::IntRect boundries;
	for(pugi::xml_node tool = atlas.first_child(); tool; tool = tool.next_sibling()){
		if(tool.first_attribute().value() == name){
			boundries.left = tool.first_attribute().next_attribute().as_int()+1;
			boundries.top = tool.first_attribute().next_attribute().next_attribute().as_int()+1;
			boundries.width = tool.first_attribute().next_attribute().next_attribute().next_attribute().as_int()-2;
			boundries.height = tool.first_attribute().next_attribute().next_attribute().next_attribute().next_attribute().as_int()-2;
			return boundries;
		}
	}
};
void Drawn::MoveTo(int x,int y, sf::Time sec){
	if(isMoving == false){
		distanceMoved = 0;
		homePosition = sf::Vector2i((int)GetSprite()->getGlobalBounds().left, (int)GetSprite()->getGlobalBounds().top);
		targetPosition = sf::Vector2i((int)x,(int)y);
		moveDistance = GetDistance(homePosition,targetPosition);
		componentMoveDistance.x = (targetPosition.x - homePosition.x);
		componentMoveDistance.y = (targetPosition.y - homePosition.y);
		if(componentMoveDistance.x > 0)
			moveDirection.x = componentMoveDistance.x/(std::abs(componentMoveDistance.x));
		else
			moveDirection.x = 0;
		if(componentMoveDistance.y > 0)
			moveDirection.y = componentMoveDistance.y/(std::abs(componentMoveDistance.y));
		else
			moveDirection.y = 0;
		velocity = moveDistance / sec.asSeconds();
		if(componentMoveDistance.x != 0)
			moveAngle = std::atan(std::abs(componentMoveDistance.y)/std::abs(componentMoveDistance.x));
		else
			moveAngle == (3.1415 / 2);
		movementClock.restart();
		isMoving = true;
	}
};
void Drawn::Return(){
	distanceMoved = 0;
	homePosition = sf::Vector2i(sprite.getGlobalBounds().left,sprite.getGlobalBounds().top);
	targetPosition = resetPosition;
	moveDistance = GetDistance(homePosition,targetPosition);
	componentMoveDistance.x = (targetPosition.x - homePosition.x);
	componentMoveDistance.y = (targetPosition.y - homePosition.y);
	if(componentMoveDistance.x != 0)
		moveDirection.x = componentMoveDistance.x/(std::abs(componentMoveDistance.x));
	else
		moveDirection.x = 0;
	if(componentMoveDistance.y != 0)
		moveDirection.y = componentMoveDistance.y/(std::abs(componentMoveDistance.y));
	else
		moveDirection.y = 0;
	if(componentMoveDistance.y != 0 && componentMoveDistance.x != 0)
		moveAngle = std::atan(std::abs(componentMoveDistance.y)/std::abs(componentMoveDistance.x));
	else
		moveAngle == (3.1415 / 2);
	movementClock.restart();
	isMoving = true;
}
int Drawn::GetDistance(sf::Vector2i initialPoint, sf::Vector2i finalPoint){
	int deltaX = finalPoint.x - initialPoint.x;
	int deltaY = finalPoint.y - initialPoint.y;
	int distance = std::sqrt(std::pow(deltaX,2) + std::pow(deltaY,2));
	return distance;
};
void Drawn::UpdateMove(){
	if(isMoving){
		float tempMoveDistance = movementClock.restart().asSeconds() * velocity;
		float tempDeltaY = moveDirection.y * (std::sin(moveAngle) * tempMoveDistance);
		float tempDeltaX = moveDirection.x * (std::cos(moveAngle) * tempMoveDistance);
		if(moveDistance <= tempMoveDistance){
			GetSprite()->setPosition(targetPosition.x,targetPosition.y);
			moveDistance = 0;
			isMoving = false;
		}
		else if(moveDistance > tempMoveDistance) {
			GetSprite()->setPosition(GetSprite()->getGlobalBounds().left + tempDeltaX, GetSprite()->getGlobalBounds().top + tempDeltaY);
			distanceMoved += tempMoveDistance;
			moveDistance -= tempMoveDistance;
		}
	}
};
bool Drawn::GetIsMoving(){
	return isMoving;
}
void Drawn::ResetPosition(){
	sprite.setPosition(resetPosition.x,resetPosition.y);
}
void Drawn::ExpandBy(float expandRatio,sf::Time sec){
	if(isExpanding == false){
		//amountExpanded = 0;
		homeScale = sf::Vector2f(GetSprite()->getScale().x, GetSprite()->getScale().y);
		targetScale = sf::Vector2f(expandRatio * GetSprite()->getScale().x,expandRatio * GetSprite()->getScale().y);
		expandAmount.x = targetScale.x - homeScale.x;
		expandAmount.y = targetScale.y - homeScale.y;
		expandVelocity.x = expandAmount.x / sec.asSeconds();
		expandVelocity.y = expandAmount.y / sec.asSeconds();
		if(expandAmount.x != 0)
			expandDirection.x = expandAmount.x / std::abs(expandAmount.x);
		else
			expandDirection.x = 0;
		if(expandAmount.y != 0)
			expandDirection.y = expandAmount.y / std::abs(expandAmount.y);
		else
			expandAmount.y = 0;
		expandClock.restart();
		isExpanding = true;
	}
};
void Drawn::ReturnExpand(){
	homeScale = sf::Vector2f(sprite.getScale().x,sprite.getScale().y);
	targetScale = resetScale;
	expandAmount.x = targetScale.x - homeScale.x;
	expandAmount.y = targetScale.y - homeScale.y;
	if(expandAmount.x != 0)
		expandDirection.x = expandAmount.x / std::abs(expandAmount.x);
	else
		expandDirection.x = 0;
	if(expandAmount.y != 0)
		expandDirection.y = expandAmount.y / std::abs(expandAmount.y);
	else
		expandAmount.y = 0;
	expandClock.restart();
	isExpanding = true;
};
void Drawn::UpdateExpand(){
	if(isExpanding){
		float tempDeltaY = expandDirection.y * expandClock.restart().asSeconds() * expandVelocity.y;
		float tempDeltaX = expandDirection.x * expandClock.restart().asSeconds() * expandVelocity.x;
		if(std::abs(sprite.getScale().y - targetScale.y) < std::abs(tempDeltaY) || std::abs(sprite.getScale().x - targetScale.x) < std::abs(tempDeltaX)){
			GetSprite()->setScale(targetScale.x,targetScale.y);
			//expandAmount = 0;
			isExpanding = false;
		}
		else{
			GetSprite()->setScale(GetSprite()->getScale().x + tempDeltaX,GetSprite()->getScale().y + tempDeltaY);
		}
	}
};
bool Drawn::GetIsExpanding(){
	return isExpanding;
};
bool Drawn::ViewContains(sf::View view,sf::IntRect rect){
	sf::Vector2f viewUpper(view.getCenter() - sf::Vector2f(view.getSize().x / 2, view.getSize().y/2));
	sf::IntRect viewRect(viewUpper.x,viewUpper.y,view.getSize().x,view.getSize().y);
	if(viewRect.contains(rect.left,rect.top)
		&& viewRect.contains(rect.left + rect.width, rect.top)
		&& viewRect.contains(rect.left, rect.top + rect.height)
		&& viewRect.contains(rect.left + rect.width, rect.top + rect.height))
		return true;
	return false;
};