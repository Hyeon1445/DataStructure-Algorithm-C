#include <stdio.h>
#include <stdlib.h>
#define BUCKET_NUM 10
#define TRUE 1
#define FALSE 0

//List Queue�� ������� ����!

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

void RadixSort(int arr[], int num, int maxLen) {//maxLen�� �Է� ������ �� ���� �� ����
	Queue buckets[BUCKET_NUM];
	int bucketIDX;
	int pos;
	int i;
	int divfac = 1;//�ڸ��� (LSD : Least Significant Digit �����̹Ƿ� ���� �ڸ������� ����)
	int radix;//N��° �ڸ����� �ش� ����
	for (bucketIDX = 0; bucketIDX < BUCKET_NUM; bucketIDX++) {
		QueueInit(&buckets[bucketIDX]);//Queue �ʱ�ȭ 10��(10���� ����)
	}
	for (pos = 0; pos < maxLen; pos++) {//�ڸ�����ŭ �ݺ�
		for (i = 0; i < num; i++) {//�Է� ������ ������ŭ �ݺ�
			radix = (arr[i] / divfac) % 10;
			Enqueue(&buckets[radix], arr[i]);//�ش� bucket�� �ֱ�
		}
		for (bucketIDX = 0, i = 0; bucketIDX < BUCKET_NUM; bucketIDX++) {
			while (!QIsEmpty(&buckets[bucketIDX]))arr[i++] = Dequeue(&buckets[bucketIDX]);//���� bucket�� ���� ���� ���� ������� ����
		}
		divfac *= 10;//���� �ڸ���
	}
}

int main(void) {
	int n, i, input;
	printf("�Է��� ���� ���� : ");
	scanf("%d", &n);
	int arr[100] = { 0 };
	for (i = 0; i < n; i++) {
		printf("���� �Է� : ");
		scanf("%d", &input);
		arr[i] = input;
	}
	RadixSort(arr,n,5);
	printf("\n\nRadixSort, ��������\n");
	for (i = 0; i < n; i++)printf("%d\n", arr[i]);
	return 0;
}