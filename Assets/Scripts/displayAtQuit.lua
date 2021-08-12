function Start(gameObject)

end

function Update(gameObject, deltaTime, inputManager)

    if inputManager:GetKeyDown("x") then
		gameObject:GetCUserInterface():SetVisibility(true)
		inputManager:LockCursor(false)
		SaveGame()
	end

	if inputManager:GetMouseButton(0) and not inputManager:CheckCursorLock() then
		inputManager:RestartGame()
		inputManager:LockCursor(false)
	end

	if GetGameObject("Water2"):GetTransform():GetPosition():GetY() < 1000 then
		if GetGameObject("Water3"):GetTransform():GetPosition():GetY() < 66 then
			if GetGameObject("Water4"):GetTransform():GetPosition():GetY() < 97 then
				if GetGameObject("Water5"):GetTransform():GetPosition():GetY() < 167 then
					if GetGameObject("Water6"):GetTransform():GetPosition():GetY() < 179 then
						if GetGameObject("Water7"):GetTransform():GetPosition():GetY() < 110 then
							gameObject:GetCUserInterface():SetVisibility(true)
							inputManager:LockCursor(false)
						end
					end
				end	
			end
		end
	end
end