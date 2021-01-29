#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define QUE_LEN 100

typedef struct _queue {
	int Front;
	int Rear;
	int Arr[QUE_LEN];
}Queue;

void QInit(Queue* pq) {//ť �ʱ�ȭ
	pq->Front = 0;
	pq->Rear = 0;
}

int QIsEmpty(Queue* pq) {
	if (pq->Front == pq->Rear)return TRUE;//Front�� Rear��ġ�� ������ ����ִٴ� �Ҹ�
	else return FALSE;//������� �ʴ�
}

int NextPosIdx(int pos) {//ť�� ���� ��ġ �ε��� ��ȯ
	if (pos == QUE_LEN - 1)return 0;//����ť�̹Ƿ� ���� Front�� Rear�� �迭�� ���� ���� �ٽ� �� ������ ��
	else return pos + 1;//�� ���� ���ܻ�Ȳ�� �ƴϸ� �׳� ��ĭ �� ��ȯ
}

void Enqueue(Queue* pq, int data) {//Rear ��ġ ��ĭ �ڷ� �̵� �� Rear��ġ�� ������ ����
	if (NextPosIdx(pq->Rear) == pq->Front) {//���� Rear����ĭ�� Front�� ������ �� á�ٴ� �Ҹ� & �� �̻� ����X
		printf("Queue ���� ��!");
		exit(-1);
	}
	else {
		pq->Rear = NextPosIdx(pq->Rear);
		pq->Arr[pq->Rear] = data;
	}
}

int Dequeue(Queue* pq) {//Front ��ġ ��ĭ �ڷ� �̵� �� Front��ġ�� ������ ��ȯ �� ����(Front�ڸ� �����ʹ� �׻� ����ִٰ� ����)
	if (QIsEmpty(pq)) {
		printf("Queue is Empty!");
		exit(-1);
	}
	else {
		pq->Front = NextPosIdx(pq->Front);
		return pq->Arr[pq->Front];//�迭�̶� ���� ���Ŵ� ���ϰ� �׳� ��ȯ
	}
}

int Qpeek(Queue* pq) {
	if (QIsEmpty(pq)) {
		printf("Queue is Empty!");
		exit(-1);
	}
	return pq->Arr[NextPosIdx(pq->Front)];//Dequeue�ϸ� ���� ���� ���� �����Ͱ� ��ȯ(Front ����ĭ)
}

int main(void) {
	Queue Q;
	int num;
	QInit(&Q);
	while (1) {
		printf("�����Է� : ");
		scanf("%d", &num);
		if (num < 1)break;
		Enqueue(&Q, num);
	}
	printf("\n\n�Էµ� ������ ��� ��� : ");
	while (!QIsEmpty(&Q))printf("%d ", Dequeue(&Q));//ť�� �Է� ������ ������ ���� ����(������)
	return 0;
}
