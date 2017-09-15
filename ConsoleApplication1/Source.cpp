#define __CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	char a;
	scanf("%c", &a);
	int b = strlen(&a);
	printf("%d",b );
	return 0;
}
