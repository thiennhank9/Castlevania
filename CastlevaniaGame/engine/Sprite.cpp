#include "Sprite.h"

// --------- init static ------------------
int Sprite::cameraXLeft = 32;
int Sprite::cameraXRight = 992;
int Sprite::cameraX = 32;
int Sprite::cameraY = 0;
// ----------------------------------------

Sprite::Sprite(LPD3DXSPRITE SpriteHandler, LPCSTR FilePath, int Width, int Height, int Count, int SpritePerRow)
{
	_Image = NULL;
	_SpriteHandler = SpriteHandler;
	_Width = Width;
	_Height = Height;
	_Count = Count;
	_SpritePerRow = SpritePerRow;
	_Index = 0;

	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(FilePath, &info);

	LPDIRECT3DDEVICE9 d3ddevice;
	SpriteHandler->GetDevice(&d3ddevice);

	D3DXCreateTextureFromFileEx(
		d3ddevice,
		FilePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),				//Mau chi ra trong suot
		&info,
		NULL,
		&_Image);
}

void Sprite::Render(int X, int Y)
{
	this->Render(NULL, X, Y);
}

void Sprite::Render(LPDIRECT3DSURFACE9 Target, int X, int Y)
{
	// từ giờ viewpointX và viewpointY sẽ do các biến static quyết định, 
	//								vpx & vpy bỏ.

	RECT srect;

	srect.left = (_Index % _SpritePerRow)*(_Width);
	srect.top = (_Index / _SpritePerRow)*(_Height);
	srect.right = srect.left + _Width;
	srect.bottom = srect.top + _Height ;

	D3DXVECTOR3 position((float)X, (float)Y, 0);

	//
	// WORLD TO VIEWPORT TRANSFORM USING MATRIX
	//

	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -cameraX;
	mt._42 = cameraY;
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);

	D3DXVECTOR3 pos(vp_pos.x, vp_pos.y, 0);
	D3DXVECTOR3 center((float)_Width / 2, (float)_Height / 2, 0);
	_SpriteHandler->Draw(
		_Image,
		&srect,
		&center,
		&pos,
		D3DCOLOR_XRGB(255, 255, 255)
		);
}

void Sprite::Next(int start,int end)
{
	if (_Index < end && _Index >= start)
		//_Index = (_Index + _Count) % _Count + 1; //Lùi từ frame n về frame 1
		_Index++;
	else
		_Index = start;
}

void Sprite::Reset()
{
	_Index = 0;
}

Sprite::~Sprite()
{
	_Image->Release();
}
