timeKeep = 0

function Start(gameObject)

end

function Update(gameObject, deltaTime, inputManager)
    if timeKeep < 5000 then
        timeKeep = timeKeep + 1
    end
    if timeKeep == 300 then
        gameObject:GetCAnimator():PlayAnimation("girlTalking")
        gameObject:GetCSound():PlaySound("girlTextSpeechOne.wav", 0, true)
    end
    

    if timeKeep == 900 then
        gameObject:GetCAnimator():PlayAnimation("Breathing Idle")
        --gameObject:GetCSound():PlaySound("girlTextSpeechOne.wav", 0, true)
    end

    if timeKeep == 1800 then
        gameObject:GetCAnimator():PlayAnimation("girlTalking")
        gameObject:GetCSound():PlaySound("girlTextSpeechThree.wav", 0, true)
    end

    if timeKeep == 2300 then
        gameObject:GetCAnimator():PlayAnimation("basic_girl")
    end

    -- run time texture loading, deleting
end
