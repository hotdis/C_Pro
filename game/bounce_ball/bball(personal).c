#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

void map(int ,int);

int main()
{
	int speedX=2;
	int speedY=2;//�����ٶ� 
	int positionX=5;
	int positionY=5;//����С���ʼλ�� 
	while(1)
	{	
		system("cls");
		positionX=positionX+speedX;
		positionY=positionY+speedY;//С��λ�õĸı� 
		if(positionX>=29||positionX<=1)speedX*=-1;
		if(positionY>=19||positionY<=1)speedY*=-1;//�����Ǹı��ٶ������ص�Ч�� 
		map(positionX,positionY);	
	}
	return 0;
}

void map(int X,int Y)//����ȷ��С���λ�� �� 
{
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<30;j++)
		{
			printf(" ");
			if(X==j&&Y==i)
			{
				printf("��");
			}
		}
		printf("\n");
	}
	Sleep(200);//��ʱ������ 
}