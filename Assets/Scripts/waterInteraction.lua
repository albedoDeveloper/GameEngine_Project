--water interaction
descentSpeed = 0.10

function Start(gameObject)
	
end

function Update(gameObject, deltaTime, inputManager)
	distance = gameObject:GetTransform():GetDistance(GetGameObject("player"):GetTransform())
	if(gameObject:GetTransform():GetDistance(GetGameObject("player"):GetTransform()) < 20)
	then
		gameObject:GetTransform():Translate(0, -descentSpeed, 0)
	end
end