#include <Stdio.h>
void SelectionSort(int arr[], int n) {//선택 정렬, 작은 값 찾아서 앞으로 옮기기
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
	printf("숫자 개수 : ");
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		printf("숫자 입력 : ");
		scanf("%d", &input);
		arr[i] = input;
	}
	SelectionSort(arr, n);
	printf("\n\nSelection Sort, 오름차순\n");
	for (i = 0; i < n; i++) {
		printf("%d\n", arr[i]);
	}
	return 0;
}