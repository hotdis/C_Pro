#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>

#define WIDTH 15
#define HEIGHT 25

#define TIME_GO 6000

int lBlock[3][3] = { 0,1,0,0,1,0,0,1,1 };		//左拐子
int rlBlock[3][3] = { 0,1,0,0,1,0,1,1,0 };		//右拐子
int tblock[3][3] = { 1,1,1,0,1,0,0,1,0 };		//T型块
int square[3][3] = { 0,0,0,0,1,1,0,1,1 };		//方块
int bump[3][3] = { 0,1,0,1,1,1,0,0,0 };			//凸块
int linePiece[3][3] = { 0,1,0,0,1,0,0,1,0 };	//长条
int temp[3][3] = { 0 };

//地图布局
int map[HEIGHT][WIDTH] = { 0 }; 

//确定方块中心位置
int xposi = WIDTH / 2;
int yposi = 1;

//方块下落速度
int time_go = TIME_GO;
//刷新方块命令
int flag_stop = 0;
int flag_down = 0;

//分数
int score = 0;

void draw_map();
void start_up();

void update_with_op(char );
void move_lr(int);
int judge_edge(int);
void update_without_op();
int judge_move();
void change_att();

void select_firuge();
void roadin(int [3][3]);

void delete_row();
void move_down(int );

void judge_over();

void change_firuge();

int main() {
	char ch;
	srand((unsigned int)time(0));

	start_up();
	draw_map();
	while (flag_down == 0) {
		xposi = WIDTH / 2;
		yposi = 1;
		select_firuge();

		flag_stop = 0;
		while (flag_stop == 0) {
			if (_kbhit()) {
				ch = _getch();
				if (ch == 'j') {
					change_firuge();
				}
				else if (ch == ' ') {
					getchar();
				}
				else {
					update_with_op(ch);
				}
			}
			update_without_op();
		}
		delete_row();
		judge_over();
	}

	puts("Done.");
	system("pause");
	return 0;
}

//初始化地图
void start_up() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if ((i == HEIGHT - 2)||(i == HEIGHT - 1)||(j == 0)||(j == WIDTH - 1)) {
				map[i][j] = 9;
			}
			else {
				map[i][j] = 0;
			}
		}
	}
}

//绘制地图
void draw_map() {
	system("cls");
	for (int i = 0; i < HEIGHT - 1; i++) {
		for (int j = 0; j < WIDTH; j++) {
			switch (map[i][j]) {
			case 9:printf("■"); break;
			case 0:printf("  "); break;
			case 1:printf("■"); break;
			case 2:printf("■"); break;
			default:;
			}
		}
		putchar('\n');
	}
	printf("SCORE ---- %d \n", score);
	for (int i = 0; i < WIDTH; i++) {
		printf("■");
	}
}

//选择图形
void select_firuge() {
	switch (rand() % 6) {
	case 0:roadin(bump);		break;
	case 1:roadin(lBlock);		break;
	case 2:roadin(rlBlock);		break;
	case 3:roadin(square);		break;
	case 4:roadin(tblock);		break;
	case 5:roadin(linePiece);	break;
	default:;
	}
}

void roadin(int block[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			map[yposi - 1 + i][xposi - 1 + j] = block[i][j];
		}
	}
}

//物块的变形
void change_firuge() {
	int temp[3][3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			temp[i][2 - j] = map[yposi + j - 1][xposi + i - 1];
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			map[yposi - 1 + i][xposi - 1 + j] =temp[i][j];
		}
	}
}

//控制方块的左右移动
void update_with_op(char ch) {
	if (ch == 'a' && judge_edge(-1) == 0) {
		move_lr(-1);
	}
	else if (ch == 'd' && judge_edge(1) == 0) {
move_lr(1);
	}
}

void move_lr(int mve) {
	for (int i = yposi + 1; i >= yposi - 1; i--) {
		if (mve == 1) {
			for (int j = xposi + 1; j >= xposi - 1; j--) {
				if (map[i][j] == 1) {
					map[i][j] = 0;
					map[i][j + 1] = 1;
				}
			}
		}
		else {
			for (int j = xposi - 1; j <= xposi + 1; j++) {
				if (map[i][j] == 1) {
					map[i][j] = 0;
					map[i][j - 1] = 1;
				}
			}
		}
	}
	xposi += mve;
}

int judge_edge(int ix) {
	int flag = 0;
	for (int i = -1; i < 2; i++) {
		if (map[yposi + i][xposi + ix] == 1 && map[yposi + i][xposi + 2 * ix] == 9) {
			flag = 1;
		}
		if (map[yposi + i][xposi + ix] == 9) {
			flag = 1;
		}
		if (map[yposi + i][xposi + ix] == 1 && map[yposi + i][xposi + 2 * ix] == 2) {
			flag = 1;
		}
		if (map[yposi + i][xposi + ix] == 2) {
			flag = 1;
		}
	}
	return flag;
}

//方块的下移
void update_without_op() {
	time_go--;
	if (time_go < 0) {
		if (judge_move() == 0) {
			for (int i = yposi + 1; i >= yposi - 1; i--) {
				for (int j = xposi + 1; j >= xposi - 1; j--) {
					if (map[i][j] == 1) {
						map[i][j] = 0;
						map[i + 1][j] = 1;
					}
				}
			}
			yposi++;
		}
		else {
			flag_stop = 1;
		}
		draw_map();
		time_go = TIME_GO;
	}
}

int judge_move() {
	int flag = 0;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (map[yposi + i][xposi + j] == 1) {
				if (map[yposi + 1 + i][xposi + j] == 2 || map[yposi + 1 + i][xposi + j] == 9) {
					change_att();
					flag = 1;
				}
			}
		}
	}

	return flag;
}

void change_att() {
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (map[yposi + i][xposi + j] == 1) {
				map[yposi + i][xposi + j] = 2;
			}
			else;
		}
	}
}

//清消得分
void delete_row() {
	int i = 0, j = 0;
	for (i = 0; i < HEIGHT; i++) {
		for (j = 1; j < WIDTH - 1; j++) {
			if (map[i][j] != 2){
				break;
			}
		}
		if (j == WIDTH - 1) {
			move_down(i);
			score = score + 10;
		}
	}
}

void move_down(int n) {
	for (int i = n; i > 0; i--) {
		for (int j = 0; j < WIDTH; j++) {
			map[i][j] = map[i - 1][j];
		}
	}
}

//游戏结束
void judge_over() {
	for (int i = 1; i < WIDTH - 1; i++) {
		if (map[0][i] == 2) {
			flag_down = 1;
		}
	}
}