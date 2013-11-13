#include "GroundItem.h"
#include <iostream>
#include "User.h"
#include "SpritePanel.h"

GroundItem::GroundItem(int x, int y, Item myItem) : GameSprite(x,y,"itemsprites/" + myItem.imageName){
	item = myItem;
	SetZ(1);
	isVisible = true;
	SetUpBoundries();
};
Item GroundItem::GetItem(){
	return item;
};
void GroundItem::Update(sf::RenderTexture& window){
		if(isVisible){
			UpdateRoomTile();
			window.draw(sprite);
			GameSprite::Update(window);
			DrawBoundries(window);
		}
};
void GroundItem::PickUp(){
	User::player->GetInventory()->Add(item);
	GetRoomTile()->TryRemoveOcupant(GetTag());
	SpritePanel::room->RemoveOcupant(GetTag());
	SpritePanel::instance->RemoveDynamicElement(std::to_string(GetTag()));
	isVisible = false;
};
void GroundItem::Interact(){
	std::cout << "Interacting with Item" << std::endl;
	PickUp();
}
void GroundItem::SetUpBoundries(){
	pugi::xml_node itemBoundsNode;
	pugi::xml_document itemBoundriesDoc;
	pugi::xml_parse_result itemBoundriesResults;
	pugi::xml_node itemBoundriesNode;
	itemBoundriesResults = itemBoundriesDoc.load_file("xml/itemBoundries.xml");
	itemBoundriesNode = itemBoundriesDoc.first_child();
	itemBoundsNode = itemBoundriesNode.find_child_by_attribute("name",std::to_string(item.GetId()).c_str());
	for(pugi::xml_node polygon = itemBoundsNode.first_child(); polygon; polygon = polygon.next_sibling()){
		sf::ConvexShape poly;
		poly.setPointCount(polygon.attribute("numVertexes").as_int());

		pugi::xml_node vertex = polygon.first_child();
		for(int x = 0; x < polygon.attribute("numVertexes").as_int(); x++){
			if(x != 0)
				vertex = vertex.next_sibling();
			poly.setPoint(x,sf::Vector2f(vertex.attribute("x").as_int(),vertex.attribute("y").as_int()));
		}
		poly.setPosition(sf::Vector2f(GetSprite()->getPosition().x  + GetSprite()->getLocalBounds().width / 2,GetSprite()->getPosition().y + GetSprite()->getLocalBounds().height / 2));
		poly.setFillColor(sf::Color(43,119,173,170));
		GameSprite::AddBoundryPolygon(poly);
	}
};