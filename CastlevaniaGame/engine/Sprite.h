#pragma once
#ifndef __SPRITE_H__
#define __SPRITE_H__

//#include <d3d9.h>
//#include <d3dx9.h>
#include "../ThamSo.h"

class Sprite
{
protected:
	LPDIRECT3DTEXTURE9 _Image;
	LPD3DXSPRITE _SpriteHandler;

	int _Width;								// Sprite width
	int _Height;							// Sprite height
	int _Count;								// Number of sprites
	int _SpritePerRow;						// Number of sprites per row

public:
	// bien index, da bi di doi sang public
	int _Index;								// Current sprite index, [0,n-1]

	// ==== CÁC BIẾN STATIC ======
	static int cameraXLeft;
	static int cameraXRight;
	static int cameraX;
	static int cameraY;
	
	//================================

	Sprite::Sprite(LPD3DXSPRITE SpriteHandler, LPCSTR FilePath, int Width, int Height, int Count, int SpritePerRow);
	void Next(int start,int end);
	void Reset();

	// Render current sprite at location (X,Y) at the target surface
	void Render(int X, int Y);
	void Render(LPDIRECT3DSURFACE9 Target, int X, int Y);
	~Sprite();
};

#endif