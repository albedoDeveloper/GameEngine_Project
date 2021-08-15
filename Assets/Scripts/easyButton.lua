local GUI

function Start(gameObject)
	GUI = gameObject:GetCUserInterface()
end

function Update(gameObject, deltaTime, inputManager)
	if GUI:MouseClicked() then
		GetGameObject("player"):SetActive(true)


		GetGameObject("startMenu"):SetActive(false)
		GetGameObject("easyButton"):SetActive(false)
		GetGameObject("mediumButton"):SetActive(false)
		GetGameObject("hardButton"):SetActive(false)
		GetGameObject("quitButton"):SetActive(false)
		GetGameObject("loadButton"):SetActive(false)

		inputManager:LockCursor(true)
	end
end
