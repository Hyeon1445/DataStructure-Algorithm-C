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

void QueueInit(Queue* pq) {//ť �ʱ�ȭ
	pq->Front = NULL;
	pq->Rear = NULL;
}
int QIsEmpty(Queue* pq) {
	if (pq->Front == NULL)return TRUE;//Front�� NULL�̸� �������
	else return FALSE;//������� ����
}
void Enqueue(Queue* pq, int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	if (QIsEmpty(pq)) {//����ִ� ���
		pq->Front = newNode;//�� ��尡 ù ���
		pq->Rear = newNode;//�� ��尡 ������ ���
	}
	else {
		pq->Rear->next = newNode;//ť�� ������ ��忡 �� ��� ����
		pq->Rear = newNode;//�߰��� ��尡 ������ ��尡 ��
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
		printf("���� �Է� : ");
		scanf("%d", &num);
		if (num < 1)break;
		Enqueue(&Q, num);
	}
	printf("\n\n�Էµ� ���� ��� ��� : ");
	while (!QIsEmpty(&Q)) {
		printf("%d ", Dequeue(&Q));
	}
	return 0;
}