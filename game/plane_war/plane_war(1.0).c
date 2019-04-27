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
//����������ݿ�ܣ�

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
//���ݳ�ʼ����

void playerloadplace()
{
	char a;
	printf("------------------------------\n");
	printf("\n");
	printf("     �ɻ���ս  1 player\n");
	printf("\n");
	printf("       �س�������Ϸ\n");
	printf("\n");
	printf("    level 5�����̬ģʽ\n");
	printf("\n");
	printf("------------------------------\n"); 
	printf("TIP:wsad������������ j���\n");
	printf("TIP:��shiift����������Ϸ\n");
	scanf("%c", &a);
	system("cls");
}
//��¼���棻

void gameover(){
	char over;
	system("cls");
	printf("============================\n");
	printf("\n");
	printf("        GAME OVER\n");
	printf("\n");
	printf("       �س�������Ϸ\n");
	printf("============================\n");
	printf("\n");
	
	scanf("%c",&over);
}
//�������棻

void show() 
{
	int i, j; 
	system("cls");
	for (i = 0; i < high; i++){
		for (j = 0; j < width; j++){
			if (i == position_y && j == position_x){
				if (level < 4){
					printf("*");//���С�ɻ���
				}
				
				if(level>=4){
					printf("^^^");//����ɻ������棻
				}
			}
			if (i == bullet_y && j == bullet_x){
				if (level < 4){
					printf("|");//����ӵ���
				}
				
				if (level >= 4){
					printf("|||");//����ӵ������棻
				}
			}
			if (i == enemy_y && j == enemy_x){
				printf("#");//����л���
			}
			else{
				printf(" ");
			}
		}

		printf("\n");
	}
	printf("HP=%d\n", HP);
	printf("score��%d\n", score);
	printf("level: %d\n", level);
}
//��Ϸ���棻

void updatewithoutputin(){
	bullet_y--;//�ӵ��Զ������˶���
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
	/*�˴��������׳��ֿ���*/
	if (level < 4){
		if (bullet_x == enemy_x && bullet_y == enemy_y){
			enemy_x = rand() % width;//�л�����ϵͳ��
			enemy_y = -1;
			score++;
		}
	}
	if (level == 4 || level == 5){
		if ((bullet_x == enemy_x && bullet_y == enemy_y) || (bullet_x + 1 == enemy_x && bullet_y == enemy_y) || (bullet_x + 2 == enemy_x && bullet_y == enemy_y)){
			enemy_x = rand() % width;//�л�����ϵͳ��
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
	/*���漼�����Կ��Ƶл��½��ٶ�*/
	static int speed = 0;
	if (speed < 24){
		speed++;}
	if (speed == 24){
		enemy_y++;
		speed = 0;
	}
	/*�����н������������һ���ķֲ��������⣿���ɷ�Ϊlevel4��level4һ�£�*/
}
//�����û���������֣�

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
//�����û����벿�ֿ���С�ɻ��ƶ������

void HideCursor(){
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
//���ع�꺯����


/*˼���� 1.��δʵ�ֲ��֣���̨�л����ɻ���ײ�����³��֡���������ӵ�����Ϸ��ͣ
		2.��ʵ�ֲ��֣���½���桢�������桢�����������ϵͳ�������ɻ����ͣ��ӵ����ͣ���ս�ȼ���������ϵͳ
		3.���ӳٵл�����С���ɴ����÷ֶε��´��������쳣���������ΪlevelΪ2����ʱ���л�λ�ò��ı䣬���ڴ˴������ȼ��ֶ�ʱ������
		4.������ຯ�����¼������벻�������������Ż�
		5.ǿ�ҽ�������������Ը���
*/
