#include "SlicedSprite.h"
#include "SpritePanel.h"

std::vector<std::vector<sf::IntRect>> SlicedSprite::spriteParts;
std::vector<std::vector<sf::IntRect>> SlicedSprite::scrollBarParts;
sf::Sprite* SlicedSprite::backgroundLeft;
sf::Sprite* SlicedSprite::backgroundRight;
sf::Sprite* SlicedSprite::backgroundCenter;
sf::Sprite* SlicedSprite::foregroundCenter;

SlicedSprite::SlicedSprite(int xPos, int yPos, float x, float y, SlicedSprite::SpriteStyle style) : Drawn("blank.png"){
	sprite.setPosition(xPos,yPos);
	std::vector<sf::IntRect> textParts = spriteParts[style];
	for(int x = 0; x < textParts.size(); x++){
		parts.push_back(new Drawn("slicedsprites/" + std::to_string(style) + "/" + std::to_string(x) + ".png"));
	}
	float topLength = x - (textParts[0].width + textParts[2].width);
	parts[1]->SetScale(sf::Vector2f(topLength / (float)textParts[1].width,1));
	parts[4]->SetScale(sf::Vector2f(topLength / (float)textParts[1].width,1));
	parts[7]->SetScale(sf::Vector2f(topLength / (float)textParts[1].width,1));
	float sideHeight = y - (textParts[0].height + textParts[6].height);
	parts[3]->SetScale(sf::Vector2f(parts[3]->GetScale().x,sideHeight / (float)textParts[3].height));
	parts[4]->SetScale(sf::Vector2f(parts[4]->GetScale().x,sideHeight / (float)textParts[3].height));
	parts[5]->SetScale(sf::Vector2f(parts[5]->GetScale().x,sideHeight / (float)textParts[3].height));
	parts[0]->GetSprite()->setOrigin(sf::Vector2f(0,0));
	parts[1]->GetSprite()->setOrigin(sf::Vector2f(-1 * (parts[0]->GetSize().x),0));
	parts[2]->GetSprite()->setOrigin(sf::Vector2f(-1 * (parts[1]->GetSize().x + parts[2]->GetSize().x),0));
	parts[3]->GetSprite()->setOrigin(sf::Vector2f(0,-1 * (parts[0]->GetSize().y)));
	parts[4]->GetSprite()->setOrigin(sf::Vector2f(-1 * (parts[3]->GetSize().x), -1 * (parts[0]->GetSize().y)));
	parts[5]->GetSprite()->setOrigin(sf::Vector2f(-1 * (parts[3]->GetSize().x + parts[4]->GetSize().x),-1 * (parts[2]->GetSize().y)));
	parts[6]->GetSprite()->setOrigin(sf::Vector2f(0,-1 * (parts[0]->GetSize().y + parts[3]->GetSize().y)));
	parts[7]->GetSprite()->setOrigin(sf::Vector2f(-1 * (parts[6]->GetSize().x),-1 * (parts[0]->GetSize().y + parts[3]->GetSize().y)));
	parts[8]->GetSprite()->setOrigin(sf::Vector2f(-1 * (parts[6]->GetSize().x + parts[7]->GetSize().x),-1 * (parts[0]->GetSize().y + parts[3]->GetSize().y)));
	SetPosition(sf::Vector2f(xPos,yPos));
	texturePart = sf::IntRect(0,0,x,y);
	size = sf::Vector2f(x,y);
	//SetRotation(0);
};
SlicedSprite::SlicedSprite(int x, int y, int length) : Drawn("blank.png"){
	sprite.setPosition(x,y);
	texturePart = sf::IntRect(0,0,length,30);
	SetRotation(0);
	CreateTiled(x,y,length - 50,"progressbar/background/1.png");
	parts.push_back(new Drawn("progressbar/background/0.png"));
	parts[parts.size() - 1]->SetPosition(sf::Vector2f(x,y));
	parts.push_back(new Drawn("progressbar/background/2.png"));
	parts[parts.size() - 1]->SetPosition(sf::Vector2f(x,y));
	parts[parts.size() - 1]->GetSprite()->setOrigin(-(length-28),0);
};

void SlicedSprite::CreateTiled(int xPos, int yPos, int length, std::string spritePath){
	sf::IntRect spriteDims = Drawn::GetTextureFromAtlas(spritePath);
	int leftover = length % spriteDims.width;
	int fit = length / spriteDims.width;
	float each = ((float)leftover) / ((float) fit);
	sf::Vector2f scale((each + spriteDims.width) / spriteDims.width,1);
	for(int x = 0; x < fit; x++){
		parts.push_back(new Drawn(spritePath));
		parts[parts.size() - 1]->SetScale(scale);
		parts[parts.size() - 1]->SetPosition(sf::Vector2f(xPos,yPos));
		parts[parts.size() - 1]->GetSprite()->setOrigin(-1*((x * (spriteDims.width * scale.x)) + 22),0);
	}
};
void SlicedSprite::Update(GamePanel* panel){
	for(int x = 0; x < parts.size(); x++){
		parts[x]->Draw(panel);
	}
};
void SlicedSprite::SetPosition(sf::Vector2f newPos){
	for(int x = 0; x < parts.size(); x++){
		parts[x]->SetPosition(newPos);
	}
};
void SlicedSprite::SetZ(int z){
	for(int x = 0; x < parts.size(); x++){
		parts[x]->SetZ(z);
	}
};
void SlicedSprite::OnStart(){
	for(int x = 0; x < Last; x++){
		std::vector<sf::IntRect> tempTexts;
		for(int y = 0; y < 9; y++){
			sf::Texture tempText;
			tempTexts.push_back(Drawn::GetTextureFromAtlas("slicedsprites/" + std::to_string(x) + "/" + std::to_string(y) + ".png"));
		}
		spriteParts.push_back(tempTexts);
	}
	for(int x = 0; x < 1; x++){
		std::vector<sf::IntRect> tempTexts;
		for(int y = 0; y < 3; y++){
			sf::Texture tempText;
			tempTexts.push_back(Drawn::GetTextureFromAtlas("slicedsprites/scrollBar/" + std::to_string(x) + "/" + std::to_string(y) + ".png"));
		}
		scrollBarParts.push_back(tempTexts);
	}
	backgroundLeft = new sf::Sprite(Drawn::GetSingleTexture("progressbar/background/0.png"));
	backgroundCenter = new sf::Sprite(Drawn::GetSingleTexture("progressbar/background/1.png"));
	backgroundRight = new sf::Sprite(Drawn::GetSingleTexture("progressbar/background/2.png"));
	foregroundCenter = new sf::Sprite(Drawn::GetSingleTexture("progressbar/foreground/0.png"));
};
sf::Vector2f SlicedSprite::GetSize(){
	return size;
};
void SlicedSprite::SetRotation(float angle){
    for(int x = 0; x < parts.size(); x++){
	parts[x]->SetRotation(angle);
	};
};
void SlicedSprite::SetSlicedOrigin(sf::Vector2f newOrigin){
    for(int x = 0; x < parts.size(); x++){
	parts[x]->GetSprite()->setOrigin(parts[x]->GetSprite()->getOrigin().x + newOrigin.x,parts[x]->GetSprite()->getOrigin().y + newOrigin.y);
	};
};