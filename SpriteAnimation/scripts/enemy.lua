local Enemy = {}

function Enemy:new(nameA,dropsA)
	local o = {
		name = nameA,
		drops = dropsA,
	}
	return o
end

local enemy = {}
 enemy["cherub"] = Enemy:new('Cherub',{{"0_1",0.5},{"0_2",0.25}})

function createEnemy(enemyName)
	instanceEnemy:SetName(enemy[enemyName]["name"])
	for i, drop in pairs(enemy[enemyName]["drops"]) do
		instanceEnemy:AddDrop(drop[1],drop[2])
	end
end