#include "common.h"

void position(int x, int y) {			//控制光标位置
	COORD loc = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, loc);
}
void drawframe() {						//画出游戏进行的框架
	for (int i = 0; i <= FRAME_WIDTH; i++) {
		position(i, 0);
		cout << "=";
	}
	for (int i = 0; i <= FRAME_WIDTH; i++) {
		position(i, FRAME_HIGHT);
		cout << "=";
	}
	for (int j = 1; j < FRAME_HIGHT; j++) {
		position(0, j);
		cout << "||";
	}
	for (int j = 1; j < FRAME_HIGHT; j++) {
		position(FRAME_WIDTH, j);
		cout << "||";
	}
	position(FRAME_WIDTH + 8, 3);
	cout << "=飞机大战=";
	position(FRAME_WIDTH + 4, 7);
	cout << "左移'A'\t右移'D'";
	position(FRAME_WIDTH + 4, 8);
	cout << "上移'W'\t下移'S'";
	position(FRAME_WIDTH + 4, 9);
	cout << "发子弹:空格键";
	position(FRAME_WIDTH + 8, 13);
	cout << "生命值：5";
	position(FRAME_WIDTH + 10, 15);
	cout << "得分：0";
}
void update(int score, int life) {		//更新生命值和得分
	position(FRAME_WIDTH + 16, 13);
	cout << life;
	position(FRAME_WIDTH + 16, 15);
	cout << score;
}