#include <Stdio.h>
void InsertionSort(int arr[], int n) {
	int i, j, insertData;
	for (i = 1; i < n; i++) {
		insertData = arr[i];
		for (j = i - 1; j >= 0; j--) {
			if (arr[j] > insertData) arr[j + 1] = arr[j]; //자리 찾을때까지 한 칸씩 뒤로 땡기기
			else break; //자리 찾으면 스탑
		}
		arr[j + 1] = insertData;//그 자리에 끼워넣기
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
	InsertionSort(arr, n);
	printf("\n\nInsertion Sort, 오름차순\n");
	for (i = 0; i < n; i++) {
		printf("%d\n", arr[i]);
	}
	return 0;
}