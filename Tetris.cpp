#include "Tetris.h"
#include <stdlib.h>
#include <time.h>
Tetris::Tetris(int rows, int cols, int left, int top, int BlockSize)
{
}

void Tetris::Init()
{

	delay = 30;
	//�����������
	srand(time(NULL));
}

void Tetris::play()
{
	Init();
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
