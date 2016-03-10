//#include "common.h"
#include "frame.h"
#include "game.h"

int random(int x) {		//随机产生0~x之间的数字（不算0和x）
	int num = rand();
	num = num % (x - 2);
	return num + 2;
}


int main() {
	//隐藏光标
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(hOut, &cursor);
	cursor.bVisible = false;
	SetConsoleCursorInfo(hOut, &cursor);

	//游戏准备
	drawframe();

	//任意输入触发游戏开始
	position(15, FRAME_HIGHT / 2);
	cout << "按任意键开始游戏";
	while (!_kbhit());
	char ch = _getch();

	//游戏开始
	position(15, FRAME_HIGHT / 2);
	cout << "               ";
	GAME game;
	game.start(0);
	game.play();

	return 0;
}