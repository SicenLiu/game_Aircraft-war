#include "common.h"

void position(int x, int y) {			//���ƹ��λ��
	COORD loc = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, loc);
}
void drawframe() {						//������Ϸ���еĿ��
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
	cout << "=�ɻ���ս=";
	position(FRAME_WIDTH + 4, 7);
	cout << "����'A'\t����'D'";
	position(FRAME_WIDTH + 4, 8);
	cout << "����'W'\t����'S'";
	position(FRAME_WIDTH + 4, 9);
	cout << "���ӵ�:�ո��";
	position(FRAME_WIDTH + 8, 13);
	cout << "����ֵ��5";
	position(FRAME_WIDTH + 10, 15);
	cout << "�÷֣�0";
}
void update(int score, int life) {		//��������ֵ�͵÷�
	position(FRAME_WIDTH + 16, 13);
	cout << life;
	position(FRAME_WIDTH + 16, 15);
	cout << score;
}