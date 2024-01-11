#include "Tetris.h"
#include <stdlib.h>
#include <time.h>


const int SPEED_NORMAL = 500;  //ms
const int SPEED_QUICK = 50;  //����

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
	//�����������
	srand(time(NULL));

	initgraph(938,896);
	
	//���ر���ͼƬ
	loadimage(&imgBg, "res/bg2.png");

	//��ʼ����Ϸ��������
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

	nextBlock = new Block;
	curBlock = nextBlock;
	nextBlock = new Block;

	int timer = 0;
	while (1) {
      //�����û�����
		KeyEvent();
		timer += getDelay();
		if (timer > delay) {
			timer = 0;
			drop();
			//��Ⱦ��Ϸ����
			update = true;
		}
		if (update) {
			update = false;
			//������Ϸ����
			updatewindow();

			//������Ϸ����
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
	putimage(0, 0, &imgBg);  //����ͼƬ

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (map[i][j] == 0) continue;

			int x = j * blockSize + leftMargin;
			int y = i * blockSize + topMargin;
			putimage(x, y, map[i][j]);
		}
	}

	curBlock->draw(leftMargin, topMargin);
	nextBlock->draw(689, 150);
}

//��һ�ε��ã�����0
//���ؾ�����һ�ε��� ���ʱ�� ms
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
}

void Tetris::ClearLine()
{
}
