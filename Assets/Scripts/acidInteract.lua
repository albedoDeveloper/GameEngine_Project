--acid interaction
--ouchSpeed = 0.10

rehurtTime = 500

function Start(gameObject)
	
end

function Update(gameObject, deltaTime, inputManager)

	playerCharacter = GetGameObject("player"):GetCCharacter()
	--print(playerCharacter:GetHitpoints())

	if(gameObject:GetTransform():GetDistance(GetGameObject("player"):GetTransform()) < 20)
	then
		
		playerCharacter:SetHitpoints(playerCharacter:GetHitpoints() - 1)

		if (rehurtTime > 0)
		then
			rehurtTime = rehurtTime - 1 * deltaTime
		else
			rehurtTime = 500
		end
	end
end