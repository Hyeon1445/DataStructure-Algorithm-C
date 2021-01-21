#include <stdio.h>
#include <stdlib.h>
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
	if ((plist->numofData) >= LIST_LEN) {
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
	for (int i = removePosition; i < (plist->numofData) - 1; i++) {
		plist->arr[i] = plist->arr[i + 1];
	}
	(plist->numofData)--;
	(plist->curPosition)--;
	return rdata;
}
int LCount(List* plist) {
	return (plist->numofData);
}

typedef struct _point {
	int xpos;
	int ypos;
}Point;

void SetPointPos(Point* ppos, int xpos, int ypos) {
	(ppos->xpos) = xpos;
	(ppos->ypos) = ypos;
}
void ShowPointPos(Point* ppos) {
	printf("(%d, %d) \n", ppos->xpos,ppos->ypos);
}
int PointComp(Point* pos1, Point* pos2) {
	if ((pos1->xpos) == (pos2->xpos) && (pos1->ypos) == (pos2->ypos))return 0;
	else if ((pos1->xpos) == (pos2->xpos))return 1;
	else if ((pos1->ypos) == (pos2->ypos))return 2;
	else return -1;
}
int main() {
	List list;
	Point compPos;
	Point* ppos;
	ListInit(&list);

	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 2, 1);
	LInsert(&list, ppos);

	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 2, 2);
	LInsert(&list, ppos);

	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 3, 1);
	LInsert(&list, ppos);

	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 3, 2);
	LInsert(&list, ppos);

	printf("현재 데이터의 수: %d\n", LCount(&list));
	if (LFirst(&list, &ppos)) {
		ShowPointPos(ppos);
		while (LNext(&list, &ppos))
			ShowPointPos(ppos);
	}
	printf("\n");
	

	compPos.xpos = 2;
	compPos.ypos = 0;

	if (LFirst(&list, &ppos)) {
		if (PointComp(ppos, &compPos) == 1) {//xpos가 2일 경우 삭제
			ppos = LRemove(&list);
			free(ppos);
		}
		while (LNext(&list, &ppos)) {
			if (PointComp(ppos, &compPos) == 1) {
				ppos = LRemove(&list);
				free(ppos);
			}
		}
	}

	printf("현재 데이터 수: %d\n", LCount(&list));

	if (LFirst(&list, &ppos)) {
		ShowPointPos(ppos);
		while (LNext(&list, &ppos)) {
			ShowPointPos(ppos);
		}
	}
	printf("\n");
	return 0;
}