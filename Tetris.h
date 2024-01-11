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
	int getDelay();  //���ؾ����ϴε��ú����ļ��ʱ�䣨ms��
	void drop();    //�����½�
	void ClearLine(); //����

	
private:
	int delay;  //�ӳ�ʱ��
	bool update;  //�Ƿ����

	//int map[20][10];
	// 0: �հ� ��ʾû���κη���
	// 5���ǵ����ַ���
	vector<vector<int>> map;
	int rows;
	int cols;
	int leftMargin;
	int topMargin;
	int blockSize;
	IMAGE imgBg;

	Block* curBlock;
	Block* nextBlock; //��һ������
};

