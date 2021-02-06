#include <stdio.h>
#include <stdlib.h>

void MergeTwoArea(int arr[], int left, int mid, int right) {//�� ����� �����Ѵ�
	int FirstIdx = left;//ù ��° ��� ù ��° �ڸ�
	int SecondIdx = mid + 1;//�� ��° ��� �� ���� �ڸ�
	int i;
	int* sortArr = (int*)malloc(sizeof(int) * (right + 1));//���� �� ���� �ڸ�
	int CurrentIdx = left;
	while (FirstIdx <= mid && SecondIdx <= right) {//�� ������� ���ڸ� �Ѿ�� ����������
		if (arr[FirstIdx] <= arr[SecondIdx])sortArr[CurrentIdx] = arr[FirstIdx++];//����
		else sortArr[CurrentIdx] = arr[SecondIdx++];//����
		CurrentIdx++;
	}
	if (FirstIdx > mid) {//���� ù ��° ��� ��� ä�� �ڿ��� ������ �ڸ��� �ι�° ��� ���� �����ͷ� ä���
		for (i = SecondIdx; i <= right; i++, CurrentIdx++)sortArr[CurrentIdx] = arr[i];
	}
	else {// �� ��° ��� ��� ä�� �ڿ��� ������ �ڸ��� ù ��° ��� ���� �����ͷ� ä���
		for (i = FirstIdx; i <= mid; i++, CurrentIdx++)sortArr[CurrentIdx] = arr[i];
	}
	for (i = left; i <= right; i++) arr[i] = sortArr[i];//���ĵ� �迭�� arr�� �ٽ� ����
	free(sortArr);//sortArr�� ���� �ʿ����
}
void MergeSort(int arr[], int left, int right) {//��͸� �̿��ؼ� ���������� �����Ѵ�(�ϳ��� �ɰ��������� ����)
	int mid;
	if (left < right) {//right-left=1�϶� ���������� 2������ 1�������� �ɰ��� �� ������ �ݺ��� Ż��
		mid = (left + right) / 2;
		MergeSort(arr, left, mid);
		MergeSort(arr, mid + 1, right);
		MergeTwoArea(arr, left, mid, right);
	}
}
int main(void) {
	int n, i, input;
	printf("�Է��� ���� ���� : ");
	scanf("%d", &n);
	int arr[100] = { 0 };
	for (i = 0; i < n; i++) {
		printf("���� �Է� : ");
		scanf("%d", &input);
		arr[i] = input;
	}
	MergeSort(arr, 0, n - 1);
	printf("\n\nMergeSort, ��������\n");
	for (i = 0; i < n; i++)printf("%d\n", arr[i]);
	return 0;
}