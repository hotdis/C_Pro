#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 20
#define LIM 20

char *s_gets(char *str, int n)
{
	char *p = fgets(str, n, stdin);
	int i = 0;
	while (str[i] != '\0'&&str[i] != '\n')
	{
		i++;
	}
	if (str[i] == '\n')
	{
		str[i] = '\0';
	}
	return p;
}


int main()
{
	const char dictionary[LIM][SIZE] = { "emeny","hello","really","those","pointer","array","buffer","integer","double","float",
									"char","string","stdio.h","stdlib.h","define","main","include","system","return","twopointer" };

	char str[SIZE];
	int current = 0;
	int wrong = 0;

	while (1)
	{
		system("cls");
		int i = rand() % LIM;
		//select words on random
		printf("Currents : %d Wrong : %d\n", current, wrong);
		puts(dictionary[i]);
		//printf target word
		s_gets(str, SIZE);
		//type target word
		if (strcmp(str, dictionary[i]) == 0)
		{
			current++;
		}
		else
		{
			wrong++;
		}
	}




	system("pause");
	return 0;
}