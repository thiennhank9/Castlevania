#include "MainGame.h"
#include <d3d9.h>
#include <d3dx9.h>


#define SIMON_SPEED 0.2f
#define GROUND 94
#define BACKGROUND_FILE "Resources\\map1_tiled.PNG"
#define VIEW_PORT_Y 448

MainGame::MainGame(HINSTANCE hInstance, LPCSTR Name, int IsFullScreen, int FrameRate):Game(hInstance, Name, IsFullScreen, FrameRate)
{
	//Just for test
	score = 5896;
	timeUI = 523;
	curHealth = 7;
	curEnemy = 16;
}

void MainGame::LoadResources(LPDIRECT3DDEVICE9 _d3ddevice)
{
	srand((unsigned)time(NULL));

	D3DXCreateSprite(_d3ddevice, &_SpriteHandler);
	_d3ddevice->CreateOffscreenPlainSurface(_ScreenWidth, _ScreenHeight, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &Background, NULL);
	 D3DXLoadSurfaceFromFile(Background, NULL, NULL, BACKGROUND_FILE, NULL, D3DX_DEFAULT, 0, NULL);
	
	//set background
	bg = new Sprite(_SpriteHandler, BACKGROUND_FILE, 5770, 896, 1, 1);
	world = new World(_SpriteHandler, this);
	world->Init();
	Sprite::cameraY = 464;

	map_1 = new TileMap();
	map_1->source = new Sprite(_SpriteHandler, BACKGROUND_FILE, 32, 32, 180, 18);
	map_2 = new TileMap();
	map_2->source = new Sprite(_SpriteHandler, "Resources\\map2_tiled.PNG", 32, 32, 66, 11);

	map_1->ReadMatrixFromFile("Resources\\map1.txt", &map_1_Matrix, "\t");
	map_2->ReadMatrixFromFile("Resources\\map2.txt", &map_2_Matrix, "\t");

	//Hình dùng để render thanh máu, trái tim, khung chứa đồ trên thanh status 
	statusBar = new Sprite(_SpriteHandler, "Resources\\Sprites\\bar_health.bmp", 8, 16, 4, 4);
	redEdge = new Sprite(_SpriteHandler, "Resources\\Sprites\\redEdge.bmp", 80, 59, 1, 1);
	heart = new Sprite(_SpriteHandler, "Resources\\Sprites\\heart.bmp", 16, 13, 1, 1);
}

// --- MAIN UPDATE FUNCTION ---
void MainGame::UpdateFrame(float _DeltaTime)
{
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
	redEdge->Render(250 + Sprite::cameraX, 396 + Sprite::cameraY - _ScreenHeight);
	heart->Render(300 + Sprite::cameraX, 410 + Sprite::cameraY - _ScreenHeight);

}

// --- MAIN RENDER FUNCTION / between BeginScene & EndScene ---
void MainGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv)// , int t)
{
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	map_1->LoadTiledMap(map_1_Matrix);
	world->Render();

	//LoadStatusBar(curHealth, curEnemy);
	LoadStatusBar(world->Simon->health, curEnemy);
	_SpriteHandler->End();
	//Mấy dòng chữ sẽ hiện lên Status bar
	statusZone1 = "SCORE - " + convertScoreFormat(score) + "                  TIME "
		+ convertTimeFormat(timeUI) +
		"                 STAGE "
		"\n" +
		"\nPLAYER" +
		"\nENEMY";

	//Số mạng của Simon
	statusZone2 = "P - " + convertTwoDigitFormat(world->Simon->heart);
}

void MainGame::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float _DeltaTime)		//Chạy khi nhấn giữ
{
	//Ngồi xuống
	if (IsKeyDown(DIK_DOWN))
	{
		//Vừa ngồi vừa sang trái
		if (IsKeyDown(DIK_LEFT))
		{
			world->Simon->isRight = false;
		}

		//Vừa ngồi vừa sang phải
		else if (IsKeyDown(DIK_RIGHT))
		{
			world->Simon->isRight = true;
		}
		world->Simon->Move(0, _DeltaTime);
		world->Simon->Down(1);
	}
	else
	{
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

void MainGame::OnKeyDown(int KeyCode)					//Chỉ nhảy khi vừa nhấn, nhấn giữ không có tác dụng
{
	switch (KeyCode)
	{
	case DIK_SPACE:
		world->Simon->Jump();
		break;
	case DIK_A:
		world->Simon->Injured();
		break;
	case DIK_LCONTROL:
		world->Simon->Attack();
		break;
	case DIK_R:
		world->Simon->RestoreHealth();
	}
}

//Nhả phím
void MainGame::OnKeyUp(int KeyCode) {}

MainGame::~MainGame()
{
	
}