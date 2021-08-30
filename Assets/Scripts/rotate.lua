
function Start(gameObject)

end

function Update(gameObject, deltaTime, inputManager)
    gameObject:GetTransform():RotateLocal(0.05,0,0,1)

    -- run time texture loading, deleting
    if inputManager:GetKeyDown('t') then
        UnloadTexture("brick_texture")
        LoadTexture("green_texture", "green.png")
        gameObject:GetCStaticMesh():GetModel():AssignTexture("green_texture")

    end
end
