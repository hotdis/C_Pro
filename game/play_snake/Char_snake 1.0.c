#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<Windows.h>

//地图属性
#define WIDTH		24
#define HEIGHT		18
#define TOPBLANK	4
#define LEFTBLANK	3
#define FENCE		'%'
#define SPACE		' '
//操作属性
#define MV_UP		'w'
#define MV_DOWN		's'
#define MV_LEFT		'a'
#define MV_RIGHT	'd'

typedef struct position {
	int x;
	int y;
}POSI, *PPOSI;

typedef struct snake_node {
	POSI posi;
	char letter;
	struct snake_node *next;
}SNAKE, *PSNAKE;

PSNAKE head;
PSNAKE tail;

typedef struct food {
	POSI posi;
	char letter;
}FOOD, *PFOOD;

FOOD food;

char game_map[HEIGHT + 2][WIDTH + 2 + 1] = { 0 };
int game_over_status = 1;
int error;

//初始化游戏
void initGame();
//绘制地图
void drawMap();
//蛇身
void snakeDir(char);
void snakeMove(int, int);
void nodeCreate(POSI);
int statusCheck(POSI);
//食物的产生
FOOD foodCreate();
//方向的键入
void pressKey(char *);

void gotoxy(int, int);

int main() {
	char key;
	HANDLE hThread;
	unsigned long *p = NULL;

	SetConsoleTitle("PlaySnake 1.0");
	initGame();

	key = 'd';
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)pressKey, &key, 0, p);
	while (game_over_status) {
		drawMap();
		WaitForSingleObject(hThread, 150);
		snakeDir(key);
	}

	gotoxy(LEFTBLANK + WIDTH / 2, TOPBLANK + HEIGHT + 3);
	printf("OVER %d\n", error);
	system("pause");
	return 0;
}

void drawMap() {
	int i;
	for (i = 0; i < HEIGHT + 2; i++) {
		gotoxy(LEFTBLANK, TOPBLANK + i);
		fputs(game_map[i], stdout);
	}
}

void initGame() {
	int i, j;
	for (i = 0; i < HEIGHT + 2; i++) {
		for (j = 0; j < WIDTH + 2; j++) {
			if (0 == i || HEIGHT + 1 == i || 0 == j || WIDTH + 1 == j) {
				game_map[i][j] = FENCE;
			}
			else {
				game_map[i][j] = SPACE;
			}
		}
	}
	//创建蛇的首节点
	head = (PSNAKE)malloc(sizeof(SNAKE));
	head->posi.x = WIDTH  / 2;
	head->posi.y = HEIGHT / 2;
	head->letter = 'A';
	head->next = NULL;
	game_map[head->posi.y][head->posi.x] = head->letter;
	//确定尾节点
	tail = head;
	//创建首个食物
	food.posi.x = rand() % (WIDTH  - 1) + 1;
	food.posi.y = rand() % (HEIGHT - 1) + 1;
	food.letter = 'a';
	game_map[food.posi.y][food.posi.x] = food.letter;
}

void snakeDir(char dir) {
	switch (dir) {
	case MV_UP		: snakeMove( 0,-1); break;
	case MV_DOWN	: snakeMove( 0, 1); break;
	case MV_LEFT	: snakeMove(-1, 0); break;
	case MV_RIGHT	: snakeMove( 1, 0); break;
	}
}

void snakeMove(int x, int y) {
	POSI new_head;
	POSI tail_pos;
	new_head.x = head->posi.x + x;
	new_head.y = head->posi.y + y;

	int flag;
	if (0 > (flag = statusCheck(new_head))) {
		game_over_status = 0;
		return;
	}
	else {
		tail_pos = tail->posi;
		if (1 == flag) {
			nodeCreate(new_head);
			foodCreate();
			game_map[food.posi.y][food.posi.x] = food.letter;
		}

		PSNAKE temp = head;
		POSI every_node[27];
		int i;
		//拷贝所有节点原位置
		for (i = 0; temp != NULL; temp = temp->next, i++) {
			every_node[i] = temp->posi;
		}
		//给与节点新位置
		for (i = 0, temp = head->next; temp != NULL; temp = temp->next, i++) {
			temp->posi = every_node[i];
			game_map[temp->posi.y][temp->posi.x] = temp->letter;
		}
		if (tail_pos.x != food.posi.y || tail_pos.y != food.posi.y) {
			game_map[tail_pos.y][tail_pos.x] = SPACE;
		}
		//补全头部
		head->posi = new_head;
		game_map[head->posi.y][head->posi.x] = head->letter;
	}
}

int statusCheck(POSI pos) {
	//成功
	if (tail->letter == 'Z' + 1) {
		error = -1;
		return -1;
	}
	//蛇头撞墙
	if (FENCE == game_map[pos.y][pos.x]) {
		error = -2;
		return -2;
	}
	//吃自己
	PSNAKE temp = head;
	while (temp != NULL) {
		if (pos.y == temp->posi.y && pos.x == temp->posi.x) {
			error = -3;
			return -3;
		}
		temp = temp->next;
	}
	//吃到了食物
	if (pos.y == food.posi.y && pos.x == food.posi.x) {
		return 1;
	}
	//然而什么也发生
	return 0;
}

void nodeCreate(POSI posi) {
	PSNAKE node = (PSNAKE)malloc(sizeof(SNAKE));
	node->next = NULL;
	node->posi = posi;
	node->letter = tail->letter + 1;
	tail->next = node;
	tail = node;
}

FOOD foodCreate() {
	food.letter++;
	food.posi.x = rand() % (WIDTH  - 5) + 3;
	food.posi.y = rand() % (HEIGHT - 5) + 3;
	
	PSNAKE temp = head;
	while ((temp = temp->next) != NULL) {
		if (temp->posi.y == food.posi.x && temp->posi.x == food.posi.x) {
			food.posi.x = rand() % (WIDTH - 1) + 1;
			food.posi.y = rand() % (HEIGHT - 1) + 1;
			temp = head;
		}
	}

	return food;
}

void pressKey(char *ch) {
	while (game_over_status) {
		*ch = _getch();
		while ('\0' != _getch());
	}
}

void gotoxy(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}