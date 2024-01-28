#include "Tetris.h"
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 5

const int SPEED_NORMAL[MAX_LEVEL] = { 500,300,150,100,80 };  //ms
const int SPEED_QUICK = 30;  //加速

Tetris::Tetris(int rows, int cols, int left, int top, int BlockSize)
{   //初始化
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
	mciSendString("play res/bg.mp3 repeat", 0, 0, 0);

	delay = SPEED_NORMAL[0];
	//配置随机种子
	srand(time(NULL));

	initgraph(938,896);
	
	//加载背景图片
	loadimage(&imgBg, "res/bg2.png");

	loadimage(&imgWin, "res/win.png");

	loadimage(&imgOver, "res/over.png");

	//初始化游戏区的数据
	char data[20][10]{};
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			map[i][j] = 0;
		}
	}
	score = 0;
	lineCount = 0;
	level = 1;
	ifstream file(RECORDER_FILE);
	if (!file.is_open()) {
		cout << "RECORDER_FILE" << "打开失败" << endl;
		highScore = 0;
	}
	else {
		file >> highScore;
	}
	file.close();  //关闭文件
	//游戏结束的标志
	gameover = false;

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
	
		if (gameover) {
			//保存分数
			SaveScore();
			//更新游戏界面
			displayOver();
			system("pause");
			Init();  //重新开局

		}
	}
}

void Tetris::KeyEvent()
{
  unsigned char ch = 0;   // 0 255
	bool rotateFlag = false;  //是否旋转
	int dx = 0;
	if (_kbhit()) {
		unsigned char ch = _getch();
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
				rotateFlag = true;
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
	if (rotateFlag) {
		//实现旋转
		rotate();
	}
	if (dx != 0) {
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
	drawScore(); //绘制分数

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

		//检测是否结束
		CheckOver();
	}
	delay = SPEED_NORMAL[level-1];
}

void Tetris::ClearLine()
{
	int lines = 0;
	int k = rows - 1;  //存储数据的行数
	for (int i = rows - 1; i >= 0; i--) {
		//检查第i行是否满行
		int count = 0;
		for (int j = 0; j < cols; j++) {
			if (map[i][j]) {
				count++;
			}
			map[k][j] = map[i][j]; //一边扫描一边存储
		}
		if (count < cols) {
			//不是满行
			k--;
		}
		else {
			//满行 count == cols
			lines++;
		}
	}
	if (lines > 0) {
		//计算得分
		int addScore[4] = { 10,30,60,80 };
		score += addScore[lines - 1];
		mciSendString(" play res/xiaochu1.mp3",0,0,0);
		update = true;

		//每100分一个级别 0-100 第一关 101-200第二关
		level = (score + 99) / 100;
		if (lineCount > MAX_LEVEL) {
			gameover = true;
		}
		lineCount += lines;

		
	}
}

void Tetris::MoveLeftRight(int offset)
{
	bakBlock = *curBlock;
	curBlock->moveleftright(offset);
	if (!curBlock->blockInMap(map)) {
		*curBlock = bakBlock;

	}

}

void Tetris::rotate()
{
	if (curBlock->getBlockType() == 7) return;
	bakBlock = *curBlock;
	curBlock->rotate();
	if (!curBlock->blockInMap(map)) {
		*curBlock = bakBlock;

	}
}

void Tetris::drawScore()
{
	char scoreText[32];
	sprintf_s(scoreText, sizeof(scoreText), "%d", score);
	setcolor(RGB(180, 180, 180));
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 55;
	f.lfWeight = 30;
	f.lfQuality = ANTIALIASED_QUALITY; //设置字体为抗锯齿效果
	strcpy_s(f.lfFaceName,sizeof(f.lfFaceName),_T("segoe UI Black"));
	settextstyle(&f);
	setbkmode(TRANSPARENT);  //字体透明效果
	outtextxy(670, 735, scoreText);
	//绘制消除了多少行
	sprintf_s(scoreText, sizeof(scoreText), "%d", lineCount);
	gettextstyle(&f);
	int xPos = 224 - f.lfWeight * strlen(scoreText);
	outtextxy(xPos, 817, scoreText);
	//绘制当前是第几关
	sprintf_s(scoreText, sizeof(scoreText), "%d", level);
	outtextxy(224-30, 727, scoreText);
	//绘制最高分
	sprintf_s(scoreText, sizeof(scoreText), "%d", highScore);
	outtextxy(670, 817, scoreText);

}

void Tetris::CheckOver()
{
	gameover =(curBlock->blockInMap(map) == false);
}

void Tetris::SaveScore()
{
	if (score > highScore) {
		highScore = score;
		ofstream file(RECORDER_FILE);
		file << highScore;
		file.close();
	}
}

void Tetris::displayOver()
{
	mciSendString("stop res/bg.mp3", 0, 0, 0);
	//判断胜利结束还是失败结束
	if (level <= MAX_LEVEL) {
		putimage(262,361,&imgOver);
		mciSendString("play res/over.mp3", 0, 0, 0);

	}
	else{
		putimage(262, 361, &imgWin);
		mciSendString("play res/win.mp3", 0, 0, 0);

	}

}
