LoadModel("crate", "crate/crate.fbx")
LoadModel("tavern_floor", "tavern_floor/tavern_floor.fbx")
LoadModel("axis", "axis/axis.fbx")
LoadModel("behind_bar_block", "behind_bar_block/behind_bar_block.fbx")
LoadModel("back_wall", "back_wall/back_wall.fbx")
LoadModel("bar_floor_rod", "bar_floor_rod/bar_floor_rod.fbx")
LoadModel("barrel1", "barrel1/barrel1.fbx")
LoadModel("barrel2", "barrel2/barrel2.fbx")
LoadModel("graffiti_block", "graffiti_block/graffiti_block.fbx")
LoadModel("main_bar_bench", "main_bar_bench/main_bar_bench.fbx")
LoadModel("pool-table", "pool-table/pool-table.fbx")
LoadModel("roof_interior", "roof_interior/roof_interior.fbx")
LoadModel("south_bar_barrier", "south_bar_barrier/south_bar_barrier.fbx")
LoadModel("south_bar_barrier_2", "south_bar_barrier_2/south_bar_barrier_2.fbx")
LoadModel("south_bar_wall", "south_bar_wall/south_bar_wall.fbx")
LoadModel("spiked_door_bar", "spiked_door_bar/spiked_door_bar.fbx")
LoadModel("spiked_door_toilet", "spiked_door_toilet/spiked_door_toilet.fbx")
LoadModel("tavern_glass_door_wall", "tavern_glass_door_wall/tavern_glass_door_wall.fbx")
LoadModel("tavern_glass_door_wall_long", "tavern_glass_door_wall_long/tavern_glass_door_wall_long.fbx")
LoadModel("tavern_glass_door_wall_long_2", "tavern_glass_door_wall_long_2/tavern_glass_door_wall_long_2.fbx")
LoadModel("toilet_block", "toilet_block/toilet_block.fbx")
LoadModel("waitress", "waitress/waitress.fbx")
LoadModel("endscreen", "endscreen/endscreen.fbx")
LoadModel("sheika", "sheika/sheika.fbx")
LoadModel("beertap1", "beertap1/beertap1.fbx")
LoadModel("beertap2", "beertap2/beertap2.fbx")
LoadModel("fridge1", "fridge1/fridge1.fbx")
LoadModel("fridge2", "fridge2/fridge2.fbx")
LoadModel("basic_girl","basic_girl/girlboxingfixed.fbx")
LoadModel("Breathing Idle","basic_girl/Breathing Idle.fbx")
LoadModel("girlTalking","basic_girl/girlTalking.fbx")
LoadModel("girlDying","basic_girl/girlDying.fbx")
LoadScript("rotate", "rotate.lua")
LoadScript("girl1script", "girl1script.lua")
LoadScript("girl2script", "girl2script.lua")

SpawnGameObject("fridge1"):SetStatic(true)
GetGameObject("fridge1"):AddCStaticMesh():AssignModel("fridge1")
GetGameObject("fridge1"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("fridge1"):GetCCollider():CollideWith(2)

SpawnGameObject("fridge2"):SetStatic(true)
GetGameObject("fridge2"):AddCStaticMesh():AssignModel("fridge2")
GetGameObject("fridge2"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("fridge2"):GetCCollider():CollideWith(2)

SpawnGameObject("beertap1"):SetStatic(true)
GetGameObject("beertap1"):AddCStaticMesh():AssignModel("beertap1")

SpawnGameObject("beertap2"):SetStatic(true)
GetGameObject("beertap2"):AddCStaticMesh():AssignModel("beertap2")

SpawnGameObject("spiked_door_toilet"):SetStatic(true)
GetGameObject("spiked_door_toilet"):AddCStaticMesh():AssignModel("spiked_door_toilet")

SpawnGameObject("waitress"):SetStatic(true)
GetGameObject("waitress"):AddCStaticMesh():AssignModel("waitress")

SpawnGameObject("toilet_block"):SetStatic(true)
GetGameObject("toilet_block"):AddCStaticMesh():AssignModel("toilet_block")
GetGameObject("toilet_block"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("toilet_block"):GetCCollider():CollideWith(2)

SpawnGameObject("tavern_glass_door_wall_long_2"):SetStatic(true)
GetGameObject("tavern_glass_door_wall_long_2"):AddCStaticMesh():AssignModel("tavern_glass_door_wall_long_2")
GetGameObject("tavern_glass_door_wall_long_2"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("tavern_glass_door_wall_long_2"):GetCCollider():CollideWith(2)

SpawnGameObject("tavern_glass_door_wall_long"):SetStatic(true)
GetGameObject("tavern_glass_door_wall_long"):AddCStaticMesh():AssignModel("tavern_glass_door_wall_long")
GetGameObject("tavern_glass_door_wall_long"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("tavern_glass_door_wall_long"):GetCCollider():CollideWith(2)

SpawnGameObject("tavern_glass_door_wall"):SetStatic(true)
GetGameObject("tavern_glass_door_wall"):AddCStaticMesh():AssignModel("tavern_glass_door_wall")
GetGameObject("tavern_glass_door_wall"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("tavern_glass_door_wall"):GetCCollider():CollideWith(2)

SpawnGameObject("basic_girl"):SetStatic(false)
GetGameObject("basic_girl"):AddCStaticMesh():AssignModel("basic_girl")
GetGameObject("basic_girl"):AddCAnimator()
GetGameObject("basic_girl"):GetCAnimator():AddAnimation("basic_girl/girlboxingfixed.fbx",false, "basic_girl")
GetGameObject("basic_girl"):GetCAnimator():AddAnimation("basic_girl/Breathing Idle.fbx", true, "Breathing Idle")
GetGameObject("basic_girl"):GetCAnimator():AddAnimation("basic_girl/girlTalking.fbx", false, "girlTalking")
GetGameObject("basic_girl"):AddCSound():LoadSound("girlTextSpeechOne.wav")
GetGameObject("basic_girl"):GetCSound():LoadSound("girlTextSpeechThree.wav")
GetGameObject("basic_girl"):AddCScript():AssignScript("girl1script")

SpawnGameObject("basic_girl2"):SetStatic(false)
GetGameObject("basic_girl2"):AddCStaticMesh():AssignModel("basic_girl")
GetGameObject("basic_girl2"):AddCAnimator()
GetGameObject("basic_girl2"):GetCAnimator():AddAnimation("basic_girl/girlDying.fbx", false, "girlDying")
GetGameObject("basic_girl2"):GetCAnimator():AddAnimation("basic_girl/Breathing Idle.fbx", true, "Breathing Idle")
GetGameObject("basic_girl2"):GetCAnimator():AddAnimation("basic_girl/girlTalking.fbx", false, "girlTalking")
GetGameObject("basic_girl2"):AddCSound():LoadSound("girlTextSpeechTwo.wav")
GetGameObject("basic_girl2"):AddCScript():AssignScript("girl2script")
GetGameObject("basic_girl2"):GetTransform():RotateLocalY(180)
GetGameObject("basic_girl2"):GetTransform():Translate(0,0,1.4)

SpawnGameObject("spiked_door_bar"):SetStatic(true)
GetGameObject("spiked_door_bar"):AddCStaticMesh():AssignModel("spiked_door_bar")
GetGameObject("spiked_door_bar"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("spiked_door_bar"):GetCCollider():CollideWith(2)

SpawnGameObject("south_bar_wall"):SetStatic(true)
GetGameObject("south_bar_wall"):AddCStaticMesh():AssignModel("south_bar_wall")

SpawnGameObject("south_bar_barrier_2"):SetStatic(true)
GetGameObject("south_bar_barrier_2"):AddCStaticMesh():AssignModel("south_bar_barrier_2")
GetGameObject("south_bar_barrier_2"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("south_bar_barrier_2"):GetCCollider():CollideWith(2)

SpawnGameObject("south_bar_barrier"):SetStatic(true)
GetGameObject("south_bar_barrier"):AddCStaticMesh():AssignModel("south_bar_barrier")
GetGameObject("south_bar_barrier"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("south_bar_barrier"):GetCCollider():CollideWith(2)

SpawnGameObject("tavern_floor"):SetStatic(true)
GetGameObject("tavern_floor"):AddCStaticMesh():AssignModel("tavern_floor")
GetGameObject("tavern_floor"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("tavern_floor"):GetCCollider():CollideWith(2)

SpawnGameObject("roof_interior"):SetStatic(true)
GetGameObject("roof_interior"):AddCStaticMesh():AssignModel("roof_interior")

SpawnGameObject("pool-table"):SetStatic(true)
GetGameObject("pool-table"):AddCStaticMesh():AssignModel("pool-table")
GetGameObject("pool-table"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("pool-table"):GetCCollider():CollideWith(2)

SpawnGameObject("main_bar_bench"):SetStatic(true)
GetGameObject("main_bar_bench"):AddCStaticMesh():AssignModel("main_bar_bench")
GetGameObject("main_bar_bench"):AddCCollider():AddConcaveCollider(1)
GetGameObject("main_bar_bench"):GetCCollider():CollideWith(2)

SpawnGameObject("graffiti_block"):SetStatic(true)
GetGameObject("graffiti_block"):AddCStaticMesh():AssignModel("graffiti_block")
GetGameObject("graffiti_block"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("graffiti_block"):GetCCollider():CollideWith(2)

SpawnGameObject("behind_bar_block"):SetStatic(true)
GetGameObject("behind_bar_block"):AddCStaticMesh():AssignModel("behind_bar_block")
GetGameObject("behind_bar_block"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("behind_bar_block"):GetCCollider():CollideWith(2)

SpawnGameObject("bar_floor_rod"):SetStatic(true)
GetGameObject("bar_floor_rod"):AddCStaticMesh():AssignModel("bar_floor_rod")

SpawnGameObject("barrel1"):SetStatic(true)
GetGameObject("barrel1"):AddCStaticMesh():AssignModel("barrel1")
GetGameObject("barrel1"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("barrel1"):GetCCollider():CollideWith(2)

SpawnGameObject("barrel2"):SetStatic(true)
GetGameObject("barrel2"):AddCStaticMesh():AssignModel("barrel2")
GetGameObject("barrel2"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("barrel2"):GetCCollider():CollideWith(2)

SpawnGameObject("crate"):SetStatic(false)
GetGameObject("crate"):AddCStaticMesh():AssignModel("crate")
GetGameObject("crate"):GetTransform():SetRelativePosition(-7.744999885559082, 1.315000057220459, -0.4449999928474426)
GetGameObject("crate"):GetTransform():RotateLocalX(45)
GetGameObject("crate"):AddCScript():AssignScript("rotate")

SpawnGameObject("back_wall"):SetStatic(true)
GetGameObject("back_wall"):AddCStaticMesh():AssignModel("back_wall")
GetGameObject("back_wall"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,1)
GetGameObject("back_wall"):GetCCollider():CollideWith(2)

SpawnGameObject("lightAnchor"):SetStatic(false)
GetGameObject("lightAnchor"):GetTransform():SetRelativePosition(4.954999923706055,
1.9049999713897705,
5.275000095367432);
GetGameObject("lightAnchor"):AddCScript():AssignScript("rotate")

SpawnGameObject("sunanchor")
--GetGameObject("sunanchor"):AddCScript():AssignScript("rotate")
GetGameObject("sunanchor"):AddCStaticMesh():AssignModel("axis")

--SpawnGameObject("sun"):SetStatic(false)
--GetGameObject("sun"):GetTransform():SetRelativePosition(0,10,10)
--GetGameObject("sun"):GetTransform():RotateLocalX(45)
--GetGameObject("sun"):GetTransform():RotateLocalY(10)
--GetGameObject("sun"):AddCDirectionalLight()
--GetGameObject("sun"):GetCDirectionalLight():AssignColour(0.5,0.5,0.5)
--GetGameObject("sun"):AddCStaticMesh():AssignModel("axis")
--GetGameObject("sun"):SetParentObject("sunanchor")


SpawnGameObject("light1"):SetStatic(false)
GetGameObject("light1"):AddCPointLight()
GetGameObject("light1"):GetCPointLight():AssignColour(0.8,0.8,0.8)
GetGameObject("light1"):GetCPointLight():AssignAmbientStrength(0.3)
GetGameObject("light1"):GetTransform():SetRelativePosition(-8.354999542236328,
2.6700000762939453,
1.0);
GetGameObject("light1"):AddCStaticMesh():AssignModel("axis")

SpawnGameObject("light2"):SetStatic(false)
GetGameObject("light2"):AddCPointLight()
GetGameObject("light2"):GetCPointLight():AssignColour(0.1,0.1,1)
GetGameObject("light2"):GetCPointLight():AssignAmbientStrength(0.6)
GetGameObject("light2"):SetParentObject("lightAnchor")
GetGameObject("light2"):AddCStaticMesh():AssignModel("axis")
GetGameObject("light2"):GetTransform():Translate(0.3,0,0)


SpawnGameObject("player");
GetGameObject("player"):GetTransform():SetRelativePosition(0, 2, 0);
GetGameObject("player"):AddCCollider():AddBoxCollider(0.25, 1.4, 0.25, 0 ,0, 0, false, 2, false);
GetGameObject("player"):GetCCollider():CollideWith(1);
GetGameObject("player"):AddCCharacter():SetPlayerControlled(true);
GetGameObject("player"):AddCCameraComponent():SetAsCurrentCamera();
GetGameObject("player"):GetCCamera():GetTransform():Translate(0,0.5,0);

SpawnGameObject("endscreen"):SetActive(false)
GetGameObject("endscreen"):AddCStaticMesh():AssignModel("endscreen")
GetGameObject("endscreen"):GetCStaticMesh():AssignShader("unlit")
GetGameObject("endscreen"):GetTransform():SetParent(
	GetGameObject("player"):GetCCamera():GetTransform()
)
GetGameObject("endscreen"):GetTransform():Translate(0,0,-0.2)
GetGameObject("endscreen"):GetTransform():Scale(5,5,5)
