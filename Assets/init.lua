
LoadModel("goblinModel", "goblin/goblin.fbx")
LoadScript("rotate", "rotate.lua")

xpos = 0
zpos = 0
for i=1,2,1 do
    goblinName = "goblin " .. i
    goblinMesh = "goblinMesh " .. i
    SpawnGameObject(goblinName)
    GetGameObject(goblinName):AddCAABBCollider()
    GetGameObject(goblinName):AddCScript():AssignScript("rotate")
    GetGameObject(goblinName):GetTransform():SetPosition(xpos,0,zpos)
    GetGameObject(goblinName):GetTransform():RotateLocal(70, 0, 1, 0)

    GetGameObject(goblinName):AddCStaticMesh(goblinMesh):AssignModel("goblinModel")
    xpos = xpos + 2.0

    if (i % 10 == 0) then
        zpos = zpos + 1.0
        xpos = 0
    end

end
