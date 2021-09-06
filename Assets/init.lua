
LoadModel("tavern_glass_door_wall", "tavern_glass_door_wall/tavern_glass_door_wall.fbx")
LoadModel("tavern_glass_door_wall_long", "tavern_glass_door_wall_long/tavern_glass_door_wall_long.fbx")
LoadModel("axis", "axis/axis.fbx")
LoadScript("rotate", "rotate.lua")

SpawnGameObject("axis")
GetGameObject("axis"):AddCStaticMesh():AssignModel("axis")

SpawnGameObject("tavern_glass_door_wall")
GetGameObject("tavern_glass_door_wall"):AddCAABBCollider()
GetGameObject("tavern_glass_door_wall"):GetTransform()
GetGameObject("tavern_glass_door_wall"):AddCStaticMesh():AssignModel("tavern_glass_door_wall")

SpawnGameObject("tavern_glass_door_wall_long")
GetGameObject("tavern_glass_door_wall_long"):AddCAABBCollider()
GetGameObject("tavern_glass_door_wall_long"):GetTransform()
GetGameObject("tavern_glass_door_wall_long"):AddCStaticMesh():AssignModel("tavern_glass_door_wall_long")
