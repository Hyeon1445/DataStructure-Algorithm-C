#include <stdio.h>
void BubbleSort(int arr[], int n) {
	int i, j,temp;
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < (n - i) - 1; j++) {
			if (arr[j] > arr[j + 1]) {//������������ ����!
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
int main(void) {
	int n,i,input;
	printf("�Է��� ���� ���� : ");
	scanf("%d", &n);
	int arr[100] = { 0 };
	for (i = 0; i < n; i++) {
		printf("���� �Է� : ");
		scanf("%d", &input);
		arr[i] = input;
	}
	BubbleSort(arr, n);
	printf("BubbleSort\n");
	for (i = 0; i < n; i++)printf("%d\n", arr[i]);
	return 0;
}