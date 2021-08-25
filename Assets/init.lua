
LoadModel("goblinModel", "goblin/goblin.fbx")

SpawnGameObject("goblin1")
GetGameObject("goblin1"):AddCStaticMesh("goblinModel"):AssignModel("goblinModel")
GetGameObject("goblin1"):AddCAABBCollider()
