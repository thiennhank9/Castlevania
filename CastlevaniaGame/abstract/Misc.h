#ifndef _MISC_H_
#define _MISC_H_

#include "../ThamSo.h"

// ======== DROP ITEM TABLE =========
struct DropLine
{
	int itemType;
	int percent;
};

class DropTable
{
	int numberItem;
	int luckyInt;
	DropLine dropLine[5];

	int DropItem();

	DropTable();
	~DropTable();
};


// ========= COLLIDER ===========
// đây là class dùng để quyết định xem vật thể đó có xét va chạm hay không
//và dùng để xét intersect cho va chạm
class Collider
{
public:
	// các biến
	// trục Y hướng lên
	int top;	// luôn > 0
	int bottom;	// luôn < 0
				// trục X hướng qua phải
	int left;	// luôn < 0
	int right;	// luôn > 0

	GameObject *owner;

	//Khởi tạo và huỷ
	Collider();
	Collider(int objectType);
	/*void setCollider(GameObject *_owner, int _top, int _bottom, int _left, int _right);
		:owner(_owner), top(_top), bottom(_bottom), left(_left), right(_right) {};*/
	
	~Collider();

	void setCollider(int _top, int _bottom, int _left, int _right);
};

#endif // !_MISC_H_
