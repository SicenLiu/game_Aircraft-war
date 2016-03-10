#include <iostream>
#include <Windows.h>
#include "common.h"
#include "main.h"
using namespace std;
//�����ӵ����ࣨһ���ӵ���
class MYBULLET {
	int pos_x;
	int pos_y;
	bool active;
public:
	MYBULLET();
	void shoot(int myplane_x, int myplane_y);//�����ӵ�
	void fly();								//�ӵ���ǰ�����С�һ��
	bool bullet_is_using();					//�ж��ӵ��Ƿ�Ϊactive����Ч��
	void restart();							//�������ã���ÿ����ʧһ����ʱ���ã�
	bool hit(int x, int y);					//�ж��ӵ��Ƿ����Ŀ�꣨Ŀ������Ϊ��x��y����
};
//��������
class MYPLANE {
	int MYPLANE_X;
	int MYPLANE_Y;
	bool alive;
	MYBULLET bullet[BULLET_BUFFER_SIZE];//�ӵ���Ա�������ӵ�����
public:
	MYPLANE();
	bool died();						//�жϱ����Ƿ�������
	void control();						//�����command��a��s��w��d��p���Ա������п���
	void location(int &x, int &y);		//�������������
	void killed();						//ɱ����ܷɻ�
	void mybullet_fly();				//����������������Ч�ӵ���ǰ�����С�һ��
	void restart();						//�������ã���ÿ����ʧһ����ʱ���ã�
	bool hit_target(int x, int y);		//����������ӵ�����Ŀ�꣨x��y��
	bool crash(int enemy_x, int enemy_y);//������Ŀ����ײ
};
//�л��ӵ����ࣨһ���ӵ���
class ENEMY_BULLET {
	int pos_x;
	int pos_y;
	bool active;
public:
	ENEMY_BULLET();
	void shoot(int enemy_x, int enemy_y);//�����ӵ�
	void fly();							//�ӵ���ǰ�����С�һ��
	bool bullet_is_using();				//�ж��ӵ��Ƿ�Ϊactive����Ч��
	void restart();						//�������ã���ÿ����ʧһ����ʱ���ã�
	void location(int &x, int &y);
};
//�л�����
class ENEMY {
	int pos_x;
	int pos_y;
	int active;
	ENEMY_BULLET bullet[BULLET_BUFFER_SIZE];//�ӵ���Ա���л��ӵ�����
public:
	int speed;
	int count_enemy;
	LEVEL level;							//�л�����1���л����ٷ��У�2���л����ٷ��У�3���л����ٷ��м��ӵ���4���л����ٷ��м��ӵ�
	ENEMY();
	bool died();							//�жϵл��Ƿ�������
	void newenemy(int l);					//�²���һ���л�
	void fly();								//�л���ǰ�����С�һ��
	void location(int &x, int &y);			//����л�������
	void killed();							//ɱ������л�
	void shoot();							//�л������ӵ�
	void enemybullet_fly();					//����л������������ӵ���ǰ�����С�һ��
	void restart();							////�������ã���ÿ����ʧһ����ʱ���ã�
	int num_bullet();
	void bullet_location(int &x, int &y, int k);
	void bullet_killed(int k);
};
//******��Ϸ����*******
class GAME {
	MYPLANE myplane;
	ENEMY* enemy;		//�л�����ͷָ��
	int num_of_enemy;	//�л���������Ļ���ֵ�������������ڿ�����Ϸ�Ѷȣ�
	int life;			//����ֵ
	int score;			//�÷֣�ÿ����һ�ܵл���һ�֣�����һ�ܵл��ټ�һ�֣�
	int game_speed;
public:
	GAME();
	~GAME() { delete enemy; }
	void start(int mode);//��0���򵥣���1���еȣ���2���ѣ�
	void hitTarget();	//�жϱ����������ӵ��Ƿ�����Ŀ��
	void playcontinue();//����ֵ��Ϊ0���������Ϸ������������������λ��
	bool gameover() { return life == 0; }
	void play();		//��Ϸ����
	void GAMEover();
};