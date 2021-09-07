
LoadModel("tavern_glass_door_wall", "tavern_glass_door_wall/tavern_glass_door_wall.fbx")
LoadModel("tavern_glass_door_wall_long", "tavern_glass_door_wall_long/tavern_glass_door_wall_long.fbx")
LoadModel("graffiti_block", "graffiti_block/graffiti_block.fbx")
LoadModel("tavern_floor", "tavern_floor/tavern_floor.fbx")
LoadModel("south_bar_barrier", "south_bar_barrier/south_bar_barrier.fbx")
LoadModel("main_bar_bench", "main_bar_bench/main_bar_bench.fbx")
LoadModel("bar_floor_rod", "bar_floor_rod/bar_floor_rod.fbx")
LoadModel("axis", "axis/axis.fbx")
LoadModel("goblin", "goblin/goblin.fbx")

LoadScript("rotate", "rotate.lua")

SpawnGameObject("goblin1")
GetGameObject("goblin1"):AddCStaticMesh():AssignModel("goblin")
GetGameObject("goblin1"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true)

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

SpawnGameObject("tavern_floor")
GetGameObject("tavern_floor"):AddCStaticMesh():AssignModel("tavern_floor")
GetGameObject("tavern_floor"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true)

SpawnGameObject("main_bar_bench")
GetGameObject("main_bar_bench"):AddCStaticMesh():AssignModel("main_bar_bench")
GetGameObject("main_bar_bench"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true)

SpawnGameObject("bar_floor_rod")
GetGameObject("bar_floor_rod"):AddCStaticMesh():AssignModel("bar_floor_rod")
GetGameObject("bar_floor_rod"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true)
