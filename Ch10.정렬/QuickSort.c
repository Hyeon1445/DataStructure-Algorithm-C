#include <stdio.h>
#include <stdlib.h>

void Swap(int arr[], int idx1, int idx2) {//�� ������ �ڸ� �ٲٱ�!
	int temp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = temp;
}
int Partition(int arr[], int left, int right) {
	int pivot = arr[left];//pivot��ġ�� left ��ġ�� ������
	int low = left + 1;// ó�� low�� pivot ��ġ�� ������ ���� ���� ��ġ
	int high = right;//ó�� high�� pivot ��ġ�� ������ ���� ������ ��ġ�ε� pivot�� left��ġ�̹Ƿ� high = right�� ����

	while (low <= high) {//low�� high�� �����Ǳ� ������ �ݺ�
		while (pivot >= arr[low] && low<=right)low++;//pivot���� low���� Ŭ ��(�켱���� ������)���� ���������� �̵�
		//low<=right ���� ������ {3,3,3}�迭 ���Ŀ��� ����!
		while (pivot <= arr[high] && high>=(left+1))high--;//pivot���� high���� ���� ��(�켱���� Ŭ��)���� �������� �̵�
		//hight>=(left+1)���� ������ {3,3,3} �迭 ���Ŀ��� ����!
		if (low <= high)Swap(arr, low, high);//low�� high �����Ͱ� �ٲٱ�!
	}
	Swap(arr, left, high);//low�� high �����ϸ� pivot(left)�� high ��ġ �ٲٰ� ��
	return high;
}
void QuickSort(int arr[], int left, int right) {//����Լ�
	if (left <= right) {//left>right�Ǵ¼��� ���ĳ���!
		int pivot = Partition(arr, left, right);
		QuickSort(arr, left, pivot - 1);//pivot ���� ���� QuickSort ����(pivot�� ���� ��������)
		QuickSort(arr, pivot + 1, right);//pivot ������ ���� QuickSort ���� (pivot�� ���� ū ����)
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
	QuickSort(arr, 0, n - 1);
	printf("\n\nQuickSort, ��������\n");
	for (i = 0; i < n; i++)printf("%d\n", arr[i]);
	return 0;
}