#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct operate {
	char op0;
	char op1;
	int fnum;
	int mnum;
	int lnum;

}OP,*POP;

int get_num_and_op(POP);
void judge(char);

int main(){
	/*Ϊ�ṹ������ڴ� */
	POP pop = (POP)malloc(sizeof(OP));

	/*��ʼ���ṹ���Ա */
	pop->fnum = 0;
	pop->mnum = 0;
	pop->lnum = 0;

	while (1)
	{
		puts("Input operational expression��empty_line to quit��.");
		int result = get_num_and_op(pop);
		printf("The result is : %d\n", result);
		puts("****************************************************");
	}

	system("pause");
	return 0;
}

int get_num_and_op(POP pop){
	char ch;
	int result;

	/*��ʼ����ֵ */
	pop->fnum = 0;
	/*��ȡ��һ��ֵ */
	while ((ch = getchar()) >= '0'&&ch <= '9'){
		pop->fnum = (pop->fnum) * 10 + (ch - '0');
	}
	/*��ȡ��һ������� */
	pop->op0 = ch;

	/********************************************/
	judge(ch);//�ж��Ƿ��˳�
	/********************************************/

	/*��ʼ���м�ֵ */
	pop->mnum = 0;
	/*��ȡ�ڶ���ֵ */
	while ((ch = getchar()) >= '0'&&ch <= '9'){
		pop->mnum = (pop->mnum) * 10 + (ch - '0');
	}
	/*��ȡ�ڶ�������� */
	pop->op1 = ch;

	while (ch != '\n'){
		
		/*��ʼ��βֵ */
		pop->lnum = 0;
		/*��ȡÿ��������βֵ */
		while ((ch = getchar()) >= '0'&&ch <= '9'){
			pop->lnum = (pop->lnum) * 10 + (ch - '0');
		}
		/*��Ϊ+��-�����ǰ�������� */
		if (pop->op1 == '+' || pop->op1 == '-'){
			if (pop->op0 == '+')
				pop->fnum = pop->fnum + pop->mnum;
			else if (pop->op0 == '-')
				pop->fnum = pop->fnum - pop->mnum;
			else if (pop->op0 == '*')
				pop->fnum = pop->fnum * pop->mnum;
			else
				pop->fnum = pop->fnum / pop->mnum;
			/*��β����ֵ���м��� */
			pop->mnum = pop->lnum;
			/*�ѵڶ������������pop->op0 */
			pop->op0 = pop->op1;
		}
		/*��Ϊ*��/����Ѻ��������� */
		else if (pop->op1 == '*'){
			pop->mnum = pop->mnum * pop->lnum;
		}
		else if (pop->op1 == '/'){
			if (pop->lnum == 0) {
				puts("Error");
				system("pause");
				exit(EXIT_FAILURE);
			}
			pop->mnum = pop->mnum / pop->lnum;
		}
		
		/*��ȡ�µ������ */
		pop->op1 = ch;
	}

	/*�ڸ��ݵ�һ�������������������*/
	switch (pop->op0) {
	case '+':
		result = pop->fnum + pop->mnum;
		break;
	case '-':
		result = pop->fnum - pop->mnum;
		break;
	case '*':
		result = pop->fnum * pop->mnum;
		break;
	case '/':
		result = pop->fnum / pop->mnum;
		break;
	}

	return result;
}

void judge(char ch)
{
	if (ch == '\n')
	{
		puts("Done");
		system("pause");
		exit(EXIT_SUCCESS);
	}
}