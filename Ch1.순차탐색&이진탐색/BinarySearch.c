#include <stdio.h>
int BinarySearch(int a[], int len, int num) { //이진 탐색 알고리즘 : 순서대로 정렬되어 있을 때 사용!
	int first = 0;
	int last = len - 1;
	int mid;
	while (first <= last) {
		mid = (first + last) / 2;
		if (a[mid] == num) {
			return mid;
		}
		else {
			if (a[mid] > num) {
				last = mid - 1;
			}
			else {
				first = mid + 1;
			}
		}
		return -1;
	}
}
int main(void) {
	int a[10], i, num, index;
	for (i = 0; i < 10; i++) scanf("%d", &a[i]);
	//숫자 10개 입력
	printf("찾을 값 입력 : ");
	scanf("%d", &num);
	index = BinarySearch(a, sizeof(a) / sizeof(int), num);
	if (index == -1) printf("fail\n");
	else printf("index : %d", index);
	return 0;
}

