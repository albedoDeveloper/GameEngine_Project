
LoadModel("goblinModel", "goblin/goblin.fbx")

--spawn player
SpawnGameObject("goblin1")
GetGameObject("goblin1"):AddCStaticMesh("goblinModel"):AssignModel("goblinModel")
