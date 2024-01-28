#pragma once
#include <graphics.h>  //easyx图形库
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
	void drop();     //下降
	void rotate();  //旋转
	void moveleftright(int offset);  //左右移动
	void draw(int leftMargin , int topMargin);  //绘制图形
	static IMAGE** getImages();
	Block& operator =(const Block& other);
    //Point* getSmallBlocks();
	bool blockInMap(const vector<vector<int>> &map);
	void solidify(vector<vector<int>>&map);   //固定方块
	int getBlockType();

private:
	int blockType;  //方块类型
	Point SmallBlocks[4];  //方块组成
	IMAGE* img;   

	static IMAGE* imgs[7];
	static int Size; //方块大小

};

