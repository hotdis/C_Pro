#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define FALSE 1
#define TURE  0
#define SPACE (' ')

const int out_stack_priority[7] = { 1, 1, 2, 2, 9, 9 }; //+-*/()
const int in_stack_priority[7] = { 1, 1, 2, 2, 0, 9 };

void __pushDo(double[], int *, double);
double __popDo(double[], int *);
double operationFunc(double, double, char);

//中缀表达式转换为后缀表达式
int toProfixEx(char[], char[]);
//运算符入栈
void __pushEx(char[], int *, char);
//运算符出栈
char __popEx(char[], int *);

int isOperator(char);
int isEmptyS(char[], int);
char topStack(char[], int);
//比较 运算符优先级
int cmpPrior(char, char);

int charToNum(char);
char *s_gets(char *, int);


int main() {
	char expr[512], profix[512], *str;
	double v_stack[512], result;
	int v_top = -1;

	puts("Please enter an expression(# to quit)");
	while(NULL != s_gets(expr, 512) && '#' != expr[0]){
		if (FALSE == toProfixEx(profix, expr)) {
			exit(1);
		}
	
		printf("Profixexpression >> %s\n", profix);
	
		str = strtok(profix, " ");
		while (NULL != str) {
			if (0 != isdigit(*str)) {
				__pushDo(v_stack, &v_top, atof(str));
			}
			else {
				double val1 = __popDo(v_stack, &v_top);
				double val2 = __popDo(v_stack, &v_top);
				__pushDo(v_stack, &v_top, operationFunc(val2, val1, *str));
			}
			str = strtok(NULL, " ");
		}
		result = __popDo(v_stack, &v_top);
		printf("Result >> %.3lf \n", result);
		puts("=======================================");
		puts("Please enter an expression(# to quit)");
	}
	
	puts("Done");
	system("pause");
	return 0;
}

void __pushDo(double stack[], int *top, double val) {
	if (*top >= 512) {
		exit(1);
	}

	stack[++(*top)] = val;
}

double __popDo(double stack[], int *top) {
	if (*top < -1) {
		exit(1);
	}

	return stack[(*top)--];
}

double operationFunc(double val1, double val2, char op) {
	switch (op) {
	case '+':return val1 + val2; break;
	case '-':return val1 - val2; break;
	case '*':return val1 * val2; break;
	case '/':if (0 == val2) exit(1); return val1 / val2; break;
	default:exit(1);
	}
}

//中缀expr 转换为并保存在 后缀profix 中
int toProfixEx(char profix[], char expr[]) {
	static char c_stack[1024];		//运算符栈
	static int c_top = -1;
	
	char op;						//保存 弹栈的 运算符

	char *psrc = expr;
	char *pdes = profix;
	
	if (NULL == profix || NULL == expr) {
		return FALSE;
	}

	while (*psrc != '\0') {
		if (0 != isdigit(*psrc) || '.' == *psrc) {
			*pdes++ = *psrc;
		}
		else if (TURE == isOperator(*psrc)) {
			if ('(' != *psrc) {
				*pdes++ = SPACE;
			}
			
			//栈空时 入栈
			if (TURE == isEmptyS(c_stack, c_top)) {
				__pushEx(c_stack, &c_top, *psrc);
			}

			else {
				if (')' == *psrc) {
					//一直弹栈直到 左括号
					while ('(' != (op = __popEx(c_stack, &c_top))) {
						*pdes++ = op;
						*pdes++ = SPACE;
					}
				}
				else {
					//运算符优先级比较 若优先级大于栈顶则入栈 小于则一直出栈 直到大于或者栈空
					int cmp = cmpPrior(*psrc, topStack(c_stack, c_top));
					if (cmp > 0) {
						__pushEx(c_stack, &c_top, *psrc);
					}
					else {
						while (TURE != isEmptyS(c_stack, c_top) && cmp <= 0) {
							op = __popEx(c_stack, &c_top);
							*pdes++ = op;
							*pdes++ = SPACE;
							cmp = cmpPrior(*psrc, topStack(c_stack, c_top));
						}
						__pushEx(c_stack, &c_top, *psrc);
					}
				}
			}
		}
		else {
			return FALSE;
		}
		psrc++;
	}

	//处理栈中剩余 元素
	while (TURE != isEmptyS(c_stack, c_top)) {
		*pdes++ = SPACE;
		*pdes++ = __popEx(c_stack, &c_top);
	}

	*pdes = '\0';
	return TURE;
}

int isOperator(char ch) {
	if (0 != strchr("+-*/()", ch)) {
		return TURE;
	}
	else {
		return FALSE;
	}
}

void __pushEx(char stack[], int *top, char ch) {
	if (*top >= 1024) {
		exit(1);
	}
	stack[++(*top)] = ch;
}

char __popEx(char stack[], int *top) {
	if (*top < 0) {
		exit(1);
	}
	return stack[(*top)--];
}

int isEmptyS(char stack[], int top) {
	if (top == -1) {
		return TURE;
	}
	else if (top < -1) {
		exit(1);
	}
	else {
		return FALSE;
	}
}

char topStack(char stack[], int top) {
	return stack[top];
}

int cmpPrior(char ch1, char ch2) {
	return out_stack_priority[charToNum(ch1)] - in_stack_priority[charToNum(ch2)];
}

int charToNum(char ch) {
	switch (ch) {
	case '+': return 0; break;
	case '-': return 1; break;
	case '*': return 2; break;
	case '/': return 3; break;
	case '(': return 4; break;
	case ')': return 5; break;
	default: return -1; break;
	}
}

char *s_gets(char *str, int size) {
	char *p = fgets(str, size, stdin);
	if (p) {
		while (*str != '\n' && *str != '\0') {
			str++;
		}
		if (*str == '\n') {
			*str = '\0';
		}
		else {
			while (getchar() != '\n') {
				continue;
			}
		}
	}

	return p;
}
