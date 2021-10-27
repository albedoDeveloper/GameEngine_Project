LoadModel("crate", "crate/crate.fbx")
LoadModel("crate_small", "crate_small/crate_small.fbx")
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
LoadModel("south_bar_wall_2", "south_bar_wall_2/south_bar_wall_2.fbx")
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
LoadModel("ball", "ball/ball.fbx")
LoadModel("table","table/table.fbx")
LoadModel("book", "book/book.fbx")
LoadModel("jukebox", "jukebox/jukebox.fbx")
LoadScript("rotate", "rotate.lua")
LoadScript("playerShoot", "playerShoot.lua")
LoadScript("girl1script", "girl1script.lua")
LoadScript("girl2script", "girl2script.lua")
LoadModel("agent_dance","ai_agent/dance.fbx")
--LoadModel("agent_walk","ai_agent/walk.fbx")

SpawnGameObject("fridge1"):SetStatic(true)
GetGameObject("fridge1"):AddCStaticMesh():AssignModel("fridge1")
GetGameObject("fridge1"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,0,true, 30)

SpawnGameObject("fridge2"):SetStatic(true)
GetGameObject("fridge2"):AddCStaticMesh():AssignModel("fridge2")
GetGameObject("fridge2"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,0,true, 30)

SpawnGameObject("beertap1"):SetStatic(true)
GetGameObject("beertap1"):AddCStaticMesh():AssignModel("beertap1")

SpawnGameObject("beertap2"):SetStatic(true)
GetGameObject("beertap2"):AddCStaticMesh():AssignModel("beertap2")

SpawnGameObject("spiked_door_toilet"):SetStatic(true)
GetGameObject("spiked_door_toilet"):AddCStaticMesh():AssignModel("spiked_door_toilet")

SpawnGameObject("table"):SetStatic(true)
GetGameObject("table"):AddCStaticMesh():AssignModel("table")
GetGameObject("table"):GetCStaticMesh():RemoveNormalMapping()
GetGameObject("table"):GetTransform():SetRelativePosition(8,0,-2.5)
GetGameObject("table"):GetTransform():Scale(0.015,0.015,0.015)
GetGameObject("table"):GetTransform():RotateLocalX(90)
--GetGameObject("table"):AddCCollider():AddConvexCollider()

-------------------------
SpawnGameObject("waitress"):SetStatic(true)
GetGameObject("waitress"):AddCStaticMesh():AssignModel("waitress")

GetGameObject("waitress"):AddCAffordanceManager():AddAffordance("OrderFood","agent_talking","OrderFood.wav")
GetGameObject("waitress"):GetCAffordanceManager():GetTransform():SetRelativePosition(5.034, 0, 5.252)
GetGameObject("waitress"):GetCAffordanceManager():AddEmotion("OrderFood","arousal",0.7)
GetGameObject("waitress"):GetCAffordanceManager():AddEmotion("OrderFood","valence", -0.4)


GetGameObject("waitress"):GetCAffordanceManager():AddAffordance("Argue","agent_loser","Argue.wav")
GetGameObject("waitress"):GetCAffordanceManager():GetTransform():SetRelativePosition(5.034, 0, 5.252)
GetGameObject("waitress"):GetCAffordanceManager():AddEmotion("Argue","arousal", 0.65)
GetGameObject("waitress"):GetCAffordanceManager():AddEmotion("Argue","valence", -0.7)
------------------------
------------------------
SpawnGameObject("pool-table"):SetStatic(true)
GetGameObject("pool-table"):AddCStaticMesh():AssignModel("pool-table")
GetGameObject("pool-table"):GetCStaticMesh():RemoveNormalMapping()
GetGameObject("pool-table"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,0,true, 30)
--GetGameObject("pool-table"):GetCCollider():CollideWith(2)

GetGameObject("pool-table"):AddCAffordanceManager():AddAffordance("Pool","agent_pool","Pool.wav")
GetGameObject("pool-table"):GetCAffordanceManager():GetTransform():SetRelativePosition(-6.5,0,0.3)
GetGameObject("pool-table"):GetCAffordanceManager():AddEmotion("Pool","arousal", -0.5)
GetGameObject("pool-table"):GetCAffordanceManager():AddEmotion("Pool","valence", 0.6)

GetGameObject("pool-table"):GetCAffordanceManager():AddAffordance("Texting","agent_mobile","Texting.wav")
GetGameObject("pool-table"):GetCAffordanceManager():AddEmotion("Texting","arousal", -0.1)
GetGameObject("pool-table"):GetCAffordanceManager():AddEmotion("Texting","valence", 0.5)
----------------------
----------------------
SpawnGameObject("barrel1"):SetStatic(true)
GetGameObject("barrel1"):AddCStaticMesh():AssignModel("barrel1")
GetGameObject("barrel1"):AddCCollider():AddConvexCollider()
--GetGameObject("barrel1"):GetTransform():SetRelativePosition(0, 0, -2.5)

GetGameObject("barrel1"):AddCAffordanceManager():AddAffordance("Drinking","agent_drinking","Drink.wav")
GetGameObject("barrel1"):GetCAffordanceManager():GetTransform():SetRelativePosition(-6.5,0,0.3)
GetGameObject("barrel1"):GetCAffordanceManager():AddEmotion("Drinking","arousal", 0.2)
GetGameObject("barrel1"):GetCAffordanceManager():AddEmotion("Drinking","valence", 0.3)

GetGameObject("barrel1"):GetCAffordanceManager():AddAffordance("LookForMoney","agent_pickup","LookForMoney.wav")
GetGameObject("barrel1"):GetCAffordanceManager():AddEmotion("LookForMoney","arousal", -0.4)
GetGameObject("barrel1"):GetCAffordanceManager():AddEmotion("LookForMoney","valence", 0.6)
-----------------------

----------------------
SpawnGameObject("barrel2"):SetStatic(true)
GetGameObject("barrel2"):AddCStaticMesh():AssignModel("barrel2")
GetGameObject("barrel2"):AddCCollider():AddConvexCollider()

GetGameObject("barrel2"):AddCAffordanceManager():AddAffordance("DanceAggressive","agent_dance","DanceAggressive.wav")
--GetGameObject("barrel2"):GetCAffordanceManager():GetTransform():SetRelativePosition(-6.5,0,0.3)
GetGameObject("barrel2"):GetCAffordanceManager():AddEmotion("DanceAggressive","arousal", 0.7)
GetGameObject("barrel2"):GetCAffordanceManager():AddEmotion("DanceAggressive","valence", -0.4)

GetGameObject("barrel2"):GetCAffordanceManager():AddAffordance("DanceRelax","agent_slowdance","DanceRelax.wav")
GetGameObject("barrel2"):GetCAffordanceManager():AddEmotion("DanceRelax","arousal", -0.4)
GetGameObject("barrel2"):GetCAffordanceManager():AddEmotion("DanceRelax","valence", 0.7)

----------------------

----------
SpawnGameObject("ai_agent_1"):SetStatic(false)
GetGameObject("ai_agent_1"):AddCStaticMesh():AssignModel("agent_dance")

GetGameObject("ai_agent_1"):AddCAnimator()
GetGameObject("ai_agent_1"):GetCAnimator():AddAnimation("ai_agent/dance.fbx", false, "agent_dance")
GetGameObject("ai_agent_1"):GetCAnimator():AddAnimation("ai_agent/drinking.fbx", false, "agent_drinking")
GetGameObject("ai_agent_1"):GetCAnimator():AddAnimation("ai_agent/walk.fbx", true, "agent_walk")
GetGameObject("ai_agent_1"):GetCAnimator():AddAnimation("ai_agent/loser.fbx", false, "agent_loser")
GetGameObject("ai_agent_1"):GetCAnimator():AddAnimation("ai_agent/pool.fbx", false, "agent_pool")
GetGameObject("ai_agent_1"):GetCAnimator():AddAnimation("ai_agent/slowdance.fbx", false, "agent_slowdance")
GetGameObject("ai_agent_1"):GetCAnimator():AddAnimation("ai_agent/mobile.fbx", false, "agent_mobile")
GetGameObject("ai_agent_1"):GetCAnimator():AddAnimation("ai_agent/pickup.fbx", false, "agent_pickup")
GetGameObject("ai_agent_1"):GetCAnimator():AddAnimation("ai_agent/talking.fbx", false, "agent_talking")

GetGameObject("ai_agent_1"):AddCSound():LoadSound("OrderFood.wav")
GetGameObject("ai_agent_1"):GetCSound():LoadSound("Argue.wav")
GetGameObject("ai_agent_1"):GetCSound():LoadSound("Pool.wav")
GetGameObject("ai_agent_1"):GetCSound():LoadSound("Drink.wav")
GetGameObject("ai_agent_1"):GetCSound():LoadSound("LookForMoney.wav")
GetGameObject("ai_agent_1"):GetCSound():LoadSound("Texting.wav")
GetGameObject("ai_agent_1"):GetCSound():LoadSound("DanceAggressive.wav")
GetGameObject("ai_agent_1"):GetCSound():LoadSound("DanceRelax.wav")

GetGameObject("ai_agent_1"):GetCSound():LoadSound("tired.wav")
GetGameObject("ai_agent_1"):GetCSound():LoadSound("bored.wav")
GetGameObject("ai_agent_1"):GetCSound():LoadSound("depressed.wav")
GetGameObject("ai_agent_1"):GetCSound():LoadSound("frustrated.wav")
GetGameObject("ai_agent_1"):GetCSound():LoadSound("angry.wav")
GetGameObject("ai_agent_1"):GetCSound():LoadSound("tense.wav")
GetGameObject("ai_agent_1"):GetCSound():LoadSound("excited.wav")
GetGameObject("ai_agent_1"):GetCSound():LoadSound("delighted.wav")
GetGameObject("ai_agent_1"):GetCSound():LoadSound("happy.wav")
GetGameObject("ai_agent_1"):GetCSound():LoadSound("content.wav")
GetGameObject("ai_agent_1"):GetCSound():LoadSound("relaxed.wav")
GetGameObject("ai_agent_1"):GetCSound():LoadSound("calm.wav")

GetGameObject("ai_agent_1"):GetTransform():Translate(2,0,1.4)
GetGameObject("ai_agent_1"):AddCAgent():AddEmotion("valence",0.7, 1.0, -0.002)
GetGameObject("ai_agent_1"):GetCAgent():AddEmotion("arousal",0.0, 1.0, 0.0)

GetGameObject("ai_agent_1"):GetCAgent():AddTrait("OrderFood", 0.2)
GetGameObject("ai_agent_1"):GetCAgent():AddTrait("Pool", 1.4)
--------------

----------
SpawnGameObject("ai_agent_2"):SetStatic(false)
GetGameObject("ai_agent_2"):AddCStaticMesh():AssignModel("agent_dance")
GetGameObject("ai_agent_2"):GetTransform():SetRelativePosition(-2, 0, 0)

GetGameObject("ai_agent_2"):AddCAnimator()
GetGameObject("ai_agent_2"):GetCAnimator():AddAnimation("ai_agent/dance.fbx", false, "agent_dance")
GetGameObject("ai_agent_2"):GetCAnimator():AddAnimation("ai_agent/drinking.fbx", false, "agent_drinking")
GetGameObject("ai_agent_2"):GetCAnimator():AddAnimation("ai_agent/walk.fbx", true, "agent_walk")
GetGameObject("ai_agent_2"):GetCAnimator():AddAnimation("ai_agent/loser.fbx", false, "agent_loser")
GetGameObject("ai_agent_2"):GetCAnimator():AddAnimation("ai_agent/pool.fbx", false, "agent_pool")
GetGameObject("ai_agent_2"):GetCAnimator():AddAnimation("ai_agent/slowdance.fbx", false, "agent_slowdance")
GetGameObject("ai_agent_2"):GetCAnimator():AddAnimation("ai_agent/mobile.fbx", false, "agent_mobile")
GetGameObject("ai_agent_2"):GetCAnimator():AddAnimation("ai_agent/pickup.fbx", false, "agent_pickup")
GetGameObject("ai_agent_2"):GetCAnimator():AddAnimation("ai_agent/talking.fbx", false, "agent_talking")

GetGameObject("ai_agent_2"):AddCSound():LoadSound("OrderFood.wav")
GetGameObject("ai_agent_2"):GetCSound():LoadSound("Argue.wav")
GetGameObject("ai_agent_2"):GetCSound():LoadSound("Pool.wav")
GetGameObject("ai_agent_2"):GetCSound():LoadSound("Drink.wav")
GetGameObject("ai_agent_2"):GetCSound():LoadSound("LookForMoney.wav")
GetGameObject("ai_agent_2"):GetCSound():LoadSound("Texting.wav")
GetGameObject("ai_agent_2"):GetCSound():LoadSound("DanceAggressive.wav")
GetGameObject("ai_agent_2"):GetCSound():LoadSound("DanceRelax.wav")

GetGameObject("ai_agent_2"):GetCSound():LoadSound("tired.wav")
GetGameObject("ai_agent_2"):GetCSound():LoadSound("bored.wav")
GetGameObject("ai_agent_2"):GetCSound():LoadSound("depressed.wav")
GetGameObject("ai_agent_2"):GetCSound():LoadSound("frustrated.wav")
GetGameObject("ai_agent_2"):GetCSound():LoadSound("angry.wav")
GetGameObject("ai_agent_2"):GetCSound():LoadSound("tense.wav")
GetGameObject("ai_agent_2"):GetCSound():LoadSound("excited.wav")
GetGameObject("ai_agent_2"):GetCSound():LoadSound("delighted.wav")
GetGameObject("ai_agent_2"):GetCSound():LoadSound("happy.wav")
GetGameObject("ai_agent_2"):GetCSound():LoadSound("content.wav")
GetGameObject("ai_agent_2"):GetCSound():LoadSound("relaxed.wav")
GetGameObject("ai_agent_2"):GetCSound():LoadSound("calm.wav")

GetGameObject("ai_agent_2"):GetTransform():Translate(2,0,1.4)
GetGameObject("ai_agent_2"):AddCAgent():AddEmotion("valence",0.1, 1.0, 0.002)
GetGameObject("ai_agent_2"):GetCAgent():AddEmotion("arousal",0.8, 1.0, 0.0)

GetGameObject("ai_agent_2"):GetCAgent():AddTrait("DanceAggressive",-0.5)
GetGameObject("ai_agent_2"):GetCAgent():AddTrait("DancePassive", 0.5)
--------------

----------
SpawnGameObject("ai_agent_3"):SetStatic(false)
GetGameObject("ai_agent_3"):AddCStaticMesh():AssignModel("agent_dance")
GetGameObject("ai_agent_3"):GetTransform():SetRelativePosition(2, 0, 0)

GetGameObject("ai_agent_3"):AddCAnimator()
GetGameObject("ai_agent_3"):GetCAnimator():AddAnimation("ai_agent/dance.fbx", false, "agent_dance")
GetGameObject("ai_agent_3"):GetCAnimator():AddAnimation("ai_agent/drinking.fbx", false, "agent_drinking")
GetGameObject("ai_agent_3"):GetCAnimator():AddAnimation("ai_agent/walk.fbx", true, "agent_walk")
GetGameObject("ai_agent_3"):GetCAnimator():AddAnimation("ai_agent/loser.fbx", false, "agent_loser")
GetGameObject("ai_agent_3"):GetCAnimator():AddAnimation("ai_agent/pool.fbx", false, "agent_pool")
GetGameObject("ai_agent_3"):GetCAnimator():AddAnimation("ai_agent/slowdance.fbx", false, "agent_slowdance")
GetGameObject("ai_agent_3"):GetCAnimator():AddAnimation("ai_agent/mobile.fbx", false, "agent_mobile")
GetGameObject("ai_agent_3"):GetCAnimator():AddAnimation("ai_agent/pickup.fbx", false, "agent_pickup")
GetGameObject("ai_agent_3"):GetCAnimator():AddAnimation("ai_agent/talking.fbx", false, "agent_talking")

GetGameObject("ai_agent_3"):AddCSound():LoadSound("OrderFood.wav")
GetGameObject("ai_agent_3"):GetCSound():LoadSound("Argue.wav")
GetGameObject("ai_agent_3"):GetCSound():LoadSound("Pool.wav")
GetGameObject("ai_agent_3"):GetCSound():LoadSound("Drink.wav")
GetGameObject("ai_agent_3"):GetCSound():LoadSound("LookForMoney.wav")
GetGameObject("ai_agent_3"):GetCSound():LoadSound("Texting.wav")
GetGameObject("ai_agent_3"):GetCSound():LoadSound("DanceAggressive.wav")
GetGameObject("ai_agent_3"):GetCSound():LoadSound("DanceRelax.wav")

GetGameObject("ai_agent_3"):GetCSound():LoadSound("tired.wav")
GetGameObject("ai_agent_3"):GetCSound():LoadSound("bored.wav")
GetGameObject("ai_agent_3"):GetCSound():LoadSound("depressed.wav")
GetGameObject("ai_agent_3"):GetCSound():LoadSound("frustrated.wav")
GetGameObject("ai_agent_3"):GetCSound():LoadSound("angry.wav")
GetGameObject("ai_agent_3"):GetCSound():LoadSound("tense.wav")
GetGameObject("ai_agent_3"):GetCSound():LoadSound("excited.wav")
GetGameObject("ai_agent_3"):GetCSound():LoadSound("delighted.wav")
GetGameObject("ai_agent_3"):GetCSound():LoadSound("happy.wav")
GetGameObject("ai_agent_3"):GetCSound():LoadSound("content.wav")
GetGameObject("ai_agent_3"):GetCSound():LoadSound("relaxed.wav")
GetGameObject("ai_agent_3"):GetCSound():LoadSound("calm.wav")

SpawnGameObject("toilet_block"):SetStatic(true)
GetGameObject("toilet_block"):AddCStaticMesh():AssignModel("toilet_block")
GetGameObject("toilet_block"):AddCCollider():AddConvexCollider()

SpawnGameObject("tavern_glass_door_wall_long_2"):SetStatic(true)
GetGameObject("tavern_glass_door_wall_long_2"):AddCStaticMesh():AssignModel("tavern_glass_door_wall_long_2")
GetGameObject("tavern_glass_door_wall_long_2"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,0,true, 30)
GetGameObject("tavern_glass_door_wall_long_2"):GetCStaticMesh():RemoveNormalMapping()

SpawnGameObject("tavern_glass_door_wall_long"):SetStatic(true)
GetGameObject("tavern_glass_door_wall_long"):AddCStaticMesh():AssignModel("tavern_glass_door_wall_long")
GetGameObject("tavern_glass_door_wall_long"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,0,true, 30)
GetGameObject("tavern_glass_door_wall_long"):GetCStaticMesh():RemoveNormalMapping()

SpawnGameObject("tavern_glass_door_wall"):SetStatic(true)
GetGameObject("tavern_glass_door_wall"):AddCStaticMesh():AssignModel("tavern_glass_door_wall")
GetGameObject("tavern_glass_door_wall"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,0,true, 30)
GetGameObject("tavern_glass_door_wall"):GetCStaticMesh():RemoveNormalMapping()

--GetGameObject("ai_agent_1"):GetCAgent():AddTrait("ToiletBreak",-1.0)
--GetGameObject("ai_agent_1"):GetCAgent():AddTrait("DrinkWater", 0.2)
--GetGameObject("ai_agent_1"):GetCAgent():AddTrait("OrderFood", -0.2)

SpawnGameObject("spiked_door_bar"):SetStatic(true)
GetGameObject("spiked_door_bar"):AddCStaticMesh():AssignModel("spiked_door_bar")
GetGameObject("spiked_door_bar"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,0,true,30)

SpawnGameObject("south_bar_wall"):SetStatic(true)
GetGameObject("south_bar_wall"):AddCStaticMesh():AssignModel("south_bar_wall")
GetGameObject("south_bar_wall"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,0,true,30)

SpawnGameObject("south_bar_wall_2"):SetStatic(true)
GetGameObject("south_bar_wall_2"):AddCStaticMesh():AssignModel("south_bar_wall_2")
GetGameObject("south_bar_wall_2"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,0,true,30)

SpawnGameObject("south_bar_barrier_2"):SetStatic(true)
GetGameObject("south_bar_barrier_2"):AddCStaticMesh():AssignModel("south_bar_barrier_2")
GetGameObject("south_bar_barrier_2"):AddCCollider():AddConvexCollider()

SpawnGameObject("south_bar_barrier"):SetStatic(true)
GetGameObject("south_bar_barrier"):AddCStaticMesh():AssignModel("south_bar_barrier")
GetGameObject("south_bar_barrier"):AddCCollider():AddConvexCollider()

SpawnGameObject("tavern_floor"):SetStatic(true)
GetGameObject("tavern_floor"):AddCStaticMesh():AssignModel("tavern_floor")
GetGameObject("tavern_floor"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,0,true,30)

SpawnGameObject("roof_interior"):SetStatic(true)
GetGameObject("roof_interior"):AddCStaticMesh():AssignModel("roof_interior")


SpawnGameObject("main_bar_bench"):SetStatic(true)
GetGameObject("main_bar_bench"):AddCStaticMesh():AssignModel("main_bar_bench")
GetGameObject("main_bar_bench"):AddCCollider():AddConvexCollider()

SpawnGameObject("graffiti_block"):SetStatic(true)
GetGameObject("graffiti_block"):AddCStaticMesh():AssignModel("graffiti_block")
GetGameObject("graffiti_block"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,0,true,30)

SpawnGameObject("behind_bar_block"):SetStatic(true)
GetGameObject("behind_bar_block"):AddCStaticMesh():AssignModel("behind_bar_block")
GetGameObject("behind_bar_block"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,0,true,30)
GetGameObject("behind_bar_block"):GetCStaticMesh():RemoveNormalMapping()

SpawnGameObject("bar_floor_rod"):SetStatic(true)
GetGameObject("bar_floor_rod"):AddCStaticMesh():AssignModel("bar_floor_rod")

SpawnGameObject("crate"):SetStatic(false)
GetGameObject("crate"):AddCStaticMesh():AssignModel("crate")
GetGameObject("crate"):GetTransform():SetRelativePosition(-8.744999885559082, 0.815000057220459, -1.4449999928474426)
GetGameObject("crate"):GetTransform():RotateLocalX(45)
GetGameObject("crate"):AddCScript():AssignScript("rotate")

SpawnGameObject("back_wall"):SetStatic(true)
GetGameObject("back_wall"):AddCStaticMesh():AssignModel("back_wall")
GetGameObject("back_wall"):AddCCollider():AddConvexCollider()
--GetGameObject("back_wall"):GetCStaticMesh():RemoveNormalMapping()

SpawnGameObject("lightAnchor"):SetStatic(false)
GetGameObject("lightAnchor"):GetTransform():SetRelativePosition(4.954999923706055,
1.9049999713897705,
5.275000095367432);
GetGameObject("lightAnchor"):AddCScript():AssignScript("rotate")

SpawnGameObject("sunanchor")
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
GetGameObject("light2"):GetCPointLight():AssignColour(0,0,0.7)
GetGameObject("light2"):GetCPointLight():AssignAmbientStrength(0.7)
GetGameObject("light2"):SetParentObject("lightAnchor")
GetGameObject("light2"):AddCStaticMesh():AssignModel("axis")
GetGameObject("light2"):GetTransform():Translate(0.3,0,0)


GetGameObject("ai_agent_3"):GetTransform():Translate(2,0,1.4)
GetGameObject("ai_agent_3"):AddCAgent():AddEmotion("valence",0.4, 1.0, 0.0)
GetGameObject("ai_agent_3"):GetCAgent():AddEmotion("arousal",0.6, 1.0, 0.0)

SpawnGameObject("NavMesh");
GetGameObject("NavMesh"):GetTransform():SetRelativePosition(1, 0, 0);
--GetGameObject("NavMesh"):AddCCollider():AddBoxCollider(0.25, 0.3, 0.25, 0 ,0, 0, false, 0, false, 31);
GetGameObject("NavMesh"):AddCNavMesh();

--------------

SpawnGameObject("jukebox"):SetStatic(true)
GetGameObject("jukebox"):AddCStaticMesh():AssignModel("jukebox")
GetGameObject("jukebox"):GetCStaticMesh():RemoveNormalMapping()
GetGameObject("jukebox"):GetTransform():SetRelativePosition(-1.5,0.9,-2.41)
GetGameObject("jukebox"):GetTransform():Scale(4,4,4)
GetGameObject("jukebox"):GetTransform():RotateLocalX(44)
GetGameObject("jukebox"):AddCSound():LoadSound("milkyway.wav")
GetGameObject("jukebox"):GetCSound():PlaySound("milkyway.wav",-1,true)
GetGameObject("jukebox"):AddCCollider():AddBoxCollider(0,0,0,0,0,0,true,0,true, 30)



SpawnGameObject("player");
GetGameObject("player"):GetTransform():SetRelativePosition(8.9, 1.4, -3.2);
GetGameObject("player"):GetTransform():RotateLocalY(-120);
GetGameObject("player"):AddCCollider():AddBoxCollider(0.25, 1.4, 0.25, 0 ,0, 0, false, 1, false, 31);
GetGameObject("player"):AddCCharacter():SetPlayerControlled(true);
GetGameObject("player"):AddCCameraComponent():SetAsCurrentCamera();
GetGameObject("player"):GetCCamera():GetTransform():Translate(0,0.5,0)

SpawnGameObject("endscreen"):SetActive(false)
GetGameObject("endscreen"):AddCStaticMesh():AssignModel("endscreen")
GetGameObject("endscreen"):GetCStaticMesh():AssignShader("unlit")
GetGameObject("endscreen"):GetTransform():SetParent(
	GetGameObject("player"):GetCCamera():GetTransform()
)
GetGameObject("endscreen"):GetTransform():Translate(0,0,-0.2)
GetGameObject("endscreen"):GetTransform():Scale(5,5,5)
