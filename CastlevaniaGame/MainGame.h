#pragma once
#ifndef _RECTANGLES_H_
#define _RECTANGLES_H_
#include "game.h"
#include "World.h"
#include "ThamSo.h"

class MainGame :public Game
{
public:
	MainGame() {}
	MainGame(HINSTANCE hInstance, LPCSTR Name, int IsFullScreen, int FrameRate);
	~MainGame();

	LPD3DXSPRITE _SpriteHandler;		//Dung truyen vao spritehandler cua class Sprite
	DWORD last_time;

	// ========== MAP ============

	//LPDIRECT3DSURFACE9 Background;
	//Sprite* bg;
	// background -----------
	//su dung TileMaps *_ by Le _*
	TileMaps *map;
	TileMaps *maps[2];
	//map <int, int > ListTileBackgoundID;

	int *ListTileBackgoundID;
	int size;

	//QuadTree Background
	BackgroundQuadTree *TreeBr;
	BackgroundQuadTree *TreeBrs[2];

	// game object ----------
	OLoader* oloader;
	OLoader* oloaders[2];


	// -----------

	// manage level
	int lvl;
	void NextLevel();
	// --------
	// ============---------------

	World *world;


	// UI
	int score;
	int timeUI;

	int curHealth;
	int curEnemy;

	float timer;
	float timeFlash;

	Sprite* statusBar;
	Sprite* statusboard;
	Sprite* weaponSprite;
	Sprite* bonusSprite;

	

protected:
	string convertScoreFormat(int score);
	string convertTimeFormat(int timeUI);
	string convertTwoDigitFormat(int digit);
	void LoadStatusBar(int curHealth, int curEnemy);
	//////////////////////////////////////////
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddevice);
	virtual void UpdateFrame(float _DeltaTime);
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddevice);// , int Delta);
	//////////////////////////////////////
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddevice, float _DeltaTime);
	
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

#endif