#include "Block.h"
#include <stdlib.h>

IMAGE* Block::imgs[7] = { NULL, };
int Block::Size = 36;

Block::Block()
{
	if (imgs[0] == NULL) {
		IMAGE imgTmp;
		loadimage(&imgTmp, "res/tiles.png");
		SetWorkingImage(&imgTmp);
		for (int i = 0; i < 7; i++) {
			imgs[i] = new IMAGE;
			getimage(imgs[i], i * Size, 0, Size, Size);

		}
		SetWorkingImage();  //恢复图片工作区
	}
   int blocks[7][4] = {
	   1,3,5,7, //I
	   2,4,5,7, //Z 1型
	   3,5,4,6, //Z 2型
	   3,5,4,7, //T
	   2,3,5,7, //L
	   3,5,7,6, //J
	   2,3,4,5, //田
	};

	//随机生成一种俄罗斯方块
	blockType = 1 + rand() % 7;  // 1 到 7
	//初始化SmallBlocks
	for (int i = 0; i < 4; i++) {
		int value = blocks[blockType-1][i];
		SmallBlocks[i].row = value / 2;
		SmallBlocks[i].col = value % 2;
	}
	img = imgs[blockType - 1];
}

void Block::drop()
{

}

void Block::moveleftright()
{
}

void Block::retate()
{
}

void Block::draw(int leftMargin, int topMargin)
{
	for (int i = 0; i < 4; i++) {
		int x = leftMargin + SmallBlocks[i].col * Size;
		int y = topMargin +  SmallBlocks[i].row * Size;
		putimage(x, y, img);
	}
}
