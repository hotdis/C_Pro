#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>

//整个地图的长宽
#define WIDTH 8
#define HEIGHT 8

//整个关卡的描述
void describe();
//从不同关卡重置一个地图
void start_up(int level);
//移动判断函数
void move_and_push(char );
//移动操作函数
void move(int, int, int);
//绘制地图
void draw_map();
//判断目标点是否被占用
void judge_target();
//游戏结束判定
int game_done();

//关卡
int **level_00(int );
void HideCursor();

//中间地图，从原始地图获取值
int map[10][10];
//定义人物位置
int posi_x = 5, posi_y = 5;
//定义箱子和目标的个数
int _tar = 0;
//存储目标的位置
struct target {
	int x;
	int y;
}*ptar;

enum attubite{space, wall, target, box, human};

int main() {
	int level = 1;
	//关卡数
	describe();

	while (level < 3) {
		_tar = 0;

		start_up(level);
		draw_map();
		printf("level_%d\n", level);

		while (1 == game_done()) {
			HideCursor();
			//隐藏光标
			if (_kbhit()) {
				char ch = _getch();
				//上帝隐藏按键，直接下一关
				if (ch == 'q') {
					break;
				}
				//上帝隐藏按键，重开关卡
				else if(ch == ' ') {
					level--;
					break;
				}
				else {
					move_and_push(ch);
					judge_target();
					draw_map();
					printf("level_%d\n", level);
				}
			}
		}
		free(ptar);
		level++;
	}
	puts("Done");

	system("pause");
	return 0;
}

void describe() {
	system("title push_box");
	system("mode con cols=40 lines=11");
	puts("+====================================+");
	puts("|Push_box:describe -> ○ is you.      |");
	puts("|                  -> ★ is box.      |");
	puts("|                  -> ☆ is target.   |");
	puts("|                  -> ■ is wall.     |");
	puts("+====================================+");
	puts("|>>>>>press any key to continue.<<<<<|");
	puts("+====================================+");
	getchar();
	system("cls");
}

//绘制地图，构建边界
void start_up(int level) {
	
	//1表示墙体，2表示目标，3表示箱子, 4表示人
	int(*map_00)[WIDTH] = (int(*)[WIDTH])level_00(level);

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			map[i][j] = *(*(map_00 + i) + j);
			if (map[i][j] == target) {
				//目的在于无论多少个箱子都可以实现
				if (_tar == 0) {
					ptar = (struct target *)malloc(sizeof(struct target));
					ptar->x = j; ptar->y = i;
					_tar++;
				}
				else {
					ptar = (struct target *)realloc(ptar,sizeof(struct target)*(_tar + 1));
					(ptar + _tar)->x = j; (ptar + _tar)->y = i;
					_tar++;
				}
			}
			else if (map[i][j] == human) {
				posi_x = j;
				posi_y = i;
			}
			else;
		}
	}
	
}

void draw_map() {
	system("cls");
	
	int temp;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			temp = map[i][j];
			if (temp == wall) {
				printf("■");
				//putchar('#');
			}
			else if (temp == target) {
				printf("☆");
				//putchar('o');
			}
			else if (temp == box) {
				printf("★");
				//putchar('*');
			}
			else if (temp == human) {
				printf("○");
				//putchar('@');
			}
			else {
				printf("  ");
				//putchar(' ');
			}
		}
		putchar('\n');
	}
}

//移动刷新
void move_and_push(char ch) {	
	if (ch == 'a'&&map[posi_y][posi_x - 1] != wall) {
		if (map[posi_y][posi_x - 1] == box) {
			if (map[posi_y][posi_x - 2] != wall&&map[posi_y][posi_x - 2] != box) {
				move(0, -1, 1);
			}
		}
		else {
			move(0, -1, 0);
		}
	}
	else if (ch == 'd'&&map[posi_y][posi_x + 1] != wall) {
		if (map[posi_y][posi_x + 1] == box) {
			if (map[posi_y][posi_x + 2] != wall&&map[posi_y][posi_x + 2] != box) {
				move(0, 1, 1);
			}
		}
		else {
			move(0, 1, 0);
		}
	}
	else if (ch == 'w'&&map[posi_y - 1][posi_x] != wall) {
		if (map[posi_y - 1][posi_x] == box) {
			if (map[posi_y - 2][posi_x] != wall&& map[posi_y - 2][posi_x] != box) {
				move(-1,0,1);
			}
		}
		else {
			move(-1, 0, 0);
		}

	}
	else if (ch == 's'&&map[posi_y + 1][posi_x] != wall) {
		if (map[posi_y + 1][posi_x] == box) {
			if (map[posi_y + 2][posi_x] != wall&& map[posi_y + 2][posi_x] != box) {
				move(1, 0, 1);
			}
		}
		else {
			move(1, 0, 0);
		}
	}
	
}

//因为老是重复这段代码，所以编成了一个函数
//移动函数
void move(int i, int j, int flag) {
	map[posi_y][posi_x] = space;
	posi_y += i;
	posi_x += j;
	map[posi_y][posi_x] = human;
	if (flag == 1) {
		map[posi_y + i][posi_x + j] = box;
	}
}

//箱子到达目标
void judge_target() {
	for (int i = 0; i < _tar; i++) {
		if (map[(ptar + i)->y][(ptar + i)->x] == space) {
			map[(ptar + i)->y][(ptar + i)->x] = target;
		}
	}
}

//完结条件
int game_done() {
	int flag = 1, i = 0;
	for (; i < _tar; i++) {
		if (map[(ptar + i)->y][(ptar + i)->x] != box) {
			break;
		}
	}
	if (i == _tar) {
		flag = 0;
	}

	return flag;
}
//不同关卡的保存
int** level_00(int level) {
	int **temp = NULL;

	if (level == 1) {
		static int map01[HEIGHT][WIDTH] = {
		0,0,1,1,1,0,0,0,
		0,0,1,2,1,0,0,0,
		0,0,1,0,1,1,1,1,
		1,1,1,3,0,3,2,1,
		1,2,0,3,4,1,1,1,
		1,1,1,1,3,1,0,0,
		0,0,0,1,2,1,0,0,
		0,0,0,1,1,1,0,0,
		};
		temp = (int **)map01;
	}
		
	else if (level == 2) {
		static int map02[HEIGHT][WIDTH] = {
		1,1,1,1,1,1,1,1,
		1,0,0,0,0,1,2,1,
		1,0,3,4,0,1,2,1,
		1,0,3,3,1,1,2,1,
		1,1,1,0,0,0,0,1,
		0,1,0,0,0,0,0,1,
		0,1,0,0,0,0,1,1,
		0,1,1,1,1,1,1,0,
		};
		temp = (int **)map02;
	}

	return temp;
}

//光标隐藏函数
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
