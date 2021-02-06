#include <Stdio.h>
void InsertionSort(int arr[], int n) {
	int i, j, insertData;
	for (i = 1; i < n; i++) {
		insertData = arr[i];
		for (j = i - 1; j >= 0; j--) {
			if (arr[j] > insertData) arr[j + 1] = arr[j]; //�ڸ� ã�������� �� ĭ�� �ڷ� �����
			else break; //�ڸ� ã���� ��ž
		}
		arr[j + 1] = insertData;//�� �ڸ��� �����ֱ�
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
	InsertionSort(arr, n);
	printf("\n\nInsertion Sort, ��������\n");
	for (i = 0; i < n; i++) {
		printf("%d\n", arr[i]);
	}
	return 0;
}