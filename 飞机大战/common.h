#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <Windows.h>
using namespace std;
#define LIFE 5

#define FRAME_WIDTH 50
#define FRAME_HIGHT 30
#define FRAME_OTHERS 30

#define SLOW 500
#define MID 250
#define FAST 100

#define EASY_MODE 10
#define MID_MODE 20
#define HARD_MODE 30

#define BULLET_BUFFER_SIZE 100
enum LEVEL { LEVEL1 = 1, LEVEL2, LEVEL3, LEVEL4 };