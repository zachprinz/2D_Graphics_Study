#ifndef DRAWN_H
#define DRAWN_H

#include <vector>
#include <SFML/Graphics.hpp>
//#include <boost\container\flat_set.hpp>
#include "AABB.h"
#include "Clock.h"

class SlicedSprite;
class ProgressBar;
class GamePanel;
class Drawn
{
public:
	static void DrawGame(sf::RenderWindow&);
	static void SetUp(sf::RenderWindow*);
	static void DrawOther(sf::Text*,GamePanel*);
	static void DrawOther(sf::RectangleShape*,GamePanel*);
	static void DrawOther(sf::ConvexShape*, GamePanel*);
	//static sf::RenderTexture 
;
	static sf::Sprite otherGraphicsSprite;
	static int quadCount;
	static sf::RenderWindow* gameWindow;
	static std::vector<sf::Drawable*> adds;
	static std::vector<sf::Transformable*> addsTransforms;
	static std::vector<sf::Vector2f> addsPositions;
	static std::vector<sf::Vector2f> addsScale;
	static sf::VertexArray gameArray;
	static sf::RenderStates gameRenderStates;
	static int GetDistance(sf::Vector2i,sf::Vector2i);
	static sf::Texture GetSingleTexture(std::string);
	static sf::IntRect GetTextureFromAtlas(std::string);
	static void DrawAdds();
	
	//static boost::container::flat_set<Drawn*> vertexPointers;
	static std::vector<Drawn*> vertexPointers;
	Drawn(std::string);
	Drawn(SlicedSprite*);
	Drawn();
	bool GetVisible();
	sf::Sprite* GetSprite();
	sf::Vector2f GetPositionOnPanel();
	virtual void Update(GamePanel*);
	virtual void OnClick();
	virtual void OnRClick(sf::Vector2i);
	virtual void OnMousePress();
	virtual void OnMouseRelease();
	virtual void OnHover(bool);
	virtual void SetPosition(sf::Vector2f);
	void Move(float,float);
	sf::Texture GetSingleTexture();
	sf::IntRect texturePart;
	void MoveTo(int x,int y, sf::Time);
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
	int z;
	bool operator<(Drawn const& drawn) const{return(z<drawn.z);};
	void ClearAdditionalQuads();
	void Destroy();
	void SetZ(int);
	void SetScale(sf::Vector2f);
	sf::Vector2f GetScale();
	sf::IntRect GetTexturePart();
	sf::Vector2f GetPosition();
	virtual sf::Vector2f GetSize();
	AABB GetBounds();
	AABB GetBounds(GamePanel*);
	AABB GetSpritePanelBounds();
	bool updateVertex;
	void SetDrawOffset(sf::Vector2f);
	float rotationAngle;
	virtual void SetRotation(float angle);
	void SetDrawBounds(bool);
	bool isSliced;
    	sf::Clock movementClock;
	bool pressed;
protected:
	sf::Vector2f testPosition;
	sf::VertexArray heldVerteces;
	sf::Vector2f myScale;
	bool ViewContains(sf::View, sf::IntRect);
	AABB screenBounds;
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
	sf::Vector2f drawOffset;
	bool drawBounds;
private:
	std::vector<sf::Vector2f> cornerRotationOffsets;
};

#endif