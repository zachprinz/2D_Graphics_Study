#include "ScrollingPanel.h"
#include "SlicedSpriteCreator.h"
#include <iostream>

ScrollingPanel::ScrollingPanel(int x,int y,int visibleX,int visibleY) : GamePanel(x,y,"Scrolling Window"){
	scrollView.reset(sf::FloatRect(0,0,visibleX,visibleY));
	scrollView.setViewport(sf::FloatRect(0,0,1.0f,0.5f));
	visibleSize = sf::Vector2f(visibleX,visibleY);
	backgroundWindowTexture = SlicedSpriteCreator::GetSlicedTexture(visibleX,visibleY + 16,SlicedSpriteCreator::Pixel);
	Drawn* backgroundWin = new Drawn(backgroundWindowTexture);
	backgroundWin->SetLocation(GetPosition().x + 6,GetPosition().y);
	backgroundElements.insert(MyPair("background",backgroundWin));
	panel.setView(scrollView);
};
ScrollingPanel::ScrollingPanel(){

};
void ScrollingPanel::Update(sf::RenderWindow& window){
	if(isPanelOpen){
		GamePanel::Update(window);
	}
};
void ScrollingPanel::OnClick(sf::Vector2i temp){
	temp.y += scrollView.getCenter().y - (scrollView.getSize().y / 2);
	GamePanel::OnClick(temp);
};
void ScrollingPanel::OnRClick(sf::Vector2i temp){
	temp.y += scrollView.getCenter().y - (scrollView.getSize().y / 2);
	GamePanel::OnRClick(temp);
};
void ScrollingPanel::ScrollDown(){
	if(scrollView.getCenter().y + (scrollView.getSize().y / 2) <= panel.getSize().y){
		scrollView.reset(sf::FloatRect(0,scrollView.getCenter().y - (scrollView.getSize().y / 2) + 12,visibleSize.x,visibleSize.y));
		panel.setView(scrollView);
	}
};
void ScrollingPanel::ScrollUp(){
	if(scrollView.getCenter().y - (scrollView.getSize().y / 2) >= 0){
		scrollView.reset(sf::FloatRect(0,scrollView.getCenter().y - (scrollView.getSize().y / 2) - 12,visibleSize.x,visibleSize.y));
		panel.setView(scrollView);
	}
};
bool ScrollingPanel::CheckUpdate(){
	return true;
};
void ScrollingPanel::SetPosition(int x, int y){
	//backgroundWindowSprite->setPosition(x,y);
	GamePanel::SetPosition(x,y);
};
Rectangle* ScrollingPanel::GetBounds(){
	return &Rectangle(GetPosition().x,GetPosition().y,visibleSize.x,visibleSize.y);
};