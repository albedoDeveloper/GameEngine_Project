
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

LoadScript("rotate", "rotate.lua")

SpawnGameObject("spiked_door_toilet"):SetStatic(true)
GetGameObject("spiked_door_toilet"):AddCStaticMesh():AssignModel("spiked_door_toilet")

SpawnGameObject("waitress"):SetStatic(true)
GetGameObject("waitress"):AddCStaticMesh():AssignModel("waitress")

SpawnGameObject("toilet_block"):SetStatic(true)
GetGameObject("toilet_block"):AddCStaticMesh():AssignModel("toilet_block")

SpawnGameObject("tavern_glass_door_wall_long_2"):SetStatic(true)
GetGameObject("tavern_glass_door_wall_long_2"):AddCStaticMesh():AssignModel("tavern_glass_door_wall_long_2")

SpawnGameObject("tavern_glass_door_wall_long"):SetStatic(true)
GetGameObject("tavern_glass_door_wall_long"):AddCStaticMesh():AssignModel("tavern_glass_door_wall_long")

SpawnGameObject("tavern_glass_door_wall"):SetStatic(true)
GetGameObject("tavern_glass_door_wall"):AddCStaticMesh():AssignModel("tavern_glass_door_wall")

SpawnGameObject("spiked_door_bar"):SetStatic(true)
GetGameObject("spiked_door_bar"):AddCStaticMesh():AssignModel("spiked_door_bar")

SpawnGameObject("south_bar_wall"):SetStatic(true)
GetGameObject("south_bar_wall"):AddCStaticMesh():AssignModel("south_bar_wall")

SpawnGameObject("south_bar_barrier_2"):SetStatic(true)
GetGameObject("south_bar_barrier_2"):AddCStaticMesh():AssignModel("south_bar_barrier_2")

SpawnGameObject("south_bar_barrier"):SetStatic(true)
GetGameObject("south_bar_barrier"):AddCStaticMesh():AssignModel("south_bar_barrier")

SpawnGameObject("tavern_floor"):SetStatic(true)
GetGameObject("tavern_floor"):AddCStaticMesh():AssignModel("tavern_floor")

SpawnGameObject("roof_interior"):SetStatic(true)
GetGameObject("roof_interior"):AddCStaticMesh():AssignModel("roof_interior")

SpawnGameObject("pool-table"):SetStatic(true)
GetGameObject("pool-table"):AddCStaticMesh():AssignModel("pool-table")

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

SpawnGameObject("crate"):SetStatic(true)
GetGameObject("crate"):AddCStaticMesh():AssignModel("crate")
GetGameObject("crate"):AddCScript():AssignScript("rotate")

SpawnGameObject("back_wall"):SetStatic(true)
GetGameObject("back_wall"):AddCStaticMesh():AssignModel("back_wall")

SpawnGameObject("whitelight"):SetStatic(true)
GetGameObject("whitelight"):AddCPointLight()
GetGameObject("whitelight"):GetTransform():Translate(-1,2,1)
GetGameObject("whitelight"):AddCStaticMesh():AssignModel("axis")

SpawnGameObject("lightAnchor"):SetStatic(false)
GetGameObject("lightAnchor"):GetTransform():Translate(0,2,0)
GetGameObject("lightAnchor"):AddCScript():AssignScript("rotate")

SpawnGameObject("light1"):SetStatic(false)
GetGameObject("light1"):AddCPointLight():AssignColour(0,0,0.6)
GetGameObject("light1"):SetParentObject("lightAnchor")
GetGameObject("light1"):GetTransform():Translate(5,0,0)

SpawnGameObject("light2"):SetStatic(false)
GetGameObject("light2"):AddCPointLight():AssignColour(0,0.6,0)
GetGameObject("light2"):SetParentObject("lightAnchor")
GetGameObject("light2"):GetTransform():Translate(-5,0,0)

