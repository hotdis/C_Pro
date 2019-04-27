//重大bug：敌机越界时会产生mapY变成3的情况

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#define emenyNum 5

int arr[15][10] = { 0 };//二维数组内0表示空格，1表示战机，2表示子弹，3表示敌机；
int emenyX[emenyNum], emenyY[emenyNum];
int mapX, mapY;
int positionX, positionY;
int score;
int moveTime;

void gotoxy(int, int);
void startUp();
void gameload();
void show();
void autoUpdata();
void Update();

int main(){
	startUp();
	gameload();
	
	while (1){
		show();
		autoUpdata();
		Update();
	}

	return 0;
}

void gotoxy(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void startUp(){
	mapX = 10, mapY = 15;//初始化边框大小

	positionX = 4;//初始化战机位置；
	positionY = 4;
	arr[positionY][positionX] = 1;

	for (int i = 0; i < emenyNum; i++){
		emenyX[i] = rand() % 10;
		emenyY[i] = rand() % 2;
		arr[emenyY[i]][emenyX[i]] = 3;
	}

	score = 0;//初始化分值
	moveTime = 0;
}
//初始化数值

void gameload()
{
	printf("+================================+\n");
	printf("|            Plane Wars          |\n");
	printf("| move-key : adws, shout key : j |\n");
	printf("|                                |\n");
	printf("+================================+\n");
	getchar();
	system("cls");
}
//登录界面设置

void show(){
	gotoxy(0, 0);
	system("cls");
	for (int i = 0; i < mapY; i++){
		printf("*");
		for (int j = 0; j < mapX; j++){
			switch (arr[i][j]){
			case 0:printf(" "); break;
			case 1:printf("A"); break;
			case 2:printf("!"); break;
			case 3:printf("@"); break;
			default:;
			}
		}
		printf("*\n");
	}
	printf("分数：%d \nmapY：%d\n", score, mapY);
}
//画面显示

void autoUpdata(){
	moveTime++;

	for (int i = 0; i < mapY; i++){
		for (int j = 0; j < mapX; j++){
			if (arr[i][j] == 2){
				arr[i][j] = 0;//子弹上移
				if (i > 0)
					arr[i - 1][j] = 2;

				for (int k = 0; k < emenyNum; k++){
					if (i - 1 == emenyY[k] && j == emenyX[k]){
						arr[i - 1][j] = 0;//敌机和子弹同时消失

						emenyX[k] = rand() % 10;//生成新的敌机
						emenyY[k] = 0;
						arr[emenyY[k]][emenyX[k]] = 3;

						score++;//击中敌机加分
					}
				}
			}
			for (int k = 0; k < emenyNum; k++){
				if (positionX == emenyX[k] && positionY == emenyY[k]){
					printf("游戏结束！\n");
					system("pause");
					exit(0);
				}
				//敌机超出屏幕，重新生成敌机
				if (emenyY[k] > mapY){
					emenyX[k] = rand() % 10;
					emenyY[k] = 0;
					arr[emenyY[k]][emenyX[k]] = 3;
				}

				if (moveTime == 50){
					for (k = 0; k < emenyNum; k++){
						arr[emenyY[k]][emenyX[k]] = 0;//敌机下移
						emenyY[k]++;
						arr[emenyY[k]][emenyX[k]] = 3;
					}
					moveTime = 0;
				}
			}
		}
	}
}
//自动更新

void Update(){
	if (_kbhit()){
		char putin = _getch();
		if (putin == 'a'&&positionX > 0){
			arr[positionY][positionX] = 0;
			positionX--;
			arr[positionY][positionX] = 1;
		}
		else if (putin == 'd'&&positionX < mapX - 1){
			arr[positionY][positionX] = 0;
			positionX++;
			arr[positionY][positionX] = 1;
		}
		else if (putin == 'w'&&positionY > 1){
			arr[positionY][positionX] = 0;
			positionY--;
			arr[positionY][positionX] = 1;
		}
		else if (putin == 's'&&positionY < mapY - 1){
			arr[positionY][positionX] = 0;
			positionY++;
			arr[positionY][positionX] = 1;
		}
		else if (putin == 'j'){
			arr[positionY - 1][positionX] = 2;
		}
		else;
	}
}
//手动更新
