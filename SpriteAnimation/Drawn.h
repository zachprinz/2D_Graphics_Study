#ifndef DRAWN_H
#define DRAWN_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <boost\container\flat_set.hpp>
#include "AABB.h"

class SlicedSprite;
class ProgressBar;
class GamePanel;
class Drawn
{
public:
	Drawn(std::string);
	Drawn(SlicedSprite*);
	Drawn();
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
	static sf::Texture GetSingleTexture(std::string);
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
	void DrawVertex(sf::RenderTexture* , GamePanel*);
	void Draw(GamePanel*);
	void Draw(GamePanel*, sf::RenderTexture*);
	void DrawAdditional(GamePanel*);
	static void DrawGame(sf::RenderWindow&);
	static void SetUp(sf::RenderWindow*);
	static sf::RenderTexture otherGraphicsPanel;
	static sf::Sprite otherGraphicsSprite;
	static void DrawOther(sf::Text*,GamePanel*);
	static void DrawOther(sf::Sprite*,GamePanel*);
	static void DrawOther(sf::RectangleShape*,GamePanel*);
	static int quadCount;
	static sf::RenderWindow* gameWindow;
	static std::vector<sf::Drawable*> adds;
	static std::vector<sf::Transformable*> addsTransforms;
	static std::vector<sf::Vector2f> addsPositions;
	int z;
	bool operator<(Drawn const& drawn) const{return(z<drawn.z);};
	static boost::container::flat_set<Drawn*> vertexPointers;
	void ClearAdditionalQuads();
	void Destroy();
	void SetZ(int);
	void SetScale(sf::Vector2f);
	sf::Vector2f GetScale();
	sf::IntRect GetTexturePart();
	virtual void SetPosition(sf::Vector2f);
	sf::Vector2f GetPosition();
	sf::Vector2f GetSize();
	AABB GetBounds();
	AABB GetBounds(sf::View);
	AABB GetSpritePanelBounds();
	bool updateVertex;
protected:
	static void DrawAdds();
	sf::Vector2f testPosition;
	sf::VertexArray heldVerteces;
	sf::Vector2f myScale;
	bool ViewContains(sf::View, sf::IntRect);
	AABB screenBounds;
	static sf::VertexArray gameArray;
	static sf::RenderStates gameRenderStates;
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