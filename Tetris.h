#pragma once
#include <vector>
using namespace std;
#include <iostream>
#include <graphics.h>
#include "Block.h"
#include <conio.h>
#include <mmsystem.h>
#include <fstream>
#pragma comment(lib,"winmm.lib")
#define RECORDER_FILE "recorder.txt"

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
	void MoveLeftRight(int offset);
	void rotate();     //旋转
	void drawScore();  //绘制分数
	void CheckOver(); //检查游戏是否结束
	void SaveScore(); //保存分数
	void displayOver(); //更新游戏画面
private:
	int delay;  //延迟时间
	bool update;  //是否更新

	//int map[20][10];
	// 0: 空白 表示没有任何方块
	// 5：是第五种方块
	vector<vector<int>> map;
	int rows = 20;
	int cols = 10;
	int leftMargin;
	int topMargin;
	int blockSize;
	IMAGE imgBg;

	Block* curBlock;
	Block* nextBlock; //预告方块
	Block bakBlock;  //当前方块降落过程中，用来备份上一个合法位置的！
	int score;
	int level;  //当前关卡
	int lineCount;  //当前已经消除了多少行
	int highScore;  //最高分
	bool gameover; //游戏是否已经结束

	IMAGE imgOver;
	IMAGE imgWin;
};

