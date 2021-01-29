#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
typedef struct _node {
	int data;
	struct _node* next;
}Node;

typedef struct ListQueue {
	Node* Front;
	Node* Rear;
}Queue;

void QueueInit(Queue* pq) {//큐 초기화
	pq->Front = NULL;
	pq->Rear = NULL;
}
int QIsEmpty(Queue* pq) {
	if (pq->Front == NULL)return TRUE;//Front가 NULL이면 비어있음
	else return FALSE;//비어있지 않음
}
void Enqueue(Queue* pq, int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	if (QIsEmpty(pq)) {//비어있는 경우
		pq->Front = newNode;//새 노드가 첫 노드
		pq->Rear = newNode;//새 노드가 마지막 노드
	}
	else {
		pq->Rear->next = newNode;//큐의 마지막 노드에 새 노드 연결
		pq->Rear = newNode;//추가된 노드가 마지막 노드가 됨
	}
}
int Dequeue(Queue* pq) {
	Node* removeNode;
	int removeData;
	if (QIsEmpty(pq)) {
		printf("Queue is Empty!\n");
		exit(-1);
	}
	removeNode = pq->Front;
	removeData = removeNode->data;
	pq->Front = pq->Front->next;
	free(removeNode);
	return removeData;
}
int Peek(Queue* pq) {
	if (QIsEmpty(pq)) {
		printf("Queue is Empty!\n");
		exit(-1);
	}
	else {
		return pq->Front->data;
	}
}
int main(void) {
	Queue Q;
	int num;
	QueueInit(&Q);
	while (1) {
		printf("숫자 입력 : ");
		scanf("%d", &num);
		if (num < 1)break;
		Enqueue(&Q, num);
	}
	printf("\n\n입력된 숫자 모두 출력 : ");
	while (!QIsEmpty(&Q)) {
		printf("%d ", Dequeue(&Q));
	}
	return 0;
}