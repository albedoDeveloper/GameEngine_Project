local GUI

function Start(gameObject)
	GUI = gameObject:GetCUserInterface()
end

function Update(gameObject, deltaTime, inputManager)
	if GUI:MouseClicked() then
		LoadGame()
		inputManager:LockCursor(true)
	end

	if not CheckSaveState() then
		gameObject:SetActive(false)
	end
end
