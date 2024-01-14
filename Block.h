#pragma once
#include <graphics.h>  //easyxͼ�ο�
#include <vector>
using namespace std;
struct Point {
	int row;
	int col;
};
class Block
{
public:
	Block();
	void drop();
	void rotate();  //��ת
	void moveleftright(int offset);
	void draw(int leftMargin , int topMargin);
	static IMAGE** getImages();
	Block& operator =(const Block& other);
    //Point* getSmallBlocks();
	bool blockInMap(const vector<vector<int>> &map);
	void solidify(vector<vector<int>>&map);
	int getBlockType();

private:
	int blockType;  //��������
	Point SmallBlocks[4];
	IMAGE* img;

	static IMAGE* imgs[7];
	static int Size; //�����С

};

