﻿// object - quadtree

#include "OQuadTree.h"
#include "Sprite.h"
#include "GroupObject.h"

OTreeNode::OTreeNode()
{
	id = 0;
	left = 0;
	bottom = 0;
	width = 0;
	height = 0;

	subNodes = new OTreeNode*[4];
	subNodes[0] = NULL;
	subNodes[1] = NULL;
	subNodes[2] = NULL;
	subNodes[3] = NULL;

	group = new GroupObject(nullptr);//-------- !!!
}

OTreeNode::OTreeNode(int _Id, int _XLeft, int _YBottom, int _Width, int _Height)
{
	id = _Id;
	left = _XLeft;
	bottom = _YBottom;
	width = _Width;
	height = _Height;

	subNodes = new OTreeNode*[4];
	subNodes[0] = NULL;
	subNodes[1] = NULL;
	subNodes[2] = NULL;
	subNodes[3] = NULL;

	group = new GroupObject(nullptr);//-------------!!!
}

OTreeNode::~OTreeNode()
{
	delete subNodes;
}

bool OTreeNode::IsIntersectVP()
{
	// bên trái view port
	if ((left + width) <= Sprite::cameraX)
		return false;
	// bên dưới view port
	if ((bottom + height) <= (Sprite::cameraY - 448))	// cameraY nằm ở top
														//chứ không phải bottom
		return false;	//	448 là chiều cao màn hình
						// bên phải view port
	if (left >= (Sprite::cameraX + 512))	// 512 chiều rộng màn hình
		return false;
	// bên trên view port
	if (bottom >= Sprite::cameraY)
		return false;

	return true;
}

// lấy id của Node cha
int OTreeNode::GetParrentId()
{
	return (id / 8);
	// tại vì tool C# đòi 8 vậy đó =.=
}

// lấy vị trí của node con trong node cha
int OTreeNode::GetOffsetId()
{
	return (id % 8);
}

	// ném object trong phạm vi camera vào destination group
			// đây là hàm đệ quy
void OTreeNode::SendObjectTo(GroupObject *destinationGroup)
{
	if (!(this->IsIntersectVP()))
		return;


	if (subNodes[0] != NULL)	// không phải node lá
	{
		subNodes[0]->SendObjectTo(destinationGroup);
		subNodes[1]->SendObjectTo(destinationGroup);
		subNodes[2]->SendObjectTo(destinationGroup);
		subNodes[3]->SendObjectTo(destinationGroup);
	}
	else
	{	
		destinationGroup->GetObjectFrom(this->group);
	}
}
