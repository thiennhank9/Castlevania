#ifndef _PLAYER_H_
#define _PLAYER_H_

// Hướng leo cầu thang
#define STAIR_UPRIGHT 1
#define STAIR_UPLEFT 2
#define STAIR_DOWNRIGHT 3
#define STAIR_DOWNLEFT 4

#include "GameObject.h"

class Player :
	public GameObject
{
public:
	int tempGround;

	// key
	bool isRight;	//trang thai quay sang phai
	bool isJump;	//trang thai nhay
	bool downJump;	//trang thai nhay xuong
	bool isCrouch;	//trang thai ngoi
	bool isAttack;  //trang thai danh
	bool killingMoment; //trang thai vung roi
	bool isHitted;  //trạng thai bị thuong
	bool isShocked;  //trang thai shock
	bool isImmortal; //trang thai bat tu
	bool isChangeFrame;

	bool isStationary; // trạng thái đứng yên

	// stair direction key
	int onStair;

	//bool upKey; // = true khi nhấn giữ
	Sprite *spriteLeft;
	Sprite *spriteRight;

	int invincibleTimer;

	int weaponLevel;	// whip level
	int weaponPosY;		// vị trí cho sprite & attack
	int weaponNumber;	// số subweapon có thể ném liên tiếp

	int heart;			// số trái tim (số lượng đạn)
	int health;			// chừng nào mi chết?


	// constructor & destructor
	Player(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Player();


	// virtual function
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();

	// input function
	// Khi có input từ bàn phím => gọi các hàm này
	// nhấn giữ
	void Move(int moveKey, const float &_DeltaTime);// -1 <-    0      1 ->
	void Up(int upKey);
	void Down(int downKey);

	// nhấn 1 lần
	void Jump();
	void Attack();
	void Injured();
	void RestoreHealth();
	
};

#endif
