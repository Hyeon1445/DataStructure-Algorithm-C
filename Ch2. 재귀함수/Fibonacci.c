#include <stdio.h>
int fibonacci(num) {
	if (num == 1) {
		return 0;
	}
	else if (num == 2) {
		return 1;
	}
	else {
		return fibonacci(num - 1) + fibonacci(num - 2);
	}
}
int main(void) {
	int num, res;
	printf("숫자 입력(개수) : ");
	scanf("%d", &num);
	for (int i = 1; i <= num; i++) {
		printf("%5d",fibonacci(i));
	}
	return 0;
}

