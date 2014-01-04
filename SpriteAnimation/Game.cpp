#include "Game.h"
#include "DropDownMenu.h"

bool Game::run;
bool Game::mouseIsPressed;
bool Game::verticleSync;
bool Game::fullscreen;
float Game::brightness;
bool Game::mute;
float Game::masterVolume;
float Game::effectVolume;
float Game::musicVolume;

Game::Game(){
	musicVolume = 1.0;
	effectVolume = 1.0;
	masterVolume = 1.0;
	brightness = 1.0;
	mouseIsPressed = false;
	gameState = GamePlay;
	run = true;
	window = new sf::RenderWindow();
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window->setKeyRepeatEnabled(false);
	window->create(sf::VideoMode(1920, 1080), "Exploration II",sf::Style::Fullscreen,settings);
	window->setVerticalSyncEnabled(false);
	Load();
};
void Game::StartLogOnScreen(){
	
};
void Game::Load(){
	Drawn::SetUp(window);
	OnStart();
	CreatePanels();
	Actor::elapsedTimeClock->restart();
	SpritePanel::instance->cameraMoveClock.restart();
	Clock::timeSpeed = 1;
	Clock::myClock.restart();
	panels.push_back(spritePanel);
	panels.push_back(actionBar);
	panels.push_back(statsPanel);
	panels.push_back(hudPanel);
	panels.push_back(textPanel);
	panels.push_back(User::player->GetLayered());
	panels.push_back(User::player->GetBank());
	panels.push_back(optionPanel);
}
void Game::Update(){
    switch(gameState){
	case(GamePlay):
		Clock::UpdateAll();
		CheckForInput();
		UpdatePanels();
		Drawn::DrawGame(*window);
		window->display();
	break;
	case(LogOn):
		int x = 0;
	break;
    }
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
	spritePanel = new SpritePanel(1920,1080);
	Actor::elapsedTimeClock = new Clock();
	spritePanel->SetPosition(-8,-8);
	User::player->GetBank()->SetPosition(spritePanel->GetPosition().x + ((spritePanel->GetSize().x - 480) / 2),spritePanel->GetPosition().y + ((spritePanel->GetSize().y - 480) / 2));
	actionBar = new ActionBar(1020,88);
	actionBar->SetPosition(523,970);
	statsPanel = new StatsPanel(320,420);
	statsPanel->SetPosition(1576,32);
	hudPanel = new HUDPanel(User::player, 485,90);
	hudPanel->SetPosition(16,970);
	optionPanel = new OptionPanel(800,800);
	optionPanel->SetPosition(390,60);
};
void Game::UpdatePanels(){
	spritePanel->Update();
	actionBar->Update();
	statsPanel->Update();
	hudPanel->Update();
	textPanel->Update();
	User::player->GetLayered()->Update();
	User::player->GetBank()->Update();
	optionPanel->Update();
};
void Game::HandleMouseMovement(sf::Event event){
	switch(gameState){
		case(GamePlay):{
	    	sf::Vector2i temp(event.mouseMove.x,event.mouseMove.y);
		for(int x = 0; x < panels.size(); x++){
			if(panels[x]->GetBounds().Contains(temp.x + 37,temp.y) || panels[x]->GetBounds().Contains(temp.x,temp.y)){
			        GamePanel::currentMousePanel = panels[x];
				panels[x]->OnHover(temp);
			}
		};
		}
		break;
		case(LogOn):
			int x = 0;
		break;
	}
};
void Game::HandleMouseClick(sf::Event event){
    switch(gameState){
	case(GamePlay):
	if(sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left){
		sf::Vector2i temp(event.mouseButton.x,event.mouseButton.y);
		if(DropDownMenu::instance->isOpen){
			if(!DropDownMenu::instance->GetBounds().Contains(temp.x - GamePanel::currentMousePanel->GetPosition().x,temp.y - GamePanel::currentMousePanel->GetPosition().y))
			    DropDownMenu::instance->Close();
			else
			    GamePanel::currentMousePanel->OnMousePress(temp);
		}
		else
			GamePanel::currentMousePanel->OnMousePress(temp);
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
	break;
	case(LogOn):
		int x = 0;
	break;
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
	if(mouseIsPressed && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
		GamePanel::currentPressedElement->OnMouseRelease();
		mouseIsPressed = false;
	}
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
void Game::UpdateSettings(){
	Drawn::gameWindow->setVerticalSyncEnabled(verticleSync);
	//Drawn::gameWindow->bright
};