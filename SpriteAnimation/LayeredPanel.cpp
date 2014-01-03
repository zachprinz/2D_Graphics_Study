#include "LayeredPanel.h"
#include "User.h"
#include "Button.h"
#include <iostream>

LayeredPanel* LayeredPanel::instance;


LayeredPanel::LayeredPanel(std::vector<GamePanel*> panels) : GamePanel(GetLayeredPanelSize(panels).x ,GetLayeredPanelSize(panels).y + 104,"LayeredPanel"){
	this->panels = panels;
	currentPanel = 0;
	SetUp();
};
LayeredPanel::LayeredPanel(){
};
void LayeredPanel::Update(){
	GamePanel::Update();
	panels[currentPanel]->Update();
};
void LayeredPanel::AddElement(std::string,Drawn*){

};
void LayeredPanel::SetUp(){
	largestSubpanelSize = GetLayeredPanelSize(panels);
	std::cout << "Largest Panel Size X: " << largestSubpanelSize.x << " Y: " << largestSubpanelSize.y << std::endl;
	Drawn panelButton;
	int spaceBetweenButtons = ((largestSubpanelSize.x) - (80*panels.size()))/(panels.size() + 1);
	for(int x = 0; x < panels.size(); x++){
		Button* tempButton = new Button((spaceBetweenButtons * (x+1)) + (80 * x), largestSubpanelSize.y + 28, "attacktextures/background.png", "buttonImages/" + panels[x]->GetName() + ".png");
		tempButton->SetTarget(this);
		tempButton->SetFunction(panels[x]->GetName());
		tempButton->CenterForeground();
		dynamicElements.insert(MyPair("Button" + panels[x]->GetName(),tempButton));
	}
	SlicedSprite* background = new SlicedSprite(-8,largestSubpanelSize.y + 14,(float)((panel.getSize().x) + 16),(float)(88 + 16),SlicedSprite::SpriteStyle::Pixel);
	backgroundElements.insert(MyPair("Background", background));
};
void LayeredPanel::OnButtonEvent(std::string btnFunction){
	std::cout << "Panel Switch Button Clicked" << std::endl;
	if(btnFunction == "Levels" && panels[currentPanel]->GetName() != "Levels"){
		for(int x = 0; x < panels.size(); x++){
			if(panels[x]->GetName() == "Levels")
				((LevelPanel*)panels[x])->ResetButtonPositions();
		}
	}
	for(int x = 0; x < panels.size(); x++){
		if(panels[x]->GetName() == btnFunction){
			currentPanel = x;
			break;
		}
	}
};
sf::Vector2i LayeredPanel::GetLayeredPanelSize(std::vector<GamePanel*> panels){
	int largestX = 0;
	int largestY = 0;
	sf::Vector2f panelSize;
	for(int x = 0; x < panels.size(); x++){
		panelSize = panels[x]->GetSize(); 
		if(panelSize.x > largestX)
			largestX = panelSize.x;
		if(panelSize.y > largestY)
			largestY = panelSize.y;
	}
	sf::Vector2i temp = sf::Vector2i(largestX, largestY);
	return temp;
};
void LayeredPanel::UpdatePanelsPosition(){
	for(int x = 0; x < panels.size(); x++){
		panels[x]->SetPosition(GetPosition().x - 8,GetPosition().y - 8);
	}
};
void LayeredPanel::SetPosition(int x, int y){
	GamePanel::SetPosition(x,y);
	for(int z = 0; z < panels.size(); z++){
		panels[z]->SetPosition(x,y);
	};
};
void LayeredPanel::UpdateCurrentPanel(){
	panels[currentPanel]->Update();
};
void LayeredPanel::OnHover(sf::Vector2i temp){
	AABB temp2 = panels[currentPanel]->GetBounds();
	if(temp2.Contains(temp.x,temp.y)){
	    panels[currentPanel]->OnHover(temp);
	    GamePanel::currentMousePanel = panels[currentPanel];
	}
	else
	    GamePanel::OnHover(temp);
};
