#include <iostream>
#include <Windows.h>
#include "common.h"
#include "main.h"
using namespace std;
//本机子弹的类（一颗子弹）
class MYBULLET {
	int pos_x;
	int pos_y;
	bool active;
public:
	MYBULLET();
	void shoot(int myplane_x, int myplane_y);//发射子弹
	void fly();								//子弹往前“飞行”一步
	bool bullet_is_using();					//判断子弹是否为active（有效）
	void restart();							//重新设置（在每次损失一条命时所用）
	bool hit(int x, int y);					//判断子弹是否击中目标（目标坐标为（x，y））
};
//本机的类
class MYPLANE {
	int MYPLANE_X;
	int MYPLANE_Y;
	bool alive;
	MYBULLET bullet[BULLET_BUFFER_SIZE];//子弹成员：本机子弹数组
public:
	MYPLANE();
	bool died();						//判断本机是否“阵亡”
	void control();						//输入的command（a、s、w、d、p）对本机进行控制
	void location(int &x, int &y);		//输出本机的坐标
	void killed();						//杀死这架飞机
	void mybullet_fly();				//本机发出的所有有效子弹向前“飞行”一步
	void restart();						//重新设置（在每次损失一条命时所用）
	bool hit_target(int x, int y);		//本机发射的子弹击中目标（x，y）
	bool crash(int enemy_x, int enemy_y);//本机与目标相撞
};
//敌机子弹的类（一颗子弹）
class ENEMY_BULLET {
	int pos_x;
	int pos_y;
	bool active;
public:
	ENEMY_BULLET();
	void shoot(int enemy_x, int enemy_y);//发射子弹
	void fly();							//子弹往前“飞行”一步
	bool bullet_is_using();				//判断子弹是否为active（有效）
	void restart();						//重新设置（在每次损失一条命时所用）
	void location(int &x, int &y);
};
//敌机的类
class ENEMY {
	int pos_x;
	int pos_y;
	int active;
	ENEMY_BULLET bullet[BULLET_BUFFER_SIZE];//子弹成员：敌机子弹数组
public:
	int speed;
	int count_enemy;
	LEVEL level;							//敌机级别：1级敌机低速飞行；2级敌机高速飞行；3级敌机低速飞行加子弹；4级敌机高速飞行加子弹
	ENEMY();
	bool died();							//判断敌机是否“阵亡”
	void newenemy(int l);					//新产生一个敌机
	void fly();								//敌机往前“飞行”一步
	void location(int &x, int &y);			//输出敌机的坐标
	void killed();							//杀死这个敌机
	void shoot();							//敌机发射子弹
	void enemybullet_fly();					//这个敌机发出的所有子弹向前“飞行”一步
	void restart();							////重新设置（在每次损失一条命时所用）
	int num_bullet();
	void bullet_location(int &x, int &y, int k);
	void bullet_killed(int k);
};
//******游戏的类*******
class GAME {
	MYPLANE myplane;
	ENEMY* enemy;		//敌机数组头指针
	int num_of_enemy;	//敌机可以在屏幕出现的最大数量（用于控制游戏难度）
	int life;			//生命值
	int score;			//得分（每产生一架敌机加一分，击中一架敌机再加一分）
	int game_speed;
public:
	GAME();
	~GAME() { delete enemy; }
	void start(int mode);//【0】简单；【1】中等；【2】难；
	void hitTarget();	//判断本机发出的子弹是否命中目标
	void playcontinue();//生命值不为0的情况下游戏继续（清屏、本机归位）
	bool gameover() { return life == 0; }
	void play();		//游戏进行
	void GAMEover();
};