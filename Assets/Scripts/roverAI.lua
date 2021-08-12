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
	thisRover = gameObject
	thisRover:GetCStateMachineAI():SetCurrentState("wander")
	xTarget = gameObject:GetTransform():GetPosition():GetX()
	zTarget = gameObject:GetTransform():GetPosition():GetZ()

	if(gameObject:GetDifficulty() == "easy")
	then
		maxSpeed = 0.02
		detectDistance = 20
		attackDistance = 4
	end

	if(gameObject:GetDifficulty() == "medium")
	then
		maxSpeed = 0.04
		detectDistance = 50
		attackDistance = 4
	end

	if(gameObject:GetDifficulty() == "hard")
	then
		maxSpeed = 0.2
		detectDistance = 80
		attackDistance = 8
	end
end

function Update(gameObject, deltaTime, inputManager)
	currentTime = currentTime + deltaTime
	while(currentTime - lastTime >= calcInterval)
	do
		thisRover:GetCStateMachineAI():RunCurrentState()
		lastTime = lastTime + calcInterval 
	end
end

function wander(gameObject, inputManager)
	--get random number and convert to heading
	if(gameObject:GetTransform():GetDistance3f(xTarget, gameObject:GetTransform():GetPosition():GetY(), zTarget) < 2) 
	then
		repeat
			xTarget = gameObject:GetTransform():GetPosition():GetX() + 20*(math.random() - 0.5)
			zTarget = gameObject:GetTransform():GetPosition():GetZ() + 20*(math.random() - 0.5)
		until(0 < xTarget and xTarget < 1000 and 0 < zTarget and zTarget < 1000)
	end

	thisRover:GetTransform():MoveTowards3f(xTarget, 0, zTarget, maxSpeed * 50)
	matchTerrainHeight(gameObject)

	if(thisRover:GetTransform():GetDistance(GetGameObject("player"):GetTransform()) < detectDistance)
	then
		thisRover:GetCStateMachineAI():SetCurrentState("pursue")
	end
end

function pursue(gameObject, inputManager)
	closestRover = gameObject:GetClosestObject("rover")
	closestRover:GetCStateMachineAI():SetCurrentState("pursue")

	gameObject:GetTransform():MoveTowards(GetGameObject("player"):GetTransform():GetPosition(), maxSpeed)
	gameObject:GetCStaticMesh():GetTransform():RotateTowards(GetGameObject("player"):GetTransform():GetPosition(), maxRotation)
	matchTerrainHeight(gameObject)

	if(thisRover:GetTransform():GetDistance(GetGameObject("player"):GetTransform()) > detectDistance)
	then
		thisRover:GetCStateMachineAI():SetCurrentState("wander")
	end

	if(thisRover:GetTransform():GetDistance(GetGameObject("player"):GetTransform()) < attackDistance)
	then
		thisRover:GetCStateMachineAI():SetCurrentState("attack")
	end
end

function attack(gameObject, inputManager)
	playerCharacter = GetGameObject("player"):GetCCharacter()
	playerCharacter:SetHitpoints(playerCharacter:GetHitpoints() - 1)

	thisRover:GetCStateMachineAI():SetCurrentState("reboot")
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