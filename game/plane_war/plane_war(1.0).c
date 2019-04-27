#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>

int position_x,position_y;
int high, width;
int bullet_x, bullet_y;
int enemy_x,enemy_y;
int score;
static int level;
static int HP;
int gameovernumber;
//定义基本数据框架；

void gotoxy(int ,int );
void startup();
void playerloadplace();
void gameover();
void show();
void updatewithoutputin();
void updatewithputin();
void HideCursor();


int main(void){
	startup();
	playerloadplace();

	while (gameovernumber == 0)	{
		show();
		updatewithoutputin();
		updatewithputin();
		HideCursor();
	}
	gameover();
	return 0;
}

void gotoxy(int x, int y){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void startup(){
	high = 20;
	width = 20;
	position_x=5;
	position_y=15;
	bullet_x = position_x;
	bullet_y = -1;
	enemy_x = position_x;
	enemy_y = -1;
	score = 0;
	level = 1;
	HP = 5;
}
//数据初始化；

void playerloadplace()
{
	char a;
	printf("------------------------------\n");
	printf("\n");
	printf("     飞机大战  1 player\n");
	printf("\n");
	printf("       回车进入游戏\n");
	printf("\n");
	printf("    level 5进入变态模式\n");
	printf("\n");
	printf("------------------------------\n"); 
	printf("TIP:wsad控制上下左右 j射击\n");
	printf("TIP:按shiift即可正常游戏\n");
	scanf("%c", &a);
	system("cls");
}
//登录界面；

void gameover(){
	char over;
	system("cls");
	printf("============================\n");
	printf("\n");
	printf("        GAME OVER\n");
	printf("\n");
	printf("       回车结束游戏\n");
	printf("============================\n");
	printf("\n");
	
	scanf("%c",&over);
}
//结束界面；

void show() 
{
	int i, j; 
	system("cls");
	for (i = 0; i < high; i++){
		for (j = 0; j < width; j++){
			if (i == position_y && j == position_x){
				if (level < 4){
					printf("*");//输出小飞机；
				}
				
				if(level>=4){
					printf("^^^");//输出飞机升级版；
				}
			}
			if (i == bullet_y && j == bullet_x){
				if (level < 4){
					printf("|");//输出子弹；
				}
				
				if (level >= 4){
					printf("|||");//输出子弹升级版；
				}
			}
			if (i == enemy_y && j == enemy_x){
				printf("#");//输出敌机；
			}
			else{
				printf(" ");
			}
		}

		printf("\n");
	}
	printf("HP=%d\n", HP);
	printf("score：%d\n", score);
	printf("level: %d\n", level);
}
//游戏界面；

void updatewithoutputin(){
	bullet_y--;//子弹自动向上运动；
	if (score == 5){
		level++;
		score++;
	}
	if (score == 10){
		level++;
		score++;
	}
	if (score == 15){
		level++;
		score++;
	}
	if (score == 30){
		level++;
		score++;
	}
	/*此处代码容易出现卡顿*/
	if (level < 4){
		if (bullet_x == enemy_x && bullet_y == enemy_y){
			enemy_x = rand() % width;//敌机生成系统；
			enemy_y = -1;
			score++;
		}
	}
	if (level == 4 || level == 5){
		if ((bullet_x == enemy_x && bullet_y == enemy_y) || (bullet_x + 1 == enemy_x && bullet_y == enemy_y) || (bullet_x + 2 == enemy_x && bullet_y == enemy_y)){
			enemy_x = rand() % width;//敌机生成系统；
			enemy_y = -1;
			score++;
		}
	}

	if (enemy_y > high || (enemy_x == position_x && enemy_y == position_y)){
		enemy_x = rand() % width;
		enemy_y = -1;
		HP--;
		if (HP <= 0){
			gameovernumber = 1;
		}
	}
	/*下面技巧用以控制敌机下降速度*/
	static int speed = 0;
	if (speed < 24){
		speed++;}
	if (speed == 24){
		enemy_y++;
		speed = 0;
	}
	/*从运行结果看可能是这一步的分步出了问题？不可分为level4和level4一下？*/
}
//更新用户非输出部分；

void updatewithputin(){
	if (_kbhit()){
		char putin;
		putin = _getch();
		if (position_x >= width){
			position_x--;
		}
		if (position_x < 0){
			position_x++;
		}
		if (position_y >= high){
			position_y--;
		}
		if (position_y < 0){
			position_y++;
		}
		if (putin == 'a'){
			position_x--;
		}
		if (putin == 'd'){
			position_x++;
		}
		if (putin == 's'){
			position_y++;
		}
		if (putin == 'w'){
			position_y--;
		}
		if (putin == 'j'){
			bullet_y = position_y - 1;
			bullet_x = position_x;
		}
	}
	
}
//更新用户输入部分控制小飞机移动射击；

void HideCursor(){
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
//隐藏光标函数；


/*思考： 1.尚未实现部分：多台敌机、飞机被撞后重新出现、更好玩的子弹、游戏暂停
		2.已实现部分：登陆界面、结束界面、不成熟的升级系统（包括飞机机型，子弹类型，挑战等级）、生命系统
		3.在延迟敌机下落小技巧处设置分段导致代码运行异常，具体表现为level为2已上时，敌机位置不改变，当在此处消除等级分段时问题解决
		4.加入过多函数导致键盘输入不灵敏，可以有优化
		5.强烈建议加入数组用以改善
*/
