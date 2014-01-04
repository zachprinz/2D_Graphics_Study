#include "GamePanel.h"
#include <iostream>
#include "User.h"
#include "RClickMenu.h"
#include "Label.h"
#include "SlicedSprite.h"
#include "SpritePanel.h"
#include "Game.h"
#include "DropDownMenu.h"

GamePanel* GamePanel::currentMousePanel;
Drawn* GamePanel::currentMouseElement;
Drawn* GamePanel::currentPressedElement;

GamePanel::GamePanel(int x, int y, std::string name){
	mySize = sf::Vector2f(x,y);
	isPanelOpen = true;
	backgroundPanel.create(x + 16, y + 16);
	panel.create(x,y);
	panelName = name;
	panel.setSmooth(true);
	panelSprite.setTexture(panel.getTexture());
	backgroundPanelSprite.setTexture(backgroundPanel.getTexture());
};
GamePanel::GamePanel(){

}
void GamePanel::Update(){
	if(isPanelOpen){
		UpdateElements();
	}
};
void GamePanel::InitiateElements(){

};
void GamePanel::UpdateElements(){
	if(dynamicElements.find("barPlaceHolder") != dynamicElements.end() && dynamicElements["barPlaceHolder"]->pressed)
		UpdateDrag();
	for(MyPair x: backgroundElements){
		if(x.second->isSliced)
			x.second->Update(this);
		else
			x.second->Draw(this);
	}
	std::vector<Drawn*> remaining;
	std::vector<Drawn*> remaining2;
	int current = 1;
	for(MyPair x: staticElements){
	if(x.second->z == 0)
			x.second->Update(this);
	else
			remaining.push_back(x.second);
	}
	current = 1;
	while(remaining.size() > 0 || remaining2.size() > 0){
		    for(int x = 0; x < remaining.size(); x++){
			if(remaining[x]->z == (current))
				    remaining[x]->Update(this);
			else
				    remaining2.push_back(remaining[x]);
		    }
		    current++;
		    remaining.clear();
		    for(int x = 0; x < remaining2.size(); x++){
			if(remaining2[x]->z == (current))
				    remaining2[x]->Update(this);
			else
				    remaining.push_back(remaining2[x]);
		    };
			remaining2.clear();
		current++;
	}
	remaining.clear();
	remaining2.clear();
	for(MyPair x: dynamicElements){
	if(x.second->z == 0)
			x.second->Update(this);
	else
			remaining.push_back(x.second);
	}
	current = 1;
	while(remaining.size() > 0 || remaining2.size() > 0){
		    for(int x = 0; x < remaining.size(); x++){
			if(remaining[x]->z == (current))
				    remaining[x]->Update(this);
			else
				    remaining2.push_back(remaining[x]);
		    }
		    current++;
		    remaining.clear();
		    for(int x = 0; x < remaining2.size(); x++){
			if(remaining2[x]->z == (current))
				    remaining2[x]->Update(this);
			else
				    remaining.push_back(remaining2[x]);
		    };
			remaining2.clear();
		current++;
	}
	if(RClickMenu::currentPanel == this){
	    RClickMenu::Update(this);
	}
};
void GamePanel::Open(){
	isPanelOpen = true;
};
void GamePanel::Close(){
	isPanelOpen = false;
};
sf::Vector2f GamePanel::GetViewLowerBound(){
	return sf::Vector2f(panel.getView().getCenter() - sf::Vector2f(panel.getView().getSize().x / 2, panel.getView().getSize().y / 2.0));
}
void GamePanel::SetPosition(int x, int y){
	panelSprite.setPosition(x + 8,y + 8);
	backgroundPanelSprite.setPosition(x,y);
	panelBounds = AABB(Vec2f(x,y),Vec2f(x + GetSize().x,y + GetSize().y));
}
void GamePanel::OnMousePress(sf::Vector2i point){
	currentMouseElement->OnMousePress();
	currentPressedElement = currentMouseElement;
	Game::mouseIsPressed = true;
}
void GamePanel::OnRClick(sf::Vector2i point){
	std::cout << "Right Click" << std::endl;
	for(MyPair x: dynamicElements){
		if(((RClickable*)(x.second))->GetRClickEnabled() && x.second->GetBounds().Contains(point.x - GetPosition().x,point.y - GetPosition().y)){
			((RClickable*)(x.second))->OnRClick(sf::Vector2i(point.x - GetPosition().x,point.y - GetPosition().y),this);
		}
		else if(((RClickable*)(x.second))->GetRClickEnabled()){
			std::cout << "RClickEnabled on this one." << std::endl;
		}
	}
}
void GamePanel::OnHover(sf::Vector2i point){
    	std::vector<Drawn*> remaining;
	std::vector<Drawn*> remaining2;
	int current = 4;
	bool stop = false;
	for(MyPair x: dynamicElements){
		    if(x.second->z == 5)
				    stop = CheckHover(x.second,point);
		    else
				    remaining.push_back(x.second);
	}
	while(current > -1 && (!stop) && remaining.size() > 0){
		    for(int x = 0; x < remaining.size(); x++){
			if(remaining[x]->z == (current))
				    stop = CheckHover(remaining[x],point);
			else
				    remaining2.push_back(remaining[x]);
		    }
		    current--;
		    remaining.clear();
		    if(stop)
			remaining2.clear();
		    for(int x = 0; x < remaining2.size(); x++){
			if(remaining2[x]->z == (current))
				    stop = CheckHover(remaining2[x],point);
			else
				    remaining.push_back(remaining2[x]);
		    };
			remaining2.clear();
		current--;
	}
	int asdf = 0;
};
bool GamePanel::CheckHover(Drawn* check,sf::Vector2i point){
	bool tempBool = false;
	if(DropDownMenu::isOpen && DropDownMenu::instance->buttons.size() > 0 && check == DropDownMenu::instance->buttons[0]){
		AABB tempBounds = check->GetBounds();
		int x = 0;
		tempBool = true;
	};
    	if(check->GetBounds(panel.getView()).Contains(point.x - GetPosition().x,point.y - GetPosition().y)){
			if(GamePanel::currentMouseElement != check){
				if(currentMouseElement != NULL)
					currentMouseElement->OnHover(false);
				currentMouseElement = check;
				(check)->OnHover(true);
			}
			if(tempBool)
			    int asdfijijig = 0;
			return true;
		}
	return false;
};
AABB GamePanel::GetBounds(){
	return panelBounds;
}
void GamePanel::RemoveDynamicElement(std::string key){
		dynamicElements.erase(key);
};
GamePanel::ElementList* GamePanel::GetDynamicElements(){
	return &dynamicElements;
}
sf::RenderTexture& GamePanel::GetRenderPanel(){
	return panel;
};
sf::Vector2f GamePanel::GetPosition(){
	return panelSprite.getPosition();
}
void GamePanel::SetUp(){
	std::string tempName = GetName();
	int tempHigher = -37;
	Drawn* background  = new Drawn("windows/" + GetName() + "background.png");
	background->SetPosition(sf::Vector2f(-4,-37));
	background->texturePart.height = 35;
	backgroundElements.insert(MyPair("Background", background));
	if(tempName != "LayeredPanel" && tempName != "Text"){
	    Button* btnLabel = new Button(0,tempHigher,tempName);
	    backgroundElements.insert(MyPair("BackgroundLabel",btnLabel));
	}
	Drawn* barPlaceHolder = new Drawn("blank.png");
	barPlaceHolder->SetPosition(sf::Vector2f(-4,-37));
	barPlaceHolder->texturePart.height = 35;
	barPlaceHolder->texturePart.width = GetSize().x;
	barPlaceHolder->SetRotation(0);
	barPlaceHolder->SetZ(2);
	dynamicElements.insert(MyPair("barPlaceHolder",barPlaceHolder));
}
bool GamePanel::GetIsPanelOpen(){
	return isPanelOpen;
}
void GamePanel::OnButtonEvent(std::string){

}
std::string GamePanel::GetName(){
	return panelName;
};
sf::Vector2f GamePanel::GetSize(){
	return mySize;
};
void GamePanel::UpdateDrag(){
	sf::Vector2i mousePositionTemp = sf::Mouse::getPosition(*(Drawn::gameWindow));
	sf::Vector2f mousePosition(mousePositionTemp.x,mousePositionTemp.y);
	sf::Vector2f relativePosition = mousePosition - GetPosition();
	//mousePosition += relativePosition;
	//SetPosition(mousePosition.x + relativePosition.x,mousePosition.y + relativePosition.y);
	SetPosition(mousePosition.x,mousePosition.y);
};