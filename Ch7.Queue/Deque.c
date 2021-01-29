#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct _node {
	int data;
	struct _node* prev;
	struct _node* next;
}Node;

typedef struct _deque {
	Node* head;
	Node* tail;
}Deque;

void DequeInit(Deque* pdeq) {
	pdeq->head = NULL;
	pdeq->tail = NULL;
}
int DQIsEmpty(Deque* pdeq) {
	if (pdeq->head == NULL)return TRUE;
	else return FALSE;
}
void DQAddFirst(Deque* pdeq, int data) {//맨 앞에 노드 넣기
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;//데이터 저장
	newNode->next = pdeq->head;//새노드 다음은 head (처음 add면 head가 NULL상태)
	if (DQIsEmpty(pdeq))pdeq->tail = newNode;//처음 add면 tail도 새노드
	else pdeq->head->prev = newNode;//head 앞은 newNode
	newNode->prev = NULL;//새노드 앞은 NULL
	pdeq->head = newNode;//head는 새노드
}
void DQAddLast(Deque* pdeq, int data) {//맨 뒤에 노드 넣기
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->prev = pdeq->tail;
	if (DQIsEmpty(pdeq))pdeq->head = newNode;
	else pdeq->tail->next = newNode;
	newNode->next = NULL;
	pdeq->tail = newNode;
}
int DQRemoveFirst(Deque* pdeq) {//맨 앞 노드 제거
	Node* removeNode = pdeq->head;
	int removeData;
	if (DQIsEmpty(&pdeq)) {
		printf("Queue is Empty!\n");
		exit(-1);
	}
	removeData = removeNode->data;
	pdeq->head = pdeq->head->next;
	free(removeNode);
	if (pdeq->head == NULL)pdeq->tail = NULL;
	else pdeq->head->prev = NULL;
	return removeData;
}
int DQRemoveLast(Deque* pdeq) {
	Node* removeNode = pdeq->tail;
	int removeData;
	if (DQIsEmpty(&pdeq)) {
		printf("Queue is Empty!\n");
		exit(-1);
	}
	removeData = removeNode->data;
	pdeq->tail = pdeq->tail->prev;
	free(removeNode);
	if (pdeq->tail == NULL)pdeq->head = NULL;
	else pdeq->tail->next = NULL;
	return removeData;
}
int DQGetFirst(Deque* pdeq) {
	if (DQIsEmpty(pdeq)) {
		printf("Deque is Empty!\n");
		exit(-1);
	}
	else return pdeq->head->data;
}
int DQGetLast(Deque* pdeq) {
	if (DQIsEmpty(pdeq)) {
		printf("Deque is Empty!\n");
		exit(-1);
	}
	else return pdeq->tail->data;
}
int main(void) {
	int i, num;
	Deque* dq;
	DequeInit(&dq);
	for (i = 0; i < 5; i++) {
		printf("숫자 입력 (앞에 추가) : ");
		scanf("%d", &num);
		DQAddFirst(&dq, num);
	}
	printf("\n\n입력된 숫자 출력 & 앞에서부터 제거 : ");
	while (!DQIsEmpty(&dq))printf("%d ", DQRemoveFirst(&dq));
	printf("\n\n");

	for (i = 0; i < 5; i++) {
		printf("숫자 입력 (뒤에 추가) : ");
		scanf("%d", &num);
		DQAddLast(&dq, num);
	}
	printf("\n\n입력된 숫자 출력 & 뒤에서부터 제거 : ");
	while (!DQIsEmpty(&dq))printf("%d ", DQRemoveLast(&dq));
	return 0;
}