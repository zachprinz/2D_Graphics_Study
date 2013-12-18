#include <SFML/Graphics.hpp>
#include "Drawn.h"
#include "GamePanel.h"
#include <MapLoader.h>
#include "ProgressBar.h"
#include "AABB.h"
#include "SlicedSprite.h"
#include "SpritePanel.h"

sf::Texture Drawn::gameTexture;
sf::VertexArray Drawn::gameArray;
sf::RenderStates Drawn::gameRenderStates;
boost::container::flat_set<Drawn*> Drawn::vertexPointers;
sf::RenderTexture Drawn::otherGraphicsPanel;
sf::Sprite Drawn::otherGraphicsSprite;
int Drawn::quadCount;
sf::RenderWindow* Drawn::gameWindow;
std::vector<sf::Drawable*> Drawn::adds;
std::vector<sf::Transformable*> Drawn::addsTransforms;
std::vector<sf::Vector2f> Drawn::addsPositions;

Drawn::Drawn(std::string textureExtension){
	drawOffset = sf::Vector2f(0,0);
	updateVertex = true;
	testPosition = sf::Vector2f(-1,0);
	heldVerteces.setPrimitiveType(sf::Quads);
	heldVerteces.resize(4);
	for(int x = 0; x < 4; x++){
		heldVerteces[x].position = sf::Vector2f(0,0);
		heldVerteces[x].texCoords = sf::Vector2f(0,0);
		cornerRotationOffsets.push_back(sf::Vector2f(0,0));
	}
	myScale = sf::Vector2f(1,1);
	sprite.setTexture(gameTexture);
	sprite.setTextureRect(GetTextureFromAtlas(textureExtension));
	sprite.setPosition(0,0);
	texturePart = sprite.getTextureRect();
	isMoving = false;
	isExpanding = false;
	resetScale = sf::Vector2f(1,1);
	z = 0;
	vertexPointers.insert(this);
	rotationAngle = 0;
	SetRotation(0);
};

Drawn::Drawn(SlicedSprite* sliced){
	drawOffset = sf::Vector2f(0,0);
	updateVertex = true;
	testPosition = sf::Vector2f(0,0);
	heldVerteces.setPrimitiveType(sf::Quads);
	heldVerteces.resize(4);
	for(int x = 0; x < 4; x++){
		heldVerteces[x].position = sf::Vector2f(0,0);
		heldVerteces[x].texCoords = sf::Vector2f(0,0);
		cornerRotationOffsets.push_back(sf::Vector2f(0,0));
	}
	myScale = sf::Vector2f(1,1);
	sprite.setTexture(gameTexture);
	sprite.setTextureRect(GetTextureFromAtlas("blank.png"));
	sprite.setPosition(0,0);
	texturePart = sprite.getTextureRect();
	isMoving = false;
	isExpanding = false;
	resetScale = sf::Vector2f(1,1);
	z = 0;
	vertexPointers.insert(this);
	rotationAngle = 0;
	SetRotation(0);
};

Drawn::Drawn(){
		drawOffset = sf::Vector2f(0,0);
		myScale = sf::Vector2f(1,1);
};

void Drawn::DrawVertex(sf::RenderTexture* texture, GamePanel* panel){
	sf::Vector2f pos = sprite.getPosition() - panel->GetViewLowerBound() + drawOffset + panel->GetPosition() - sprite.getOrigin();
	if(testPosition != pos || updateVertex){
		sf::IntRect texRec = sprite.getTextureRect();
		gameArray.append(sf::Vertex());
		gameArray[quadCount].position = pos + cornerRotationOffsets[1];
		heldVerteces[0].position = gameArray[quadCount].position;
		gameArray[quadCount++].texCoords = sf::Vector2f(texRec.left,texRec.top);
		gameArray.append(sf::Vertex());
		gameArray[quadCount].position = pos + cornerRotationOffsets[0];
		heldVerteces[1].position = gameArray[quadCount].position;
		gameArray[quadCount++].texCoords = sf::Vector2f(texRec.left + texRec.width,texRec.top);
		gameArray.append(sf::Vertex());
		gameArray[quadCount].position = pos + cornerRotationOffsets[3];
		heldVerteces[2].position = gameArray[quadCount].position;
		gameArray[quadCount++].texCoords = sf::Vector2f(texRec.left + texRec.width,texRec.top + texRec.height);
		gameArray.append(sf::Vertex());
		gameArray[quadCount].position = pos  + cornerRotationOffsets[2];
		heldVerteces[3].position = gameArray[quadCount].position;
		gameArray[quadCount++].texCoords = sf::Vector2f(texRec.left,texRec.top + texRec.height);
		testPosition = pos;
		updateVertex = false;
	}
	else{
		sf::IntRect texRec = sprite.getTextureRect();
		gameArray.append(sf::Vertex());
		gameArray[quadCount].position = heldVerteces[0].position;
		gameArray[quadCount++].texCoords = sf::Vector2f(texRec.left,texRec.top);
		gameArray.append(sf::Vertex());
		gameArray[quadCount].position = heldVerteces[1].position;
		gameArray[quadCount++].texCoords = sf::Vector2f(texRec.left + texRec.width,texRec.top);
		gameArray.append(sf::Vertex());
		gameArray[quadCount].position = heldVerteces[2].position;
		gameArray[quadCount++].texCoords = sf::Vector2f(texRec.left + texRec.width,texRec.top + texRec.height);
		gameArray.append(sf::Vertex());
		gameArray[quadCount].position = heldVerteces[3].position;
		gameArray[quadCount++].texCoords = sf::Vector2f(texRec.left,texRec.top + texRec.height);
	}
};
void Drawn::Draw(GamePanel* panel){
	DrawVertex(&panel->GetRenderPanel(),panel);
}
void Drawn::SetDrawOffset(sf::Vector2f off){
	drawOffset = off;
};
void Drawn::Draw(GamePanel* panel, sf::RenderTexture* texture){
	DrawVertex(texture,panel);
};
void Drawn::Destroy(){

};
void Drawn::DrawGame(sf::RenderWindow& window){
	window.draw(SpritePanel::instance->panelSprite);
	window.draw(gameArray,gameRenderStates);
	Drawn::DrawAdds();
	gameArray.clear();
	quadCount = 0;
	sf::IntRect texRec = GetTextureFromAtlas("gamebackground.png");
	gameArray.append(sf::Vertex());
	gameArray[quadCount].position = sf::Vector2f(0,0);
	gameArray[quadCount++].texCoords = sf::Vector2f(texRec.left,texRec.top);
	gameArray.append(sf::Vertex());
	gameArray[quadCount].position = sf::Vector2f(1920,0);
	gameArray[quadCount++].texCoords = sf::Vector2f(texRec.left + texRec.width,texRec.top);
	gameArray.append(sf::Vertex());
	gameArray[quadCount].position = sf::Vector2f(1920,1080);
	gameArray[quadCount++].texCoords = sf::Vector2f(texRec.left + texRec.width,texRec.top + texRec.height);
	gameArray.append(sf::Vertex());
	gameArray[quadCount].position = sf::Vector2f(0,1080);
	gameArray[quadCount++].texCoords = sf::Vector2f(texRec.left,texRec.top + texRec.height);
};
void Drawn::SetUp(sf::RenderWindow* window){
	gameWindow = window;
	quadCount = 0;
	gameArray.setPrimitiveType(sf::Quads);
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
AABB Drawn::GetBounds(){
	return AABB(Vec2f(GetPosition().x - sprite.getOrigin().x,
					  (GetPosition().y - sprite.getOrigin().y)),
				Vec2f(GetPosition().x + (myScale.x * (float)texturePart.width * sprite.getScale().x - sprite.getOrigin().x),
					  GetPosition().y + (myScale.y * (float)texturePart.height * sprite.getScale().y) - sprite.getOrigin().y));
};
AABB Drawn::GetBounds(sf::View view){
	return AABB(Vec2f((GetPosition().x - (view.getCenter().x - (view.getSize().x / 2))) - sprite.getOrigin().x,
					  (GetPosition().y - (view.getCenter().y - (view.getSize().y / 2))) - sprite.getOrigin().y),
				Vec2f((GetPosition().x + (myScale.x * (float)texturePart.width * sprite.getScale().x)  - (view.getCenter().x - (view.getSize().x / 2))) - sprite.getOrigin().x,
					  (GetPosition().y + (myScale.y * (float)texturePart.height * sprite.getScale().y)  - (view.getCenter().y - (view.getSize().y / 2))) - sprite.getOrigin().y));
};
AABB Drawn::GetSpritePanelBounds(){
	return GetBounds(SpritePanel::instance->GetRenderPanel().getView());
}
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
void Drawn::DrawOther(sf::Text* label,GamePanel* panel){
	sf::Vector2f tempPos = label->getPosition();
	addsPositions.push_back(tempPos);
	label->setPosition(tempPos + panel->GetPosition());
	adds.push_back(label);
	addsTransforms.push_back(label);
};
void Drawn::DrawOther(sf::RectangleShape* sprite, GamePanel* panel){
	sf::Vector2f pos = sprite->getPosition() - panel->GetViewLowerBound();
	sf::Vector2f tempPos = sprite->getPosition();
	addsPositions.push_back(tempPos);
	sprite->setPosition(tempPos + panel->GetPosition());
	adds.push_back(sprite);	
	addsTransforms.push_back(sprite);
};
void Drawn::DrawAdds(){
	for(int x = 0; x < adds.size(); x++){
		gameWindow->draw(*adds[x]);
		addsTransforms[x]->setPosition(addsPositions[x]);
	}
	addsTransforms.clear();
	adds.clear();
	addsPositions.clear();
};
void Drawn::Update(GamePanel* panel){
	Draw(panel);
};
void Drawn::MoveOnGrid(int x,int y){

};
void Drawn::SetScale(sf::Vector2f newScale){
	updateVertex = true;
	if(newScale.x != 0 && newScale.y != 0)
		myScale = newScale;
	SetRotation(rotationAngle);
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
		homeScale = sf::Vector2f(GetScale().x, GetScale().y);
		targetScale = sf::Vector2f(expandRatio * GetScale().x,expandRatio * GetScale().y);
		expandAmount = targetScale - homeScale;
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
	homeScale = sf::Vector2f(GetScale().x,GetScale().y);
	targetScale = resetScale;
	expandAmount = targetScale - homeScale;
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
		if(std::abs(GetScale().y - targetScale.y) < std::abs(tempDeltaY) || std::abs(GetScale().x - targetScale.x) < std::abs(tempDeltaX)){
			SetScale(targetScale);
			//expandAmount = 0;
			isExpanding = false;
		}
		else{
			SetScale(sf::Vector2f(GetScale().x + tempDeltaX,GetScale().y + tempDeltaY));
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
sf::Vector2f Drawn::GetSize(){
	return sf::Vector2f(texturePart.width * myScale.x * sprite.getScale().x, texturePart.height * myScale.y * sprite.getScale().y);
};
void Drawn::SetRotation(float angle){
	rotationAngle = angle;
	float radius = std::sqrt(std::pow(GetSize().y,2.0) + std::pow(GetSize().x,2.0)) / 2.0f;
	float baseAngle = 0;
	baseAngle = std::atan(((float)GetSize().y) / ((float)GetSize().x));
	for(int x = 0; x < 4; x++){
		// The below line replaced a 15 line switch statement. Because IM SUCH A FUCKING BOSS.
		float tempBaseAngle = ((std::ceil(std::floor((x % 3) + .1)/((x % 3) + .1)) * 180)/57.29) + ((1 - (2*(x % 2))) * baseAngle); 
		cornerRotationOffsets[x].x = cos((angle / 57.29) + tempBaseAngle) * radius + (GetSize().x / 2.0f);
		cornerRotationOffsets[x].y = -sin((angle / 57.29) + tempBaseAngle) * radius + (GetSize().y / 2.0f);
	}
};