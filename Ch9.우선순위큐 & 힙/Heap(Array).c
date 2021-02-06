#include <stdio.h>
#include <stdlib.h>

#define HEAP_LEN 100


//�켱������ ���� ��(1�� �������� ����)�� ��Ʈ�� ����!
//���� �켱���� ���� ���� �� ����!

typedef struct _heapElem {
	int priority;
	char data;
}HeapElem;

typedef struct _heap {
	int NumOfData;
	HeapElem arr[HEAP_LEN];
}Heap;

void HeapInit(Heap* pheap) {
	pheap->NumOfData = 0;
}

int HeapIsEmpty(Heap* pheap) { //��������� 1,������� ������ 0 
	if (pheap->NumOfData == 0) return 1;
	else return 0;
}
int GetParentIdx(int idx) {
	return idx / 2;
}
int GetLeftChildIdx(int idx) {//���� child �ε����� ��ȯ
	return idx * 2;
}
int GetRightChildIdx(int idx) {//������ child �ε��� �� ��ȯ
	return idx * 2+1;
}
int GetHighPriorityChildIdx(Heap* pheap, int idx) {//Child�� �� ���� �켱����(�� ������)�� Child�� �ε��� ��ȯ
	if (GetLeftChildIdx(idx) > pheap->NumOfData)return 0;//���� �ε����� ��������� 0��ȯ
	else if (GetLeftChildIdx(idx) == pheap->NumOfData)return GetLeftChildIdx(idx); //���� LeftChild�� ���� ���̸� LeftChild�� �ε��� ��ȯ(������ ����)
	else {
		if (pheap->arr[GetLeftChildIdx(idx)].priority > pheap->arr[GetRightChildIdx(idx)].priority)return GetRightChildIdx(idx);
		//���� LeftChild�� �켱������ RightChild�� �켱�������� ũ�� RightChild�� �ε��� ��ȯ(�� ���� �켱���� ��ȯ)
		else return GetLeftChildIdx(idx);
		//���� LeftChild�� �켱������ RightChild�� �켱�������� ������ LeftChild�� �ε��� ��ȯ(�� ���� �켱���� ��ȯ)
	}
}
void HeapInsert(Heap* pheap, char data, int priority) {//�� �ڿ� ������ �ְ� �ڸ� ã�ư���!
	int idx = pheap->NumOfData + 1;//�� �� ���� �ε��� ����
	HeapElem elem = { priority,data };//�� element
	while (idx != 1) {//��Ʈ���� ���� ����
		if (priority < (pheap->arr[GetParentIdx(idx)].priority)) {//���԰� �켱������ Parent���� ũ��
			pheap->arr[idx] = pheap->arr[GetParentIdx(idx)];//���� ��ġ(child)�� parent�� ����� �� ����
			idx = GetParentIdx(idx);//���� ��ġ�� Parent�� �ε������� ��
		}
		else break;//������ �´� �ڸ� ������ ��ž
	}
	pheap->arr[idx] = elem;//�������� �� �ڸ��� �Է°� ����
	pheap->NumOfData+=1;//���� �� �����ͼ� 1����
}
char HeapDelete(Heap* pheap) {//��Ʈ ���� �� �� �켱���� ���� ä������ �ڿ� ���� �ٲٱ�
	char RemoveData = (pheap->arr[1]).data;//������ ���� ��Ʈ�� ����� char��
	HeapElem lastElem = pheap->arr[pheap->NumOfData];//������ �켱������ �� ����
	int parentIdx = 1;
	int childIdx;
	while (childIdx = GetHighPriorityChildIdx(pheap, parentIdx)) {//Child�� ������� ����������(��������� 0)
		if (lastElem.priority <= pheap->arr[childIdx].priority)break;//���� ������ �켱������ child�� �켱�������� ������ ��ž (�ڸ� �� ã�ư�, ��)
		pheap->arr[parentIdx] = pheap->arr[childIdx];//�ڸ� ã�ư��� ����, parent���� child�� ����
		parentIdx = childIdx;
	}
	pheap->arr[parentIdx] = lastElem;//������ ��ġ�� lastElem�ֱ�
	pheap->NumOfData -= 1;//������ �ϳ� ����
	return RemoveData;//���ŵ� data�� ��ȯ
}
int main(void) {
	Heap heap;
	HeapInit(&heap);
	int priority;
	char a,b;
	for (int i = 0; i < 5; i++) {
		printf("���ĺ� �Է� : ");
		scanf("%c" ,&a);
		scanf("%c", &b);//\n �����ֱ�
		printf("�켱���� �Է� : ");
		scanf("%d", &priority);
		scanf("%c", &b);//\n�����ֱ�
		HeapInsert(&heap, a, priority);
	}
	while (!HeapIsEmpty(&heap))printf("%c \n", HeapDelete(&heap));
	return 0;
}