#include <stdio.h>
#include <stdlib.h>
#define BUCKET_NUM 10
#define TRUE 1
#define FALSE 0

//List Queue를 기반으로 구현!

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

void RadixSort(int arr[], int num, int maxLen) {//maxLen은 입력 데이터 중 가장 긴 길이
	Queue buckets[BUCKET_NUM];
	int bucketIDX;
	int pos;
	int i;
	int divfac = 1;//자릿수 (LSD : Least Significant Digit 기준이므로 일의 자릿수부터 시작)
	int radix;//N번째 자릿수의 해당 숫자
	for (bucketIDX = 0; bucketIDX < BUCKET_NUM; bucketIDX++) {
		QueueInit(&buckets[bucketIDX]);//Queue 초기화 10개(10진수 기준)
	}
	for (pos = 0; pos < maxLen; pos++) {//자릿수만큼 반복
		for (i = 0; i < num; i++) {//입력 데이터 개수만큼 반복
			radix = (arr[i] / divfac) % 10;
			Enqueue(&buckets[radix], arr[i]);//해당 bucket에 넣기
		}
		for (bucketIDX = 0, i = 0; bucketIDX < BUCKET_NUM; bucketIDX++) {
			while (!QIsEmpty(&buckets[bucketIDX]))arr[i++] = Dequeue(&buckets[bucketIDX]);//같은 bucket에 들은 값은 들어온 순서대로 나옴
		}
		divfac *= 10;//다음 자릿수
	}
}

int main(void) {
	int n, i, input;
	printf("입력할 숫자 개수 : ");
	scanf("%d", &n);
	int arr[100] = { 0 };
	for (i = 0; i < n; i++) {
		printf("숫자 입력 : ");
		scanf("%d", &input);
		arr[i] = input;
	}
	RadixSort(arr,n,5);
	printf("\n\nRadixSort, 오름차순\n");
	for (i = 0; i < n; i++)printf("%d\n", arr[i]);
	return 0;
}