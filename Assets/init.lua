
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

LoadScript("rotate", "rotate.lua")

SpawnGameObject("roof_interior")
GetGameObject("roof_interior"):AddCStaticMesh():AssignModel("roof_interior")

SpawnGameObject("goblin1")
GetGameObject("goblin1"):AddCStaticMesh():AssignModel("goblin")

GetGameObject("goblin1"):AddCSound():LoadSound("CantinaBand60.wav")
GetGameObject("goblin1"):GetCSound():PlaySound("CantinaBand60.wav", 2,true)
GetGameObject("goblin1"):AddCScript():AssignScript("rotate")

SpawnGameObject("tavern_glass_door_wall_long_2")
GetGameObject("tavern_glass_door_wall_long_2"):AddCStaticMesh():AssignModel("tavern_glass_door_wall_long_2")
GetGameObject("tavern_glass_door_wall_long_2"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true)

SpawnGameObject("back_wall")
GetGameObject("back_wall"):AddCStaticMesh():AssignModel("back_wall")
GetGameObject("back_wall"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true)

SpawnGameObject("island")
GetGameObject("island"):AddCStaticMesh():AssignModel("island")

SpawnGameObject("toilet_block")
GetGameObject("toilet_block"):AddCStaticMesh():AssignModel("toilet_block")
GetGameObject("toilet_block"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true)

SpawnGameObject("spiked_door_toilet")
GetGameObject("spiked_door_toilet"):AddCStaticMesh():AssignModel("spiked_door_toilet")
GetGameObject("spiked_door_toilet"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true)

SpawnGameObject("spiked_door_bar")
GetGameObject("spiked_door_bar"):AddCStaticMesh():AssignModel("spiked_door_bar")
GetGameObject("spiked_door_bar"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true)

SpawnGameObject("south_bar_wall")
GetGameObject("south_bar_wall"):AddCStaticMesh():AssignModel("south_bar_wall")
GetGameObject("south_bar_wall"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true)

SpawnGameObject("behind_bar_block")
GetGameObject("behind_bar_block"):AddCStaticMesh():AssignModel("behind_bar_block")
GetGameObject("behind_bar_block"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true)

SpawnGameObject("tavern_glass_door_wall")
GetGameObject("tavern_glass_door_wall"):AddCStaticMesh():AssignModel("tavern_glass_door_wall")
GetGameObject("tavern_glass_door_wall"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true)

SpawnGameObject("tavern_glass_door_wall_long")
GetGameObject("tavern_glass_door_wall_long"):AddCStaticMesh():AssignModel("tavern_glass_door_wall_long")
GetGameObject("tavern_glass_door_wall_long"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true)

SpawnGameObject("graffiti_block")
GetGameObject("graffiti_block"):AddCStaticMesh():AssignModel("graffiti_block")
GetGameObject("graffiti_block"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true)

SpawnGameObject("south_bar_barrier")
GetGameObject("south_bar_barrier"):AddCStaticMesh():AssignModel("south_bar_barrier")
GetGameObject("south_bar_barrier"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true)

SpawnGameObject("south_bar_barrier_2")
GetGameObject("south_bar_barrier_2"):AddCStaticMesh():AssignModel("south_bar_barrier_2")
GetGameObject("south_bar_barrier_2"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true)

SpawnGameObject("tavern_floor")
GetGameObject("tavern_floor"):AddCStaticMesh():AssignModel("tavern_floor")
GetGameObject("tavern_floor"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true)

SpawnGameObject("main_bar_bench")
GetGameObject("main_bar_bench"):AddCStaticMesh():AssignModel("main_bar_bench")
GetGameObject("main_bar_bench"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true)

SpawnGameObject("bar_floor_rod")
GetGameObject("bar_floor_rod"):AddCStaticMesh():AssignModel("bar_floor_rod")
GetGameObject("bar_floor_rod"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true)
