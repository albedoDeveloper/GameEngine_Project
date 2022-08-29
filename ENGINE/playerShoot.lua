
function Start(gameObject)

end

function Update(gameObject, deltaTime, inputManager)
    gameObject:GetTransform():RotateLocal(40 * deltaTime,0,1,0)
    -- run time texture loading, deleting
end
