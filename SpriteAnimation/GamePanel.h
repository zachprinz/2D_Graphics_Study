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
	GamePanel(int,int,std::string);
	GamePanel();
	typedef std::map<std::string, Drawn*> ElementList;
	typedef std::pair<std::string, Drawn*> MyPair;
	ElementList dynamicElements;
	ElementList staticElements;
	ElementList backgroundElements;
	bool GetIsPanelOpen();
	virtual void Update(sf::RenderWindow&);
	void DrawToWindow(sf::RenderWindow&);
	void InitiateElements();
	virtual void UpdateElements();
	void Open();
	void Close();
	virtual void OnClick(sf::Vector2i);
	virtual void OnRClick(sf::Vector2i);
	virtual void OnButtonEvent(std::string);
	virtual bool CheckUpdate();
	static GamePanel* currentMousePanel;
	static Drawn* currentMouseElement;
	bool doUpdate;
	void OnHover(sf::Vector2i);
	virtual void SetPosition(int,int);
	bool drawCollision;
	virtual AABB GetBounds();
	virtual void RemoveDynamicElement(std::string);
	ElementList* GetDynamicElements();
	sf::RenderTexture& GetRenderPanel();
	sf::Vector2f GetPosition();
	void SetUp();
	std::string GetName();
	sf::Vector2i GetSize();
	sf::Vector2<Drawn*> nonVertexElements;
protected:
	bool updateElements;
	bool createPanelLabel;
	std::string panelName;
	AABB panelBounds;
	sf::RenderTexture panel;
	sf::RenderTexture backgroundPanel;
	sf::Sprite backgroundPanelSprite;
	sf::Sprite panelSprite;
	bool isPanelOpen;
};

#endif