
LoadModel("goblinModel", "goblin/goblin.fbx")


xpos = 0
zpos = 0
for i=1,5,1 do
    goblinName = "goblin " .. i
    goblinMesh = "goblinMesh " .. i
    SpawnGameObject(goblinName)
    GetGameObject(goblinName):GetTransform():SetPosition(xpos,0,zpos)
    GetGameObject(goblinName):AddCAABBCollider()
    GetGameObject(goblinName):AddCStaticMesh(goblinMesh):AssignModel("goblinModel")
    xpos = xpos + 0.5

    if (i % 10 == 0) then
        zpos = zpos + 0.5
        xpos = 0
    end

end
