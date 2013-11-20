#include "AmbienceObject.h"

std::vector<std::string> AmbienceObject::tags;

AmbienceObject::AmbienceObject(int x,int y,std::string physical,std::string nonphysical){

};
AmbienceObject::AmbienceObject(int x,int y,tmx::MapObject* obj) : GameSprite(GetPhysicalPosition(x,y,obj).x,GetPhysicalPosition(x,y,obj).y,"ambienceObjects/" +obj->GetPropertyString("physical") + ".png"){
	std::cout << "Creating new Ambience Object| Physical: " << obj->GetPropertyString("physical") << " | Nonphysical: " << obj->GetPropertyString("nonphysical") << std::endl;
	nonphysical = new GameSprite(x,y,"ambienceObjects/" + obj->GetPropertyString("nonphysical") + ".png");
	//SetUpBoundries(obj->GetPropertyString("nonphysical"),nonphysical);
	//SetUpBoundries(obj->GetPropertyString("physical"),this);
	tags.push_back(std::to_string(GetTag()));
	UpdateRoomTile();
};
AmbienceObject::AmbienceObject(int x,int y,tmx::MapObject* obj,bool isLightObject) : GameSprite(GetPhysicalPosition(x,y,obj).x,GetPhysicalPosition(x,y,obj).y,"ambienceObjects/" +obj->GetPropertyString("physical") + ".png"){
	std::cout << "Creating new Ambience Object| Physical: " << obj->GetPropertyString("physical") << " | Nonphysical: " << obj->GetPropertyString("nonphysical") << std::endl;
	nonphysical = new GameSprite(x,y,"ambienceObjects/" + obj->GetPropertyString("nonphysical") + ".png");
	//SetUpBoundries(obj->GetPropertyString("nonphysical"),nonphysical);
	//SetUpBoundries(obj->GetPropertyString("physical"),this);
	tags.push_back(std::to_string(GetTag()));
	UpdateRoomTile();	
};
void AmbienceObject::Update(sf::RenderTexture& window){
	window.draw(sprite);
	GameSprite::Update(window);
};
void AmbienceObject::Update2(sf::RenderTexture& window){
	window.draw(*(nonphysical->GetSprite()));
	((GameSprite*)nonphysical)->Update(window);
	//nonphysical->DrawBoundries(window);
	//DrawBoundries(window);
};
void AmbienceObject::Interact(){

};
void AmbienceObject::OnClick(){

};
void AmbienceObject::SetNonphysical(std::string){
	nonphysical = nonphysical;
};
void AmbienceObject::SetNonphysical(GameSprite* nonphysical){
	this->nonphysical = nonphysical; 
};
GameSprite* AmbienceObject::GetNonphysical(){
	return nonphysical;
};
void AmbienceObject::SetUpBoundries(std::string name, GameSprite* target){
	pugi::xml_node itemBoundsNode;
	pugi::xml_document itemBoundriesDoc;
	pugi::xml_parse_result itemBoundriesResults;
	pugi::xml_node itemBoundriesNode;
	itemBoundriesResults = itemBoundriesDoc.load_file("xml/ambienceBoundries.xml");
	itemBoundriesNode = itemBoundriesDoc.first_child();
	itemBoundsNode = itemBoundriesNode.find_child_by_attribute("name",name.c_str());
	for(pugi::xml_node polygon = itemBoundsNode.first_child(); polygon; polygon = polygon.next_sibling()){
		sf::ConvexShape poly;
		poly.setPointCount(polygon.attribute("numVertexes").as_int());
		pugi::xml_node vertex = polygon.first_child();
		for(int x = 0; x < polygon.attribute("numVertexes").as_int(); x++){
			if(x != 0)
				vertex = vertex.next_sibling();
			poly.setPoint(x,sf::Vector2f(vertex.attribute("x").as_int(),vertex.attribute("y").as_int()));
		}
		target->AddBoundryPolygon(poly);
	}
};
sf::Vector2i AmbienceObject::GetPhysicalPosition(int x, int y,tmx::MapObject* obj){
	int physicalX = x + std::stoi(obj->GetPropertyString("offsetX"));
	int physicalY = y + std::stoi(obj->GetPropertyString("offsetY"));
	return sf::Vector2i(physicalX,physicalY);
}