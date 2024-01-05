#include "Tetris.h"
#include <stdlib.h>
#include <time.h>


const int SPEED_NORMAL = 500;  //ms
const int SPEED_QUICK = 50;  //加速

Tetris::Tetris(int rows, int cols, int left, int top, int BlockSize)
{
	this->rows = rows;
	this->cols = cols;
	this->leftMargin = left;
	this->topMargin = top;
	this->blockSize = blockSize;

	for (int i = 0; i < rows; i++) {
		vector<int> mapRow;
		for (int j = 0; j < cols; j++) {
			mapRow.push_back(0);
		}
		map.push_back(mapRow);
	}
}

void Tetris::Init()
{

	delay = SPEED_NORMAL;
	//配置随机种子
	srand(time(NULL));

	initgraph(938,896);
	
	//加载背景图片
	loadimage(&imgBg, "res/bg2.png");

	//初始化游戏区的数据
	char data[20][10];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			map[i][j] = 0;
		}
	}
}

void Tetris::play()
{
	Init();
	int timer = 0;
	while (1) {
      //接受用户输入
		KeyEvent();
		timer += getDelay();
		if (timer > delay) {
			timer = 0;
			drop();
			//渲染游戏画面
			update = true;
		}
		if (update) {
			update = false;
			//更新游戏画面
			updatewindow();

			//更新游戏数据
			ClearLine();
		}
	
	}
}

void Tetris::KeyEvent()
{
	//to do
}

void Tetris::updatewindow()
{
	putimage(0, 0, &imgBg);  //绘制图片
}

int Tetris::getDelay()
{
	return 0;
}

void Tetris::drop()
{
}

void Tetris::ClearLine()
{
}
