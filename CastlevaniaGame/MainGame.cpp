#include "MainGame.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "OLoader.h"

#define SIMON_SPEED 0.2f
#define GROUND 94
#define BACKGROUND_FILE "Resources\\map1_tiled.PNG"
#define VIEW_PORT_Y 448

MainGame::MainGame(HINSTANCE hInstance, LPCSTR Name, int IsFullScreen, int FrameRate):Game(hInstance, Name, IsFullScreen, FrameRate)
{
	//Just for test
	
	timeUI = 523;
	timer = 0;
	timeFlash = 0;
	curEnemy = 16;

	// create world
}

void MainGame::LoadResources(LPDIRECT3DDEVICE9 _d3ddevice)
{
	srand((unsigned)time(NULL));

	D3DXCreateSprite(_d3ddevice, &_SpriteHandler);
	
	 world = new World(_SpriteHandler, this);
	 world->Init();
	 
	 // background ---------------------
	 maps[0] = new TileMaps("Resources\\Maps\\map1_tiled.png", _SpriteHandler,64,104,14);
	 maps[0]->ReadMatrixFromFile("Resources\\Maps\\map1_matrix.txt", "\t");

	 maps[1] = new TileMaps("Resources\\Maps\\map2_tiled.png", _SpriteHandler, 64, 49, 9);
	 maps[1]->ReadMatrixFromFile("Resources\\Maps\\map2_matrix.txt", "\t");

	 TreeBrs[0] = new BackgroundQuadTree();
	 TreeBrs[0]->loadTreeFromFile("Resources\\Maps\\map1_quadtree.txt");

	 TreeBrs[1] = new BackgroundQuadTree();
	 TreeBrs[1]->loadTreeFromFile("Resources\\Maps\\map2_quadtree.txt");

	 ListTileBackgoundID = new int[5000];
	 size = 0;

	 // gameobject ----------------
	 oloaders[0] = new OLoader(1, _SpriteHandler, world);
	 oloaders[1] = new OLoader(2, _SpriteHandler, world);

	 lvl = 0;

	 NextLevel();

	 
	 // ---------------------------------------

	 //Sprite::cameraY = 448;

	//Hình dùng để render thanh máu, trái tim, khung chứa đồ trên thanh status 
	statusBar = new Sprite(_SpriteHandler, "Resources\\Sprites\\bar_health.bmp", 8, 16, 4, 4);
	statusboard = new Sprite(_SpriteHandler, "Resources\\Sprites\\blackboard.png", 520, 80, 1, 1);
	weaponSprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\bonus.bmp", 64, 64, 22, 6);
	bonusSprite = weaponSprite;
}

// --- MAIN UPDATE FUNCTION ---
void MainGame::UpdateFrame(float _DeltaTime)
{
	//cap nhat lai danh sach cac ID tile có nằm trong viewport
	size = 0;
	TreeBr->ListObjectInViewPort(ListTileBackgoundID, size);
	
	world->Update(_DeltaTime);
}


// --- UI FUNCTION ---
string MainGame::convertScoreFormat(int score)
{
	if (score < 10)
		return "00000" + std::to_string(score);
	else if (score < 100)
		return "0000" + std::to_string(score);
	else if (score < 1000)
		return "000" + std::to_string(score);
	else if (score < 10000)
		return "00" + std::to_string(score);
	else if (score < 100000)
		return "0" + std::to_string(score);
	else
		return std::to_string(score);
}
string MainGame::convertTimeFormat(int timeUI)
{
	if (timeUI < 10)
		return "000" + std::to_string(timeUI);
	else if (timeUI < 100)
		return "00" + std::to_string(timeUI);
	else if (timeUI < 1000)
		return "0" + std::to_string(timeUI);
	else
		return std::to_string(score);
}
string MainGame::convertTwoDigitFormat(int digit)
{
	if (digit < 10)
		return "0" + std::to_string(digit);
	else
		return std::to_string(digit);
}

void MainGame::LoadStatusBar(int curHealth, int curEnemy)
{
	statusboard->Render(160+Sprite::cameraX, 400 + Sprite::cameraY - _ScreenHeight);
	for (int i = 0; i < curHealth; i++)
	{
		statusBar->Next(0, 0);
		statusBar->Render(70 + i * 8 + Sprite::cameraX, 410 + Sprite::cameraY - _ScreenHeight);
	}
	for (int i = curHealth; i < 16; i++)
	{
		statusBar->Next(1, 1);
		statusBar->Render(70 + i * 8 + Sprite::cameraX, 410 + Sprite::cameraY - _ScreenHeight);
	}
	for (int i = 0; i < curEnemy; i++)
	{
		statusBar->Next(2, 2);
		statusBar->Render(70 + i * 8 + Sprite::cameraX, 396 + Sprite::cameraY - _ScreenHeight);
	}
	for (int i = curEnemy; i < 16; i++)
	{
		statusBar->Next(3, 3);
		statusBar->Render(70 + i * 8 + Sprite::cameraX, 396 + Sprite::cameraY - _ScreenHeight);
	}
	switch (world->Simon->subWeapon)
	{
	case KNIFE:
		weaponSprite->Next(0, 0);
		break;
	case AXE:
		weaponSprite->Next(1, 1);
		break;
	case BOOMERANG:
		weaponSprite->Next(2, 2);
		break;
	case HOLYWATER:
		weaponSprite->Next(3, 3);
		break;
	case GETWATCH:
		weaponSprite->Next(4, 4);
		break;
	default:
		weaponSprite->Next(-1, -1);
		break;
		
	}
	weaponSprite->Render(Sprite::cameraX + 245, 395 + Sprite::cameraY - 448);

	switch (world->Simon->weaponNumber)
	{
	case 2:
		bonusSprite->Next(11, 11);
		break;
	case 3:
		bonusSprite->Next(12, 12);
		break;
	default:
		bonusSprite->Next(-1, -1);
		break;
	}
	bonusSprite->Render(Sprite::cameraX + 370, 395 + Sprite::cameraY - 448);
}

// --- MAIN RENDER FUNCTION / between BeginScene & EndScene ---
void MainGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv)// , int t)
{
	
	
	//d3ddv->ColorFill(backbuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
	if (world->isFlash)
	{
		timer += 0.1f;
		timeFlash += 0.1f;
		if (timer >= 0.3f)
		{
			d3ddv->ColorFill(backbuffer, NULL, D3DCOLOR_XRGB(188, 188, 188));
			timer = 0;
		}
		if (timeFlash > 2.0f)
		{
			world->isFlash = false;
			timeFlash = 0;
		}

	}
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	map->LoadTiledMap(ListTileBackgoundID, size);

	world->Render();
	
	LoadStatusBar(world->Simon->health, curEnemy);
	_SpriteHandler->End();
	//------------Lúc simon ăn thánh giá -> sấm chớp--------
	
	//-------------------------------------
	//Mấy dòng chữ sẽ hiện lên Status bar
	statusZone1 = "SCORE - " + convertScoreFormat(world->Simon->score) + 
		"                  TIME "
		+ convertTimeFormat(timeUI) +
		"                 STAGE "
		"\n" +
		"\nPLAYER" +
		"\nENEMY";
	statusZone2 = convertTwoDigitFormat(world->Simon->heart)+ "\n"
		+ convertTwoDigitFormat(world->Simon->P);
	
}


void MainGame::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float _DeltaTime)		//Chạy khi nhấn giữ
{
	if (world->Simon->onStair <= 0) // truong hop chua leo cau thang
	{
		if (IsKeyDown(DIK_DOWN))
		{
			if (world->Simon->onStair == 0)
			{
				world->Simon->Down(-1);
				return;
			}

			//-- trang thai khong lien quan den cau thang
			if (IsKeyDown(DIK_LEFT))
			{
				world->Simon->isRight = false;
			}
			else if (IsKeyDown(DIK_RIGHT))
			{
				world->Simon->isRight = true;
			}
			world->Simon->Move(0, _DeltaTime);
			world->Simon->Down(1);
		}
		else // khong nhan phim DOWN
		{
			//truong hop nhan phim UP
			if (IsKeyDown(DIK_UP))
			{
				if (world->Simon->onStair == 0)
				{
					if (world->Simon->stairType == STAIR_UPLEFT || world->Simon->stairType == STAIR_UPRIGHT)
					{
						world->Simon->onStair = 1;
						world->Simon->isMoveToX = true;
						world->Simon->MovingOnStair(1);
						
						return;
					}
				}

			}

			//cac trang thai ngoai cau thang
			world->Simon->Down(0);

			if (IsKeyDown(DIK_LEFT))
			{
				world->Simon->Move(-1, _DeltaTime);
			}
			else if (IsKeyDown(DIK_RIGHT))
			{
				world->Simon->Move(1, _DeltaTime);
			}
			else
			{
				world->Simon->Move(0, _DeltaTime);
			}
		}
	}


	else // truong hop dang leo cau thang
	{
		if (IsKeyDown(DIK_UP) ||
			(IsKeyDown(DIK_RIGHT) && ((world->Simon->stairType == STAIR_UPRIGHT) || (world->Simon->stairType == STAIR_DOWNLEFT))) ||
			(IsKeyDown(DIK_LEFT) && ((world->Simon->stairType == STAIR_UPLEFT) || (world->Simon->stairType == STAIR_DOWNRIGHT))))
		{
			world->Simon->MovingOnStair(1);
		}
		if (IsKeyDown(DIK_DOWN) ||
			(IsKeyDown(DIK_RIGHT) && ((world->Simon->stairType == STAIR_UPLEFT) || (world->Simon->stairType == STAIR_DOWNRIGHT))) ||
			(IsKeyDown(DIK_LEFT) && ((world->Simon->stairType == STAIR_UPRIGHT) || (world->Simon->stairType == STAIR_DOWNLEFT))))
		{
			world->Simon->MovingOnStair(-1);
		}
		world->Simon->MovingOnStair(0);
	}

	// --------------- cheat
	if (IsKeyDown(DIK_Q))
	{
		world->Simon->velocity.y = 400;
	}
}

void MainGame::OnKeyDown(int KeyCode)					//Chỉ nhảy khi vừa nhấn, nhấn giữ không có tác dụng
{
	switch (KeyCode)
	{
	case DIK_LSHIFT:
	case DIK_SPACE:
		world->Simon->Jump();
		break;
	case DIK_LCONTROL:
		if (IsKeyDown(DIK_UP))
			world->Simon->ActivateWeapon();
		else
			world->Simon->Attack(0);
		break;
	case DIK_M:
		NextLevel();
		break;
	case DIK_H:
		world->Simon->RestoreHP();
		break;
	case DIK_J:
		world->Simon->IncreaseHeart();
		break;
	case DIK_K:
		world->Simon->ChangeSubWeapon();
		break;
	case DIK_O:
		world->Simon->SimonDeath();
	}
}

void MainGame::OnKeyUp(int KeyCode) {}

MainGame::~MainGame()
{
	
}

// hàm chuyển lvl
void MainGame::NextLevel()
{
	lvl++;
	if (lvl > 2)
		lvl = 1;

	// cập nhật các con trỏ background theo lvl
	TreeBr = TreeBrs[lvl-1];
	map = maps[lvl-1];

	// cập nhật các con trỏ object theo lvl
	oloader = oloaders[lvl - 1];
	oloader->Reload();
}