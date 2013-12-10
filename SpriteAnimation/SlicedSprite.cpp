#include "SlicedSprite.h"
#include "SpritePanel.h"

std::vector<std::vector<sf::IntRect>> SlicedSprite::spriteParts;
std::vector<std::vector<sf::IntRect>> SlicedSprite::scrollBarParts;
sf::Sprite* SlicedSprite::backgroundLeft;
sf::Sprite* SlicedSprite::backgroundRight;
sf::Sprite* SlicedSprite::backgroundCenter;
sf::Sprite* SlicedSprite::foregroundCenter;

SlicedSprite::SlicedSprite(int xPos, int yPos, float x, float y, SlicedSprite::SpriteStyle style) : Drawn("blank.png"){
	size = sf::Vector2f(x,y);
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
	parts[0]->SetPosition(sf::Vector2f(0,0));
	parts[1]->SetPosition(sf::Vector2f(parts[0]->GetTexturePart().width,0));
	parts[2]->SetPosition(sf::Vector2f(parts[1]->GetTexturePart().width + parts[2]->GetTexturePart().width,0));
	parts[3]->SetPosition(sf::Vector2f(0,parts[0]->GetTexturePart().height));
	parts[4]->SetPosition(sf::Vector2f(parts[3]->GetTexturePart().width, parts[0]->GetTexturePart().height));
	parts[5]->SetPosition(sf::Vector2f(parts[3]->GetTexturePart().width + parts[4]->GetTexturePart().width,parts[2]->GetTexturePart().height));
	parts[6]->SetPosition(sf::Vector2f(0,parts[0]->GetTexturePart().height + parts[3]->GetTexturePart().height));
	parts[7]->SetPosition(sf::Vector2f(parts[6]->GetTexturePart().width,parts[0]->GetTexturePart().height + parts[3]->GetTexturePart().height));
	parts[8]->SetPosition(sf::Vector2f(parts[6]->GetTexturePart().width + parts[7]->GetTexturePart().width,parts[0]->GetTexturePart().height + parts[3]->GetTexturePart().height));
	SetPosition(sf::Vector2f(xPos,yPos));
};
SlicedSprite::SlicedSprite(int x, int y, int length) : Drawn("blank.png"){
	CreateTiled(25 + x,y,length - 50,"progressbar/background/1.png");
	parts.push_back(new Drawn("progressbar/background/0.png"));
	parts[parts.size() - 1]->SetPosition(sf::Vector2f(x,y));
	parts.push_back(new Drawn("progressbar/background/2.png"));
	parts[parts.size() - 1]->SetPosition(sf::Vector2f(length-25 + x,y));
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
		parts[parts.size() - 1]->SetPosition(sf::Vector2f((x * (spriteDims.width * scale.x)) + xPos,yPos));
	}
};
void SlicedSprite::Update(GamePanel* panel){
	for(int x = 0; x < parts.size(); x++){
		parts[x]->Draw(panel);
	}
};
void SlicedSprite::SetPosition(sf::Vector2f newPos){
	for(int x = 0; x < parts.size(); x++){
		parts[x]->SetPosition(parts[x]->GetPosition() + newPos);
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