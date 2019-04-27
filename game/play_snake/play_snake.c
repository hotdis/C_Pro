#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<Windows.h>

#define WIDTH 30
#define HEIGHT 25
#define SNA_LEN_MAX WIDTH * HEIGHT
#define SPD_DLY 2500

static int nodeNumber = 0;
static int spd = SPD_DLY;

struct snake {
	int xposi;
	int yposi;
}snake[SNA_LEN_MAX];

struct food {
	int xposi;
	int yposi;
}food;

void start_up();
void draw_walls();

void snake_auto_move(char);
void create_food();
void eat_food(char);

void snake_turn_direction(char *, char);

int game_over();

void gotoxy(int, int);
void take_move();
void add_head();
void clear_tail();
void check();

int main() {
	char ch = 'd', direction = 'd';
	int flag = 1;
	
	start_up();
	while (flag != 0&&ch != 'q') {
		if (_kbhit()) {
			ch = _getch();
			snake_turn_direction(&direction, ch);
			flag = game_over();
			eat_food(direction);
			check();
			while (_getch() != '\0');
		}
		snake_auto_move(direction);
		flag = game_over();
		eat_food(direction);
		check();
	}
	gotoxy(0, HEIGHT + 2);
	puts("Done.");
	system("pause");
	return 0;
}

//初始化数据以及地图
void start_up() {
	srand((unsigned int)time(0));
	nodeNumber = 3;
	for (int i = 0; i < nodeNumber; i++) {
		snake[i].xposi = WIDTH / 2 + - 3 + i;
		snake[i].yposi = HEIGHT / 2;
	}
	draw_walls();
	create_food();
}

void draw_walls() {
	for (int i = 0; i < WIDTH + 1; i++) {
		gotoxy(i, 0);
		putchar('#');
		gotoxy(i, HEIGHT + 1);
		putchar('#');
	}
	for (int j = 0; j < HEIGHT + 1; j++) {
		gotoxy(0, j);
		putchar('#');
		gotoxy(WIDTH + 1, j);
		putchar('#');
	}
}

//自动操作（蛇的移动以及食物的生成）
void snake_auto_move(char direction) {
	spd--;
	if (spd <= 0) {
		spd = SPD_DLY;
		clear_tail();
		if (direction == 'd') {
			take_move();
			snake[nodeNumber - 1].xposi += 1;
		}
		else if (direction == 'a') {
			take_move();
			snake[nodeNumber - 1].xposi -= 1;
		}
		else if (direction == 's') {
			take_move();
			snake[nodeNumber - 1].yposi += 1;
		}
		else if (direction == 'w') {
			take_move();
			snake[nodeNumber - 1].yposi -= 1;
		}
		else {
			puts("Error");
			getchar();
		}
		add_head();
	}
}

void create_food() {
	food.xposi = rand() % WIDTH + 1;
	food.yposi = rand() % HEIGHT + 1;
	for (int j = 0; j < nodeNumber; j++) {
		if (food.xposi == snake[j].xposi&&food.yposi == snake[j].yposi) {
			j--;
			food.xposi = rand() % WIDTH + 1;
			food.yposi = rand() % HEIGHT + 1;
		}
	}
	gotoxy(food.xposi, food.yposi);
	putchar('@');
	
}

void eat_food(char direction) {
	int x, y;
	switch (direction) {
	case 'd':x = 1; y = 0; break;
	case 'a':x = -1; y = 0; break;
	case 's':x = 0; y = 1; break;
	case 'w':x = 0;y = -1; break;
	}

	if (snake[nodeNumber - 1].xposi == food.xposi&&snake[nodeNumber - 1].yposi == food.yposi) {
		nodeNumber++;
		snake[nodeNumber - 1].xposi = food.xposi + x;
		snake[nodeNumber - 1].yposi = food.yposi + y;
		gotoxy(snake[nodeNumber - 1].xposi, snake[nodeNumber - 1].yposi);
		putchar('*');
		create_food(1);
	}

}

//手动操作（蛇的转向）
void snake_turn_direction(char *direction, char ch) {
	if (ch == 'd'&&*direction != 'a') {
		take_move();
		snake[nodeNumber - 1].xposi += 1;
		*direction = ch;
	}
	else if (ch == 'a'&&*direction != 'd') {
		take_move();
		snake[nodeNumber - 1].xposi -= 1;
		*direction = ch;
	}
	else if (ch == 's'&&*direction != 'w') {
		take_move();
		snake[nodeNumber - 1].yposi += 1;
		*direction = ch;
	}
	else if (ch == 'w'&&*direction != 's') {
		take_move();
		snake[nodeNumber - 1].yposi -= 1;
		*direction = ch;
	}
	else;
	add_head();
}

//结束判定
int game_over() {
	int flag = 1;
	for (int i = 0; i < nodeNumber - 1; i++) {
		if (snake[nodeNumber - 1].xposi == snake[i].xposi && snake[nodeNumber - 1].yposi == snake[i].yposi) {
			flag = 0;
		}
	}
	if (snake[nodeNumber - 1].xposi <= 0||snake[nodeNumber - 1].xposi >= WIDTH + 1||snake[nodeNumber - 1].yposi <= 0||snake[nodeNumber - 1].yposi >= HEIGHT + 1) {
		flag = 0;
	}
	return flag;
}

//辅助函数
void gotoxy(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void take_move() {
	clear_tail();
	for (int i = 0; i < nodeNumber - 1; i++) {
		snake[i].xposi = snake[i + 1].xposi;
		snake[i].yposi = snake[i + 1].yposi;
	}
}

void add_head() {
	gotoxy(snake[nodeNumber - 1].xposi, snake[nodeNumber - 1].yposi);
	putchar('*');
}

void clear_tail() {
	gotoxy(snake[0].xposi, snake[0].yposi);
	putchar(' ');
}

void check() {
	gotoxy(WIDTH + 4, 0);
	printf("(%d,%d,%d)", snake[nodeNumber - 1].xposi, snake[nodeNumber - 1].yposi,nodeNumber);
}
