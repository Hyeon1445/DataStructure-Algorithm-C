#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct _node {
	int data;
	struct _node* next;
	struct _node* prev;//양방향 연결 리스트
}Node;

typedef struct DoubleLinkedList {
	Node* head;
	Node* cur;
	int numOfData;
}List;

void ListInit(List* plist) {//초기화
	plist->head = NULL;
	plist->numOfData = 0;
}
void LInsert(List* plist, int data) {//head위치에 노드 삽입
	Node* newNode = (Node*)malloc(sizeof(Node));//메모리 할당
	newNode->data = data;

	newNode->next = plist->head;
	if (plist->head != NULL) {//만약 첫 번째 노드 삽입이 아니면
		plist->head->prev = newNode;//head의 앞은 새노드
	}
	newNode->prev = NULL;//새노드가 제일 앞이므로 앞은 비어있음
	plist->head = newNode;//head를 새노드로!
	(plist->numOfData)++;//노드 증가
}
int LFirst(List* plist, int* pdata) {
	if (plist->head == NULL)return FALSE;//노드 하나도 없으면 FALSE반환
	else {//노드 최소 하나
		plist->cur = plist->head;
		*pdata = plist->cur->data;
		return TRUE;//노드 하나 이상이면 TRUE 반환
	}
}
int LNext(List* plist, int* pdata) {
	if (plist->cur->next == NULL) {//다음 노드 없으면 FALSE반환
		return FALSE;
	}
	else {//다음 노드 있으면
		plist->cur = plist->cur->next;//뒤로 한 칸 이동
		*pdata = plist->cur->data;
		return TRUE;
	}
}
int LPrevious(List* plist, int* pdata) {
	if (plist->cur->prev == NULL) {//앞 노드 없으면 FALSE반환
		return FALSE;
	}
	else {//앞 노드 있으면
		plist->cur = plist->cur->prev;//앞으로 한 칸 이동
		*pdata = plist->cur->data;
		return TRUE;
	}
}
int LCount(List* plist) {
	return plist->numOfData;
}

int main(void) {
	List list;
	int data;
	ListInit(&list);
	LInsert(&list, 1);
	LInsert(&list, 2);
	LInsert(&list, 3);
	LInsert(&list, 4);
	LInsert(&list, 5);
	LInsert(&list, 6);
	LInsert(&list, 7);
	LInsert(&list, 8);

	if (LFirst(&list, &data)) {
		printf("%d ", data);
		while (LNext(&list, &data)) {
			printf("%d ", data);
		}
		while (LPrevious(&list, &data)) {
			printf("%d ", data);
		}
		printf("\n\n");
	}
	return 0;
}