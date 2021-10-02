timeKeep = 0

function Start(gameObject)

end

function Update(gameObject, deltaTime, inputManager)
    if timeKeep < 5000 then
        timeKeep = timeKeep + 1
    end
    

    if timeKeep == 1000 then
        gameObject:GetCAnimator():PlayAnimation("girlTalking")
        gameObject:GetCSound():PlaySound("girlTextSpeechTwo.wav", 0, true)
    end

    if timeKeep == 1700 then
        gameObject:GetCAnimator():PlayAnimation("Breathing Idle")
    end

    if timeKeep == 2400 then
        gameObject:GetCAnimator():PlayAnimation("girlDying")
    end

    if timeKeep ==3000 then
        gameObject:SetActive(false);
    end

    -- run time texture loading, deleting
end
