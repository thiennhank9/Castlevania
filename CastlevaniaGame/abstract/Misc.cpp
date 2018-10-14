#include "Misc.h"

// ======= DROP ITEM TABLE =============
DropTable::DropTable()
{
	numberItem = 0;
	luckyInt = 0;
}

DropTable::~DropTable() {}

// hàm trả về loại item sẽ rơi ra
int DropTable::DropItem()
{
	if (numberItem)
	{
		luckyInt = rand() % numberItem;
		if (dropLine[this->luckyInt].percent > rand() % 100)
			return dropLine[luckyInt].itemType;
	}
	return 0;
}
// rồi tạo item theo loại item



// ============ COLLIDER ============


Collider::Collider()
{
	top = 0;
	bottom = 0;
	left = 0;
	right = 0;

	owner = NULL;
}

Collider::Collider(int objectType)
{
	switch (objectType)
	{
	case 1:
		top =26;
		left =- 17;
		right = 17;
		bottom = - 32;
	case 5:
		top = 24;
		bottom =- 24;
		left = -17;
		right =17;
	}

}

void Collider::setCollider(int _top, int _bottom, int _left, int _right)
{
	top = _top;
	bottom = _bottom;
	left = _left;
	right = _right;
}

// có 1 con trỏ đến owner (GameObject)
Collider::~Collider() {}
// mà GameObject có sẵn Destructor rồi