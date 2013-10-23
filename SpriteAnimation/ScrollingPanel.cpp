#include "ScrollingPanel.h"
#include "SlicedSpriteCreator.h"
#include "Button.h"
#include <iostream>

ScrollingPanel::ScrollingPanel(int x,int y,int visibleX,int visibleY) : GamePanel(x + 58,y,"Scrolling Window"){
	scrollView.reset(sf::FloatRect(0,0,visibleX,visibleY - 80));
	scrollView.setViewport(sf::FloatRect(0,0,0.9f,0.5f));
	visibleSize = sf::Vector2f(visibleX,visibleY);
	backgroundWindowTexture = SlicedSpriteCreator::GetSlicedTexture(visibleX + 58,visibleY + 16,SlicedSpriteCreator::Pixel);
	scrollBarBackgroundTexture = SlicedSpriteCreator::GetSlicedScrollBar(visibleY - 80);
	Drawn* backgroundWin = new Drawn(backgroundWindowTexture);
	Drawn* scrollBarBackground = new Drawn(scrollBarBackgroundTexture);
	backgroundWin->SetLocation(GetPosition().x + 6,GetPosition().y);
	scrollBarBackground->SetLocation(GetPosition().x + visibleX + 30,GetPosition().y + 48);
	backgroundElements.insert(MyPair("background",backgroundWin));
	backgroundElements.insert(MyPair("scrollBarBackground",scrollBarBackground));
	Button* scrollUpButton = new Button(scrollBarBackground->GetPositionOnPanel().x - (0.5 *(40 - scrollBarBackground->GetSprite()->getLocalBounds().width)),scrollBarBackground->GetPositionOnPanel().y - 35,"scrollbar/PgUp.png","blank.png");
	scrollUpButton->SetTarget(this);
	scrollUpButton->SetFunction("ScrollUp");
	backgroundElements.insert(MyPair("scrollUpButton",scrollUpButton));
	Button* scrollDownButton = new Button(scrollBarBackground->GetPositionOnPanel().x - (0.5 *(40 - scrollBarBackground->GetSprite()->getLocalBounds().width)),scrollBarBackground->GetPositionOnPanel().y + scrollBarBackground->GetSprite()->getLocalBounds().height,"scrollbar/PgUp.png","blank.png");
	scrollDownButton->SetTarget(this);
	scrollDownButton->SetFunction("ScrollDown");
	backgroundElements.insert(MyPair("scrollDownButton",scrollDownButton));
	Button* scrollDragButton = new Button(scrollBarBackground->GetPositionOnPanel().x - (0.5 *(30 - scrollBarBackground->GetSprite()->getLocalBounds().width)),scrollBarBackground->GetPositionOnPanel().y - 75,"scroll.png","blank.png");
	scrollDragButton->SetTarget(this);
	scrollDragButton->SetFunction("Scrolling");
	backgroundElements.insert(MyPair("scrollDragButton",scrollDragButton));
	panel.setView(scrollView);
	panelSprite.setPosition(panelSprite.getPosition().x + 13,panelSprite.getPosition().y + 80);
};
ScrollingPanel::ScrollingPanel(){

};
void ScrollingPanel::Update(sf::RenderWindow& window){
	if(isPanelOpen){
		GamePanel::Update(window);
	}
};
void ScrollingPanel::OnClick(sf::Vector2i temp){
	std::cout << "Scrolling Panel OnClick Called." << std::endl;
	for(MyPair x: backgroundElements){
		if(x.first != "background" && x.first != "scrollBarBackground" && x.second->GetSprite()->getGlobalBounds().contains(temp.x - backgroundPanelSprite.getPosition().x,temp.y - backgroundPanelSprite.getPosition().y)){
			std::cout << "Found a background sprite clicked on." << std::endl;
			x.second->OnClick();
		}
	}
	temp.y += scrollView.getCenter().y - (scrollView.getSize().y / 2);
	std::cout << "Target Point: " << temp.x << "," << temp.y << std::endl;
	for(MyPair x: dynamicElements){
		if(x.second->GetSprite()->getGlobalBounds().contains(temp.x - panelSprite.getPosition().x,temp.y - panelSprite.getPosition().y)){
			x.second->OnClick();
		}
		else{
			sf::FloatRect rect = x.second->GetSprite()->getGlobalBounds();
		}
	}
};
void ScrollingPanel::OnRClick(sf::Vector2i temp){
	temp.y += scrollView.getCenter().y - (scrollView.getSize().y / 2);
	GamePanel::OnRClick(temp);
};
void ScrollingPanel::ScrollDown(){
	if(scrollView.getCenter().y + (scrollView.getSize().y / 2) <= panel.getSize().y){
		scrollView.reset(sf::FloatRect(0,scrollView.getCenter().y - (scrollView.getSize().y / 2) + 12,visibleSize.x,visibleSize.y-80));
		panel.setView(scrollView);
	}
};
void ScrollingPanel::ScrollUp(){
	if(scrollView.getCenter().y - (scrollView.getSize().y / 2) >= 0){
		scrollView.reset(sf::FloatRect(0,scrollView.getCenter().y - (scrollView.getSize().y / 2) - 12,visibleSize.x,visibleSize.y-80));
		panel.setView(scrollView);
	}
};
bool ScrollingPanel::CheckUpdate(){
	return true;
};
void ScrollingPanel::SetPosition(int x, int y){
	GamePanel::SetPosition(x,y);
	panelSprite.setPosition(panelSprite.getPosition().x + 13,panelSprite.getPosition().y + 80);
};
Rectangle* ScrollingPanel::GetBounds(){
	sf::FloatRect temp = backgroundPanelSprite.getGlobalBounds();
	return &Rectangle(temp.left,temp.top,temp.width,temp.height);
};
void ScrollingPanel::OnButtonEvent(std::string function){
	if(function == "ScrollUp")
		ScrollUp();
	else if(function == "ScrollDown")
		ScrollDown();
};