#include <stdio.h>
int BinarySearchRecur(int a[],int first, int last, int num) {
	int mid;
	if (first > last) {
		return -1;//����
	}
	else {
		mid = (first + last) / 2;
		if (a[mid] == num) {
			return mid;
		}
		else if (a[mid] > num) {
			return BinarySearchRecur(a, first, mid - 1, num);
		}
		else {
			return BinarySearchRecur(a, mid + 1, last, num);
		}
	}
}
int main(void) {
	int a[10], idx, i, num;
	printf("���� 10�� �Է� : ");
	for (i = 0; i < 10; i++) {
		scanf("%d", &a[i]);
	}
	printf("ã�� ���� : ");
	scanf("%d", &num);
	printf("%d", sizeof(a) / sizeof(int));
	idx=BinarySearchRecur(a, 0, sizeof(a) / sizeof(int)-1, num);
	if (idx == -1) {
		printf("fail");
	}
	else {
		printf("%d", idx);
	}
	return 0;
}

