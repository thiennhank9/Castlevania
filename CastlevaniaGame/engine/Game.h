#pragma once
#pragma warning
		////////////////////////////////////////////////////////
		// -Class này cài đặt các xử lý khi game chạy, gồm:
		//		+ Khai báo, cài đặt DirectX 
		//		+ Cài đặt DInput
		//		+ Đăng kí lớp cửa sổ, tạo Hwnd, các thuộc 
		//		tính màn hình,...
		//		+ Game Time
		////////////////////////////////////////////////////////

#ifndef _GAME_H_
#define _GAME_H_

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <dxerr.h>
#include <dsound.h>
#include <string>

using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#include "sound/dsutil.h"
#define KEY_DOWN(code) ( IsKeyDown(code) )

class Game
{
public:

	//Khởi tạo game
	Game() {}
	Game(HINSTANCE hInstance, LPCSTR Name, int IsFullscreen, int FrameRate);

	//Giải phóng game
	~Game();

	//Cửa sổ
	static LRESULT CALLBACK _WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//Các đối tượng directX
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddevice;
	LPDIRECT3DSURFACE9 backbuffer;
	D3DFORMAT _BackBufferFormat;

	//Đối tượng bàn phím
	LPDIRECTINPUT8 directinput;
	LPDIRECTINPUTDEVICE8 keyboard;

	//Trạng thái phím
	BYTE keystate[256];					

	//Dữ liệu sự kiện phím
	DIDEVICEOBJECTDATA _KeyEvents[1024];		

	//Đối tượng sound
	LPDIRECTSOUND8        g_pDS;
	LPDIRECTSOUNDBUFFER DSBuffer;

	//Thời gian giữa frame
	DWORD _DeltaTime;

	//30 frames/second
	int _FrameRate;								

	//Screen resolution
	int _IsFullScreen;		
	int _ScreenWidth;
	int _ScreenHeight;

	//Dùng đăng kí cửa sổ
	HINSTANCE _hInstance;	
	HWND _hWnd;				
	LPCSTR _Name;	

	//Tạo font, dùng hiện chữ
	ID3DXFont *font;

	//Rect of toolbar
	RECT recZone1;

	//Rect of main scenes
	RECT recZone2;

	//Status
	std::string statusZone1;
	std::string statusZone2;

	//Khởi tạo toàn bộ
	void Init();

	//Khởi tạo cửa sổ, directX, keyboard, sound, fonts
	void _InitWindow();
	void _InitDirectX();
	void _InitKeyboard();
	void _LoadSound();
	void _InitFont();

	//Khởi tạo sound
	bool initDirectSound(HWND hwnd);

	//Giải phóng sound
	void shutdownDirectSound(void);
	LPDIRECTSOUNDBUFFER LoadWaveToSoundBuffer(std::string wavFilename);

	//Play sound and loop
	void playSound(LPDIRECTSOUNDBUFFER whichBuffer);
	void playSoundLoop(LPDIRECTSOUNDBUFFER whichBuffer);

	//Dừng sound
	void stopSound(LPDIRECTSOUNDBUFFER whichBuffer);

	//Hàm chạy game
	void Run();
	
	//Nhận bàn phím
	void _ProcessKeyBoard();		
	int IsKeyDown(int KeyCode);		

	//Hàm ảo, các đối tượng kế thừa

	//Load resource
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);

	//Update và vẽ frame
	virtual void UpdateFrame(float _DeltaTime);
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float _DeltaTime);

	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};
#endif