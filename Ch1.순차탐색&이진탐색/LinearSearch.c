#include <stdio.h>

int LinearSearch(int a[], int len, int num) { //���� Ž�� �˰��� T(n)=n
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
	//���� 10�� �Է�
	printf("ã�� �� �Է� : ");
	scanf("%d", &num);
	index = LinearSearch(a, sizeof(a) / sizeof(int), num);
	if (index == -1) printf("fail\n");
	else printf("index : %d", index);
	return 0;
}
