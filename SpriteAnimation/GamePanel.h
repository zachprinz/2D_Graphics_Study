#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "AABB.h"

class Drawn;
class GamePanel
{
public:
	static GamePanel* currentMousePanel;
	static Drawn* currentMouseElement;
	static Drawn* currentPressedElement;

	GamePanel(int,int,std::string);
	GamePanel();
	typedef std::map<std::string, Drawn*> ElementList;
	typedef std::pair<std::string, Drawn*> MyPair;
	ElementList dynamicElements;
	ElementList staticElements;
	ElementList backgroundElements;
	bool GetIsPanelOpen();
	virtual void Update();
	void InitiateElements();
	virtual void UpdateElements();
	virtual void Open();
	virtual void Close();
	//void OnClick(sf::Vector2i);
	void OnMousePress(sf::Vector2i);
	void OnRClick(sf::Vector2i);
	virtual void OnButtonEvent(std::string);
	virtual void OnHover(sf::Vector2i);
	virtual void SetPosition(int,int);
	virtual AABB GetBounds();
	virtual void RemoveDynamicElement(std::string);
	ElementList* GetDynamicElements();
	sf::RenderTexture& GetRenderPanel();
	sf::Vector2f GetPosition();
	void SetUp();
	std::string GetName();
	sf::Vector2f GetSize();
	sf::Sprite panelSprite;
	virtual sf::Vector2f GetViewLowerBound();
protected:
	bool CheckHover(Drawn* check,sf::Vector2i point);
	sf::Vector2f mySize;
	std::string panelName;
	AABB panelBounds;
	sf::RenderTexture panel;
	sf::RenderTexture backgroundPanel;
	sf::Sprite backgroundPanelSprite;
	bool isPanelOpen;
};

#endif