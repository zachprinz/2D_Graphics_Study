#include <SFML/Graphics.hpp>
#include "RClickable.h"
#include "RClickMenu.h"
#include <iostream>
#include "GamePanel.h"
#include "InventoryPanel.h"
#include "BankPanel.h"

RClickable::RClickable(std::string textureName) : Drawn(textureName){
	isMenuOpen = false;
	rClickEnabled = false;
};
RClickable::RClickable(sf::Texture text) : Drawn(text){
	isMenuOpen = false;
	rClickEnabled = false;
};
RClickable::RClickable(){

};
void RClickable::OnClick(){

};
void RClickable::OnHover(bool hovered){

};
void RClickable::OnRClick(sf::Vector2i mousePos,GamePanel* panel){ //TODO: Delete old menu contents.
	if(rClickEnabled){
		std::cout << "RightClickable Reached" << std::endl;
		RClickMenu::Reset(mousePos.x,mousePos.y,name, this, panel);
		isMenuOpen = true;
		for(int x = 0; x < rClickOptions.size(); x++){
			RClickMenu::AddOption(mousePos.x,mousePos.y,rClickOptions[x]);
		}
		if(panel == (GamePanel*)(InventoryPanel::instance)){
			if(BankPanel::instance->GetIsPanelOpen())
				RClickMenu::AddOption(mousePos.x,mousePos.y,3);
		}
		mousePos = sf::Vector2i(mousePos.x + panel->GetPosition().x, mousePos.y + panel->GetPosition().y);
		if(!panel->GetBounds()->Contains(mousePos.x,(RClickMenu::labels.size() * RClickMenu::labels[0]->GetSprite()->getLocalBounds().height) + mousePos.y + 10)){
				if(!panel->GetBounds()->Contains(RClickMenu::labels[0]->GetSprite()->getLocalBounds().width + mousePos.x + 10,mousePos.y))
					RClickMenu::SetOrgin(RClickMenu::BottomRight);
				else
					RClickMenu::SetOrgin(RClickMenu::TopLeft);
		}
		else{
			if(!panel->GetBounds()->Contains(RClickMenu::labels[0]->GetSprite()->getLocalBounds().width + mousePos.x + 10,mousePos.y))
					RClickMenu::SetOrgin(RClickMenu::TopRight);
				else
					RClickMenu::SetOrgin(RClickMenu::TopLeft);
		}
	}
};
void RClickable::AddRClickOption(int x){
	rClickOptions.push_back(x);	
};
void RClickable::Update(sf::RenderTexture& panel){

};
void RClickable::Update(GamePanel* panel){

};
void RClickable::EnableRClick(std::string myName){
	rClickEnabled = true;
	name = myName;
};
void RClickable::DisableRClick(){
	rClickEnabled = false;
}
bool RClickable::GetRClickEnabled(){
	return rClickEnabled;
};
void RClickable::OnMenuSelection(std::string){

}


