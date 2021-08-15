local GUI

function Start(gameObject)
	GUI = gameObject:GetCUserInterface()
end

function Update(gameObject, deltaTime, inputManager)
	if GUI:MouseClicked() then
		GetGameObject("player"):SetActive(true)
		GetGameObject("endScreen"):SetActive(true)
		GetGameObject("help"):SetActive(true)
		GetGameObject("healthBar"):SetActive(true)

		inputManager:LockCursor(true)
	end
end
