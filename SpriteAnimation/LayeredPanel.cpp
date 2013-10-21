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
void LayeredPanel::Update(sf::RenderWindow& window){
	if(isPanelOpen){
		if(this->CheckUpdate() == true || doUpdate){
			panel.clear(sf::Color(0,0,0,0));
			backgroundPanel.clear(sf::Color(0,0,0,0));
			UpdateElements();
			panel.display();
			backgroundPanel.display();
			DrawToWindow(window);
			panels[currentPanel]->Update(window);
		}
		else{
			DrawToWindow(window);
		}
	}
};
void LayeredPanel::UpdateElements(){
	GamePanel::UpdateElements();
	for(int x = 0; x < panels.size(); x++){
		panels[x]->UpdateElements();
	}
};
void LayeredPanel::SetUp(){
	largestSubpanelSize = GetLayeredPanelSize(panels);
	sf::Texture buttonTexture;
	sf::Texture backgroundTexture = SlicedSpriteCreator::GetSlicedTexture(80,80,SlicedSpriteCreator::SpriteStyle::WoodPanel);
	int spaceBetweenButtons = ((largestSubpanelSize.x) - (80*panels.size()))/(panels.size() + 1);
	for(int x = 0; x < panels.size(); x++){
		buttonTexture.loadFromFile("buttonImages/" + panels[x]->GetName() + ".png");
		Button* tempButton = new Button((spaceBetweenButtons * (x+1)) + (80 * x), largestSubpanelSize.y + 20, backgroundTexture, buttonTexture);
		tempButton->SetTarget(this);
		tempButton->SetFunction(panels[x]->GetName());
		tempButton->CenterForeground();
		dynamicElements.insert(MyPair("Button" + panels[x]->GetName(),tempButton));
	}
	Drawn* background = new Drawn(SlicedSpriteCreator::GetSlicedTexture((panel.getSize().x) + 16,(panel.getSize().y - largestSubpanelSize.y),SlicedSpriteCreator::Pixel));
	background->SetLocation(0,largestSubpanelSize.y + 16);
	backgroundElements.insert(MyPair("Background", background));
};
void LayeredPanel::OnButtonEvent(std::string btnFunction){
	std::cout << "Panel Switch Button Clicked" << std::endl;
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
		panelSize = panels[x]->GetBounds()->GetSize(); 
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

