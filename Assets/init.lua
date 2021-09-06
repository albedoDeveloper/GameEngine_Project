
LoadModel("goblinModel", "goblin/goblin.fbx")
LoadScript("rotate", "rotate.lua")

xpos = 0
for i=1,2,1 do
    goblinName = "goblin " .. i
    SpawnGameObject(goblinName)
    GetGameObject(goblinName):AddCStaticMesh():AssignModel("goblinModel")

    
   -- GetGameObject(goblinName):AddCCollider():AddConcaveCollider()
    GetGameObject(goblinName):AddCCollider():AddBoxCollider(1,1,1,0,-0.7,0,true)
    GetGameObject(goblinName):GetTransform():SetPosition(xpos,0,0)
    

   --GetGameObject(goblinName):GetTransform():RotateLocal(140,1,0, 1)

    xpos = xpos + 2

    if (i % 10 == 0) then
        xpos = 0
    end

end
        

GetGameObject("goblin 1"):AddCScript():AssignScript("rotate")
GetGameObject("goblin 2"):SetParentObject("goblin 1")
