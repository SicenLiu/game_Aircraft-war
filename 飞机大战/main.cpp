//#include "common.h"
#include "frame.h"
#include "game.h"

int random(int x) {		//�������0~x֮������֣�����0��x��
	int num = rand();
	num = num % (x - 2);
	return num + 2;
}


int main() {
	//���ع��
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(hOut, &cursor);
	cursor.bVisible = false;
	SetConsoleCursorInfo(hOut, &cursor);

	//��Ϸ׼��
	drawframe();

	//�������봥����Ϸ��ʼ
	position(15, FRAME_HIGHT / 2);
	cout << "���������ʼ��Ϸ";
	while (!_kbhit());
	char ch = _getch();

	//��Ϸ��ʼ
	position(15, FRAME_HIGHT / 2);
	cout << "               ";
	GAME game;
	game.start(0);
	game.play();

	return 0;
}