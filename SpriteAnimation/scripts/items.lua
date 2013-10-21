local Item = {}

function Item:new(nameA,idA,slotA,str,endure,speedA,tech,mine,wc,priceA)
	local o = {
		name = nameA,
		id = idA,
		slot = slotA;
		strength = str,
		endurance = endure,
		speed = speedA,
		technique = tech,
		woodcutting = wc,
		mining = mine,
		price = priceA,
		smithing = 0;
		crafting = 0;
	}
	return o
end

local items = {}
 items["item0_0"] = Item:new('Wood Helm',0, 0, 2, 1, 0, 0, 0, 0, 50)
 items["item0_1"] = Item:new('Bronze Helm', 1, 0, 4, 2, 0, 0, 0, 0, 100)
 items["item0_2"] = Item:new('Iron Helm', 2, 0, 6, 3, 0, 0, 0, 0, 150)
 items["item0_3"] = Item:new('Steel Helm', 3, 0, 8, 4, 0, 0, 0, 0, 200)
 items["item1_0"] = Item:new('Wood Sword', 4, 1, 2, 0, 2, 1, 0, 0, 100)
 items["item1_1"] = Item:new('Bronze Sword', 5, 1, 4, 0, 4, 2, 0, 0, 200)
 items["item1_2"] = Item:new('Iron Sword', 6, 1, 6, 0, 6, 3, 0, 0, 300)
 items["item1_3"] = Item:new('Steel Sword', 7, 1, 8, 0, 8, 4, 0, 0, 400)
 items["item2_0"] = Item:new('Wood Torso', 8, 2, 3, 3, 0, 0, 0, 0, 150)
 items["item2_1"] = Item:new('Bronze Torso', 9, 2, 6, 6, 0, 0, 0, 0, 300)
 items["item2_2"] = Item:new('Iron Torso', 10, 2 ,9 ,9 ,0 ,0 ,0 ,0, 450)
 items["item2_3"] = Item:new('Steel Torso', 11, 2, 12, 12, 0, 0, 0, 0, 600)
 items["item3_0"] = Item:new('Wood Shield', 12, 3, 0, 3, 0, 0, 0, 0, 100)
 items["item3_1"] = Item:new('Bronze Shield', 13, 3, 0, 6, 0, 0, 0, 0, 200)
 items["item3_2"] = Item:new('Iron Shield', 14, 3, 0, 9, 0, 0, 0, 0, 300)
 items["item3_3"] = Item:new('Steel Shield', 15, 3, 0, 15, 0, 0, 0, 0, 400)
 items["item4_0"] = Item:new('Wood Legs', 16, 4, 3, 3, 0, 0, 0, 0, 100)
 items["item4_1"] = Item:new('Bronze Legs', 17, 4, 6, 6, 0, 0, 0, 0, 200)
 items["item4_2"] = Item:new('Iron Legs', 18, 4, 9, 9, 0, 0, 0, 0, 300)
 items["item4_3"] = Item:new('Steel Legs', 19, 4, 12, 12, 0, 0, 0, 0, 400)


function createItem(itemId)
	instanceItem.slot = items[itemId]["slot"]
	instanceItem.name = items[itemId]["name"]
	instanceItemLevels:SetLevels(items[itemId]["strength"],items[itemId]["endurance"],items[itemId]["speed"],items[itemId]["technique"],items[itemId]["mining"],items[itemId]["woodcutting"],items[itemId]["smithing"],items[itemId]["crafting"])
end
