
function Start(gameObject)

end

function Update(gameObject, deltaTime, inputManager)
    gameObject:GetTransform():RotateLocal(40 * deltaTime,0,1,1)
    -- run time texture loading, deleting
end
