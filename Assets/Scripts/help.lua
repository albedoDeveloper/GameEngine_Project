local visible = false

function Start(gameObject)

end

function Update(gameObject, deltaTime, inputManager)

    if inputManager:GetKeyDown("m") then
		visible = not visible
		gameObject:GetCUserInterface():SetVisibility(visible)
	end

end
