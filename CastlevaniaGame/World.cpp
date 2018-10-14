// THIS WORLD IS SUCKED! DOOM THIS WORLD!

#include "World.h"
#include "MainGame.h"
#include <time.h>
#include "GroupObject.h"
#include "ColliderBlock.h"


World::World(LPD3DXSPRITE _SpriteHandler, MainGame *_MainGame)
{
	// ---  init core  ---
	spriteHandler = _SpriteHandler;
	castlevania = _MainGame;

	// ---  init static object  ---
	Simon = new Player(spriteHandler, this);
	
	//-----------
	// idea: collect the active objects from QUADTREE "active-Object with Collision"
	groupQuadtreeCollision = new GroupObject(this);
	// of course, these objects are live in the nodes that intersect with current viewport

	// idea: collect the active objects from SPECIAL (other object not lived in quadtree) "active-Object with Collision"
	groupSpecialCollision = new GroupObject(this);




	// just a holder for management
	groupItem = new GroupObject(this);
	// just a holder for management
	groupEffect = new GroupObject(this);

	groupProjectile = new GroupObject(this);
	
	// just a holder for management
	groupEnemy = new GroupObject(this);

	// root GameObject Node: for handle level
	rootGONode = NULL;// 
	// -----------
}


World::~World()
{
	delete Simon;
	delete whip;

	delete groupSpecialCollision;
	delete groupQuadtreeCollision;

}

// 
void World::Init()
{
	// ---  init changable object
	isFlash = false;

	
	// need to be clean, put into "GroupObject" ----
	ghoul = new Ghoul(spriteHandler, this);
	redBat = new RedBat(spriteHandler, this);
	blueBat = new BlueBat(spriteHandler, this);
	
	fish = new Fish(spriteHandler, this);
	vamBat = new VamBat(spriteHandler, this);
	// ---------------

	// should keep in here (or create a new better place to put in)
	boss = NULL;

	// damn rubishes of the Simon ##############
	whip = new Whip(spriteHandler, this);
	groupProjectile->AddObject(whip);

	knife[0] = new Knife(spriteHandler, this);
	knife[1] = new Knife(spriteHandler, this);
	knife[2] = new Knife(spriteHandler, this);
	groupProjectile->AddObject(knife[0]);
	groupProjectile->AddObject(knife[1]);
	groupProjectile->AddObject(knife[2]);

	boo[0] = new Boomerang(spriteHandler, this);
	boo[1] = new Boomerang(spriteHandler, this);
	boo[2] = new Boomerang(spriteHandler, this);
	groupProjectile->AddObject(boo[0]);
	groupProjectile->AddObject(boo[1]);
	groupProjectile->AddObject(boo[2]);

	axe[0] = new Axe(spriteHandler, this);
	axe[1] = new Axe(spriteHandler, this);
	axe[2] = new Axe(spriteHandler, this);
	groupProjectile->AddObject(axe[0]);
	groupProjectile->AddObject(axe[1]);
	groupProjectile->AddObject(axe[2]);

	holyFire[0] = new HolyFire(spriteHandler, this);
	holyFire[1] = new HolyFire(spriteHandler, this);
	holyFire[2] = new HolyFire(spriteHandler, this);
	groupProjectile->AddObject(holyFire[0]);
	groupProjectile->AddObject(holyFire[1]);
	groupProjectile->AddObject(holyFire[2]);

	holyWater[0] = new HolyWater(spriteHandler, this);
	holyWater[1] = new HolyWater(spriteHandler, this);
	holyWater[2] = new HolyWater(spriteHandler, this);
	groupProjectile->AddObject(holyWater[0]);
	groupProjectile->AddObject(holyWater[1]);
	groupProjectile->AddObject(holyWater[2]);
	// ##
}

// gọi ở đầu game_run
void World::Update(float _DeltaTime)
{

	// -- collecting all objects that can collide with the main player
	groupSpecialCollision->GetCollisionSpecial();
	groupQuadtreeCollision->GetCollisionQuadtree();
	// fortunately, these objects are appear in the screen (not all of them), so we can use this group for update() and render()
	// =========-------------------------
	Simon->Update(_DeltaTime);
	//whip->Update(_DeltaTime);
	//-----------
	//medusa->Update(_DeltaTime);
	//snake->Update(_DeltaTime);
	/*
	timer += _DeltaTime;
	if (timer >= 0.2f)
	{
		flash->Next(0, 1);
		timer = 0;
	}*/
	// lol, what are you doing here, fish?
	fish->Update(_DeltaTime);




	groupQuadtreeCollision->Update(_DeltaTime);
	groupSpecialCollision->Update(_DeltaTime);
	// ---------------
}

// gọi bên trong BeginScene() và EndScene();
void World::Render()
{
	fish->Render();
	
	groupQuadtreeCollision->Render();
	groupSpecialCollision->Render();

	Simon->Render();
}

// We don't need to use it now
void World::CheckActive(float _DeltaTime)
{
	/////////////////
	/*if (!medusa->isActive)
	{

		medusa->Init(800, 600);

		medusa->CheckActive();
	}

	if (medusa->isAttack)
	{
		if (!snake->isActive)
			snake->Init(medusa->position.x, medusa->position.y);

	}
	else
		snake->Destroy();

	if (!vamBat->isActive)
	{
		vamBat->Init(1000, 600);
		vamBat->CheckActive();
	}*/
	///////////////
	
	
}

void World::Destroy()
{

}
