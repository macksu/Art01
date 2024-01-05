#pragma once
#include <graphics.h>  //easyx图形库
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
	void retate();  //旋转
	void draw(int leftMargin , int topMargin);

private:
	int blockType;  //方块类型
	Point SmallBlocks[4];

};

