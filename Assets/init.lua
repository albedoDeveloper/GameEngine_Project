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
LoadTexture("healthBar_image", "healthBar.png")
LoadTexture("test_tex", "maxresdefault.png")
LoadScript("water_interact", "waterInteraction.lua")
LoadScript("acid_interact", "acidInteract.lua")

-- set skybox
InitSkybox(
    "skybox/negx.png",
    "skybox/negy.png",
    "skybox/negz.png",
    "skybox/posx.png",
    "skybox/posy.png",
    "skybox/posz.png"
)

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
GetGameObject("player"):SetActive(false)
GetGameObject("player"):AddCCameraComponent():SetAsCurrentCamera()
GetGameObject("player"):AddCScript():AssignScript("player_script")
GetGameObject("player"):GetTransform():SetPosition(512,250,512)

--Spawn wall collision boxes
SpawnGameObject("Wall1")
GetGameObject("Wall1"):GetTransform():SetPosition(0, 150, 0)
GetGameObject("Wall1"):AddCAABBCollider():SetCollider(8,130,1100,-10,0,0)

SpawnGameObject("Wall2")
GetGameObject("Wall2"):GetTransform():SetPosition(0, 150, 1020)
GetGameObject("Wall2"):AddCAABBCollider():SetCollider(1100,100,8,0,-80,-10)

SpawnGameObject("Wall3")
GetGameObject("Wall3"):GetTransform():SetPosition(1020, 150, 0)
GetGameObject("Wall3"):AddCAABBCollider():SetCollider(8,100,1100,-10,-80,0)

SpawnGameObject("Wall4")
GetGameObject("Wall4"):GetTransform():SetPosition(0, 150, 0)
GetGameObject("Wall4"):AddCAABBCollider():SetCollider(1100,100,8,0,-80,-10)

--spawn Water Plane
--SpawnGameObject("Water1")
--GetGameObject("Water1"):GetTransform():SetPosition(512, 125, 512)
--GetGameObject("Water1"):GetTransform():Scale(25, 1, 25)
--GetGameObject("Water1"):AddCStaticMesh():AssignModel("water_plane"):AssignTexture("test_tex")
--GetGameObject("Water1"):AddCWaterComponent():AssignModel("water_plane"):AssignTexture("water_texture")

--spawn Water Circle

--spawn fault crack side One
SpawnGameObject("faultCrack1")
GetGameObject("faultCrack1"):GetTransform():SetPosition(0, 210, 0)
GetGameObject("faultCrack1"):GetTransform():Scale(10, 12, 10)
GetGameObject("faultCrack1"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")
--GetGameObject("faultCrack1"):AddCAABBCollider():SetCollider(1,3,10,-3,0,0)

SpawnGameObject("faultCrack2")
GetGameObject("faultCrack2"):GetTransform():SetPosition(0, 210, 95)
GetGameObject("faultCrack2"):GetTransform():Scale(10, 15, 10)
GetGameObject("faultCrack2"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")
--GetGameObject("faultCrack2"):AddCAABBCollider():SetCollider(1,3,10,-3,0,0)

SpawnGameObject("faultCrack3")
GetGameObject("faultCrack3"):GetTransform():SetPosition(0, 210, 190)
GetGameObject("faultCrack3"):GetTransform():Scale(10, 15, 10)
GetGameObject("faultCrack3"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")
--GetGameObject("faultCrack3"):AddCAABBCollider():SetCollider(1,3,10,-3,0,0)

SpawnGameObject("faultCrack4")
GetGameObject("faultCrack4"):GetTransform():SetPosition(0, 210, 285)
GetGameObject("faultCrack4"):GetTransform():Scale(10, 15, 10)
GetGameObject("faultCrack4"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")
--GetGameObject("faultCrack4"):AddCAABBCollider():SetCollider(1,3,10,-3,0,0)

SpawnGameObject("faultCrack5")
GetGameObject("faultCrack5"):GetTransform():SetPosition(0, 210, 380)
GetGameObject("faultCrack5"):GetTransform():Scale(10, 15, 10)
GetGameObject("faultCrack5"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")
--GetGameObject("faultCrack5"):AddCAABBCollider():SetCollider(1,3,10,-3,0,0)

SpawnGameObject("faultCrack6")
GetGameObject("faultCrack6"):GetTransform():SetPosition(0, 210, 475)
GetGameObject("faultCrack6"):GetTransform():Scale(10, 15, 10)
GetGameObject("faultCrack6"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")
--GetGameObject("faultCrack6"):AddCAABBCollider():SetCollider(1,3,10,-3,0,0)

SpawnGameObject("faultCrack7")
GetGameObject("faultCrack7"):GetTransform():SetPosition(0, 190, 570)
GetGameObject("faultCrack7"):GetTransform():Scale(10, 15, 10)
GetGameObject("faultCrack7"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")
--GetGameObject("faultCrack7"):AddCAABBCollider():SetCollider(1,3,10,-3,0,0)

SpawnGameObject("faultCrack8")
GetGameObject("faultCrack8"):GetTransform():SetPosition(0, 180, 665)
GetGameObject("faultCrack8"):GetTransform():Scale(10, 15, 10)
GetGameObject("faultCrack8"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")
--GetGameObject("faultCrack8"):AddCAABBCollider():SetCollider(1,3,10,-3,0,0)

SpawnGameObject("faultCrack9")
GetGameObject("faultCrack9"):GetTransform():SetPosition(0, 180, 760)
GetGameObject("faultCrack9"):GetTransform():Scale(10, 15, 10)
GetGameObject("faultCrack9"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")
--GetGameObject("faultCrack9"):AddCAABBCollider():SetCollider(1,3,10,-3,0,0)

SpawnGameObject("faultCrack10")
GetGameObject("faultCrack10"):GetTransform():SetPosition(0, 180, 855)
GetGameObject("faultCrack10"):GetTransform():Scale(10, 15, 10)
GetGameObject("faultCrack10"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")
--GetGameObject("faultCrack10"):AddCAABBCollider():SetCollider(1,3,10,-3,0,0)

SpawnGameObject("faultCrack11")
GetGameObject("faultCrack11"):GetTransform():SetPosition(0, 150, 950)
GetGameObject("faultCrack11"):GetTransform():Scale(10, 20, 10)
GetGameObject("faultCrack11"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")
--GetGameObject("faultCrack11"):AddCAABBCollider():SetCollider(1,3,10,-3,0,0)

--spawn fault crack side Two
SpawnGameObject("faultCrack12")
GetGameObject("faultCrack12"):GetTransform():SetPosition(1020, 85, 1030)
GetGameObject("faultCrack12"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack12"):GetTransform():RotateLocal(110, 0, 1, 0)
GetGameObject("faultCrack12"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack13")
GetGameObject("faultCrack13"):GetTransform():SetPosition(1020, 85, 945)
GetGameObject("faultCrack13"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack13"):GetTransform():RotateLocal(110, 0, 1, 0)
GetGameObject("faultCrack13"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack14")
GetGameObject("faultCrack14"):GetTransform():SetPosition(1020, 85, 850)
GetGameObject("faultCrack14"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack14"):GetTransform():RotateLocal(110, 0, 1, 0)
GetGameObject("faultCrack14"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack15")
GetGameObject("faultCrack15"):GetTransform():SetPosition(1020, 85, 755)
GetGameObject("faultCrack15"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack15"):GetTransform():RotateLocal(110, 0, 1, 0)
GetGameObject("faultCrack15"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack16")
GetGameObject("faultCrack16"):GetTransform():SetPosition(1020, 90, 660)
GetGameObject("faultCrack16"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack16"):GetTransform():RotateLocal(110, 0, 1, 0)
GetGameObject("faultCrack16"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack17")
GetGameObject("faultCrack17"):GetTransform():SetPosition(1020, 95, 565)
GetGameObject("faultCrack17"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack17"):GetTransform():RotateLocal(110, 0, 1, 0)
GetGameObject("faultCrack17"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack18")
GetGameObject("faultCrack18"):GetTransform():SetPosition(1020, 100, 470)
GetGameObject("faultCrack18"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack18"):GetTransform():RotateLocal(110, 0, 1, 0)
GetGameObject("faultCrack18"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack19")
GetGameObject("faultCrack19"):GetTransform():SetPosition(1020, 100, 375)
GetGameObject("faultCrack19"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack19"):GetTransform():RotateLocal(110, 0, 1, 0)
GetGameObject("faultCrack19"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack20")
GetGameObject("faultCrack20"):GetTransform():SetPosition(1020, 100, 280)
GetGameObject("faultCrack20"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack20"):GetTransform():RotateLocal(110, 0, 1, 0)
GetGameObject("faultCrack20"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack21")
GetGameObject("faultCrack21"):GetTransform():SetPosition(1020, 100, 185)
GetGameObject("faultCrack21"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack21"):GetTransform():RotateLocal(110, 0, 1, 0)
GetGameObject("faultCrack21"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack22")
GetGameObject("faultCrack22"):GetTransform():SetPosition(1020, 100, 90)
GetGameObject("faultCrack22"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack22"):GetTransform():RotateLocal(110, 0, 1, 0)
GetGameObject("faultCrack22"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

--spawn fault crack side Three
SpawnGameObject("faultCrack23")
GetGameObject("faultCrack23"):GetTransform():SetPosition(1030, 105, 0)
GetGameObject("faultCrack23"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack23"):GetTransform():RotateLocal(-55, 0, 1, 0)
GetGameObject("faultCrack23"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack24")
GetGameObject("faultCrack24"):GetTransform():SetPosition(935, 115, 0)
GetGameObject("faultCrack24"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack24"):GetTransform():RotateLocal(-55, 0, 1, 0)
GetGameObject("faultCrack24"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack25")
GetGameObject("faultCrack25"):GetTransform():SetPosition(840, 115, 0)
GetGameObject("faultCrack25"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack25"):GetTransform():RotateLocal(-55, 0, 1, 0)
GetGameObject("faultCrack25"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack26")
GetGameObject("faultCrack26"):GetTransform():SetPosition(745, 120, 0)
GetGameObject("faultCrack26"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack26"):GetTransform():RotateLocal(-55, 0, 1, 0)
GetGameObject("faultCrack26"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack27")
GetGameObject("faultCrack27"):GetTransform():SetPosition(745, 120, 0)
GetGameObject("faultCrack27"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack27"):GetTransform():RotateLocal(-55, 0, 1, 0)
GetGameObject("faultCrack27"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack28")
GetGameObject("faultCrack28"):GetTransform():SetPosition(650, 120, 0)
GetGameObject("faultCrack28"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack28"):GetTransform():RotateLocal(-55, 0, 1, 0)
GetGameObject("faultCrack28"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack29")
GetGameObject("faultCrack29"):GetTransform():SetPosition(555, 125, 0)
GetGameObject("faultCrack29"):GetTransform():Scale(10, 12, 10)
GetGameObject("faultCrack29"):GetTransform():RotateLocal(-55, 0, 1, 0)
GetGameObject("faultCrack29"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack30")
GetGameObject("faultCrack30"):GetTransform():SetPosition(460, 130, 0)
GetGameObject("faultCrack30"):GetTransform():Scale(10, 15, 10)
GetGameObject("faultCrack30"):GetTransform():RotateLocal(-55, 0, 1, 0)
GetGameObject("faultCrack30"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack31")
GetGameObject("faultCrack31"):GetTransform():SetPosition(365, 150, 0)
GetGameObject("faultCrack31"):GetTransform():Scale(10, 15, 10)
GetGameObject("faultCrack31"):GetTransform():RotateLocal(-55, 0, 1, 0)
GetGameObject("faultCrack31"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack32")
GetGameObject("faultCrack32"):GetTransform():SetPosition(300, 180, 0)
GetGameObject("faultCrack32"):GetTransform():Scale(10, 15, 10)
GetGameObject("faultCrack32"):GetTransform():RotateLocal(-55, 0, 1, 0)
GetGameObject("faultCrack32"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack33")
GetGameObject("faultCrack33"):GetTransform():SetPosition(215, 200, 0)
GetGameObject("faultCrack33"):GetTransform():Scale(10, 12, 10)
GetGameObject("faultCrack33"):GetTransform():RotateLocal(-55, 0, 1, 0)
GetGameObject("faultCrack33"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack34")
GetGameObject("faultCrack34"):GetTransform():SetPosition(120, 215, 0)
GetGameObject("faultCrack34"):GetTransform():Scale(10, 15, 10)
GetGameObject("faultCrack34"):GetTransform():RotateLocal(-55, 0, 1, 0)
GetGameObject("faultCrack34"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack35")
GetGameObject("faultCrack35"):GetTransform():SetPosition(50, 215, 0)
GetGameObject("faultCrack35"):GetTransform():Scale(10, 14, 10)
GetGameObject("faultCrack35"):GetTransform():RotateLocal(-55, 0, 1, 0)
GetGameObject("faultCrack35"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

--spawn fault crack side Four
SpawnGameObject("faultCrack36")
GetGameObject("faultCrack36"):GetTransform():SetPosition(0, 140, 1020)
GetGameObject("faultCrack36"):GetTransform():Scale(10, 14, 10)
GetGameObject("faultCrack36"):GetTransform():RotateLocal(55, 0, 1, 0)
GetGameObject("faultCrack36"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack37")
GetGameObject("faultCrack37"):GetTransform():SetPosition(95, 110, 1020)
GetGameObject("faultCrack37"):GetTransform():Scale(10, 15, 10)
GetGameObject("faultCrack37"):GetTransform():RotateLocal(55, 0, 1, 0)
GetGameObject("faultCrack37"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack38")
GetGameObject("faultCrack38"):GetTransform():SetPosition(190, 110, 1020)
GetGameObject("faultCrack38"):GetTransform():Scale(10, 12, 10)
GetGameObject("faultCrack38"):GetTransform():RotateLocal(55, 0, 1, 0)
GetGameObject("faultCrack38"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack39")
GetGameObject("faultCrack39"):GetTransform():SetPosition(285, 105, 1020)
GetGameObject("faultCrack39"):GetTransform():Scale(10, 12, 10)
GetGameObject("faultCrack39"):GetTransform():RotateLocal(55, 0, 1, 0)
GetGameObject("faultCrack39"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack40")
GetGameObject("faultCrack40"):GetTransform():SetPosition(380, 105, 1020)
GetGameObject("faultCrack40"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack40"):GetTransform():RotateLocal(55, 0, 1, 0)
GetGameObject("faultCrack40"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack41")
GetGameObject("faultCrack41"):GetTransform():SetPosition(475, 95, 1020)
GetGameObject("faultCrack41"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack41"):GetTransform():RotateLocal(55, 0, 1, 0)
GetGameObject("faultCrack41"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack42")
GetGameObject("faultCrack42"):GetTransform():SetPosition(570, 90, 1020)
GetGameObject("faultCrack42"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack42"):GetTransform():RotateLocal(55, 0, 1, 0)
GetGameObject("faultCrack42"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack43")
GetGameObject("faultCrack43"):GetTransform():SetPosition(665, 85, 1020)
GetGameObject("faultCrack43"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack43"):GetTransform():RotateLocal(55, 0, 1, 0)
GetGameObject("faultCrack43"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack44")
GetGameObject("faultCrack44"):GetTransform():SetPosition(760, 85, 1020)
GetGameObject("faultCrack44"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack44"):GetTransform():RotateLocal(55, 0, 1, 0)
GetGameObject("faultCrack44"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack45")
GetGameObject("faultCrack45"):GetTransform():SetPosition(855, 85, 1020)
GetGameObject("faultCrack45"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack45"):GetTransform():RotateLocal(55, 0, 1, 0)
GetGameObject("faultCrack45"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

SpawnGameObject("faultCrack46")
GetGameObject("faultCrack46"):GetTransform():SetPosition(950, 85, 1020)
GetGameObject("faultCrack46"):GetTransform():Scale(10, 10, 10)
GetGameObject("faultCrack46"):GetTransform():RotateLocal(55, 0, 1, 0)
GetGameObject("faultCrack46"):AddCStaticMesh():AssignModel("fault_crack_model"):AssignTexture("brick_texture")

-- spawn end screen
SpawnGameObject("endScreen")
GetGameObject("endScreen"):SetActive(false)
GetGameObject("endScreen"):AddCUserInterface():AssignTexture("end_image")
GetGameObject("endScreen"):GetCUserInterface():SetSize(300, 300)
GetGameObject("endScreen"):AddCScript():AssignScript("displayAtQuit_script")

--help GUI
SpawnGameObject("help")
GetGameObject("help"):SetActive(false)
GetGameObject("help"):AddCUserInterface():AssignTexture("help_image")
GetGameObject("help"):GetCUserInterface():SetSize(300, 300)
GetGameObject("help"):AddCScript():AssignScript("help_lua")



--spawn rovers
roverXcoords = {517, 931, 478, 615, 008, 572, 525, 382, 697, 151, 399, 502, 503, 112, 802, 301, 130, 623, 203, 978}
roverZcoords = {337, 266, 901, 130, 776, 757, 815, 615, 355, 609, 024, 860, 907, 756, 289, 541, 949, 839, 307, 665}
for i=1,20,1 do
    roverName = "rover " .. i
    SpawnGameObject(roverName)
    GetGameObject(roverName):SetActive(false)
    GetGameObject(roverName):GetTransform():SetPosition(roverXcoords[i],20,roverZcoords[i])
    GetGameObject(roverName):AddCStaticMesh():AssignModel("rover_model"):AssignTexture("brick_texture")
    GetGameObject(roverName):AddCStateMachineAI():AssignScript("rover_ai")

end


--spawn rocks
rockXcoords = {512, 105, 838, 474, 735, 086, 689, 895, 256, 479, 598, 031, 745, 860, 306, 803, 740, 333, 950, 688, 037}
rockZcoords = {500, 794, 945, 559, 986, 127, 338, 729, 463, 292, 887, 795, 426, 476, 524, 335, 483, 755, 588, 724, 100}
for i=1,5,1 do
    rockName = "rock " .. i
    SpawnGameObject(rockName)
    GetGameObject(rockName):GetTransform():Scale(5,5,5)
    GetGameObject(rockName):GetTransform():SetPosition(rockXcoords[i],0,rockZcoords[i])
    yPos = GetGameObject("terrain"):GetCTerrainBruteForce():GetHeightBilinear(GetGameObject(rockName):GetTransform():GetPosition()) + 3
    GetGameObject(rockName):GetTransform():SetPosition(rockXcoords[i],yPos,rockZcoords[i])
    GetGameObject(rockName):AddCStaticMesh():AssignModel("rock_outcrop"):AssignTexture("rock_texture")
    GetGameObject(rockName):AddCAABBCollider():SetCollider(1.6,1.2,1.2,-1.1,-3,-1.8)
end

GetGameObject("player"):SetActive(true)
GetGameObject("healthBar"):SetActive(true)
for i=1,20,1 do
    roverName = "rover " .. i
    GetGameObject(roverName):SetActive(true)
    GetGameObject(roverName):SetDifficulty("easy")
end