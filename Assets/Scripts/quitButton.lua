local GUI

function Start(gameObject)
	GUI = gameObject:GetCUserInterface()
end

function Update(gameObject, deltaTime, inputManager)
	if GUI:MouseClicked() then
		QuitGame()
	end
end
