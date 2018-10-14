#include "Player.h"
#include "..\World.h"

// === CONSTRUCTOR === DESTRUCTOR ===
Player::Player(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = PLAYER_TYPE;
	collider = new Collider(objectType);

	sizeWidth = 64;
	sizeHeight = 64;

	isRight = true;
	isJump = false;
	downJump = false;
	isCrouch = false;
	isAttack = false;
	isHitted = false;
	isImmortal = false;
	killingMoment = false;
	isShocked = false;
	isChangeFrame = false;

	onStair = 0;

	//upKey = false;
	
	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\simon_left.bmp", sizeWidth, sizeHeight, 27, 6);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\simon_right.bmp", sizeWidth, sizeHeight, 27, 6);
	sprite = spriteRight;

	// mấy cái dưới hơi thừa, để cho toàn vẹn
	invincibleTimer = 0;

	weaponLevel = 1;
	weaponPosY = -2;// animate weapon at position.y - 2
	weaponNumber = 1;

	heart = 5;
	health = 16;
	position.y = 94;
}


Player::~Player()
{
	if (spriteLeft != NULL)
	{
		delete spriteLeft;
	}
	if (spriteRight != NULL)
	{
		delete spriteRight;
	}
}

// ===== VIRTUAL =====
void Player::Init(int _X, int _Y)
{
	// testing only
	tempGround = 94;

	// main init
	isActive = true;
	isRight = true;
	isImmortal = false;
	isJump = false;
	downJump = false;
	isCrouch = false;
	isAttack = false;
	isStationary = true;
	isChangeFrame = false;
	killingMoment = false;
	onStair = 0;
	//upKey = false;
	

	invincibleTimer = 0;

	position.x = _X;
	position.y = _Y;

	weaponLevel = 1;
	weaponPosY = -2;
	weaponNumber = 1;

	heart = 5;
	health = 16;
}

// ---=== THE MAIN PROCESSING ===---
void Player::Update(const float &_DeltaTime)
{
	//Update condition Simon collide with gateway and change the stage
	float entryTime = this->sweptAABB(manager->castleDoor, _DeltaTime);

	if (entryTime >= 0 && entryTime < _DeltaTime)
	{
		// giả sử ta không biết "castleDoor" này là thằng nào
		if ((manager->castleDoor->objectType) == ZONE_TYPE)
		{
			manager->castleDoor->Collision(this, _DeltaTime);
		}
	}

	
	if (isImmortal)
	{
		timerSprite += _DeltaTime;
		if (timerSprite > IMMORTAL_TIME)
		{
			isImmortal = false;
			timerSprite = 0;
		}
	}

	if (isHitted)
	{
		isAttack = false;
	}

	if (isAttack)
	{
		if (position.y < tempGround)
			position.y = tempGround;
		timerSprite += _DeltaTime;
		//truong hop ngoi danh
		if (isCrouch)
		{
			if (timerSprite >= ANIM_TIME)
			{
				//timerSprite -= ANIM_TIME;
				timerSprite = 0;
				sprite->Next(14, 17);
				if (sprite->_Index == 16)
					killingMoment = true;
				else
					killingMoment = false;
			}
			if (sprite->_Index == 17)
			{
				isAttack = false;
				sprite->_Index = 4;
			}
		}

		else // truong hop dung danh
		{
			if (timerSprite >= ANIM_TIME)
			{
				//timerSprite -= ANIM_TIME;
				timerSprite = 0;
				sprite->Next(11, 14);
				if (sprite->_Index == 13)
					killingMoment = true;
				else
					killingMoment = false;
			}
			if (sprite->_Index == 14)
			{
				isAttack = false;
				sprite->_Index = 0;
			}
		}
		if (isJump)
		{
			position.x += (velocity.x * _DeltaTime);
		}
	}
	else
		position.x += (velocity.x * _DeltaTime);


	velocity.y += -(1000 * _DeltaTime);
	position.y += (velocity.y * _DeltaTime);
	if (isJump)
	{
		if (velocity.y > 0)
		{
			//sprite->Next(4, 4);
		}
		else if (downJump)
		{
			downJump = false;

			// this line break the SweptAABB rule, but it made the game look like original
			position.y -= 10;
			if(!isAttack)
			{
				sprite->Next(0, 0);
				collider->top = 28;
			}
				
		}
	}

	if (position.y < tempGround)
	{
		position.y = tempGround;
		isJump = false;
		if (isHitted)
		{
			isHitted = false;
			isImmortal = true;
			if(!isAttack)
				sprite->_Index = 0;
			timerSprite = 0;
		}

		velocity.y = 0;
	}



	////////// update camera 
	Sprite::cameraX = position.x - 256;
	//nếu cạnh của camera bé hơn giới hạn trái
	if (Sprite::cameraX < Sprite::cameraXLeft)
	{
		//Cho cạnh camera chính là giới hạn trái 
		Sprite::cameraX = Sprite::cameraXLeft;
	}
	else if (Sprite::cameraX > Sprite::cameraXRight)
	{
		Sprite::cameraX = Sprite::cameraXRight;
	}
}

void Player::Render()
{
	sprite->Render(position.x, position.y);
}

void Player::Destroy() {}

void Player::Collision() {}

void Player::Move(int moveKey, const float &_DeltaTime)

{
	if (isJump)
		return;
	if (isAttack)
		return;
	if (isHitted)
		return;

	if (onStair == 0)
	{
		switch (moveKey)
		{
		case -1:
			velocity.x = -70;
			isRight = false;
			sprite = spriteLeft;
			break;
		case 1:
			velocity.x = 70;
			isRight = true;
			sprite = spriteRight;
			break;
		default:
			velocity.x = 0;
			sprite->Next(0, 0);
			break;
		}

		if (velocity.x != 0)
		{
			timerSprite += _DeltaTime;
			if (timerSprite > ANIM_TIME)
			{
				timerSprite -= ANIM_TIME;
				sprite->Next(0, 3);
			}
		}

	}
	
}

void Player::Up(int upKey)
{

}

void Player::Down(int downKey)
{
	if (onStair)
	{
		return;
	}
	if (isJump)
	{
		return;
	}
	if (isAttack)
	{
		return;
	}
	if (isHitted)
	{
		return;
	}

	if (downKey == 0)
	{
		isCrouch = false;
		collider->top = 28;
		weaponPosY = -2;
	}
	else
	{
		isCrouch = true;
		collider->top = 14;
		weaponPosY = -16;

		if (isRight)
			sprite = spriteRight;
		else
			sprite = spriteLeft;
		sprite->Next(4, 4);
	}

}

void Player::Jump()
{
	if (isHitted)
		return;

	if (!isJump)
	{
		isJump = true;
		downJump = true;
		position.y += 10;
		velocity.y = 410;
		sprite->Next(4, 4);
		collider->top = 14;
	}
}

void Player::Attack()
{
	if (isAttack)
		return;
	isAttack = true;
	timerSprite = 0;
}

void Player::Injured()
{
	if (isAttack)
		return;
	if (isImmortal)
		return;
	if (isHitted)
		return;
	velocity.y = 300;
	isHitted = true;
	sprite->Next(9, 9);
	this->health--;
	if (isRight)
	{
		velocity.x = -80;
	}
	else
		velocity.x = 80;
}

void Player::RestoreHealth()
{
	this->health = 16;
}
	
