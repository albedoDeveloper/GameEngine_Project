
local MOUSE_SENS = 0.03
local MOVE_SPEED = 4.00

jumpHeight = 5

lastTime = 0.0
currentTime = 0.0

function Start(gameObject)

end

function Update(gameObject, deltaTime, inputManager)
    
    currentTime = currentTime + deltaTime
    --print(currentTime)
    if inputManager:CheckCursorLock() then
        gameObject:GetTransform():RotateLocal(
            inputManager:GetAxis("Mouse X") * MOUSE_SENS,
            0,
            1,
            0
        )

        gameObject:GetCCamera():GetTransform():RotateLocal(
            inputManager:GetAxis("Mouse Y") * -MOUSE_SENS,
            1,
            0,
            0
        )
    end
    
    if inputManager:GetKey("w") then
        gameObject:GetCCharacter():Move(0, 0, -MOVE_SPEED * deltaTime)
    end

    if inputManager:GetKey("s") then
        gameObject:GetCCharacter():Move(0, 0, MOVE_SPEED * deltaTime)
    end

    if inputManager:GetKey("a") then
        gameObject:GetCCharacter():Move(-MOVE_SPEED * deltaTime, 0, 0)
    end

    if inputManager:GetKey("d") then
        gameObject:GetCCharacter():Move(MOVE_SPEED * deltaTime, 0, 0)
    end

    if inputManager:GetKey(" ") then
        gameObject:GetCCharacter():Jump(0, jumpHeight, 0)
    end

    if inputManager:GetMouseButton(0) and inputManager:CheckCursorLock() then
        inputManager:LockCursor(true)
    end
end
