#include <Stdio.h>
void SelectionSort(int arr[], int n) {//���� ����, ���� �� ã�Ƽ� ������ �ű��
	int i, j;
	int minIdx;
	int temp;
	for (i = 0; i < n - 1; i++) {
		minIdx = i;
		for (j = i+1; j < n; j++) {
			if (arr[minIdx] > arr[j])minIdx = j;
		}
		temp = arr[i];
		arr[i] = arr[minIdx];
		arr[minIdx] = temp;
	}
}
int main(void) {
	int arr[10];
	int n,input,i;
	printf("���� ���� : ");
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		printf("���� �Է� : ");
		scanf("%d", &input);
		arr[i] = input;
	}
	SelectionSort(arr, n);
	printf("\n\nSelection Sort, ��������\n");
	for (i = 0; i < n; i++) {
		printf("%d\n", arr[i]);
	}
	return 0;
}