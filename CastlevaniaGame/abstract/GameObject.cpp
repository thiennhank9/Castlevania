#include "GameObject.h"


// --- constructor & destructor ---
GameObject::GameObject()
{
	manager = NULL;

	isActive = false;
	objectType = 0;

	sizeWidth = 0;
	sizeHeight = 0;

	sprite = NULL;
	timerSprite = 0;
	collider = NULL;

	position.x = 0;
	position.y = 0;
	velocity.x = 0;
	velocity.y = 0;
}


GameObject::~GameObject()
{
	if (collider != NULL)
	{
		delete collider;
	}
	manager = NULL;
}


// check if there is a intersect
bool GameObject::Intersect(GameObject *target)
{
	// No collider? No intersect
	if ((target->collider == NULL) || (this->collider == NULL))
		return false;
	
	// cạnh trái của this > cạnh phải của target
	if ((position.x + collider->left) > (target->position.x + target->collider->right))
		return false;

	// cạnh phải của this < cạnh trái của target
	if ((position.x + collider->right) < (target->position.x + target->collider->left))
		return false;

	// cạnh trên của this < cạnh dưới của target
	if ((position.y + collider->top) < (target->position.y + target->collider->bottom))
		return false;

	// cạnh dưới của this > cạnh trên của target
	if ((position.y + collider->bottom) > (target->position.y + target->collider->top))
		return false;

	// ko thoả điều kiện nào hết => đang nằm lồng vào nhau
	return true;

}

/*hàm thực thi sweptAABB
* target: mục tiêu để xét va chạm
* deltatime: thời gian trong frame
--- hàm kiểm tra coi trong quãng thười gian delta_time, vật chủ đi từ A -> B
--- có thể va chạm target trong khoảng thời gian này hay không
> trả về:
* 0 : va chạm nhau ngay từ đầu (intersect)
* 0 < 'trả về' < delta_time : có va chạm xảy ra trong frame này, normal là vector pháp tuyến của bề mặt va chạm
* delta_time : không có va chạm xảy ra trong frame này
### 0 < 'trả về' < delta_time thất bại khi position của vật chủ BỊ THAY ĐỔI 1 CÁCH THỦ CÔNG
. vd: simon->position.x -= 10 (theo nguyên tắc thì position BẮT BUỘC phải update theo velocity*delta_time)
### tuy nhiên, để chữa cháy cho trường hợp này, thêm hàm Intersect() ở đầu code và trả về 0*/ 
float GameObject::sweptAABB(GameObject *target, float _deltatime)
{
	//normalX, normalY là giá trị để xác định kết quả phản ứng sau quá trình va chạm.
	//normalX chỉ vật A va chạm với vật B theo trục Ox, 
	//normalY chỉ vật A va chạm với vật B theo trục Oy, 
	float normalX = 0.0f, normalY = 0.0f;



	// if there is a intersect
	// chữa cháy cho trường hợp set position bậy bạ mà ko phải là 'position += velocity*delta_time';
	// ví dụ: là whip của Simon đột nhiên từ hư không chợt hiện ra hộp collider thế là nó nằm chồng lên các con quái 
	// Không có intersect thì fail toàn tập 
	if (Intersect(target))
	{
		return 0;
	}

	////////// board phrasing
	//Loại trước trường hợp nếu target kg nằm trong khối vuông di chuyển của this thì không cần tính các bước sweptAABB phia sau
	Collider boundingPhrase;
	D3DXVECTOR2 distanceInFrame;

	distanceInFrame = this->velocity * _deltatime;
	if (distanceInFrame.x < 0)
	{
		boundingPhrase.left = this->collider->left + distanceInFrame.x;
		boundingPhrase.right = this->collider->right;
	}
	else
	{
		boundingPhrase.left = this->collider->left;
		boundingPhrase.right = this->collider->right + distanceInFrame.x;
	}

	if (distanceInFrame.y < 0)
	{
		boundingPhrase.bottom = this->collider->bottom + distanceInFrame.y;
		boundingPhrase.top = this->collider->top;
	}
	else
	{
		boundingPhrase.bottom = this->collider->bottom;
		boundingPhrase.top = this->collider->top + distanceInFrame.y;
	}


	// if there is a intersect of board phrasing => may be the "sweptAABB" complete
	// if no? A and B never collide other in this frame

	if ((position.x + boundingPhrase.left) > (target->position.x + target->collider->right))
	{// return the value that A and B never collide other in this frame
		return _deltatime;
	}
	if ((position.x + boundingPhrase.right) < (target->position.x + target->collider->left))
	{
		return _deltatime;
	}
	if ((position.y + boundingPhrase.top) < (target->position.y + target->collider->bottom))
	{
		return _deltatime;
	}
	if ((position.y + boundingPhrase.bottom) > (target->position.y + target->collider->top))
	{
		return _deltatime;
	}
	

	//xInvEntry, yInvEntry chỉ khoảng cách 2 cạnh GẦN NHẤT của vật xét va chạm xét 2 chiều x và y 
	//xInvEntry khoảng cách 2 cạnh gần nhất của 2 vật trên trục x
	//yInvEntry khoảng cách 2 cạnh gần nhất của 2 vật trên trục y
	float xInvEntry, yInvEntry;
	//xInvExit, yInvExit chỉ khoảng cách 2 cạnh XA NHẤT của 2 vật xét va chạm theo 2 trục x và y
	//xInvExit khoảng cách 2 cạnh xa nhất của 2 vật trên trục x
	//xInvExit khoảng cách 2 cạnh xa nhất của 2 vật trên trục y
	float xInvExit, yInvExit;

	//nếu như vật đi về bên phải --->
	if (this->velocity.x > 0)
	{
		//với position.x là vị trí tại tâm của vật  thì, hình mô tả A là this, B là target
		//  [A]  ----->  [B]
		//target->position.x + target->collider->left = vị trí cạnh trái của target
		//this->position.x + this->collider->right = vị trí của cạnh phải this
		xInvEntry = (target->position.x + target->collider->left) - (this->position.x + this->collider->right);
		//target->position.x + target->collider->right = vị trí cạnh phải của target
		//this->position.x + this->collider->left = vị trí của cạnh trái this
		xInvExit = (target->position.x + target->collider->right) - (this->position.x + this->collider->left);
	}
	else
	{
		//với position.x là vị trí tại tâm của vật  thì, hình mô tả A là this, B là target
		//  [B]  <-----  [A]
		//target->position.x + target->collider->right = vị trí cạnh phải của target
		//this->position.x + this->collider->left = vị trí của cạnh trái this
		xInvEntry = (target->position.x + target->collider->right) - (this->position.x + this->collider->left);
		//target->position.x + target->collider->left = vị trí cạnh trái của target
		//this->position.x + this->collider->right = vị trí của cạnh phải this
		xInvExit = (target->position.x + target->collider->left) - (this->position.x + this->collider->right);
	}

	//Nếu vật đi lên trên
	if (this->velocity.y > 0.0f)
	{
		yInvEntry = (target->position.y + target->collider->bottom) - (this->position.y + this->collider->top);
		yInvExit = (target->position.y + target->collider->top) - (this->position.y + this->collider->bottom);
	}
	else
	{
		yInvEntry = (target->position.y + target->collider->top) - (this->position.y + this->collider->bottom);
		yInvExit = (target->position.y + target->collider->bottom) - (this->position.y + this->collider->top);
	}



	//Xác định thời gian xảy ra va chạm (có loại bỏ trường hợp lỗi khi chia cho 0)
	float xEntry, yEntry;
	float xExit, yExit;

	// Xác định thời gian bắt đầu xảy ra va chạm và kết thuc va chạm theo trục X
	if (this->velocity.x == 0.0f)
	{
		//Trường hợp vận tốc bằng 0 thì tất cả các thông số là vô cực
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / this->velocity.x; //Khoảng thời gian bắt đầu va chạm theo chiều X
		xExit = xInvExit / this->velocity.x; //Khoảng thời gian kết thúc va chạm theo chiều X
	}

	//Xác định thời gian bắt đầu xảy ra va chạm và kết thúc va chạm theo chiều Y
	if (this->velocity.y == 0.0f)
	{
		//Trường hợp vận tốc bằng 0 thì tất cả các thông số là vô cực
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / this->velocity.y; //Khoảng thời gian bắt đầu va chạm theo chiều Y
		yExit = yInvExit / this->velocity.y; //Khoảng thời gian kết thúc va chạm theo chiều Y
	}

	//tìm khoảng thời gian bắt đầu và kết thúc va chạm 
	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);

	//Trường hợp không xảy ra va chạm
	//DK1: thời gian bắt đầu va chạm trễ hơn thời gian kết thúc va chạm
	//DK2: thời gian bắt đầu va chạm trên cả 2 chiều đều âm
	//Dk3: 1 trong 2 thời gian bắt đầu va chạm theo chiều X và Y lớn hơn 1 lần vận tốc (trong frame này không thể va chạm với nhau)
	if (entryTime > exitTime || (xEntry < 0.0f && yEntry < 0.0f))
	{															// chỗ này là _DeltaTime mới đúng, 1.0f là timeScale
		normalX = 0.0f;
		normalY = 0.0f;
		//return 1.0f;
		return _deltatime;
	}
	else
	{
		// 1 vật thể được thể hiện bởi 1 hộp va chạm hình chữ nhật thì có 4 trường hợp tương tác va chạm xảy ra
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normalX = 1.0f;
				normalY = 0.0f;
			}
			else
			{
				normalX = -1.0f;
				normalY = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normalX = 0.0f;
				normalY = 1.0f;
			}
			else
			{
				normalX = 0.0f;
				normalY = -1.0f;
			}
		}

		return entryTime;
	}



}


// --- cac phuong thuc ao
void GameObject::Init(int _X, int _Y) {}
void GameObject::Update(const float &_DeltaTime) {}
void GameObject::Render() {}
void GameObject::Destroy() {}
void GameObject::Collision() {};

