#include <SFML/Graphics.hpp>
#include "RoomTile.h"
#include "Room.h"
#include "User.h"
#include "Enemy.h"
#include "GroundItem.h"
#include "Bank.h"
#include "SpritePanel.h"
#include "InventoryPanel.h"
#include "Label.h"
#include "RClickMenu.h"
#include <iostream>
#include "BankPanel.h"
#include "Button.h"
#include <MapLoader.h>
#include "SlicedSpriteCreator.h"
#include "SlicedSprite.h"
#include "MapPanel.h"
#include "ActionBar.h"
#include "StatsPanel.h"
#include "ProgressBar.h"
#include "HUDPanel.h"
#include "TextPanel.h"

int main()
{
	Drawn::SetUp();
    sf::Clock clock;
    float lastTime = 0;
	sf::Text fps;
	fps.setCharacterSize(22);
	fps.setPosition(5,1);
	std::cout << "Test" << std::endl;
	sf::Font font;
	font.loadFromFile("arial.ttf");
	fps.setColor(sf::Color::Red);
	fps.setFont(font);

	sf::RenderWindow window;
	sf::Clock elapsedTime;
	sf::ContextSettings settings;
	bool debug = true;

	settings.antialiasingLevel = 8;
	window.setKeyRepeatEnabled(false);
	window.create(sf::VideoMode(1920, 1080), "Exploration II",sf::Style::Fullscreen,settings);
	window.setPosition(sf::Vector2i(0,0));
	window.setVerticalSyncEnabled(false);
	window.setFramerateLimit(300);
	sf::Sprite loadingSprite;
	loadingSprite.setTexture(Drawn::gameTexture);
	loadingSprite.setTextureRect(Drawn::GetTextureFromAtlas("loading.png"));
	loadingSprite.setPosition(550,300);
	window.clear(sf::Color(255,255,255,255));
	window.draw(loadingSprite);
	window.display();

	Label::OnStart();
	Button::OnStart();
	RClickMenu::OnStart();
	SlicedSprite::OnStart();
	SlicedSpriteCreator::OnStart();

	TextPanel textPanel(1004,175);
	textPanel.SetPosition(62,740);

	SpritePanel spritePanel(1024,800);
	spritePanel.SetPosition(52,125);
	User::player->GetBank()->SetPosition(SpritePanel::instance->GetPosition().x + ((SpritePanel::instance->GetSize().x - 480) / 2),SpritePanel::instance->GetPosition().y + ((SpritePanel::instance->GetSize().y - 480) / 2));

	std::cout << "Loading Action Bar." << std::endl;
	ActionBar actionBar(1024,88);
	actionBar.SetPosition(52,941);

	std::cout << "Loading Map Panel." << std::endl;
	MapPanel mapPanel(375,300);
	mapPanel.SetPosition(1493,19);

	std::cout << "Loading Stats Panel." << std::endl;
	StatsPanel statsPanel(375,480);
	statsPanel.SetPosition(1493,445);

	std::cout << "Loading HUD Panels." << std::endl;
	HUDPanel hudPanel(User::player, 485,90);
	hudPanel.SetPosition(52,19);
	HUDPanel::instance = &hudPanel;

	HUDPanel hudPanel2(User::player, 485, 90);
	hudPanel2.SetPosition(590,19);
	HUDPanel::instanceEnemy = &hudPanel2;

	Actor::elapsedTimeClock.restart();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
			switch(event.type){
				case(sf::Event::MouseMoved): {
					sf::Vector2i temp(event.mouseMove.x,event.mouseMove.y);
					if(spritePanel.GetBounds().Contains(temp.x,temp.y)){
						spritePanel.OnHover(sf::Vector2i(temp.x + spritePanel.view.getCenter().x - 512, temp.y + (float)spritePanel.view.getCenter().y - 400));
						GamePanel::currentMousePanel = &spritePanel;
					}
					if(User::player->GetLayered()->GetBounds().Contains(temp.x,temp.y)){
						User::player->GetLayered()->OnHover(temp);
						GamePanel::currentMousePanel = User::player->GetLayered();
					}
					if(User::player->GetInventory()->GetBounds().Contains(temp.x,temp.y) && User::player->GetLayered()->panels[User::player->GetLayered()->currentPanel] == User::player->GetInventory()){
						User::player->GetInventory()->OnHover(temp);
						GamePanel::currentMousePanel = User::player->GetInventory();
					}
					else if(User::player->GetEquiped()->GetBounds().Contains(temp.x,temp.y) && User::player->GetLayered()->panels[User::player->GetLayered()->currentPanel] == User::player->GetEquiped()){
						User::player->GetEquiped()->OnHover(temp);
						GamePanel::currentMousePanel = User::player->GetEquiped();
					}
					else if(User::player->GetLevelPanel()->GetBounds().Contains(temp.x,temp.y) && User::player->GetLayered()->panels[User::player->GetLayered()->currentPanel] == User::player->GetLevelPanel()){
						User::player->GetLevelPanel()->OnHover(temp);
						GamePanel::currentMousePanel = User::player->GetLevelPanel();
					}
					else if(User::player->GetBank()->GetIsPanelOpen() && User::player->GetBank()->GetBounds().Contains(temp.x,temp.y)){
						User::player->GetBank()->OnHover(temp);
						GamePanel::currentMousePanel = User::player->GetBank();
					}
					else if(actionBar.GetBounds().Contains(temp.x,temp.y)){
						actionBar.OnHover(temp);
						GamePanel::currentMousePanel = &actionBar;
					}
											 }
					break;
				case(sf::Event::MouseButtonPressed): {
				if(sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left){ //Eventually will iterate through these
					sf::Vector2i temp(event.mouseButton.x,event.mouseButton.y);
					if(RClickMenu::GetIsOpen()){
						RClickMenu::currentPanel->doUpdate = true;
						temp = sf::Vector2i(temp.x - RClickMenu::currentPanel->GetPosition().x , temp.y - RClickMenu::currentPanel->GetPosition().y);
						std::cout << temp.x << "," << temp.y << std::endl;
						if(!RClickMenu::Contains(sf::Vector2f(temp)))
							RClickMenu::Close();
					}
					else{
					if(textPanel.GetBounds().Contains(temp.x,temp.y) && textPanel.GetIsPanelOpen())
						textPanel.OnClick(temp);
					else if(spritePanel.GetBounds().Contains(temp.x,temp.y))
						spritePanel.OnClick(temp);
					if(User::player->GetInventory()->GetBounds().Contains(temp.x,temp.y)&& User::player->GetLayered()->panels[User::player->GetLayered()->currentPanel] == User::player->GetInventory())
						User::player->GetInventory()->OnClick(temp);
					else{
						if(User::player->GetEquiped()->GetBounds().Contains(temp.x,temp.y))
							User::player->GetEquiped()->OnClick(temp);
						else if(User::player->GetLevelPanel()->GetBounds().Contains(temp.x,temp.y))
							User::player->GetLevelPanel()->OnClick(temp);
					}
					if(User::player->GetBank()->GetIsPanelOpen() && User::player->GetBank()->GetBounds().Contains(temp.x,temp.y))
						User::player->GetBank()->OnClick(temp);
					if(actionBar.GetBounds().Contains(temp.x,temp.y))
						actionBar.OnClick(temp);
					if(statsPanel.GetBounds().Contains(temp.x,temp.y))
						statsPanel.OnClick(temp);
					if(User::player->GetLayered()->panels[User::player->GetLayered()->currentPanel]->GetBounds().Contains(temp.x,temp.y)){
						User::player->GetLayered()->panels[User::player->GetLayered()->currentPanel]->OnClick(temp);
					}
					else if(User::player->GetLayered()->GetBounds().Contains(temp.x,temp.y))
						User::player->GetLayered()->OnClick(temp);
					}
				}
				if(sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Right){ //Eventually will iterate through these
					if(!RClickMenu::GetIsOpen()){
						sf::Vector2i temp(event.mouseButton.x,event.mouseButton.y);
						if(User::player->GetInventory()->GetBounds().Contains(temp.x,temp.y) && User::player->GetLayered()->panels[User::player->GetLayered()->currentPanel] == User::player->GetInventory())
							User::player->GetInventory()->OnRClick(temp);
						else if(User::player->GetEquiped()->GetBounds().Contains(temp.x,temp.y))
							User::player->GetEquiped()->OnRClick(temp);
						if(User::player->GetBank()->GetIsPanelOpen() && User::player->GetBank()->GetBounds().Contains(temp.x,temp.y))
							User::player->GetBank()->OnRClick(temp);
					}
				}
													 }
				break;
				case(sf::Event::Closed):
					window.close();
				break;
				case(sf::Event::MouseWheelMoved):{
					if(User::player->GetBank()->GetIsPanelOpen()){//GamePanel::currentMousePanel == User::player->GetBank() && 
						if(event.mouseWheel.delta > 0)
							User::player->GetBank()->ScrollUp();
						else
							User::player->GetBank()->ScrollDown();
					}							 
					}
				break;
			}
        }
        window.clear();
		spritePanel.Update(window);
		actionBar.Update(window);
		//mapPanel.Update(window);
		statsPanel.Update(window);
		hudPanel.Update(window);
		textPanel.Update(window);
		hudPanel2.Update(window);
		User::player->GetLayered()->Update(window);
		User::player->GetLayered()->UpdateCurrentPanel(window);
		User::player->GetBank()->Update(window);
		Drawn::DrawGame(window);
		window.display();
    }
    return 0;
}