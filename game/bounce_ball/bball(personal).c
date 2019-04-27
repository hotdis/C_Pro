#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

void map(int ,int);

int main()
{
	int speedX=2;
	int speedY=2;//定义速度 
	int positionX=5;
	int positionY=5;//定义小球初始位置 
	while(1)
	{	
		system("cls");
		positionX=positionX+speedX;
		positionY=positionY+speedY;//小球位置的改变 
		if(positionX>=29||positionX<=1)speedX*=-1;
		if(positionY>=19||positionY<=1)speedY*=-1;//碰壁是改变速度做到回弹效果 
		map(positionX,positionY);	
	}
	return 0;
}

void map(int X,int Y)//函数确定小球的位置 ； 
{
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<30;j++)
		{
			printf(" ");
			if(X==j&&Y==i)
			{
				printf("。");
			}
		}
		printf("\n");
	}
	Sleep(200);//延时函数； 
}