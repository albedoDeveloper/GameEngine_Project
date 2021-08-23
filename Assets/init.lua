
LoadScript("player_script", "playerController.lua")

LoadModel("rock_outcrop", "outcrop.obj")
LoadModel("toyota", "goblin.fbx")

--spawn player
SpawnGameObject("player")
GetGameObject("player"):AddCCharacter():SetHitpoints(5)
GetGameObject("player"):SetActive(true)
GetGameObject("player"):AddCCameraComponent():SetAsCurrentCamera()
GetGameObject("player"):AddCScript():AssignScript("player_script")
GetGameObject("player"):GetTransform():SetPosition(512,20,512)


--spawn rovers
roverXcoords = {517, 931, 478, 615, 008, 572, 525, 382, 697, 151, 399, 502, 503, 112, 802, 301, 130, 623, 203, 978}
roverZcoords = {337, 266, 901, 130, 776, 757, 815, 615, 355, 609, 024, 860, 907, 756, 289, 541, 949, 839, 307, 665}
for i=1,20,1 do
    roverName = "rover " .. i
    SpawnGameObject(roverName)
    GetGameObject(roverName):SetActive(true)
    GetGameObject(roverName):GetTransform():RotateLocal(-60, 1, 0, 0)
    GetGameObject(roverName):GetTransform():Scale(3,3,3)
    GetGameObject(roverName):GetTransform():SetPosition(roverXcoords[i],20,roverZcoords[i])
    GetGameObject(roverName):AddCStaticMesh():AssignModel("toyota"):AssignTexture("brick_texture")

end


--spawn rocks

rockName = "rock1"
SpawnGameObject(rockName)
GetGameObject(rockName):GetTransform():Scale(5,5,5)
GetGameObject(rockName):GetTransform():SetPosition(500,20,500)
GetGameObject(rockName):AddCStaticMesh():AssignModel("rock_outcrop"):AssignTexture("rock_texture")
GetGameObject(rockName):AddCAABBCollider():SetCollider(1.6,1.2,1.2,-1.1,-3,-1.8)

rockName = "rock2"
SpawnGameObject(rockName)
GetGameObject(rockName):GetTransform():Scale(5,5,5)
GetGameObject(rockName):GetTransform():SetPosition(520,20,500)
GetGameObject(rockName):AddCStaticMesh():AssignModel("rock_outcrop"):AssignTexture("rock_texture")
GetGameObject(rockName):AddCAABBCollider():SetCollider(1.6,1.2,1.2,-1.1,-3,-1.8)

