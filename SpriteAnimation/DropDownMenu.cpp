#include "DropDownMenu.h"
#include "GamePanel.h"

DropDownMenu* DropDownMenu::instance;
bool DropDownMenu::isOpen = false;

DropDownMenu::DropDownMenu(int x, int y, std::vector<std::string> buttons) : GuiElement(x,y,GetSlicedBackground(x,y,buttons),"blank.png"){
	currentPanel = GamePanel::currentMousePanel;
    instance = this;
    title = new Label(x + 8,y + 8,"blank.png",Label::Fonts::Game,buttons[0]);
    GamePanel::currentMousePanel->dynamicElements.insert(GamePanel::MyPair(buttons[0],title));
	this->SetZ(2);
	base->SetZ(2);
    GamePanel::currentMousePanel->dynamicElements.insert(GamePanel::MyPair("dropDownBackground",this));
	float labelHeight = title->GetText()->getGlobalBounds().height;
	float buttonHeight = (Button(0,0,SlicedSprite::SpriteStyle::WoodPanel,buttons[0])).GetSize().y;
    for(int z = 1; z < buttons.size(); z++){
	this->buttons.push_back(new Button(x + 4,y + ((z-1)*(buttonHeight + 8)) + 50,buttons[z]));
	this->buttons[this->buttons.size() -  1]->SetFunction(buttons[z]);
	this->buttons[this->buttons.size() -  1]->SetZ(1);
	GamePanel::currentMousePanel->dynamicElements.insert(GamePanel::MyPair(buttons[z],this->buttons[this->buttons.size() - 1]));
	}
    isOpen = true;
    SetZ(2);
};
void DropDownMenu::Update(GamePanel* panel){
    base->Update(panel);
};
void DropDownMenu::SetTarget(GuiElement* element){
    for(int x = 0; x < buttons.size(); x++){
	buttons[x]->SetTarget(element);
	}
}
void DropDownMenu::SetOrgin(Orgins orgin){
	for(int x = 0; x < buttons.size(); x++){
		Button* tempLabel = buttons[x];
		sf::Sprite* tempSprite = tempLabel->GetSprite();
		sf::Vector2f halfSize = sf::Vector2f(tempLabel->GetSize().x / 2,tempLabel->GetSize().y / 2);
		sf::Text* tempText = ((Label*)tempLabel->foreground)->GetText();
		switch(orgin){
			case(TopLeft):
				tempLabel->SetOrgin(0,0);
				((Label*)tempLabel->foreground)->CenterText();
				break;
			case(TopRight):
				tempLabel->SetOrgin(halfSize.x * 2,0);
				((Label*)tempLabel->foreground)->CenterText();
				break;
			case(BottomLeft):
				tempLabel->SetOrgin(0,halfSize.y * 2);
				((Label*)tempLabel->foreground)->CenterText();
				break;
			case(BottomRight):
				tempLabel->SetOrgin(halfSize.x * 2,halfSize.y * 2);
				((Label*)tempLabel->foreground)->CenterText();
				break;
		}
	}
};
void DropDownMenu::Close(){
	currentPanel->RemoveDynamicElement("dropDownBackground");
	for(int x = 0; x < buttons.size(); x++){
		currentPanel->RemoveDynamicElement(((Label*)buttons[x]->foreground)->GetText()->getString());
	}
	currentPanel->RemoveDynamicElement(title->GetText()->getString());
	isOpen = false;
};
SlicedSprite* DropDownMenu::GetSlicedBackground(int x,int y,std::vector<std::string> strings){
    return new SlicedSprite(x,y,GetLongestTextWidth(strings),GetTextHeight(strings),SlicedSprite::SpriteStyle::RightClick);
};
float DropDownMenu::GetLongestTextWidth(std::vector<std::string> strings){
    float longest = 0;
    for(int x = 0; x < strings.size(); x++){
	float temp = (sf::Text(strings[x],Label::fonts[0],30)).getGlobalBounds().width;
	if(temp > longest)
		longest = temp;
	}
    return longest;
};
float DropDownMenu::GetTextHeight(std::vector<std::string>strings){
    float buttonHeight = (Button(0,0,SlicedSprite::SpriteStyle::WoodPanel,strings[0])).GetSize().y;
    return 50 + ((strings.size() - 1) * (8+ buttonHeight));
};
void DropDownMenu::OnClick(){
    	int mousePosX = sf::Mouse::getPosition(*Drawn::gameWindow).x - currentPanel->GetPosition().x;
	int mousePosY = sf::Mouse::getPosition(*Drawn::gameWindow).y - currentPanel->GetPosition().y;
    for(int x = 0; x < buttons.size(); x++){
	std::cout << mousePosX << std::endl;
		    if(buttons[x]->GetBounds().Contains(mousePosX,mousePosY)){
			buttons[x]->OnClick();
			Close();
			x = 999;
		    }
	}
};