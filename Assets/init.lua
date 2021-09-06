
LoadModel("tavern_glass_door_wall", "tavern_glass_door_wall/tavern_glass_door_wall.fbx")
LoadModel("tavern_glass_door_wall_long", "tavern_glass_door_wall_long/tavern_glass_door_wall_long.fbx")
LoadModel("graffiti_block", "graffiti_block/graffiti_block.fbx")
LoadModel("tavern_floor", "tavern_floor/tavern_floor.fbx")
LoadModel("south_bar_barrier", "south_bar_barrier/south_bar_barrier.fbx")
LoadModel("axis", "axis/axis.fbx")
LoadScript("rotate", "rotate.lua")

SpawnGameObject("tavern_glass_door_wall")
GetGameObject("tavern_glass_door_wall"):AddCAABBCollider()
GetGameObject("tavern_glass_door_wall"):AddCStaticMesh():AssignModel("tavern_glass_door_wall")

SpawnGameObject("tavern_glass_door_wall_long")
GetGameObject("tavern_glass_door_wall_long"):AddCAABBCollider()
GetGameObject("tavern_glass_door_wall_long"):GetTransform()
GetGameObject("tavern_glass_door_wall_long"):AddCStaticMesh():AssignModel("tavern_glass_door_wall_long")

SpawnGameObject("graffiti_block")
GetGameObject("graffiti_block"):AddCAABBCollider()
GetGameObject("graffiti_block"):AddCStaticMesh():AssignModel("graffiti_block")

SpawnGameObject("south_bar_barrier")
GetGameObject("south_bar_barrier"):AddCAABBCollider()
GetGameObject("south_bar_barrier"):AddCStaticMesh():AssignModel("south_bar_barrier")

SpawnGameObject("tavern_floor")
GetGameObject("tavern_floor"):AddCAABBCollider()
GetGameObject("tavern_floor"):AddCStaticMesh():AssignModel("tavern_floor")
