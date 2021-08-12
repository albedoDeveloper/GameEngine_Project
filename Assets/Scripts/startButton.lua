local GUI

function Start(gameObject)
	GUI = gameObject:GetCUserInterface()
end

function Update(gameObject, deltaTime, inputManager)
	if GUI:MouseClicked() then
		GetGameObject("player"):SetActive(true)
		GetGameObject("monke"):SetActive(true)
		GetGameObject("endScreen"):SetActive(true)
		GetGameObject("help"):SetActive(true)
		GetGameObject("monke1"):SetActive(true)

		GetGameObject("startMenu"):SetActive(false)
		GetGameObject("startButton"):SetActive(false)
		GetGameObject("quitButton"):SetActive(false)
		for i=1,20,1 do
			roverName = "rover " .. i
			GetGameObject(roverName):SetActive(true)
			GetGameObject(roverName):SetDifficulty("hard")
		end
		inputManager:LockCursor(true)
	end
end
