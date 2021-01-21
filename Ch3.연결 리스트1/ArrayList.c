#include <stdio.h>
#define LIST_LEN 100

typedef struct __Arraylist {
	int arr[LIST_LEN];
	int numofData;
	int curPosition;
}List;

void ListInit(List* plist) {
	(plist->numofData) = 0;
	(plist->curPosition) = -1;
}
void LInsert(List* plist, int data) {
	if ((plist->numofData)>=LIST_LEN) {
		printf("저장 불가\n");
	}
	else {
		plist->arr[plist->numofData] = data;
		(plist->numofData)++;
	}
}
int LFirst(List* plist, int* pdata) {
	if (plist->numofData == 0) {
		return 0;
	}
	else {
		*pdata = (plist->arr[0]);
		(plist->curPosition) = 0;
		return 1;
	}
}
int LNext(List* plist, int* pdata) {
	if (plist->curPosition >= (plist->numofData) - 1) {
		return 0;
	}
	else {
		(plist->curPosition)++;
		*pdata = plist->arr[plist->curPosition];
		return 1;
	}
}
int LRemove(List* plist) {
	int removePosition = (plist->curPosition);
	int rdata = plist->arr[removePosition];
	for (int i = removePosition; i < (plist->numofData)-1; i++) {
		plist->arr[i] = plist->arr[i + 1];
	}
	(plist->numofData)--;
	(plist->curPosition)--;
	return rdata;
}
int LCount(List* plist) {
	return (plist->numofData);
}
int main() {
	List list;
	int data, i, sum;
	ListInit(&list);
	//리스트 생성 및 초기화

	sum = 0;
	for (i = 1; i <= 9; i++) {
		LInsert(&list, i);
	}
	if (LFirst(&list, &data)) {
		sum += data;
	}
	while (LNext(&list, &data)) {
		sum += data;
	}
	printf("합 : %d\n", sum);
	//리스에 저장된 값을 순차적으로 참조하여 합을 계산&출력

	if (LFirst(&list, &data)) {
		if (data % 2 == 0 || data % 3 == 0) {
			LRemove(&list);
		}
	}
	while (LNext(&list, &data)) {
		if (data % 2 == 0 || data % 3 == 0) {
			LRemove(&list);
		}
	}
	//2의배수와 3의 배수 삭제

	printf("저장된 숫자들 : ");
	if (LFirst(&list, &data)) {
		printf("%5d", data);
	}
	while (LNext(&list, &data)) {
		printf("%5d", data);
	}
	//리스트에 저장된 데이터 순서대로 출력

	return 0;
}
