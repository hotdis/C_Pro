#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#define NUM_LOAD 2

#define ACC_LEN 101
#define PAW_LEN 101
#define SIUP_SUCC 0
#define SIUP_FAIL -1
#define SIIN_SUCC 0
#define SIIN_FAIL -1

const char fname[20] = { "account.txt" };

int load_in_menu();
void dynamic_menu(char *[],int *,int );
void paste_ch(char *, const char *, int);

int sign_in_menu();
int check_sign_in(const char *,const char *);

int sign_up_menu();
void write_sign_up(const char *,const char *);
int check_account(const char *);

char *s_gets(char *, int num);

int main() {
	int choice = 0;
	while ((choice = load_in_menu()) != -1) {
		if (choice == 0) {
			sign_up_menu();
		}
		else if (choice == 1) {
			if (sign_in_menu() == 0) {
				puts("hello");
			}
			else {
				puts("Error");
				getchar();
				continue;
			}
		}
		else;
		getchar();
	}
	
	puts("Welcome to students management system.");
	system("pause");
	return 0;
}

//登陆界面
int load_in_menu() {
	char str0[12] = { "|■Sign_up|" };
	char str1[12] = { "|  Sign_in|" };
	char *pstr[2] = { str0,str1 };
	char ch;
	int count = 0;

	puts("+---------+");
	for (int i = 0; i < NUM_LOAD; i++) {
		puts(pstr[i]);
	}
	puts("+---------+");
	while (1) {
		if (_kbhit()) {
			system("cls");
			ch = _getch();
			switch (ch) {
			case 'w':dynamic_menu(pstr, &count, -1); break;
			case 's':dynamic_menu(pstr, &count, 1); break;
			case ' ':return -1;
			case 'j':return count % NUM_LOAD;
			}
			puts("+---------+");
			for (int i = 0; i < NUM_LOAD; i++) {
				puts(pstr[i]);
			}
			puts("+---------+");
		}
	}
}

void dynamic_menu(char *pstr[],int *count,int op) {
	int flag = *count % NUM_LOAD;
	paste_ch(pstr[flag], "  ",2);
	if (((*count) + op) < 0) {
		*count = NUM_LOAD;
	}
	flag = (*count = ((*count) + op)) % NUM_LOAD;
	paste_ch(pstr[flag], "■", 2);
}

void paste_ch(char *target, const char *ssource, int num) {
	target++;
	for (int i = 0; i < num; i++) {
		*target++ = *ssource++;
	}
}

//注册界面
int sign_up_menu() {
	char data[ACC_LEN];
	char pawd[PAW_LEN];

	printf("User name(below %d chars):",ACC_LEN - 1);
	while (fgets(data, ACC_LEN,stdin) == NULL) {
		printf("please below %d characters.\n",ACC_LEN - 1);
	}
	while (1 == check_account(data)) {
		printf("Account has existed.try again:");
		while (fgets(data, ACC_LEN,stdin) == NULL) {
			system("cls");
			printf("please below %d characters.\n",ACC_LEN - 1);
		}
	}
	printf("Password(at least 8 chars):");
	while (fgets(pawd, PAW_LEN, stdin) == NULL || strlen(pawd) < 8) {
		printf("Illagel password.try again:");
	}

	printf("Confirm your account and password(y or n).");
	if (getchar() == 'y') {
		write_sign_up(data, pawd);
		return 0;
	}
	else {
		return -1;
	}

}

void write_sign_up(const char *acc,const char *pas) {
	const char fname[20] = { "account.txt" };
	
	FILE *fp;
	if ((fp = fopen(fname, "a")) == NULL) {
		fprintf(stderr, "Error to open %s.\n", fname);
		exit(EXIT_FAILURE);
	}

	fprintf(fp, "#%s", acc);
	fprintf(fp, "@%s", pas);

	fclose(fp);
}

int check_account(const char *str) {
	char data[ACC_LEN];
	char temp[ACC_LEN];
	char pp[1024];
	int flag = 0;

	FILE *fp;
	if ((fp = fopen(fname, "r")) == NULL) {
		fprintf(stderr, "Error to open %s", fname);
		exit(EXIT_FAILURE);
	}
	while (fscanf(fp, "#%s\n@%s\n", data,pp) != EOF) {
		strcpy(temp, str);
		temp[strlen(temp) - 1] = '\0';
		if (strcmp(temp, data) == 0) {
			flag = 1;
			break;
		}
		else;
	}

	fclose(fp);
	return flag;
}

//功能选择界面
int sign_in_menu() {
	char account[ACC_LEN];
	char password[PAW_LEN];
	int flag = SIIN_FAIL;


	printf("Account : ");
	while (s_gets(account, ACC_LEN) == NULL) {
		printf("Try again : ");
	}
	if (account[0] == ' ') {
		return flag;
	}
	printf("Password : ");
	while (s_gets(password, PAW_LEN) == NULL) {
		printf("Try again : ");
	}
	if (0 == check_sign_in(account, password)) {
		flag = SIIN_SUCC;
	}
	return flag;
}

int check_sign_in(const char *acc, const char *pas) {
	FILE *fp;
	char data[ACC_LEN];
	char pp[PAW_LEN];
	int flag = 0;

	if ((fp = fopen(fname, "r")) == NULL) {
		fprintf(stderr, "Error to open %s", fname);
		exit(EXIT_FAILURE);
	}
	while (fscanf(fp, "#%s\n@%s\n", data, pp) != EOF) {
		if (strcmp(data, acc) == 0) {
			flag = 1;
			break;
		}
	}
	if (flag) {
		if (strcmp(pp, pas) == 0) {
			return SIIN_SUCC;
		}
		else {
			puts("Error password.");
		}
	}
	else {
		puts("No account.");
	}

	return SIIN_FAIL;
}


//功能选择可能存在的次级界面

char *s_gets(char *str, int num) {
	char *p = fgets(str, num, stdin);
	if (p) {
		while (*str != '\n'&&*str != '\0') {
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
