#include <stdio.h>

int InterpolationSearch(int arr[], int first, int last, int target) {
	int mid;
	if (arr[first]>target||arr[last]<target)return -1;
	//ch2 RecursiveBinarySearch���� ������!!
	//���� if(first>last)return -1;�̸� {1,3,5,7,9}���� 2 ã�� ���� ����� ����
	mid = ((double)(target - arr[first]) / (arr[last] - arr[first])) * (last - first) + first;
	//ch2 RecursiveBinarySearch���� ������!! - ����!
	//mid�����̸��� ���⼭�� �߰����� �ǹ����� ������ �׳� ��
	if (arr[mid] == target)return mid;
	else if (target < arr[mid])return InterpolationSearch(arr, first, mid - 1, target);//���
	else return InterpolationSearch(arr, mid + 1,last, target);//���
}
int main(void) {
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	int idx,num;
	printf("ã�� ����(1~10) : ");
	scanf("%d", &num);
	idx = InterpolationSearch(arr, 0, sizeof(arr) / sizeof(int)-1, num);
	if (idx == -1)printf("Ž������!\n");
	else printf("Ÿ�� ���� �ε��� : %d\n", idx);
	return 0;
}