--load assets
LoadModel("cube_model", "cube.obj")
LoadModel("monke_model", "monke.obj")
LoadModel("rover_model", "Rover.obj")
LoadTexture("brick_texture", "brick.png")
LoadTexture("water_texture", "water.png")
LoadTexture("acid_texture", "acid.png")
LoadTexture("rock_texture", "rock_stones.png")
LoadScript("rotate_script", "rotate.lua")
LoadScript("player_script", "playerController.lua")
LoadHeightMap("heightmap", "heightmap.raw")
LoadScript("wireframe_script", "terrainWireframe.lua")
LoadTexture("detailmap_texture", "detailmap.png")
LoadScript("displayAtQuit_script", "displayatQuit.lua")
LoadScript("help_lua", "help.lua")
LoadScript("startButton_lua", "startButton.lua")
LoadScript("easyButton_lua", "easyButton.lua")
LoadScript("mediumButton_lua", "mediumButton.lua")
LoadScript("hardButton_lua", "hardButton.lua")
LoadScript("quitButton_lua", "quitButton.lua")
LoadScript("loadButton_lua", "loadButton.lua")
LoadTexture("end_image", "endscreen.png")
LoadTexture("help_image", "help.png")
LoadTexture("start_image", "start.png")
LoadTexture("startButton_image", "startButtonDefault.png")
LoadTexture("easyButton_image", "easyButtonDefault.png")
LoadTexture("mediumButton_image", "mediumButtonDefault.png")
LoadTexture("hardButton_image", "hardButtonDefault.png")
LoadTexture("quitButton_image", "quitButtonDefault.png")
LoadTexture("loadButton_image", "loadButton.png")
LoadScript("rover_ai", "roverAI.lua")
LoadModel("fault_crack_model", "FaultCrack.obj")
LoadModel("rock_outcrop", "outcrop.obj")
LoadModel("water_plane", "waterplane.obj")
LoadModel("water_circle", "watercircle.obj")
LoadModel("toyota", "backpack.obj")
LoadTexture("healthBar_image", "healthBar.png")
LoadTexture("test_tex", "maxresdefault.png")
LoadScript("water_interact", "waterInteraction.lua")
LoadScript("acid_interact", "acidInteract.lua")


-- spawn start menu backdrop
SpawnGameObject("startMenu")
GetGameObject("startMenu"):AddCUserInterface():AssignTexture("start_image") --placeholder image
GetGameObject("startMenu"):GetCUserInterface():SetFullscreen()
GetGameObject("startMenu"):GetCUserInterface():SetVisibility(true)

-- spawn easy/medium/hard buttons
SpawnGameObject("easyButton")
GetGameObject("easyButton"):AddCUserInterface():AssignTexture("easyButton_image") --placeholder image
GetGameObject("easyButton"):GetCUserInterface():SetSize(150,50)
GetGameObject("easyButton"):GetCUserInterface():SetPosition(120, 120)
GetGameObject("easyButton"):GetCUserInterface():SetVisibility(true)
GetGameObject("easyButton"):AddCScript():AssignScript("easyButton_lua")

SpawnGameObject("mediumButton")
GetGameObject("mediumButton"):AddCUserInterface():AssignTexture("mediumButton_image") --placeholder image
GetGameObject("mediumButton"):GetCUserInterface():SetSize(150,50)
GetGameObject("mediumButton"):GetCUserInterface():SetPosition(320, 120)
GetGameObject("mediumButton"):GetCUserInterface():SetVisibility(true)
GetGameObject("mediumButton"):AddCScript():AssignScript("mediumButton_lua")

SpawnGameObject("hardButton")
GetGameObject("hardButton"):AddCUserInterface():AssignTexture("hardButton_image") --placeholder image
GetGameObject("hardButton"):GetCUserInterface():SetSize(150,50)
GetGameObject("hardButton"):GetCUserInterface():SetPosition(520, 120)
GetGameObject("hardButton"):GetCUserInterface():SetVisibility(true)
GetGameObject("hardButton"):AddCScript():AssignScript("hardButton_lua")

-- spawn quit button
SpawnGameObject("quitButton")
GetGameObject("quitButton"):AddCUserInterface():AssignTexture("quitButton_image")
GetGameObject("quitButton"):GetCUserInterface():SetSize(150,50)
GetGameObject("quitButton"):GetCUserInterface():SetPosition(120, 200)
GetGameObject("quitButton"):GetCUserInterface():SetVisibility(true)
GetGameObject("quitButton"):AddCScript():AssignScript("quitButton_lua")

-- spawn load button
SpawnGameObject("loadButton")
GetGameObject("loadButton"):AddCUserInterface():AssignTexture("loadButton_image")
GetGameObject("loadButton"):GetCUserInterface():SetSize(150,50)
GetGameObject("loadButton"):GetCUserInterface():SetPosition(320, 200)
GetGameObject("loadButton"):GetCUserInterface():SetVisibility(true)
GetGameObject("loadButton"):AddCScript():AssignScript("loadButton_lua")

--spawn health bar
SpawnGameObject("healthBar")
GetGameObject("healthBar"):AddCUserInterface():AssignTexture("healthBar_image")
GetGameObject("healthBar"):GetCUserInterface():SetSize(200,50)
GetGameObject("healthBar"):GetCUserInterface():SetPosition(60, 600)
GetGameObject("healthBar"):GetCUserInterface():SetVisibility(true)
GetGameObject("healthBar"):SetActive(false)

-- spawn terrain
SpawnGameObject("terrain")
GetGameObject("terrain"):AddCTerrainBruteForce(1,1,1):AssignHeightMap("heightmap"):AssignTexture("rock_texture", 0, 255)
GetGameObject("terrain"):GetCTerrainBruteForce():GetHeightMap():AssignDetailMap("detailmap_texture")
GetGameObject("terrain"):AddCScript():AssignScript("wireframe_script")

--spawn player
SpawnGameObject("player")
GetGameObject("player"):AddCCharacter():SetHitpoints(5)
GetGameObject("player"):SetActive(true)
GetGameObject("player"):AddCCameraComponent():SetAsCurrentCamera()
GetGameObject("player"):AddCScript():AssignScript("player_script")
GetGameObject("player"):GetTransform():SetPosition(512,250,512)



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

