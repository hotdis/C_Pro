#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

double judge_fop(double, double, char);
double less_data(double, double, char);

int main() {
	double fdata = 1, mdata = 0, ldata = 0;
	int err_c = 0;
	char fop = 0, lop = 0;

	puts("Enter a expression.I'll give you the result.");
	while (2 == scanf("%lf%c", &fdata, &fop)) {
		if (fop == '\n') {
			less_data(fdata, 0, '+');
			continue;
		}
		scanf("%lf%c", &mdata, &lop);
		if (lop == '\n') {
			less_data(fdata, mdata, fop);
			continue;
		}

		while (1 == scanf("%lf", &ldata)) {
			if (lop == '+' || lop == '-') {
				fdata = judge_fop(fdata, mdata, fop);
				mdata = ldata;
				fop = lop;
			}
			else if (lop == '*') {
				mdata = mdata * ldata;
			}
			else if (lop == '/') {
				if (ldata == 0) {
					mdata = 0;
					puts("There is a zero in pression.The result is invalid.");
				}
				else {
					mdata = mdata / ldata;
				}
			}
			else {
				mdata = 0;
				puts("Expression include illegal operator.The result is invalid.");
			}

			scanf("%c", &lop);
			if (lop == '\n') {
				break;
			}
		}

		printf("The result is %lf\n", judge_fop(fdata, mdata, fop));
		puts("======================================================");
		puts("Enter a expression.I'll give you the result(# to quit).");
	}

	puts("Done.");

	system("pause");
	return 0;
}

double judge_fop(double f, double m, char op) {
	if (op == '+') {
		f = f + m;
	}
	else if (op == '-') {
		f = f - m;
	}
	else if (op == '*') {
		f = f * m;
	}
	else if (op == '/'){
		if (m == 0) {
			f = 0;
			puts("There is a zero in expression.The result is invalid.");
		}
		else {
			f = f / m;
		}
	}
	else {
		f = 0;
		puts("Expression include illegal operator.The result is invalid.");
	}

	return f;
}

double less_data(double data,double data2,char op) {
	double sum = judge_fop(data, data2, op);
	printf("The result is %lf\n", sum);
	puts("======================================================");
	puts("Enter a expression.I'll give you the result(# to quit).");
	return sum;
}