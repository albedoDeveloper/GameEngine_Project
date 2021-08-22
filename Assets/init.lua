
LoadScript("player_script", "playerController.lua")

LoadModel("rock_outcrop", "outcrop.obj")
LoadModel("toyota", "house uv unwraped.fbx")

--spawn player
SpawnGameObject("player")
GetGameObject("player"):AddCCharacter():SetHitpoints(5)
GetGameObject("player"):SetActive(true)
GetGameObject("player"):AddCCameraComponent():SetAsCurrentCamera()
GetGameObject("player"):AddCScript():AssignScript("player_script")
GetGameObject("player"):GetTransform():SetPosition(512,50,512)


--spawn rovers
roverXcoords = {517, 931, 478, 615, 008, 572, 525, 382, 697, 151, 399, 502, 503, 112, 802, 301, 130, 623, 203, 978}
roverZcoords = {337, 266, 901, 130, 776, 757, 815, 615, 355, 609, 024, 860, 907, 756, 289, 541, 949, 839, 307, 665}
for i=1,20,1 do
    roverName = "rover " .. i
    SpawnGameObject(roverName)
    GetGameObject(roverName):SetActive(true)
    GetGameObject(roverName):GetTransform():Scale(3,3,3)
    GetGameObject(roverName):GetTransform():SetPosition(roverXcoords[i],20,roverZcoords[i])
    GetGameObject(roverName):AddCStaticMesh():AssignModel("toyota"):AssignTexture("brick_texture")

end


--spawn rocks
rockXcoords = {512, 105, 838, 474, 735, 086, 689, 895, 256, 479, 598, 031, 745, 860, 306, 803, 740, 333, 950, 688, 037}
rockZcoords = {500, 794, 945, 559, 986, 127, 338, 729, 463, 292, 887, 795, 426, 476, 524, 335, 483, 755, 588, 724, 100}
for i=1,5,1 do
    rockName = "rock " .. i
    SpawnGameObject(rockName)
    GetGameObject(rockName):GetTransform():Scale(5,5,5)
    GetGameObject(rockName):GetTransform():SetPosition(rockXcoords[i],0,rockZcoords[i])
    GetGameObject(rockName):GetTransform():SetPosition(rockXcoords[i],200,rockZcoords[i])
    GetGameObject(rockName):AddCStaticMesh():AssignModel("rock_outcrop"):AssignTexture("rock_texture")
    GetGameObject(rockName):AddCAABBCollider():SetCollider(1.6,1.2,1.2,-1.1,-3,-1.8)
end

