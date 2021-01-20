#include <stdio.h>
int factorial(num) {
	if (num == 0) {
		return 1;
	}
	else {
		return num * factorial(num-1);
	}
}
int main(void) {
	int num, res;
	scanf("%d", &num);
	res = factorial(num);
	printf("%d! = %d", num, res);
	return 0;
}

