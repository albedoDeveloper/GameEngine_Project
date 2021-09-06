
function Start(gameObject)

end

function Update(gameObject, deltaTime, inputManager)
    gameObject:GetTransform():RotateLocal(10 * deltaTime,0,0,1)
    -- run time texture loading, deleting
end
