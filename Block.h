#pragma once
#include <graphics.h>  //easyxͼ�ο�
struct Point {
	int row;
	int col;
};
class Block
{
public:
	Block();
	void drop();
	void moveleftright();
	void retate();  //��ת
	void draw(int leftMargin , int topMargin);

private:
	int blockType;  //��������
	Point SmallBlocks[4];

};

