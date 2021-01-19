#include <stdio.h>

int LinearSearch(int a[], int len, int num) { //순차 탐색 알고리즘 T(n)=n
	for (int i = 0; i < len; i++) {
		if (a[i] == num) {
			return i;
		}
	}
	return -1;
}

int main(void) {
	int a[10], i, num, index;
	for (i = 0; i < 10; i++) {
		scanf("%d", &a[i]);
	}
	//숫자 10개 입력
	printf("찾을 값 입력 : ");
	scanf("%d", &num);
	index = LinearSearch(a, sizeof(a) / sizeof(int), num);
	if (index == -1) printf("fail\n");
	else printf("index : %d", index);
	return 0;
}
