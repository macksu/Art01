#include "Tetris.h"
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 5

const int SPEED_NORMAL[MAX_LEVEL] = { 500,300,150,100,80 };  //ms
const int SPEED_QUICK = 30;  //����

Tetris::Tetris(int rows, int cols, int left, int top, int BlockSize)
{   //��ʼ��
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
	//�����������
	srand(time(NULL));

	initgraph(938,896);
	
	//���ر���ͼƬ
	loadimage(&imgBg, "res/bg2.png");

	loadimage(&imgWin, "res/win.png");

	loadimage(&imgOver, "res/over.png");

	//��ʼ����Ϸ��������
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
		cout << "RECORDER_FILE" << "��ʧ��" << endl;
		highScore = 0;
	}
	else {
		file >> highScore;
	}
	file.close();  //�ر��ļ�
	//��Ϸ�����ı�־
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
	
		if (gameover) {
			//�������
			SaveScore();
			//������Ϸ����
			displayOver();
			system("pause");
			Init();  //���¿���

		}
	}
}

void Tetris::KeyEvent()
{
  unsigned char ch = 0;   // 0 255
	bool rotateFlag = false;  //�Ƿ���ת
	int dx = 0;
	if (_kbhit()) {
		unsigned char ch = _getch();
		//������·���������Զ����������ַ�
		//������� ���Ϸ���������ȷ��� 224 72
	    //         ����                 224 80
		//         ����                 224 75
		//         ����                 224 77
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
		//ʵ����ת
		rotate();
	}
	if (dx != 0) {
		//ʵ�������ƶ�
		MoveLeftRight(dx);
		update = true;
	}
	
}

void Tetris::updatewindow()
{
	putimage(0, 0, &imgBg);  //����ͼƬ

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
	drawScore(); //���Ʒ���

	EndBatchDraw();
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
	bakBlock = *curBlock;
	curBlock->drop();
	if (!curBlock->blockInMap(map)) {
		//���������̶�
		bakBlock.solidify(map);
		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;

		//����Ƿ����
		CheckOver();
	}
	delay = SPEED_NORMAL[level-1];
}

void Tetris::ClearLine()
{
	int lines = 0;
	int k = rows - 1;  //�洢���ݵ�����
	for (int i = rows - 1; i >= 0; i--) {
		//����i���Ƿ�����
		int count = 0;
		for (int j = 0; j < cols; j++) {
			if (map[i][j]) {
				count++;
			}
			map[k][j] = map[i][j]; //һ��ɨ��һ�ߴ洢
		}
		if (count < cols) {
			//��������
			k--;
		}
		else {
			//���� count == cols
			lines++;
		}
	}
	if (lines > 0) {
		//����÷�
		int addScore[4] = { 10,30,60,80 };
		score += addScore[lines - 1];
		mciSendString(" play res/xiaochu1.mp3",0,0,0);
		update = true;

		//ÿ100��һ������ 0-100 ��һ�� 101-200�ڶ���
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
	f.lfQuality = ANTIALIASED_QUALITY; //��������Ϊ�����Ч��
	strcpy_s(f.lfFaceName,sizeof(f.lfFaceName),_T("segoe UI Black"));
	settextstyle(&f);
	setbkmode(TRANSPARENT);  //����͸��Ч��
	outtextxy(670, 735, scoreText);
	//���������˶�����
	sprintf_s(scoreText, sizeof(scoreText), "%d", lineCount);
	gettextstyle(&f);
	int xPos = 224 - f.lfWeight * strlen(scoreText);
	outtextxy(xPos, 817, scoreText);
	//���Ƶ�ǰ�ǵڼ���
	sprintf_s(scoreText, sizeof(scoreText), "%d", level);
	outtextxy(224-30, 727, scoreText);
	//������߷�
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
	//�ж�ʤ����������ʧ�ܽ���
	if (level <= MAX_LEVEL) {
		putimage(262,361,&imgOver);
		mciSendString("play res/over.mp3", 0, 0, 0);

	}
	else{
		putimage(262, 361, &imgWin);
		mciSendString("play res/win.mp3", 0, 0, 0);

	}

}
