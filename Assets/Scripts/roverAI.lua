-- rover ai
require "math"

thisRover = nil
xTarget = 0
zTarget = 0
maxSpeed = 0.004
maxRotation = 4
detectDistance = 50
attackDistance = 4
lastTime = 0.0
currentTime = 0.0
calcInterval = 1/60
rebootLength = 500
rebootTimer = rebootLength

function Start(gameObject)

end

function Update(gameObject, deltaTime, inputManager)

end

function wander(gameObject, inputManager)

end

function pursue(gameObject, inputManager)
	
end

function attack(gameObject, inputManager)

end

function reboot(gameObject, inputManager)
	if(rebootTimer > 0)
	then
		rebootTimer = rebootTimer - 1
	else
		thisRover:GetCStateMachineAI():SetCurrentState("wander")
		rebootTimer = rebootLength
	end
end

function matchTerrainHeight(gameObject)
	yPos = GetGameObject("terrain"):GetCTerrainBruteForce():GetHeightBilinear(gameObject:GetTransform():GetPosition())
	yDisplacement = yPos - gameObject:GetTransform():GetPosition():GetY()
	thisRover:GetTransform():Translate(0, yDisplacement, 0)
end