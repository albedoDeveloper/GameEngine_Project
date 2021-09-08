
LoadModel("tavern_glass_door_wall", "tavern_glass_door_wall.fbx")
LoadModel("tavern_glass_door_wall_long", "tavern_glass_door_wall_long.fbx")
LoadModel("tavern_glass_door_wall_long_2", "tavern_glass_door_wall_long_2.fbx")
LoadModel("back_wall", "back_wall.fbx")
LoadModel("graffiti_block", "graffiti_block.fbx")
LoadModel("tavern_floor", "tavern_floor.fbx")
LoadModel("south_bar_barrier", "south_bar_barrier.fbx")
LoadModel("south_bar_barrier_2", "south_bar_barrier_2.fbx")
LoadModel("main_bar_bench", "main_bar_bench.fbx")
LoadModel("behind_bar_block", "behind_bar_block.fbx")
LoadModel("bar_floor_rod", "bar_floor_rod.fbx")
LoadModel("island", "island.fbx")
LoadModel("spiked_door_toilet", "spiked_door_toilet.fbx")
LoadModel("spiked_door_bar", "spiked_door_bar.fbx")
LoadModel("south_bar_wall", "south_bar_wall.fbx")
LoadModel("axis", "axis/axis.fbx")
LoadModel("goblin", "goblin/goblin.fbx")
LoadModel("roof_interior", "roof_interior.fbx")
LoadModel("toilet_block", "toilet_block.fbx")
LoadModel("barrel", "barrel.fbx")
LoadModel("barrel2", "barrel2.fbx")
LoadModel("beer_tap", "beer-tap/beertap.fbx")
LoadModel("waitress", "waitress/waitress.fbx")
LoadModel("cola_fridge", "cola_fridge/cola_fridge.fbx")
LoadModel("pool-table", "pool-table/pool-table.fbx")
LoadModel("table", "table_chair/table.fbx")
LoadModel("chair", "table_chair/chair.fbx")
LoadModel("tv", "tv-screen/tv.fbx")


LoadScript("rotate", "rotate.lua")



SpawnGameObject("roof_interior"):SetStatic(true)
GetGameObject("roof_interior"):AddCStaticMesh():AssignModel("roof_interior")

SpawnGameObject("lightAnchor"):SetStatic(false)
GetGameObject("lightAnchor"):GetTransform():Translate(0,2,0)
GetGameObject("lightAnchor"):AddCScript():AssignScript("rotate")

SpawnGameObject("light1"):SetStatic(false)
GetGameObject("light1"):AddCPointLight():AssignColour(0,0,0.6)
GetGameObject("light1"):SetParentObject("lightAnchor")
GetGameObject("light1"):GetTransform():Translate(4,0,0)

SpawnGameObject("light2"):SetStatic(false)
GetGameObject("light2"):AddCPointLight():AssignColour(0,0.6,0)
GetGameObject("light2"):SetParentObject("lightAnchor")
GetGameObject("light2"):GetTransform():Translate(-4,0,0)

SpawnGameObject("whitelight"):SetStatic(true)
GetGameObject("whitelight"):AddCPointLight():AssignColour(0.8,0.8,0.8)
GetGameObject("whitelight"):GetTransform():Translate(4.034,2.2,4.3)

SpawnGameObject("barrel"):SetStatic(true)
GetGameObject("barrel"):AddCStaticMesh():AssignModel("barrel")
GetGameObject("barrel"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("barrel"):GetCCollider():CollideWith(2)

SpawnGameObject("barrel2"):SetStatic(true)
GetGameObject("barrel2"):AddCStaticMesh():AssignModel("barrel2")
GetGameObject("barrel2"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("barrel2"):GetCCollider():CollideWith(2)

SpawnGameObject("goblin1")
GetGameObject("goblin1"):AddCStaticMesh():AssignModel("goblin")
--GetGameObject("goblin1"):AddCSound():LoadSound("CantinaBand60.wav")
--GetGameObject("goblin1"):GetCSound():PlaySound("CantinaBand60.wav", 2,true)
GetGameObject("goblin1"):AddCScript():AssignScript("rotate")
GetGameObject("goblin1"):GetTransform():SetPosition(0,2.0,-1)

SpawnGameObject("tavern_glass_door_wall_long_2"):SetStatic(true)
GetGameObject("tavern_glass_door_wall_long_2"):AddCStaticMesh():AssignModel("tavern_glass_door_wall_long_2")
GetGameObject("tavern_glass_door_wall_long_2"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("tavern_glass_door_wall_long_2"):GetCCollider():CollideWith(2)

SpawnGameObject("back_wall"):SetStatic(true)
GetGameObject("back_wall"):AddCStaticMesh():AssignModel("back_wall")
GetGameObject("back_wall"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("back_wall"):GetCCollider():CollideWith(2)

SpawnGameObject("island"):SetStatic(true)
GetGameObject("island"):AddCStaticMesh():AssignModel("island")

SpawnGameObject("toilet_block"):SetStatic(true)
GetGameObject("toilet_block"):AddCStaticMesh():AssignModel("toilet_block")
GetGameObject("toilet_block"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("toilet_block"):GetCCollider():CollideWith(2)

SpawnGameObject("spiked_door_toilet"):SetStatic(true)
GetGameObject("spiked_door_toilet"):AddCStaticMesh():AssignModel("spiked_door_toilet")
GetGameObject("spiked_door_toilet"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("spiked_door_toilet"):GetCCollider():CollideWith(2)

SpawnGameObject("spiked_door_bar"):SetStatic(true)
GetGameObject("spiked_door_bar"):AddCStaticMesh():AssignModel("spiked_door_bar")
GetGameObject("spiked_door_bar"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("spiked_door_bar"):GetCCollider():CollideWith(2)

SpawnGameObject("south_bar_wall"):SetStatic(true)
GetGameObject("south_bar_wall"):AddCStaticMesh():AssignModel("south_bar_wall")

SpawnGameObject("behind_bar_block"):SetStatic(true)
GetGameObject("behind_bar_block"):AddCStaticMesh():AssignModel("behind_bar_block")
GetGameObject("behind_bar_block"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("behind_bar_block"):GetCCollider():CollideWith(2)

SpawnGameObject("tavern_glass_door_wall"):SetStatic(true)
GetGameObject("tavern_glass_door_wall"):AddCStaticMesh():AssignModel("tavern_glass_door_wall")
GetGameObject("tavern_glass_door_wall"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("tavern_glass_door_wall"):GetCCollider():CollideWith(2)

SpawnGameObject("tavern_glass_door_wall_long"):SetStatic(true)
GetGameObject("tavern_glass_door_wall_long"):AddCStaticMesh():AssignModel("tavern_glass_door_wall_long")
GetGameObject("tavern_glass_door_wall_long"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("tavern_glass_door_wall_long"):GetCCollider():CollideWith(2)

SpawnGameObject("graffiti_block"):SetStatic(true)
GetGameObject("graffiti_block"):AddCStaticMesh():AssignModel("graffiti_block")
GetGameObject("graffiti_block"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("graffiti_block"):GetCCollider():CollideWith(2)

SpawnGameObject("south_bar_barrier"):SetStatic(true)
GetGameObject("south_bar_barrier"):AddCStaticMesh():AssignModel("south_bar_barrier")
GetGameObject("south_bar_barrier"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("south_bar_barrier"):GetCCollider():CollideWith(2)

SpawnGameObject("south_bar_barrier_2"):SetStatic(true)
GetGameObject("south_bar_barrier_2"):AddCStaticMesh():AssignModel("south_bar_barrier_2")
GetGameObject("south_bar_barrier_2"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("south_bar_barrier_2"):GetCCollider():CollideWith(2)

SpawnGameObject("tavern_floor"):SetStatic(true)
GetGameObject("tavern_floor"):AddCStaticMesh():AssignModel("tavern_floor")
GetGameObject("tavern_floor"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("tavern_floor"):GetCCollider():CollideWith(2)

SpawnGameObject("main_bar_bench"):SetStatic(true)
GetGameObject("main_bar_bench"):AddCStaticMesh():AssignModel("main_bar_bench")
GetGameObject("main_bar_bench"):AddCCollider():AddConcaveCollider()
GetGameObject("main_bar_bench"):GetCCollider():CollideWith(2)

SpawnGameObject("bar_floor_rod"):SetStatic(true)
GetGameObject("bar_floor_rod"):AddCStaticMesh():AssignModel("bar_floor_rod")

SpawnGameObject("beer_tap1"):SetStatic(true)
GetGameObject("beer_tap1"):AddCStaticMesh():AssignModel("beer_tap")
GetGameObject("beer_tap1"):GetTransform():SetPosition(2.97,1.36,4.0)

SpawnGameObject("beer_tap2"):SetStatic(true)
GetGameObject("beer_tap2"):AddCStaticMesh():AssignModel("beer_tap")
GetGameObject("beer_tap2"):GetTransform():SetPosition(6.55,1.36,3.69)

SpawnGameObject("waitress"):SetStatic(true)
GetGameObject("waitress"):AddCStaticMesh():AssignModel("waitress")
GetGameObject("waitress"):GetTransform():SetPosition(3.8,0.1,4.5)
GetGameObject("waitress"):GetTransform():ScaleLocal(1.4,1.4,1.4)
GetGameObject("waitress"):AddCSound():LoadSound("humming.wav")
GetGameObject("waitress"):GetCSound():PlaySound("humming.wav", -1,true)

SpawnGameObject("cola_fridge1"):SetStatic(true)
GetGameObject("cola_fridge1"):AddCStaticMesh():AssignModel("cola_fridge")
GetGameObject("cola_fridge1"):GetTransform():SetPosition(6.66,0.245,6)
GetGameObject("cola_fridge1"):GetTransform():ScaleLocal(3,4.720,3)


SpawnGameObject("cola_fridge2"):SetStatic(true)
GetGameObject("cola_fridge2"):AddCStaticMesh():AssignModel("cola_fridge")
GetGameObject("cola_fridge2"):GetTransform():SetPosition(2.55,0.245,6)
GetGameObject("cola_fridge2"):GetTransform():ScaleLocal(3,4.720,3)
GetGameObject("cola_fridge2"):AddCCollider():AddBoxCollider(0.5,1,0.5,0,0,0,false,1)
GetGameObject("cola_fridge2"):GetCCollider():CollideWith(2)

SpawnGameObject("pool-table"):SetStatic(true)
GetGameObject("pool-table"):AddCStaticMesh():AssignModel("pool-table")
GetGameObject("pool-table"):GetTransform():SetPosition(-7.44,0.12,0)
GetGameObject("pool-table"):GetTransform():ScaleLocal(1.0,1.41,1.0)
GetGameObject("pool-table"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("pool-table"):GetCCollider():CollideWith(2)

SpawnGameObject("chair1"):SetStatic(true)
GetGameObject("chair1"):AddCStaticMesh():AssignModel("chair")
GetGameObject("chair1"):GetTransform():SetPosition(8.56,0.16,1.8)
GetGameObject("chair1"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("chair1"):GetCCollider():CollideWith(2)

SpawnGameObject("chair2"):SetStatic(true)
GetGameObject("chair2"):AddCStaticMesh():AssignModel("chair")
GetGameObject("chair2"):GetTransform():SetPosition(9.03,0.16,0-2.67)
GetGameObject("chair2"):GetTransform():RotateLocal(90,0,90,1)
GetGameObject("chair2"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("chair2"):GetCCollider():CollideWith(2)

SpawnGameObject("chair3"):SetStatic(true)
GetGameObject("chair3"):AddCStaticMesh():AssignModel("chair")
GetGameObject("chair3"):GetTransform():SetPosition(-0.15,0.16,-1.785)
GetGameObject("chair3"):GetTransform():RotateLocal(0,0,0,1)
GetGameObject("chair3"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("chair3"):GetCCollider():CollideWith(2)

SpawnGameObject("chair4"):SetStatic(true)
GetGameObject("chair4"):AddCStaticMesh():AssignModel("chair")
GetGameObject("chair4"):GetTransform():SetPosition(-0.69,0.16,-1.785)
GetGameObject("chair4"):GetTransform():RotateLocal(180,0,180,1)
GetGameObject("chair4"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("chair4"):GetCCollider():CollideWith(2)

SpawnGameObject("tv"):SetStatic(true)
GetGameObject("tv"):AddCStaticMesh():AssignModel("tv")
GetGameObject("tv"):GetTransform():SetPosition(-4.64,2.54,3.96)
GetGameObject("tv"):GetTransform():RotateLocal(185,0,185,1)

