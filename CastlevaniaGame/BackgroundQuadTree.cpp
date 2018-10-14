#include "BackgroundQuadTree.h"
#include "Sprite.h"

BackgroundQuadTree::BackgroundQuadTree()
{
	tl = NULL;
	tr = NULL;
	bl = NULL;
	br = NULL;
	rect = new RECT();
	nodeID = 0;
	//tileIDs.clear();
}

BackgroundQuadTree::~BackgroundQuadTree()
{
	delete(tl);
	delete(tr);
	delete(bl);
	delete(br);
	/*if (!tileIDs.empty())
		tileIDs.clear();*/
	delete(rect);
}

// the root node has ID: 1 (view file)
void BackgroundQuadTree::setRootNode(map<int, BackgroundQuadTree*> &Nodes)
{
	//gan gia tri cua Nodes[1] vao node hien tai
	nodeID = 1;
	tl = Nodes[1]->tl;
	tr = Nodes[1]->tr;
	bl = Nodes[1]->bl;
	br = Nodes[1]->br;
	rect = Nodes[1]->rect;

	tile_IDs = Nodes[1]->tile_IDs;

	//cho Nodes[1] tro vao node hien tai
	Nodes[1] = this;
}

// paste the file into excel, you will see that \t separate column
BackgroundQuadTree* BackgroundQuadTree::createNodeFromString(string line)
{
	//tao mot node moi
	BackgroundQuadTree *node = new BackgroundQuadTree;

	if (line == "")
		return node;// empty node

	int x, y, width, height;

	//tao mot danh sach kieu chuoi
	vector <string> words;
	words.clear();

	//cat line thanh nhieu chuoi va dua vao words
	string word = "";
	int i = 0;
	while (i < line.length())
	{
		if (line[i] != '	')// separated by \t
		{
			word += line[i];
		}
		else
		{
			words.push_back(word);
			word = "";
		}
		i++;
	}
	//dua tu cuoi vao words
	words.push_back(word);

	// *************
	// ** words[] array of "std::string"
	// ** words[ <index> ].c_str() => return "char*" point to the content of the "std::string"

	// xet gia tri node bang cac gia tri tuong ung trong words

	// ** atoi = Ascii TO Integer, convert the ascii characters to number
	node->nodeID = atoi(words[0].c_str());// first column is ID
	x = atoi(words[1].c_str());// 2nd, 3rd columns is position of the node // what corner? I'm forgot :v
	y = atoi(words[2].c_str());
	width = atoi(words[3].c_str());// 4th, 5th columns is the size
	height = atoi(words[4].c_str());

	node->rect->left = x;
	node->rect->bottom = y;
	node->rect->top = y + height;
	node->rect->right = x + width;


	//su dung bien dem i de duyet words
	i = 5;// 6th column and the after columns is ID of tile

	//neu so luong phan tu cua word > 5 thi node co chua doi tuong ta tien hanh lap danh sach cac doi tuong do
	
	node->n = words.size() - 5;
	node->tile_IDs = new int[node->n];

	if (node->n == 0) //khong co ID tile trong node
		return node;

	while (i < words.size())
	{
		node->tile_IDs[i-5] = atoi(words[i].c_str());
		i++;
	}
	return node;
}

// linking nodes with others, building a quad-tree
//  (a node will have 4 subnodes)  (the end-node will have no childs)  (data will be contained at the end-nodes)
void BackgroundQuadTree::ConnectToTheChildNodes(map<int, BackgroundQuadTree*> &Nodes)
{
	if (Nodes[nodeID * 10 + 1] == NULL)
		return;

	int childID = nodeID * 10;
	tl = Nodes[childID + 1];
	tr = Nodes[childID + 2];
	bl = Nodes[childID + 3];
	br = Nodes[childID + 4];

	tl->ConnectToTheChildNodes(Nodes);
	tr->ConnectToTheChildNodes(Nodes);
	bl->ConnectToTheChildNodes(Nodes);
	br->ConnectToTheChildNodes(Nodes);
}

void BackgroundQuadTree::loadTreeFromFile(char* filename)
{
	//chuoi line de luu tung chuoi trong qua trinh doc file
	string line = "";

	//su dung cau truc map de luu cac node
	map <int, BackgroundQuadTree*> Nodes;
	Nodes.clear();//dam bao map trong

	BackgroundQuadTree *node = new BackgroundQuadTree();

	//doc file
	ifstream fi;// <input-file-stream>
	fi.open(filename);

	//xet dieu kien trong khi chua het file
	while (!fi.eof())// eof = end-of-file
	{
		getline(fi, line);
		node = createNodeFromString(line);
		Nodes[node->nodeID] = node;
	}
	setRootNode(Nodes);
	ConnectToTheChildNodes(Nodes);
}

// is intersect viewport?
bool BackgroundQuadTree::IsIntersectVP()
{
	RECT cameraRect; // bien xac dinh 4 canh cua camera

	cameraRect.left = Sprite::cameraX;
	cameraRect.right = cameraRect.left+ 544;
	cameraRect.top = Sprite::cameraY;
	cameraRect.bottom = cameraRect.top - 448;

	if (rect->left >= cameraRect.right)
		return false;
	if (rect->right <= cameraRect.left)
		return false;
	if (rect->top <= cameraRect.bottom)
		return false;
	if (rect->bottom >= cameraRect.top)
		return false;
	return true;
}

void BackgroundQuadTree::ListObjectInViewPort(int *ObjectIDs, int &size )
{
	if (!IsIntersectVP())
		return;
	//kiem tra node la node la
	if (tl == NULL)
	{
		//kiem tra neu node khong co chua doi tuong
		if (n == 0)
			return;

		//node co doi tuong ->tien hanh them vao danh sach
		int i = 0;
		while (i < n)
		{
			ObjectIDs[size] = tile_IDs[i];
			i++;
			size++;
		}
	}
	else //node khong phai la node la
	{
		tl->ListObjectInViewPort(ObjectIDs, size);
		tr->ListObjectInViewPort(ObjectIDs, size);
		bl->ListObjectInViewPort(ObjectIDs, size);
		br->ListObjectInViewPort(ObjectIDs, size);
	}
}