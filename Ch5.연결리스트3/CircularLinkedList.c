#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct _node {
	int data;
	struct _node* next;
}Node;

typedef struct CircularLinkedList {
	Node* tail;
	Node* cur;
	Node* before;
	int numOfData;
}List;

void ListInit(List* plist) {//리스트 초기화(처음에 호출)
	plist->tail = NULL;
	plist->cur = NULL;
	plist->before = NULL;
	plist->numOfData = 0;
}

void LInsert(List* plist, int data) {//tail에 삽입하는 경우
	Node* newNode = (Node*)malloc(sizeof(Node));//새노드
	newNode->data = data;//데이터 입력
	if (plist->tail == NULL){//처음 insert하는 경우
		plist->tail = newNode;//List의 tail자리에 insert
		newNode->next = newNode; //원형 연결 리스트(처음과 끝을 이어줌)
	}
	else {//처음이 아닐 때
		newNode->next = plist->tail->next;//삽입 노드의 다음은 tail->next(head)
		plist->tail->next = newNode;//head위치(tail의 다음)가 newNode : 여기까지 보면 head위치에 삽입됨
		plist->tail = newNode;//tail을 newNode로 이동 : tail위치에 삽입됨
	}
	(plist->numOfData)++;//리스트의 노드 증가
}

void LInsertFront(List* plist, int data) {//head에 삽입하는 경우
	Node* newNode = (Node*)malloc(sizeof(Node));//새 노드 할당
	newNode->data = data;//데이터 입력
	if (plist->tail == NULL) {//처음 입력하는 경우
		plist->tail = newNode;
		newNode->next = newNode;
	}
	else {//처음 아닌 경우
		newNode->next = plist->tail->next;
		plist->tail->next = newNode;//tail위치에 새 노드 삽입
	}
	(plist->numOfData)++;//리스트의 노드 증가
}

int LFirst(List* plist, int* pdata) {
	if (plist->tail == NULL)return FALSE;//노드 하나도 없음
	else {//노드 최소 하나라도 있음
		plist->before = plist->tail;//head 전 위치는 tail
		plist->cur = plist->tail->next;//현재는 tail의 next(head)
		*pdata = plist->cur->data;//데이터값 저장
		return TRUE;
	}
}
int LNext(List* plist, int* pdata) {
	if (plist->tail == NULL)return FALSE;//노드 하나도 없으면 안됨
	else {//노드 하나 이상인 경우 끝 없이 무한반복
		plist->before = plist->cur;
		plist->cur = plist->cur->next;//한칸씩 다음으로 옮김
		*pdata = plist->cur->data;
		return TRUE;
	}
}
int LRemove(List* plist) {//노드 제거
	Node* removeNode = plist->cur;//제거할 거
	int removeData = removeNode->data;//제거할 데이터

	if (removeNode == plist->tail) {//경우1)제거할 노드가 꼬리위치
		if (plist->tail == plist->tail->next) {//경우1-1)노드 하나뿐
			plist->tail = NULL;
		}
		else {//경우1-2)노드 여러개
			plist->tail = plist->before;
		}
	}
	plist->before->next = plist->cur->next;
	plist->cur = plist->before;//제거할 거 쏙 빼고 앞뒤 서로 이어줌
	free(removeNode);//쏙 빼버린 제거노드 메모리 제거
	(plist->numOfData)--;//노드 감소
	return removeData;
}
int LCount(List* plist) {
	return plist->numOfData;
}

int main(void) {
	List list;
	int data, i, nodeNum;
	ListInit(&list);


	//값 입력
	LInsert(&list, 4);
	LInsert(&list, 5);
	LInsert(&list, 6);
	LInsert(&list, 7);
	LInsertFront(&list, 3);
	LInsertFront(&list, 2);
	LInsertFront(&list, 1);
	
	
	//5번씩 반복출력
	if (LFirst(&list, &data)) {
		printf("%d ", data);
		for (i = 0; i < LCount(&list) * 5; i++) {
			if (LNext(&list, &data)) {
				printf("%d ", data);
			}
		}
	}
	printf("\n\n\n");


	//3의 배수면 삭제
	nodeNum = LCount(&list);
	if (nodeNum != 0) {
		LFirst(&list, &data);
		if (data % 3 == 0)LRemove(&list);
		for (i = 0; i < nodeNum - 1; i++) {
			LNext(&list, &data);
			if (data % 3 == 0)LRemove(&list);
		}
	}

	//전체 값 출력
	if (LFirst(&list, &data)) {
		printf("%d ", data);
		for (i = 0; i < LCount(&list) - 1; i++) {
			if (LNext(&list, &data))printf("%d ", data);
		}
	}
	return 0;
}