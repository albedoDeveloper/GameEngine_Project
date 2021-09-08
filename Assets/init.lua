
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
GetGameObject("goblin1"):AddCSound():LoadSound("CantinaBand60.wav")
GetGameObject("goblin1"):GetCSound():PlaySound("CantinaBand60.wav", 2,true)
GetGameObject("goblin1"):AddCScript():AssignScript("rotate")

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
GetGameObject("beer_tap1"):GetTransform():SetPosition(1,0,0)

SpawnGameObject("waitress"):SetStatic(true)
GetGameObject("waitress"):AddCStaticMesh():AssignModel("waitress")
GetGameObject("waitress"):GetTransform():SetPosition(2,0,0)

SpawnGameObject("cola_fridge"):SetStatic(true)
GetGameObject("cola_fridge"):AddCStaticMesh():AssignModel("cola_fridge")
GetGameObject("cola_fridge"):GetTransform():SetPosition(3,0,0)

SpawnGameObject("pool-table"):SetStatic(true)
GetGameObject("pool-table"):AddCStaticMesh():AssignModel("pool-table")
GetGameObject("pool-table"):GetTransform():SetPosition(5,0,0)

SpawnGameObject("table"):SetStatic(true)
GetGameObject("table"):AddCStaticMesh():AssignModel("table")
GetGameObject("table"):GetTransform():SetPosition(6,0,0)

SpawnGameObject("chair"):SetStatic(true)
GetGameObject("chair"):AddCStaticMesh():AssignModel("chair")
GetGameObject("chair"):GetTransform():SetPosition(7,0,0)

SpawnGameObject("tv"):SetStatic(true)
GetGameObject("tv"):AddCStaticMesh():AssignModel("tv")
GetGameObject("tv"):GetTransform():SetPosition(8,1,0)

