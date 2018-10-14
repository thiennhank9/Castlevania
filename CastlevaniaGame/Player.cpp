#include "Player.h"
#include "World.h"
#include "GroupObject.h"
#include "Ground.h"

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
	isMoveToX = false;

	onStair = -1;
	stairMoveKey = 0;
	isShowTime = false;
	animStart = false;
	isClimbing = true;
	isDeath = false;
	alreadyDeath = false;


	//upKey = false;

	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\simon_left.bmp", sizeWidth, sizeHeight, 27, 6);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\simon_right.bmp", sizeWidth, sizeHeight, 27, 6);
	sprite = spriteRight;

	weaponLevel = 1;
	weaponNumber = 2;
	subWeapon = 6;
	invicinbleTimer = 0;

	heart = 5;
	health = HEALTH;
	P = 3;
	score = 0;
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
	tempGround = 20;

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

	isMoveToX = false;

	onStair = -1;
	stairMoveKey = 0;
	isShowTime = false;
	animStart = false;
	isClimbing = true;
	isDeath = false;
	alreadyDeath = false;


	position.x = _X;
	position.y = _Y;

	weaponLevel = 1;
	weaponNumber = 2;
	subWeapon = 1;
	isUsingWeapon = false;

	invicinbleTimer = 0;

	heart = 5;
	health = 16;
	P = 3;
	score = 0;
}

void Player::Render()
{
	if ((int)(timeImmortal*(2.0f / ANIM_TIME)) % 2 == 0)
	{
		sprite->Render(position.x, position.y);
	}
}

void Player::Destroy() {}

void Player::Collision()
{
}

// ---=== UPDATE ===---
void Player::Update(const float &_DeltaTime)
{

	if (isDeath)
	{
		this->UpdateSimonDeath(_DeltaTime);
		return;
	}

	//truong hop dang bat tu
	if (isImmortal)
	{
		timeImmortal += _DeltaTime;
		if (timeImmortal > IMMORTAL_TIME)
			isImmortal = false;
	}

	//truong hop dang bi thuong
	if (isHitted)
	{
		isAttack = false;
		isUsingWeapon = false;
	}

	if (onStair <= 0)
	{
		//dang tan cong
		if (isAttack || isUsingWeapon)
		{
			UpdateWhenAttack(_DeltaTime);
		}
		else
		{
			isChangeFrame = false;
		}
	}
	else
	{
		velocity.x = 0;
		velocity.y = 0;

		//dang tan cong
		if (isAttack || isUsingWeapon)
		{
			UpdateWhenAttackOnStair(_DeltaTime);
		}
		else
		{
			isChangeFrame = false;
		}
	}

	//thực thi lệnh chuyển vị trí player (nếu có)
	if (isMoveToX)
	{
		UpdateWhenMoveToPossionX(_DeltaTime);
		UpdateCamera();
		CollisionObject(_DeltaTime);
		return;
	}

	//
	if (onStair <= 0)
		velocity.y += -(1000 * _DeltaTime);
	else
		UpdateWhenOnStair(_DeltaTime);

	CollisionObject(_DeltaTime);

	//cap nhat toa do Y
	if (isAttack && !isJump)
	{
	}
	else
		position.x += (velocity.x * _DeltaTime);

	position.y += (velocity.y * _DeltaTime);

	//dieu khien truong hop nhay
	if (isJump)
		UpdateWhenJumping(_DeltaTime);

	// truong hop toa do Y < mat dat
	if (position.y < tempGround)
	{
		position.y = tempGround;
		isJump = false;
		if (isHitted)
		{
			isHitted = false;
			if (!isAttack)
				sprite->_Index = 0;
		}

		velocity.y = 0;
	}

	//UpdateCamera();
	Sprite::CameraFollow(this, _DeltaTime);
	if (position.x < (Sprite::cameraXLeft + 8))
		position.x = Sprite::cameraXLeft + 8;
	if (position.x > (Sprite::cameraXRight + 504))
		position.x = Sprite::cameraXRight + 504;
}

void Player::UpdateCamera()
{
	
	Sprite::cameraX = position.x - 256;
	if (Sprite::cameraX < Sprite::cameraXLeft)
	{
		Sprite::cameraX = Sprite::cameraXLeft;
	}
	else if (Sprite::cameraX > Sprite::cameraXRight)
	{
		Sprite::cameraX = Sprite::cameraXRight;
	}
}

void Player::UpdateWhenJumping(float _DeltaTime)
{
	if (velocity.y > 0)
	{
		//sprite->Next(4, 4);
	}
	else if (downJump)
	{
		downJump = false;
		position.y -= 10;
		if (!isAttack)
		{
			sprite->Next(0, 0);
			collider->top = 28;
		}

	}
}

void Player::UpdateWhenAttack(float _DeltaTime)
{
	if (position.y < tempGround)
		position.y = tempGround;
	timerSprite += _DeltaTime;
	//truong hop ngoi danh
	if (isCrouch)
	{
		isChangeFrame = false;
		if (timerSprite >= ANIM_TIME)
		{
			timerSprite -= ANIM_TIME;
			sprite->Next(15, 17);
			isChangeFrame = true;
			if (sprite->_Index == 16)
				killingMoment = true;
			else
				killingMoment = false;
		}
		if (sprite->_Index == 17)
		{
			isChangeFrame = false;
			isAttack = false;
			sprite->_Index = 4;
			isUsingWeapon = false;
		}
	}

	else // truong hop dung danh
	{
		isChangeFrame = false;
		if (timerSprite >= ANIM_TIME)
		{
			timerSprite -= ANIM_TIME;
			sprite->Next(12, 14);
			isChangeFrame = true;
			if (sprite->_Index == 13)
				killingMoment = true;
			else
				killingMoment = false;
		}
		if (sprite->_Index == 14)
		{
			isChangeFrame = false;
			isAttack = false;
			isUsingWeapon = false;
			sprite->_Index = 0;
		}
	}
}

void Player::UpdateWhenAttackOnStair(float _DeltaTime)
{
	timerSprite += _DeltaTime;
	//truong hop đang đi lên
	if (isClimbing)
	{
		isChangeFrame = false;
		if (timerSprite >= ANIM_TIME)
		{
			timerSprite -= ANIM_TIME;
			sprite->Next(21, 23);
			isChangeFrame = true;
			if (sprite->_Index == 22)
				killingMoment = true;
			else
				killingMoment = false;
		}
		if (sprite->_Index == 23)
		{
			isChangeFrame = false;
			isAttack = false;
			isUsingWeapon = false;
			sprite->_Index = 7;
		}
	}
	else // trường hợp đang đi xuống
	{
		isChangeFrame = false;
		if (timerSprite >= ANIM_TIME)
		{
			timerSprite -= ANIM_TIME;
			sprite->Next(18, 20);
			isChangeFrame = true;
			if (sprite->_Index == 19)
				killingMoment = true;
			else
				killingMoment = false;
		}
		if (sprite->_Index == 20)
		{
			isChangeFrame = false;
			isAttack = false;
			sprite->_Index = 5;
			isUsingWeapon = false;
		}
	}

}

void Player::UpdateWhenOnStair(float _DeltaTime)
{
	velocity.x = 0;
	velocity.y = 0;
	if (stairMoveKey == 0)
	{
		animStart = false;
		isShowTime = false;
		return;
	}
	else // truong hop di chuyen
	{
		timeStairAnim += _DeltaTime;
		if (timeStairAnim >= ANIM_TIME / 2.0f)
		{
			timeStairAnim -= ANIM_TIME / 2.0f;

			//truong hop nhan phim len
			if (stairMoveKey == 1)
			{
				// neu dang o cau thang nghieng ben phai "/"
				if (stairType == STAIR_UPRIGHT || stairType == STAIR_DOWNLEFT)
				{
					sprite = spriteRight;
					isRight = true;
					if (animStart)
					{
						sprite->_Index = 6;
						position.x += 8;
						animStart = false;
					}
					else
					{
						sprite->_Index = 7;
						position.x += 8;
						position.y += 16;
						isShowTime = false;
					}
				}
				// neu dang o cau thang nghieng ben trai "\"	
				else
				{
					sprite = spriteLeft;
					isRight = false;
					if (animStart)
					{
						sprite->_Index = 6;
						position.x -= 8;
						animStart = false;
					}
					else
					{
						sprite->_Index = 7;
						position.x -= 8;
						position.y += 16;
						isShowTime = false;
					}
				}
			}

			//truong hop bam phim xuong
			else
			{
				// neu dang o cau thang nghieng ben phai "/"
				if (stairType == STAIR_UPRIGHT || stairType == STAIR_DOWNLEFT)
				{
					sprite = spriteLeft;
					isRight = false;
					if (animStart)
					{
						sprite->_Index = 6;
						position.x -= 8;
						animStart = false;
					}
					else
					{
						sprite->_Index = 5;
						position.x -= 8;
						position.y -= 16;
						isShowTime = false;
					}
				}
				// neu dang o cau thang nghieng ben trai "\"
				else
				{
					sprite = spriteRight;
					isRight = true;
					if (animStart)
					{
						sprite->_Index = 6;
						position.x += 8;
						animStart = false;
					}
					else
					{
						sprite->_Index = 5;
						position.x += 8;
						position.y -= 16;
						isShowTime = false;
					}
				}
			}
		}

	}


}

void Player::UpdateWhenMoveToPossionX(float _DeltaTime)
{
	//nếu player đang ở tại vi tri cần đến (sai số không quá 1.0f) thì di chuyển hoàn tất
	if (position.x > DestinationX - 1 && position.x <= DestinationX + 1)
	{
		isMoveToX = false;
		position.x = DestinationX;
		Move(0, _DeltaTime);
		return;
	}

	if (position.x < DestinationX)
		Move(1, _DeltaTime);
	else
		Move(-1, _DeltaTime);


	position.x += velocity.x*_DeltaTime / 2;

}


// Update trạng thái khi Simon death
void Player::UpdateSimonDeath(float _DeltaTime)
{
	if (!this->alreadyDeath)
	{
		this->timeSimonDeath += _DeltaTime;

		if (this->timeSimonDeath > ANIM_TIME)
		{
			this->timeSimonDeath -= ANIM_TIME;
			this->sprite->Next(9, 11);
			this->heart = this->sprite->_Index;
			if (this->sprite->_Index == 10)
			{
				this->alreadyDeath = true;
			}
		}
	}

}


// ---===PROCESSINPUT ===---

void Player::Move(int moveKey, const float &_DeltaTime)

{
	if (isJump)
		return;
	if (isAttack)
		return;
	if (isUsingWeapon)
		return;
	if (isHitted)
		return;
	if (isDeath)
		return;

	switch (moveKey)
	{
	case -1:
		velocity.x = -VELOCITY;
		isRight = false;
		sprite = spriteLeft;
		break;
	case 1:
		velocity.x = VELOCITY;
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

void Player::Up(int upKey)
{

}

void Player::Down(int downKey)
{
	if (isDeath)
		return;

	if (isJump)
	{
		return;
	}
	if (isAttack)
	{
		return;
	}

	if (isUsingWeapon)
		return;

	if (isHitted)
	{
		return;
	}


	//truong hop nhan nut xuong khi dang o dau cau thang di xuong
	if (downKey == -1)
	{
		if (stairType == STAIR_DOWNLEFT || stairType == STAIR_DOWNRIGHT)
		{
			onStair = 1;
			MovingOnStair(-1);
			isMoveToX = true;
			return;
		}
	}



	if (downKey == 0)
	{
		isCrouch = false;
		collider->top = 28;
	}
	else
	{
		isCrouch = true;
		collider->top = 14;

		if (isRight)
			sprite = spriteRight;
		else
			sprite = spriteLeft;
		sprite->Next(4, 4);
	}


}

void Player::Jump()
{
	if (isDeath)
		return;
	if (onStair == 1)
		return;
	if (isAttack)
		return;

	if (isUsingWeapon)
		return;

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

void Player::Attack(int keyAttack)
{
	if (isDeath)
		return;
	if (isShowTime)
		return;
	//truong hop dang bi thuong
	if (isHitted)
		return;
	//truong hop dang danh ma nhan phim danh
	if (isAttack)
		return;

	if (isUsingWeapon)
		return;


	//danh hop le
	isAttack = true;


	// tấn công bình thường
	if (onStair <= 0)
	{
		//kiem tra co dang ngoi khong?
		if (isCrouch)
			sprite->_Index = 14;
		else
			sprite->_Index = 11;

		timerSprite = 0;
	}
	//tấn công khi đang leo cầu thang
	else
	{
		//kiểm tra Player đang leo lên hay đi xuống
		if (isClimbing)
			sprite->_Index = 20;
		else
			sprite->_Index = 17;

		timerSprite = 0;
	}

	if (keyAttack == 0 && manager->whip->isActive == false)
		manager->whip->Init(position.x, position.y);
}

void Player::ActivateWeapon()
{
	if (isActive || isShowTime || isHitted || this->heart <= 0)
		return;
	Attack(1);
	if (!isAttack)
		return;
	int count = 0;
	bool isActivateWeapon = false;
	switch (subWeapon)
	{
	case BOOMERANG:
		count = 0;

		//dem so luong weapon cung loai dang active
		for (int i = 0; i < 3; i++)
		{
			if (manager->boo[i]->isActive)
				count++;
		}

		// neu so luong weapon dang active nho hon so luong cho phep thi cho phep danh them
		if (count < weaponNumber)
			for (int i = 0; i < 3; i++)
			{
				if (!manager->boo[i]->isActive)
				{
					this->heart--;
					manager->boo[i]->Init(position.x, position.y);
					isActivateWeapon = true;
					return;
				}
			}
		break;
	case AXE:
		count = 0;

		//dem so luong weapon cung loai dang active
		for (int i = 0; i < 3; i++)
		{
			if (manager->axe[i]->isActive)
				count++;
		}

		// neu so luong weapon dang active nho hon so luong cho phep thi cho phep danh them
		if (count < weaponNumber)
			for (int i = 0; i < 3; i++)
			{
				if (!manager->axe[i]->isActive)
				{
					this->heart--;
					manager->axe[i]->Init(position.x, position.y);
					isActivateWeapon = true;
					return;
				}
			}
		break;
	case KNIFE:
		count = 0;

		//dem so luong weapon cung loai dang active
		for (int i = 0; i < 3; i++)
		{
			if (manager->knife[i]->isActive)
				count++;
		}

		// neu so luong weapon dang active nho hon so luong cho phep thi cho phep danh them
		if (count < weaponNumber)
			for (int i = 0; i < 3; i++)
			{
				if (!manager->knife[i]->isActive)
				{
					this->heart--;
					manager->knife[i]->Init(position.x, position.y);
					isActivateWeapon = true;
					return;
				}
			}
		break;
	case HOLYWATER:
		count = 0;
		int countHolyFire = 0;

		//dem so luong weapon cung loai dang active
		for (int i = 0; i < 3; i++)
		{
			if (manager->holyWater[i]->isActive)
				count++;
		}

		//dem so luong holyFire dang active
		for (int i = 0; i < 3; i++)
		{
			if (manager->holyFire[i]->isActive)
				countHolyFire++;
		}


		// neu so luong weapon dang active nho hon so luong cho phep thi cho phep danh them
		if (count < weaponNumber && countHolyFire < weaponNumber) 
			for (int i = 0; i < 3; i++)
			{
				if (!manager->holyWater[i]->isActive)
				{
					this->heart--;
					manager->holyWater[i]->Init(position.x, position.y);
					isActivateWeapon = true;
					return;
				}
			}
		break;
	}


	// truong hop khong co weapon nao duoc danh ra
	
	//kiem tra xem whip co duoc danh chua
	if (!manager->whip->isActive)
		manager->whip->Init(position.x, position.y);
	else
		isActive = false;

}

void Player::Injured(int keyInjured)
{
	if (isImmortal)
		return;
	if (isHitted)
		return;
	velocity.y = 300;


	//bien xac dinh trang thai bi thuong
	isHitted = true;

	//kich hoat trang thai bất tử
	isImmortal = true;
	timeImmortal = 0;

	sprite->Next(9, 9);
	// update by K
	if (keyInjured == 1) // va cham tu ben phai
	{
		velocity.x = 80;
		sprite = spriteLeft;
		isRight = false;
	}
		
	else //khong phai va cham tu ben phai
	{
		velocity.x = -80;
		sprite = spriteRight;
		isRight = true;
	}

	//khi bị thương, ngừng mọi hoạt động hiện tai như đánh, ngồi, nhảy
	isCrouch = false;
	isAttack = false;
	killingMoment = false;
	isShocked = false;
	isChangeFrame = false;
	isMoveToX = false;

	onStair = -1;
	stairMoveKey = 0;
	isShowTime = false;
	animStart = false;

	this->health--;

	if (this->health == 0)
		this->SimonDeath();



}

void Player::MovingOnStair(int keyMove)
{
	if(isJump || downJump || isHitted)
	{
		onStair = 0;
		isMoveToX = false;
		return;
	}
	if (isAttack || isUsingWeapon)
	{
		return;
	}
	if (isShowTime)
		return;
	stairMoveKey = keyMove;
	if (stairMoveKey != 0)
	{
		if (keyMove == 1)
			isClimbing = true;
		else
			isClimbing = false;
		animStart = true;
		timeStairAnim = 0;
		isShowTime = true;
	}


}

void Player::SimonDeath()
{
	this->timeSimonDeath = 0;
	this->isDeath = true;
}


// ---=== COLLISION ===---

void Player::CollisionObject(float _DeltaTime)
{
	if (onStair == 0)
		onStair = -1;

	// ----  ----- testing only
	// -------------------------------------------------------------------------------------
	// -- MÔ HÌNH XÉT COLLISION MỚI, những cái này để ở hàm CollisionObject() trong mỗi object
	//						CollisionObject() gọi ở đầu Update() trong mỗi object
	// -------------------------------------------------------------------------------------
	float collisionScale = 0;



	GameObject* tempObject;
	// Xét va chạm với nhóm đối tượng đặc biệt. Ví dụ như ghoul (Respawn), Item,...
	// mấy con ghoul, item,... không cần xét va chạm với nhóm này
	for (int i = 0; i < (manager->groupSpecialCollision->number); i++)
	{
		// cho biến tạm trỏ vào, biến này ngắn hơn code đỡ mỏi tay :v
		tempObject = manager->groupSpecialCollision->objects[i];

		switch (tempObject->objectType)
		{
		case ZONE_TYPE:// nếu đối tượng là zone => chạy hàm Collision() của Zone
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			if (collisionScale < 1.0f)
			{
				switch (((Zone*)tempObject)->typeZone)
				{
				case ZONE_GATEWAY:
					((GateWay*)tempObject)->Collision(this, _DeltaTime);
					break;
				}////
			}//////// Ghi chơi cho vui thôi, block & zone nằm trong chỗ quadtree rồi
			break;
		case ITEM_TYPE:
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			if (collisionScale < 1.0f)
			{
				if (tempObject->isActive)
					((Item*)tempObject)->Collision(this);
				
			}
			break;
		

		case ENEMY_TYPE:
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			if (collisionScale < 1.0f)
			{
				if (!isImmortal)
					if (normalx > 0.1f)
						Injured(1);
					else
						Injured(-1);
				tempObject->Collision();
			}
			break;
		
		default:
			break;
		}

	}


	// Xét va chạm với nhóm đối tượng trong quadtree. Ví dụ như Ground, Destructibe, Zone,...
	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{
		
		tempObject = manager->groupQuadtreeCollision->objects[i];
		switch (tempObject->objectType)
		{
		case ZONE_TYPE:// nếu đối tượng là zone => chạy hàm Collision() của Zone
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			if (collisionScale < 1.0f)
			{
				
				((Zone*)tempObject)->Collision(this, _DeltaTime);
			}
			break;
		case GROUND_TYPE:
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			if (collisionScale < 1.0f)
			{
			
				if(normaly > 0.1f)//chạm từ trên xuống
				{
					isJump = false;
					isHitted = false;
					//
					this->velocity.x += tempObject->velocity.x;
				}
				SlideFromGround(tempObject, _DeltaTime, collisionScale);
			}
			break;
		
		case ENEMY_TYPE:
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			if (collisionScale < 1.0f)
			{
				if (!isImmortal)
					if (normalx > 0.1f)
						Injured(1);
					else
						Injured(-1);
				tempObject->Collision();
			}
			break;
		case STAIR_TYPE:
			if (IsCollide(tempObject))
			{
				switch (((Stair*)tempObject)->stairType)
				{
				case STAIR_DOWNLEFT:
					stairType = STAIR_DOWNLEFT;
					if (!isShowTime && position.y + 2 >= tempObject->position.y)
					{
						DestinationX = tempObject->position.x;
						onStair = 0;
					}

					break;
				case STAIR_DOWNRIGHT:
					stairType = STAIR_DOWNRIGHT;
					if (!isShowTime && position.y + 2 >= tempObject->position.y)
					{
						DestinationX = tempObject->position.x;
						onStair = 0;
					}
					break;
				case STAIR_UPLEFT:
					stairType = STAIR_UPLEFT;
					if (!isShowTime && position.y - 2 <= tempObject->position.y)
					{
						DestinationX = tempObject->position.x;
						onStair = 0;
					}
					break;
				case STAIR_UPRIGHT:
					stairType = STAIR_UPRIGHT;
					if (!isShowTime && position.y - 2 <= tempObject->position.y)
					{
						DestinationX = tempObject->position.x;
						onStair = 0;
					}
					break;
				}
			}

			break;
		}
	}
	// -------------------------------------------------------------------------------------
	// --------------
	// -------------------------------------------------------------------------------------
}


//~~~~~~~~~~~~~~~~~~Cheat function
void Player::RestoreHP()
{
	this->health = 16;
}

void Player::IncreaseHeart()
{
	this->heart += 10;
}

void Player::ChangeSubWeapon()
{
	this->subWeapon++;

	if (this->subWeapon >= 7)
		this->subWeapon = this->subWeapon / 7 + 1;
}