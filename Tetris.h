#pragma once
#include <vector>
using namespace std;
#include <graphics.h>
#include "Block.h"
class Tetris
{
public:
	Tetris(int rows, int cols, int left, int top, int BlockSize);
	void Init();
	void play();

private:
	void KeyEvent();
	void updatewindow();
	int getDelay();  //返回距离上次调用函数的间隔时间（ms）
	void drop();    //方块下降
	void ClearLine(); //清行

	
private:
	int delay;  //延迟时间
	bool update;  //是否更新

	//int map[20][10];
	// 0: 空白 表示没有任何方块
	// 5：是第五种方块
	vector<vector<int>> map;
	int rows;
	int cols;
	int leftMargin;
	int topMargin;
	int blockSize;
	IMAGE imgBg;

	Block* curBlock;
	Block* nextBlock; //下一个方块
};

