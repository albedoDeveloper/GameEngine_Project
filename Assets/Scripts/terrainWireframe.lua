function Start(gameObject)
end

function Update(gameObject, deltaTime, inputManager)
    if inputManager:GetKeyDown("k") then
		currentDisplayMode = gameObject:GetCTerrainBruteForce():GetDisplayWireframe()
		gameObject:GetCTerrainBruteForce():SetDisplayMode(not currentDisplayMode)
	end
end
