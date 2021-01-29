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

void QInit(Queue* pq) {//큐 초기화
	pq->Front = 0;
	pq->Rear = 0;
}

int QIsEmpty(Queue* pq) {
	if (pq->Front == pq->Rear)return TRUE;//Front와 Rear위치가 같으면 비어있다는 소리
	else return FALSE;//비어있지 않다
}

int NextPosIdx(int pos) {//큐의 다음 위치 인덱스 반환
	if (pos == QUE_LEN - 1)return 0;//원형큐이므로 만약 Front나 Rear가 배열의 끝에 가면 다시 맨 앞으로 감
	else return pos + 1;//맨 끝의 예외상황이 아니면 그냥 한칸 뒤 반환
}

void Enqueue(Queue* pq, int data) {//Rear 위치 한칸 뒤로 이동 후 Rear위치에 데이터 저장
	if (NextPosIdx(pq->Rear) == pq->Front) {//만약 Rear다음칸이 Front랑 같으면 꽉 찼다는 소리 & 더 이상 저장X
		printf("Queue 가득 참!");
		exit(-1);
	}
	else {
		pq->Rear = NextPosIdx(pq->Rear);
		pq->Arr[pq->Rear] = data;
	}
}

int Dequeue(Queue* pq) {//Front 위치 한칸 뒤로 이동 후 Front위치의 데이터 반환 및 제거(Front자리 데이터는 항상 비어있다고 생각)
	if (QIsEmpty(pq)) {
		printf("Queue is Empty!");
		exit(-1);
	}
	else {
		pq->Front = NextPosIdx(pq->Front);
		return pq->Arr[pq->Front];//배열이라 굳이 제거는 안하고 그냥 반환
	}
}

int Qpeek(Queue* pq) {
	if (QIsEmpty(pq)) {
		printf("Queue is Empty!");
		exit(-1);
	}
	return pq->Arr[NextPosIdx(pq->Front)];//Dequeue하면 제일 먼저 나올 데이터값 반환(Front 다음칸)
}

int main(void) {
	Queue Q;
	int num;
	QInit(&Q);
	while (1) {
		printf("숫자입력 : ");
		scanf("%d", &num);
		if (num < 1)break;
		Enqueue(&Q, num);
	}
	printf("\n\n입력된 데이터 모두 출력 : ");
	while (!QIsEmpty(&Q))printf("%d ", Dequeue(&Q));//큐는 입력 순서와 나오는 순서 같다(선착순)
	return 0;
}
