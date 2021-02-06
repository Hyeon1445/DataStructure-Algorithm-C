#include <stdio.h>
#include <stdlib.h>

void MergeTwoArea(int arr[], int left, int mid, int right) {//두 덩어리를 병합한다
	int FirstIdx = left;//첫 번째 덩어리 첫 번째 자리
	int SecondIdx = mid + 1;//두 번째 덩어리 두 번재 자리
	int i;
	int* sortArr = (int*)malloc(sizeof(int) * (right + 1));//정렬 후 넣을 자리
	int CurrentIdx = left;
	while (FirstIdx <= mid && SecondIdx <= right) {//각 덩어리별로 끝자리 넘어가지 않을때까지
		if (arr[FirstIdx] <= arr[SecondIdx])sortArr[CurrentIdx] = arr[FirstIdx++];//정렬
		else sortArr[CurrentIdx] = arr[SecondIdx++];//정렬
		CurrentIdx++;
	}
	if (FirstIdx > mid) {//만약 첫 번째 덩어리 모두 채운 뒤에는 나머지 자리는 두번째 덩어리 남은 데이터로 채운다
		for (i = SecondIdx; i <= right; i++, CurrentIdx++)sortArr[CurrentIdx] = arr[i];
	}
	else {// 두 번째 덩어리 모두 채운 뒤에는 나머지 자리는 첫 번째 덩어리 남은 데이터로 채운다
		for (i = FirstIdx; i <= mid; i++, CurrentIdx++)sortArr[CurrentIdx] = arr[i];
	}
	for (i = left; i <= right; i++) arr[i] = sortArr[i];//정렬된 배열을 arr에 다시 저장
	free(sortArr);//sortArr은 이제 필요없음
}
void MergeSort(int arr[], int left, int right) {//재귀를 이용해서 병합정렬을 진행한다(하나씩 쪼개질때까지 분할)
	int mid;
	if (left < right) {//right-left=1일때 마지막으로 2개에서 1개씩으로 쪼개고 그 다음에 반복문 탈출
		mid = (left + right) / 2;
		MergeSort(arr, left, mid);
		MergeSort(arr, mid + 1, right);
		MergeTwoArea(arr, left, mid, right);
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
	MergeSort(arr, 0, n - 1);
	printf("\n\nMergeSort, 오름차순\n");
	for (i = 0; i < n; i++)printf("%d\n", arr[i]);
	return 0;
}