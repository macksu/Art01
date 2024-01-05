#include "Block.h"
#include <stdlib.h>

Block::Block()
{
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
		int value = blocks[blockType][i];
		SmallBlocks[i].row = value / 2;
		SmallBlocks[i].col = value % 2;
	}
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
}
