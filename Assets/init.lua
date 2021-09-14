
LoadModel("crate", "crate/crate.fbx")
LoadModel("tavern_floor", "tavern_floor/tavern_floor.fbx")
LoadModel("axis", "axis/axis.fbx")
LoadModel("behind_bar_block", "behind_bar_block/behind_bar_block.fbx")
LoadModel("back_wall", "back_wall/back_wall.fbx")
LoadModel("bar_floor_rod", "bar_floor_rod/bar_floor_rod.fbx")
LoadModel("barrel1", "barrel1/barrel1.fbx")
LoadModel("barrel2", "barrel2/barrel2.fbx")
LoadModel("graffiti_block", "graffiti_block/graffiti_block.fbx")
LoadModel("main_bar_bench", "main_bar_bench/main_bar_bench.fbx")
LoadModel("pool-table", "pool-table/pool-table.fbx")
LoadModel("roof_interior", "roof_interior/roof_interior.fbx")
LoadModel("south_bar_barrier", "south_bar_barrier/south_bar_barrier.fbx")
LoadModel("south_bar_barrier_2", "south_bar_barrier_2/south_bar_barrier_2.fbx")
LoadModel("south_bar_wall", "south_bar_wall/south_bar_wall.fbx")
LoadModel("spiked_door_bar", "spiked_door_bar/spiked_door_bar.fbx")
LoadModel("spiked_door_toilet", "spiked_door_toilet/spiked_door_toilet.fbx")
LoadModel("tavern_glass_door_wall", "tavern_glass_door_wall/tavern_glass_door_wall.fbx")
LoadModel("tavern_glass_door_wall_long", "tavern_glass_door_wall_long/tavern_glass_door_wall_long.fbx")
LoadModel("tavern_glass_door_wall_long_2", "tavern_glass_door_wall_long_2/tavern_glass_door_wall_long_2.fbx")
LoadModel("toilet_block", "toilet_block/toilet_block.fbx")
LoadModel("waitress", "waitress/waitress.fbx")
LoadModel("endscreen", "endscreen/endscreen.fbx")

LoadScript("rotate", "rotate.lua")

SpawnGameObject("endscreen"):SetStatic(true)
GetGameObject("endscreen"):AddCStaticMesh():AssignModel("endscreen")

SpawnGameObject("spiked_door_toilet"):SetStatic(true)
GetGameObject("spiked_door_toilet"):AddCStaticMesh():AssignModel("spiked_door_toilet")

SpawnGameObject("waitress"):SetStatic(true)
GetGameObject("waitress"):AddCStaticMesh():AssignModel("waitress")

SpawnGameObject("toilet_block"):SetStatic(true)
GetGameObject("toilet_block"):AddCStaticMesh():AssignModel("toilet_block")
GetGameObject("toilet_block"):AddCCollider():AddConcaveCollider(1)
GetGameObject("toilet_block"):GetCCollider():CollideWith(2)

SpawnGameObject("tavern_glass_door_wall_long_2"):SetStatic(true)
GetGameObject("tavern_glass_door_wall_long_2"):AddCStaticMesh():AssignModel("tavern_glass_door_wall_long_2")
GetGameObject("tavern_glass_door_wall_long_2"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("tavern_glass_door_wall_long_2"):GetCCollider():CollideWith(2)

SpawnGameObject("tavern_glass_door_wall_long"):SetStatic(true)
GetGameObject("tavern_glass_door_wall_long"):AddCStaticMesh():AssignModel("tavern_glass_door_wall_long")
GetGameObject("tavern_glass_door_wall_long"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("tavern_glass_door_wall_long"):GetCCollider():CollideWith(2)

SpawnGameObject("tavern_glass_door_wall"):SetStatic(true)
GetGameObject("tavern_glass_door_wall"):AddCStaticMesh():AssignModel("tavern_glass_door_wall")
GetGameObject("tavern_glass_door_wall"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("tavern_glass_door_wall"):GetCCollider():CollideWith(2)

SpawnGameObject("spiked_door_bar"):SetStatic(true)
GetGameObject("spiked_door_bar"):AddCStaticMesh():AssignModel("spiked_door_bar")

SpawnGameObject("south_bar_wall"):SetStatic(true)
GetGameObject("south_bar_wall"):AddCStaticMesh():AssignModel("south_bar_wall")

SpawnGameObject("south_bar_barrier_2"):SetStatic(true)
GetGameObject("south_bar_barrier_2"):AddCStaticMesh():AssignModel("south_bar_barrier_2")
GetGameObject("south_bar_barrier_2"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("south_bar_barrier_2"):GetCCollider():CollideWith(2)

SpawnGameObject("south_bar_barrier"):SetStatic(true)
GetGameObject("south_bar_barrier"):AddCStaticMesh():AssignModel("south_bar_barrier")
GetGameObject("south_bar_barrier"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("south_bar_barrier"):GetCCollider():CollideWith(2)

SpawnGameObject("tavern_floor"):SetStatic(true)
GetGameObject("tavern_floor"):AddCStaticMesh():AssignModel("tavern_floor")
GetGameObject("tavern_floor"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("tavern_floor"):GetCCollider():CollideWith(2)

SpawnGameObject("roof_interior"):SetStatic(true)
GetGameObject("roof_interior"):AddCStaticMesh():AssignModel("roof_interior")

SpawnGameObject("pool-table"):SetStatic(true)
GetGameObject("pool-table"):AddCStaticMesh():AssignModel("pool-table")
GetGameObject("pool-table"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("pool-table"):GetCCollider():CollideWith(2)

SpawnGameObject("main_bar_bench"):SetStatic(true)
GetGameObject("main_bar_bench"):AddCStaticMesh():AssignModel("main_bar_bench")

SpawnGameObject("graffiti_block"):SetStatic(true)
GetGameObject("graffiti_block"):AddCStaticMesh():AssignModel("graffiti_block")

SpawnGameObject("behind_bar_block"):SetStatic(true)
GetGameObject("behind_bar_block"):AddCStaticMesh():AssignModel("behind_bar_block")

SpawnGameObject("bar_floor_rod"):SetStatic(true)
GetGameObject("bar_floor_rod"):AddCStaticMesh():AssignModel("bar_floor_rod")

SpawnGameObject("barrel1"):SetStatic(true)
GetGameObject("barrel1"):AddCStaticMesh():AssignModel("barrel1")

SpawnGameObject("barrel2"):SetStatic(true)
GetGameObject("barrel2"):AddCStaticMesh():AssignModel("barrel2")

SpawnGameObject("crate"):SetStatic(false)
GetGameObject("crate"):AddCStaticMesh():AssignModel("crate")
GetGameObject("crate"):GetTransform():SetPosition(-7.744999885559082, 1.315000057220459, -0.4449999928474426)
GetGameObject("crate"):GetTransform():RotateLocalX(45)
GetGameObject("crate"):AddCScript():AssignScript("rotate")

SpawnGameObject("back_wall"):SetStatic(true)
GetGameObject("back_wall"):AddCStaticMesh():AssignModel("back_wall")

SpawnGameObject("lightAnchor"):SetStatic(false)
GetGameObject("lightAnchor"):GetTransform():SetPosition(4.954999923706055,
1.9049999713897705,
5.275000095367432);
GetGameObject("lightAnchor"):AddCScript():AssignScript("rotate")

SpawnGameObject("light1"):SetStatic(false)
GetGameObject("light1"):AddCPointLight()
GetGameObject("light1"):GetCPointLight():AssignColour(0.8,0.8,0.8)
GetGameObject("light1"):GetCPointLight():AssignAmbientStrength(1)
GetGameObject("light1"):GetTransform():SetPosition(-8.354999542236328,
2.6700000762939453,
1.0);
GetGameObject("light1"):AddCStaticMesh():AssignModel("axis")


SpawnGameObject("light2"):SetStatic(false)
GetGameObject("light2"):AddCPointLight()
GetGameObject("light2"):GetCPointLight():AssignColour(0,0,1)
GetGameObject("light2"):GetCPointLight():AssignAmbientStrength(0.1)
GetGameObject("light2"):SetParentObject("lightAnchor")
GetGameObject("light2"):AddCStaticMesh():AssignModel("axis")
GetGameObject("light2"):GetTransform():Translate(0.5,0,0)

SpawnGameObject("player");
GetGameObject("player"):GetTransform():SetPosition(0, 2, 0);
GetGameObject("player"):AddCCollider():AddBoxCollider(0.5, 1.4, 0.5, 0 ,0, 0, false, 2, false);
GetGameObject("player"):GetCCollider():CollideWith(1);
GetGameObject("player"):AddCCharacter():SetPlayerControlled(true);
GetGameObject("player"):AddCCameraComponent():SetAsCurrentCamera();