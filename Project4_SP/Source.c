#include <stdio.h>
#include <malloc.h>

typedef int (*fpointer)(int, int);
typedef fpointer* delegate;

int razn(int a, int b);
int summa(int a, int b);
int umn(int a, int b);
delegate initDelegate(int n);
void showDelegate(delegate d, int a, int b);
void addFunc(delegate d, fpointer f);
void removeFunc(delegate d, fpointer f, int type);

int countfunc;

int razn(int a, int b)
{
	return a - b;
}

int summa(int a, int b)
{
	return a + b;
}

int umn(int a, int b)
{
	return a * b;
}

delegate initDelegate()
{
	delegate d = calloc(1, (sizeof(fpointer) + 1));
	return d;
}

void showDelegate(delegate d, int a, int b)
{
	for (int i = 0; i < countfunc; i++)
	{
		if (d[i])
		{
			printf("%d ", d[i](a, b));
		}
	}
	printf("\n");
}

void addFunc(delegate d, fpointer f)
{
	d[countfunc] = f;
	countfunc++;
	d = realloc(d, (countfunc + 1) * (sizeof(fpointer) + 1));
}

void removeFunc(delegate d, fpointer f, int type)
{
	for (int i = 0; i < countfunc; i++)
	{
		if (d[i] == f)
		{
			countfunc--;
			for (int j = 0; j < countfunc; j++)
			{
				d[j] = d[j + 1];
			}
			d = realloc(d, (countfunc + 1) * (sizeof(fpointer) + 1));
			if (type)
			{
				break;
			}
		}
	}
}

void deleteDublicat(delegate d)
{
	for (int i = 0; i < countfunc; i++)
	{
		for (int j = i + 1; j < countfunc; j++)
		{
			if (d[j] == d[i])
			{
				countfunc--;
				for (int k = j; k < countfunc; k++)
				{
					d[k] = d[k + 1];
					i--;
				}
				d = realloc(d, (countfunc + 1) * (sizeof(fpointer) + 1));
			}
		}
	}
}

int main(void)
{
	delegate d = initDelegate();
	addFunc(d, summa);
	addFunc(d, umn);
	addFunc(d, razn);
	showDelegate(d, 2, 6);
	removeFunc(d, summa, 0);
	showDelegate(d, 2, 6);
	addFunc(d, summa);
	addFunc(d, summa);
	addFunc(d, summa);
	addFunc(d, summa);
	addFunc(d, razn);
	addFunc(d, razn);
	showDelegate(d, 2, 6);
	deleteDublicat(d);
	showDelegate(d, 2, 6);
	return 0;
}