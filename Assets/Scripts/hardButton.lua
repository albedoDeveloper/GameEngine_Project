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

		GetGameObject("startMenu"):SetActive(false)
		GetGameObject("easyButton"):SetActive(false)
		GetGameObject("mediumButton"):SetActive(false)
		GetGameObject("hardButton"):SetActive(false)
		GetGameObject("quitButton"):SetActive(false)
		GetGameObject("loadButton"):SetActive(false)
		for i=1,20,1 do
			roverName = "rover " .. i
			GetGameObject(roverName):SetActive(true)
			GetGameObject(roverName):SetDifficulty("hard")
		end
		inputManager:LockCursor(true)
	end
end
