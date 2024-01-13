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
	char map[20][10];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			map[i][j] = 0;
		}
	}
}

void Tetris::play()
{
	Init();

	nextBlock = new Block;
	curBlock = nextBlock;
	nextBlock = new Block;

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
	char ch;   // 0 255
	bool retateFlag = false;  //是否旋转
	int dx = 0;
	if (_kbhit()) {
		ch = _getch();
		//如果按下方向键，会自动返回两个字符
		//如果按下 向上方向键，会先返回 224 72
	    //         向下                 224 80
		//         向左                 224 75
		//         向右                 224 77
		if (ch == 224) {
			ch = _getch();
			switch (ch)
			{
			case 72:
				retateFlag = true;
				break;
			case 80:
				delay = SPEED_QUICK;
				break;
			case 75:
				dx = -1;
				break;
			case 77:
				dx = 1;
				break;
			default:
				break;
			}
		}
	}
	if (retateFlag) {
		//实现旋转
	}
	if (dx!= 0) {
		//实现左右移动
		MoveLeftRight(dx);
		update = true;
	}
	
}

void Tetris::updatewindow()
{
	putimage(0, 0, &imgBg);  //绘制图片

	IMAGE** imgs = Block::getImages();
	BeginBatchDraw();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (map[i][j] == 0) continue;

			int x = j * blockSize + leftMargin;
			int y = i * blockSize + topMargin;
			putimage(x, y, imgs[map[i][j]-1]);
		}
	}

	curBlock->draw(leftMargin, topMargin);
	nextBlock->draw(689, 150);
	EndBatchDraw();
}

//第一次调用，返回0
//返回距离上一次调用 间隔时间 ms
int Tetris::getDelay()
{
	static unsigned long long lastTime = 0;

	unsigned long long currentTime = GetTickCount();
	if (lastTime == 0) {
		lastTime = currentTime;
		return 0;
	}
	else {
	int ret = 	currentTime - lastTime;
	lastTime = currentTime;
	return ret;
	}
	return 0;
}

void Tetris::drop()
{
	bakBlock = *curBlock;
	curBlock->drop();
	if (!curBlock->blockInMap(map)) {
		//把这个方块固定
		bakBlock.solidify(map);
		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;
	}
	delay = SPEED_NORMAL;
}

void Tetris::ClearLine()
{
}

void Tetris::MoveLeftRight(int offset)
{
	bakBlock = *curBlock;
	curBlock->moveleftright(dx);
	/*if (!curBlock > blockInMap(map)) {
		*curBlock = bakBlock;

	}*/

}
