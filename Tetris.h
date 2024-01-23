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
	int getDelay();  //���ؾ����ϴε��ú����ļ��ʱ�䣨ms��
	void drop();    //�����½�
	void ClearLine(); //����
	void MoveLeftRight(int offset);
	void rotate();     //��ת
	void drawScore();  //���Ʒ���
	void CheckOver(); //�����Ϸ�Ƿ����
	void SaveScore(); //�������
	void displayOver(); //������Ϸ����
private:
	int delay;  //�ӳ�ʱ��
	bool update;  //�Ƿ����

	//int map[20][10];
	// 0: �հ� ��ʾû���κη���
	// 5���ǵ����ַ���
	vector<vector<int>> map;
	int rows = 20;
	int cols = 10;
	int leftMargin;
	int topMargin;
	int blockSize;
	IMAGE imgBg;

	Block* curBlock;
	Block* nextBlock; //Ԥ�淽��
	Block bakBlock;  //��ǰ���齵������У�����������һ���Ϸ�λ�õģ�
	int score;
	int level;  //��ǰ�ؿ�
	int lineCount;  //��ǰ�Ѿ������˶�����
	int highScore;  //��߷�
	bool gameover; //��Ϸ�Ƿ��Ѿ�����

	IMAGE imgOver;
	IMAGE imgWin;
};

