#ifndef DRAWN_H
#define DRAWN_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <boost\container\flat_set.hpp>

class GamePanel;
class Drawn
{
public:
	Drawn(std::string);
	Drawn(sf::Texture);
	Drawn();
	Drawn(bool);
	bool GetVisible();
	sf::Sprite* GetSprite();
	sf::Vector2f GetPositionOnPanel();
	virtual void Update(sf::RenderTexture&);
	virtual void Update(GamePanel*);
	virtual void OnClick();
	virtual void OnRClick(sf::Vector2i);
	virtual void OnHover(bool);
	void Move(float,float);
	sf::Texture GetSingleTexture();
	void SetLocation(float,float);
	static sf::IntRect GetTextureFromAtlas(std::string);
	sf::IntRect texturePart;
	static sf::Texture gameTexture;
	void MoveTo(int x,int y, sf::Time);
	static int GetDistance(sf::Vector2i,sf::Vector2i);
	bool GetIsMoving();
	void UpdateMove();
	void ResetPosition();
	void Return();
	void ExpandBy(float,sf::Time);
	void ReturnExpand();
	void UpdateExpand();
	bool GetIsExpanding();
	void Draw(GamePanel*);
	void DrawAdditional(GamePanel*);
	static sf::Vertex* GetVertexPointer();
	static void DrawGame(sf::RenderWindow&);
	static void SetUp();
	static int quadCount;
	int z;
	bool operator<(Drawn const& drawn) const{return(z<drawn.z);};
	static boost::container::flat_set<Drawn*> vertexPointers;
	void ClearAdditionalQuads();
	void Destroy();
	void SetZ(int);
protected:
	static sf::VertexArray gameArray;
	static sf::RenderStates gameRenderStates;
	sf::Vertex* quad;
	int additionalQuadCount;
	std::vector<sf::Vertex*> additionalQuads;
	sf::Clock movementClock;
	sf::Vector2i targetPosition;
	sf::Vector2i homePosition;
	sf::Vector2i resetPosition;
	sf::Vector2i moveDirection;
	sf::Vector2i componentMoveDistance;
	float velocity;
	float moveAngle;
	float distanceMoved;
	float moveDistance;
	sf::Clock expandClock;
	sf::Vector2f targetScale;
	sf::Vector2f homeScale;
	sf::Vector2f resetScale;
	sf::Vector2f amountExpanded;
	sf::Vector2f expandAmount;
	sf::Vector2f expandVelocity;
	sf::Vector2f expandDirection;
	bool isExpanding;
	bool isMoving;
	void MoveOnGrid(int,int);
	bool isVisible;
	sf::Texture texture;
	sf::Texture myTexture;
	sf::Sprite sprite;
	sf::Vector2f positionOnPanel;
};

#endif