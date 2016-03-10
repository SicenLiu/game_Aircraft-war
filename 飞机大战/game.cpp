#include <iostream>
#include <Windows.h>
//#include "common.h"
#include "frame.h"
//#include "main.h"
#include "game.h"
using namespace std;

MYBULLET::MYBULLET() {
	pos_x = 0;
	pos_y = 0;
	active = false;
}
void MYBULLET::shoot(int myplane_x, int myplane_y) {
	if (myplane_y != 1) {
		position(myplane_x, myplane_y - 1);
		cout << "^";
		pos_x = myplane_x;
		pos_y = myplane_y - 1;
		active = true;
	}
	else active = false;
}
void MYBULLET::fly() {
	position(pos_x, pos_y);
	cout << " ";
	if (pos_y != 1) {
		pos_y--;
		position(pos_x, pos_y);
		cout << "^";
	}
	else active = false;
}
bool MYBULLET::bullet_is_using() {
	return active;
}
void MYBULLET::restart() {
	position(pos_x, pos_y);
	cout << " ";
	pos_x = 0;
	pos_y = 0;
	active = false;
}
bool MYBULLET::hit(int x, int y) {
	if (pos_x == x){
		if (pos_y == y - 1 || pos_y == y) {
			active = false;
			position(pos_x, pos_y);
			cout << " ";
			return true;
		}
	}
	return false;
}

MYPLANE::MYPLANE() {
	MYPLANE_X = FRAME_WIDTH / 2;
	MYPLANE_Y = FRAME_HIGHT - 3;
	alive = true;
	position(MYPLANE_X, MYPLANE_Y);
	cout << "O";
}
bool MYPLANE::died() {
	return !alive;
}
void MYPLANE::control() {
	if (GetAsyncKeyState(0x41)) {			//'A'
		if (MYPLANE_X != 2) {
			position(MYPLANE_X, MYPLANE_Y);
			cout << " ";
			MYPLANE_X--;
			position(MYPLANE_X, MYPLANE_Y);
			cout << "O";
		}
	}
	if (GetAsyncKeyState(0x44)) {			//'D'
		if (MYPLANE_X != FRAME_WIDTH - 1) {
			position(MYPLANE_X, MYPLANE_Y);
			cout << " ";
			MYPLANE_X++;
			position(MYPLANE_X, MYPLANE_Y);
			cout << "O";
		}
	}
	if (GetAsyncKeyState(0x57)) {			//'W'
		if (MYPLANE_Y != 1) {
			position(MYPLANE_X, MYPLANE_Y);
			cout << " ";
			MYPLANE_Y--;
			position(MYPLANE_X, MYPLANE_Y);
			cout << "O";
		}
	}
	if (GetAsyncKeyState(0x53)) {			//'S'
		if (MYPLANE_Y != FRAME_HIGHT - 1) {
			position(MYPLANE_X, MYPLANE_Y);
			cout << " ";
			MYPLANE_Y++;
			position(MYPLANE_X, MYPLANE_Y);
			cout << "O";
		}
	}
	if (GetAsyncKeyState(VK_SPACE)) {			//空格
		int i = 0;
		while (bullet[i].bullet_is_using()) i++;
		bullet[i].shoot(MYPLANE_X, MYPLANE_Y);
	}
}
void MYPLANE::location(int &x, int &y) {
	x = MYPLANE_X;
	y = MYPLANE_Y;
}
void MYPLANE::killed() {
	position(MYPLANE_X, MYPLANE_Y);
	cout << "X";
	alive = false;
}
void MYPLANE::mybullet_fly() {
	for (int i = 0; i < BULLET_BUFFER_SIZE; i++) {
		if (bullet[i].bullet_is_using())
			bullet[i].fly();
	}
}
void MYPLANE::restart() {
	position(MYPLANE_X, MYPLANE_Y);
	cout << " ";
	for (int i = 0; i < BULLET_BUFFER_SIZE; i++) {
		if (bullet[i].bullet_is_using())
			bullet[i].restart();
	}
	MYPLANE_X = FRAME_WIDTH / 2;
	MYPLANE_Y = FRAME_HIGHT - 3;
	alive = true;
	position(MYPLANE_X, MYPLANE_Y);
	cout << "O";
}
bool MYPLANE::hit_target(int x, int y) {
	for (int i = 0; i < BULLET_BUFFER_SIZE; i++) {
		if (bullet[i].bullet_is_using())
			if (bullet[i].hit(x, y)) return true;
	}
	return false;
}
bool MYPLANE::crash(int enemy_x, int enemy_y) {
	if (enemy_x == MYPLANE_X && enemy_y == MYPLANE_Y) {
		killed();
		return true;
	}
	else return false;
}

ENEMY_BULLET::ENEMY_BULLET() {
	pos_x = 0;
	pos_y = 0;
	active = false;
}
void ENEMY_BULLET::shoot(int enemy_x, int enemy_y) {
	if (enemy_y != FRAME_HIGHT - 1) {
		position(enemy_x, enemy_y + 1);
		cout << "v";
		pos_x = enemy_x;
		pos_y = enemy_y + 1;
		active = true;
	}
	else active = false;
}
void ENEMY_BULLET::fly() {
	position(pos_x, pos_y);
	cout << " ";
	if (pos_y != FRAME_HIGHT - 1) {
		pos_y++;
		position(pos_x, pos_y);
		cout << "v";
	}
	else active = false;
}
bool ENEMY_BULLET::bullet_is_using() {
	return active;
}
void ENEMY_BULLET::restart() {
	position(pos_x, pos_y);
	cout << " ";
	pos_x = 0;
	pos_y = 0;
	active = false;
}
void ENEMY_BULLET::location(int &x, int &y) {
	x = pos_x;
	y = pos_y;
}

ENEMY::ENEMY() {
	pos_x = 0;
	pos_y = 0;
	active = false;
	speed = 4;
	count_enemy = 0;
	level = (LEVEL)0;
}
bool ENEMY::died() {
	return !active;
}
void ENEMY::newenemy(int l) {
	pos_x = random(FRAME_WIDTH);
	pos_y = 1;
	position(pos_x, pos_y);
	cout << "W";
	active = true;
	level = (LEVEL)l;
	speed = (level % 2) ? 4 : 2;
	if (level > 2) shoot();
	count_enemy++;
}
void ENEMY::fly() {
	position(pos_x, pos_y);
	cout << " ";
	if (pos_y != FRAME_HIGHT - 1) {
		pos_y++;
		position(pos_x, pos_y);
		cout << "W";
	}
	else {
		active = false;
	}
	if (count_enemy < (FRAME_HIGHT / 2))
		if (count_enemy % 4 == 0) shoot();
	count_enemy++;
}
void ENEMY::location(int &x, int &y) {
	x = pos_x;
	y = pos_y;
}
void ENEMY::killed() {
	active = false;
	position(pos_x, pos_y);
	cout << " ";
}
void ENEMY::shoot() {
	int i = 0;
	while (bullet[i].bullet_is_using()) i++;
	bullet[i].shoot(pos_x, pos_y + 1);
}
void ENEMY::enemybullet_fly() {
	for (int i = 0; i < BULLET_BUFFER_SIZE; i++) {
		if (bullet[i].bullet_is_using())
			bullet[i].fly();
	}
}
void ENEMY::restart() {
	position(pos_x, pos_y);
	cout << " ";
	for (int i = 0; i < BULLET_BUFFER_SIZE; i++) {
		if (bullet[i].bullet_is_using())
			bullet[i].restart();
	}
	pos_x = 0;
	pos_y = 0;
	active = false;
}
int ENEMY::num_bullet() {
	int num = 0;
	for (int i = 0; i < BULLET_BUFFER_SIZE; i++) {
		if (bullet[i].bullet_is_using())
			num++;
	}
	return num;
}
void ENEMY::bullet_location(int &x, int &y,int k) {
	int j = 0;
	for (int i = 0; i < BULLET_BUFFER_SIZE; i++) {
		if (bullet[i].bullet_is_using()) {
			if (j == k) {
				bullet[i].location(x, y);
				break;
			}
			else j++;
		}
	}
}
void ENEMY::bullet_killed(int k) {
	int j = 0;
	for (int i = 0; i < BULLET_BUFFER_SIZE; i++) {
		if (bullet[i].bullet_is_using()) {
			if (j == k) {
				bullet[i].restart();
				break;
			}
			else j++;
		}
	}
}

GAME::GAME() {
	enemy = NULL;
	num_of_enemy = 0;
	life = 5;
	score = 0;
	game_speed = 15;
}
void GAME::start(int mode) {
	game_speed = (3 - mode) * 5;
	switch (mode) {
	case 0:
		num_of_enemy = EASY_MODE;
		enemy = new ENEMY[EASY_MODE];
	case 1:
		num_of_enemy = MID_MODE;
		enemy = new ENEMY[MID_MODE];
	case 2:
		num_of_enemy = HARD_MODE;
		enemy = new ENEMY[HARD_MODE];
	}
	int life = LIFE;
}
void GAME::hitTarget() {
	int enemy_x, enemy_y;
	int bullet_x, bullet_y;
	for (int i = 0; i < num_of_enemy; i++) {
		if (!enemy[i].died()) {
			enemy[i].location(enemy_x, enemy_y);
			if (myplane.hit_target(enemy_x, enemy_y)) {
				enemy[i].killed();
				score++;
			}
		}
		for (int k = 0; k < enemy[i].num_bullet(); k++) {
			enemy[i].bullet_location(bullet_x, bullet_y, k);
			if (myplane.hit_target(bullet_x, bullet_y)) {
				enemy[i].bullet_killed(k);
				score++;
			}
		}
	}
}
void GAME::playcontinue() {
	for (int i = 0; i < num_of_enemy; i++) {
		enemy[i].restart();
	}
	myplane.restart();
}
void GAME::GAMEover() {
	position(21, FRAME_HIGHT / 2);
	cout << "游戏结束";
	position(19, FRAME_HIGHT / 2 + 2);
}
void GAME::play() {
	int count = 0;
	int myplane_x, myplane_y;
	int enemy_x, enemy_y;
	int bullet_x, bullet_y;
	bool die_once = false;
	int exscore = score;
	int exlife = life;
	update(score, life);	//更新信息
	//主循环
	while (1) {
		if (exscore != score || exlife != life) {
			update(score, life);	//更新信息
			exscore = score;
			exlife = life;
		}
		Sleep(50);
		if (life == 0) {	//生命值为0就gameover
			GAMEover();
			return;
		}
		count++;				//用于计数

		//键盘输入对本机的控制
		myplane.control();

		//判断本机是否被敌机或子弹击中
		myplane.location(myplane_x, myplane_y);
		for (int i = 0; i < num_of_enemy; i++) {
			if (!enemy[i].died()) {
				enemy[i].location(enemy_x, enemy_y);
				if (myplane.crash(enemy_x, enemy_y)) {
					life--;
					enemy[i].killed();
					myplane.killed();  
					playcontinue();
					die_once = true;
					goto L;
				}
			}
			for (int k = 0; k < enemy[i].num_bullet(); k++) {
				enemy[i].bullet_location(bullet_x, bullet_y, k);
				if (myplane.crash(bullet_x,bullet_y)) {
					life--;
					enemy[i].killed();
					myplane.killed();
					playcontinue();
					die_once = true;
					goto L;
				}
			}
		}
	L:	if (die_once) {
			die_once = false;
			continue;
		}

		//每隔一段时间产生新的敌机
		if (count % game_speed == 1) {
			score++;
			int j = 0;
			while (!enemy[j].died() && j != num_of_enemy) j++;
			/*********目前是这个样子的，系统内设敌机的速度，之后会随着游戏的进行而调整*********/
			if (score > 100) {
				if (j != num_of_enemy) enemy[j].newenemy(LEVEL4);
			}
			else if (score > 60) {
				if (j != num_of_enemy) enemy[j].newenemy(LEVEL3);
			}
			else if (score > 30) {
				if (j != num_of_enemy) enemy[j].newenemy(LEVEL2);
			}
			while (!enemy[j].died() && j != num_of_enemy) j++;
			if (j != num_of_enemy) enemy[j].newenemy(LEVEL1);
		}

		//子弹与敌机飞行，判断各子弹是否击中目标
		hitTarget();
		myplane.mybullet_fly();
		for (int i = 0; i < num_of_enemy; i++) {
			if (!enemy[i].died()) {
				if (!(count % enemy[i].speed)) enemy[i].fly();
			}
			enemy[i].enemybullet_fly();
		}
		if (score % 30 == 0) {
			if (game_speed != 5) game_speed--;
		}
	}
}