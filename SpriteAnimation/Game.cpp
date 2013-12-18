#include "Game.h"

bool Game::run;

Game::Game(){
	run = true;
	window = new sf::RenderWindow();
	sf::ContextSettings settings;
	Drawn::SetUp(window);
	settings.antialiasingLevel = 8;
	window->setKeyRepeatEnabled(false);
	window->create(sf::VideoMode(1920, 1080), "Exploration II",sf::Style::Fullscreen,settings);
	window->setVerticalSyncEnabled(false);
	OnStart();
	CreatePanels();
	Actor::elapsedTimeClock->restart();
	Clock::timeSpeed = 1;
	Clock::myClock.restart();
};
void Game::Update(){
	Clock::UpdateAll();
	CheckForInput();
	UpdatePanels();
	Drawn::DrawGame(*window);
	window->display();
}
void Game::OnStart(){
	Label::OnStart();
	Button::OnStart();
	RClickMenu::OnStart();
	SlicedSprite::OnStart();
	GamePanel::currentMouseElement = new Drawn();
};
void Game::CreatePanels(){
	textPanel = new TextPanel(1004,175);
	textPanel->SetPosition(292,748);
	spritePanel = new SpritePanel(1526,922);
	Actor::elapsedTimeClock = new Clock();
	spritePanel->SetPosition(-8,-8);
	User::player->GetBank()->SetPosition(spritePanel->GetPosition().x + ((spritePanel->GetSize().x - 480) / 2),spritePanel->GetPosition().y + ((spritePanel->GetSize().y - 480) / 2));
	actionBar = new ActionBar(1020,88);
	actionBar->SetPosition(523,961);
	statsPanel = new StatsPanel(320,420);
	statsPanel->SetPosition(1566,16);
	hudPanel = new HUDPanel(User::player, 485,90);
	hudPanel->SetPosition(16,961);
};
void Game::UpdatePanels(){
	spritePanel->Update();
	actionBar->Update();
	statsPanel->Update();
	hudPanel->Update();
	textPanel->Update();
	User::player->GetLayered()->Update();
	User::player->GetBank()->Update();
};
void Game::HandleMouseMovement(sf::Event event){
	sf::Vector2i temp(event.mouseMove.x,event.mouseMove.y);
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
	else if(User::player->GetLayered()->GetBounds().Contains(temp.x,temp.y)){
		User::player->GetLayered()->OnHover(temp);
		GamePanel::currentMousePanel = User::player->GetLayered();
	}
	else if(User::player->GetBank()->GetIsPanelOpen() && User::player->GetBank()->GetBounds().Contains(temp.x,temp.y)){
		User::player->GetBank()->OnHover(temp);
		GamePanel::currentMousePanel = User::player->GetBank();
	}
	else if(actionBar->GetBounds().Contains(temp.x,temp.y)){
		actionBar->OnHover(temp);
		GamePanel::currentMousePanel = actionBar;
	}
	else if(spritePanel->GetBounds().Contains(temp.x,temp.y)){
		spritePanel->OnHover(sf::Vector2i(temp));
		GamePanel::currentMousePanel = spritePanel;
	}
	else if(hudPanel->GetBounds().Contains(temp.x,temp.y)){
		hudPanel->OnHover(temp);
		GamePanel::currentMousePanel = hudPanel;
	}
};
void Game::HandleMouseClick(sf::Event event){
	if(sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left){ //Eventually will iterate through these
		sf::Vector2i temp(event.mouseButton.x,event.mouseButton.y);
		if(RClickMenu::GetIsOpen()){
			temp = sf::Vector2i(temp.x - RClickMenu::currentPanel->GetPosition().x , temp.y - RClickMenu::currentPanel->GetPosition().y);
			std::cout << temp.x << "," << temp.y << std::endl;
			if(!RClickMenu::Contains(sf::Vector2f(temp)))
				RClickMenu::Close();
		}
		else{
			if(textPanel->GetBounds().Contains(temp.x,temp.y) && textPanel->GetIsPanelOpen())
				textPanel->OnClick(temp);
			else if(spritePanel->GetBounds().Contains(temp.x,temp.y))
				spritePanel->OnClick(temp);
			if(User::player->GetInventory()->GetBounds().Contains(temp.x,temp.y)&& User::player->GetLayered()->panels[User::player->GetLayered()->currentPanel] == User::player->GetInventory())
				User::player->GetInventory()->OnClick(temp);
			else{
				if(User::player->GetEquiped()->GetBounds().Contains(temp.x,temp.y) && User::player->GetLayered()->panels[User::player->GetLayered()->currentPanel] == User::player->GetEquiped())
					User::player->GetEquiped()->OnClick(temp);
				else if(User::player->GetLevelPanel()->GetBounds().Contains(temp.x,temp.y)){
					User::player->GetLevelPanel()->OnClick(temp);
					std::cout << "Layered Panel Clicked" << std::endl;
				}
			}
			if(User::player->GetBank()->GetIsPanelOpen() && User::player->GetBank()->GetBounds().Contains(temp.x,temp.y))
				User::player->GetBank()->OnClick(temp);
			if(actionBar->GetBounds().Contains(temp.x,temp.y))
				actionBar->OnClick(temp);
			if(hudPanel->GetBounds().Contains(temp.x,temp.y))
				hudPanel->OnClick(temp);
			if(statsPanel->GetBounds().Contains(temp.x,temp.y))
				statsPanel->OnClick(temp);
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
};
void Game::HandleMouseScroll(sf::Event event){
	/*
	if(User::player->GetBank()->GetIsPanelOpen()){ 
		if(event.mouseWheel.delta > 0)
			User::player->GetBank()->ScrollUp();
		else
			User::player->GetBank()->ScrollDown();
	}
	*/
};
void Game::CheckForInput(){
	sf::Event event;
	while (Drawn::gameWindow->pollEvent(event)){
		switch(event.type){
			case(sf::Event::MouseMoved): 
				HandleMouseMovement(event);
				break;
			case(sf::Event::MouseButtonPressed):
				HandleMouseClick(event);
				break;
			case(sf::Event::Closed):
				Drawn::gameWindow->close();
				break;
			case(sf::Event::MouseWheelMoved):
				HandleMouseScroll(event);
				break;
		}
    }
};