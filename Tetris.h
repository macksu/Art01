#pragma once
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
};

