#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<windows.h>

#define MAX_BALLS 4
#define WIDTH 20
#define HEIGHT 10
#define DELAY_TIME 200
#define TURE 1

typedef struct ball{
	int posix;
	int posiy;
	int speedx;
	int speedy;
}BALL,*PBALL;

void start_up(BALL []);
void check_walls(BALL []);
void check_crash(BALL []);
void balls_move(BALL []);
void draw_balls(BALL []);
void brush_balls(BALL []);
void gotoxy(int ,int );

int main(){
	srand((unsigned int)time(0));
	
	BALL balls[MAX_BALLS];
	start_up(balls);
	while(TURE){
		check_walls(balls);
		check_crash(balls);
		balls_move(balls);
		draw_balls(balls);
		Sleep(DELAY_TIME);
		brush_balls(balls);
	}
	
	system("pause");
	return 0;
}

void start_up(BALL balls[]){
	for (int i = 0; i <= WIDTH; i++) {
		gotoxy(i, 0); putchar('#');
		gotoxy(i, HEIGHT); putchar('#');
	}
	for (int i = 0; i <= HEIGHT; i++) {
		gotoxy(0, i); putchar('#');
		gotoxy(WIDTH, i); putchar('#');
	}
	for(int i = 0;i < MAX_BALLS;i++){
		balls[i].posix = rand() % (WIDTH - 2) + 2;	//range : 2 ->WIDTH - 1
		balls[i].posiy = rand() % (HEIGHT - 2) + 2;	//range : 2 -> HEIGHT - 1
		balls[i].speedx = 1;
		balls[i].speedy = 1;
	}
}

void check_walls(BALL balls[]){
	for(int i = 0;i < MAX_BALLS;i++){
		if(balls[i].posix >= WIDTH - 1|| balls[i].posix <= 1){
			balls[i].speedx *= -1;
		}
		if(balls[i].posiy >= HEIGHT  - 1|| balls[i].posiy <= 1){
			balls[i].speedy *= -1;
		}
	}
}

void check_crash(BALL balls[]){
	for(int i = 0;i < MAX_BALLS - 1;i++){
		for(int j = i + 1;j < MAX_BALLS;j++){
			if(balls[i].posix == balls[j].posix && balls[i].posiy == balls[j].posiy){
				balls[i].speedx *= -1;balls[i].speedy *= -1;
				balls[j].speedx *= -1;balls[j].speedy *= -1;
			}
		}
	}
}

void balls_move(BALL balls[]){
	for(int i = 0; i < MAX_BALLS;i++){
		balls[i].posix += balls[i].speedx;
		balls[i].posiy += balls[i].speedy;
	}
}

void draw_balls(BALL balls[]){
	for(int i = 0;i < MAX_BALLS;i++){
		gotoxy(balls[i].posix,balls[i].posiy);
		putchar('*');
	}
}

void brush_balls(BALL balls[]) {
	for (int i = 0; i < MAX_BALLS; i++) {
		gotoxy(balls[i].posix, balls[i].posiy);
		putchar(' ');
	}
}

void gotoxy(int x,int y){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}