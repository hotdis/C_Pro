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
	/*为结构体分配内存 */
	POP pop = (POP)malloc(sizeof(OP));

	/*初始化结构体成员 */
	pop->fnum = 0;
	pop->mnum = 0;
	pop->lnum = 0;

	while (1)
	{
		puts("Input operational expression（empty_line to quit）.");
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

	/*初始化首值 */
	pop->fnum = 0;
	/*获取第一个值 */
	while ((ch = getchar()) >= '0'&&ch <= '9'){
		pop->fnum = (pop->fnum) * 10 + (ch - '0');
	}
	/*获取第一个运算符 */
	pop->op0 = ch;

	/********************************************/
	judge(ch);//判断是否退出
	/********************************************/

	/*初始化中间值 */
	pop->mnum = 0;
	/*获取第二个值 */
	while ((ch = getchar()) >= '0'&&ch <= '9'){
		pop->mnum = (pop->mnum) * 10 + (ch - '0');
	}
	/*获取第二个运算符 */
	pop->op1 = ch;

	while (ch != '\n'){
		
		/*初始化尾值 */
		pop->lnum = 0;
		/*获取每次运算后的尾值 */
		while ((ch = getchar()) >= '0'&&ch <= '9'){
			pop->lnum = (pop->lnum) * 10 + (ch - '0');
		}
		/*若为+或-号则把前两项运算 */
		if (pop->op1 == '+' || pop->op1 == '-'){
			if (pop->op0 == '+')
				pop->fnum = pop->fnum + pop->mnum;
			else if (pop->op0 == '-')
				pop->fnum = pop->fnum - pop->mnum;
			else if (pop->op0 == '*')
				pop->fnum = pop->fnum * pop->mnum;
			else
				pop->fnum = pop->fnum / pop->mnum;
			/*把尾数的值给中间数 */
			pop->mnum = pop->lnum;
			/*把第二个运算符给与pop->op0 */
			pop->op0 = pop->op1;
		}
		/*若为*或/号则把后两项运算 */
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
		
		/*获取新的运算符 */
		pop->op1 = ch;
	}

	/*在根据第一个运算符进行最后的运算*/
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