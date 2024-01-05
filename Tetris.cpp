#include "Tetris.h"
#include <stdlib.h>
#include <time.h>
Tetris::Tetris(int rows, int cols, int left, int top, int BlockSize)
{
}

void Tetris::Init()
{

	delay = 30;
	//配置随机种子
	srand(time(NULL));
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
