#include <stdio.h>
#include <stdlib.h>

void Swap(int arr[], int idx1, int idx2) {//두 데이터 자리 바꾸기!
	int temp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = temp;
}
int Partition(int arr[], int left, int right) {
	int pivot = arr[left];//pivot위치를 left 위치로 지정함
	int low = left + 1;// 처음 low는 pivot 위치를 제외한 가장 왼쪽 위치
	int high = right;//처음 high는 pivot 위치를 제외한 가장 오른쪽 위치인데 pivot이 left위치이므로 high = right인 상태

	while (low <= high) {//low와 high가 교차되기 전까지 반복
		while (pivot >= arr[low] && low<=right)low++;//pivot보다 low값이 클 때(우선순위 작을때)까지 오른쪽으로 이동
		//low<=right 조건 없으면 {3,3,3}배열 정렬에서 오류!
		while (pivot <= arr[high] && high>=(left+1))high--;//pivot보다 high값이 작을 때(우선순위 클때)까지 왼쪽으로 이동
		//hight>=(left+1)조건 없으면 {3,3,3} 배열 정렬에서 오류!
		if (low <= high)Swap(arr, low, high);//low와 high 데이터값 바꾸기!
	}
	Swap(arr, left, high);//low와 high 교차하면 pivot(left)와 high 위치 바꾸고 끝
	return high;
}
void QuickSort(int arr[], int left, int right) {//재귀함수
	if (left <= right) {//left>right되는순간 정렬끝남!
		int pivot = Partition(arr, left, right);
		QuickSort(arr, left, pivot - 1);//pivot 왼쪽 따로 QuickSort 정렬(pivot에 비해 작은값들)
		QuickSort(arr, pivot + 1, right);//pivot 오른쪽 따로 QuickSort 정렬 (pivot에 비해 큰 값들)
	}
}
int main(void) {
	int n, i, input;
	printf("입력할 숫자 개수 : ");
	scanf("%d", &n);
	int arr[100] = { 0 };
	for (i = 0; i < n; i++) {
		printf("숫자 입력 : ");
		scanf("%d", &input);
		arr[i] = input;
	}
	QuickSort(arr, 0, n - 1);
	printf("\n\nQuickSort, 오름차순\n");
	for (i = 0; i < n; i++)printf("%d\n", arr[i]);
	return 0;
}