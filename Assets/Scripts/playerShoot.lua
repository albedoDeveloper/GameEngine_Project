
function Start(gameObject)
    
end

function Update(gameObject, deltaTime, inputManager)
    if (inputManager:GetMouseButtonDown(1)) then
        GetGameObject("book"):SetActive(true)
        GetGameObject("book"):GetTransform():SetRelativePosition(
            GetGameObject("playerThrowPoint"):GetTransform():GetWorldTransform():GetRelativePosition():GetX(),
            GetGameObject("playerThrowPoint"):GetTransform():GetWorldTransform():GetRelativePosition():GetY(),
            GetGameObject("playerThrowPoint"):GetTransform():GetWorldTransform():GetRelativePosition():GetZ()
        )
    end
end
