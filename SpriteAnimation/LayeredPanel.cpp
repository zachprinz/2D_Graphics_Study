#include "LayeredPanel.h"
#include "User.h"
#include "Button.h"
#include "SlicedSpriteCreator.h"
#include <iostream>

LayeredPanel* LayeredPanel::instance;


LayeredPanel::LayeredPanel(std::vector<GamePanel*> panels) : GamePanel(GetLayeredPanelSize(panels).x ,GetLayeredPanelSize(panels).y + 104,"LayeredPanel"){
	this->panels = panels;
	currentPanel = 0;
	SetUp();
};
LayeredPanel::LayeredPanel(){

};
void LayeredPanel::AddElement(std::string,Drawn*){

};
void LayeredPanel::SetUp(){
	largestSubpanelSize = GetLayeredPanelSize(panels);
	Drawn panelButton;
	int spaceBetweenButtons = ((largestSubpanelSize.x) - (80*panels.size()))/(panels.size() + 1);
	for(int x = 0; x < panels.size(); x++){
		Button* tempButton = new Button((spaceBetweenButtons * (x+1)) + (80 * x), largestSubpanelSize.y + 20, new SlicedSprite((spaceBetweenButtons * (x+1)) + (80 * x), largestSubpanelSize.y + 20,80.0,80.0,SlicedSprite::SpriteStyle::WoodPanel), "buttonImages/" + panels[x]->GetName() + ".png");
		tempButton->SetTarget(this);
		tempButton->SetFunction(panels[x]->GetName());
		//tempButton->CenterForeground();
		dynamicElements.insert(MyPair("Button" + panels[x]->GetName(),tempButton));
	}
	Drawn* background = new Drawn(new SlicedSprite(0,largestSubpanelSize.y + 16,(float)((panel.getSize().x) + 16),(float)(panel.getSize().y - largestSubpanelSize.y),SlicedSprite::SpriteStyle::Pixel));
	background->SetPosition(sf::Vector2f(0,largestSubpanelSize.y + 16));
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
bool LayeredPanel::CheckUpdate(){
	return true;
};
sf::Vector2i LayeredPanel::GetLayeredPanelSize(std::vector<GamePanel*> panels){
	int largestX = 0;
	int largestY = 0;
	sf::Vector2i panelSize;
	for(int x = 0; x < panels.size(); x++){
		panelSize = panels[x]->GetBounds().GetSize(); 
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
void LayeredPanel::UpdateCurrentPanel(sf::RenderWindow& panel){
	panels[currentPanel]->Update(panel);
};

