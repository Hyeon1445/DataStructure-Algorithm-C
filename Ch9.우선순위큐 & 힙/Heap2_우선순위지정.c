#include <stdio.h>
#include <stdlib.h>

#define HEAP_LEN 100

typedef int PriorityComp(char d1, char d2);
typedef struct _heap {
	PriorityComp* comp;
	int NumOfData;
	char arr[HEAP_LEN];
}Heap;

void HeapInit(Heap* pheap, PriorityComp pc) {
	pheap->NumOfData = 0;
	pheap->comp = pc;//�� �Լ�
}
int HeapIsEmpty(Heap* pheap) {
	if (pheap->NumOfData == 0)return 1;
	else return 0;
}
int GetParentIdx(int idx) {
	return idx / 2;
}
int GetLeftChildIdx(int idx) {
	return idx * 2;
}
int GetRightChildIdx(int idx) {
	return idx * 2 + 1;
}
int GetHighPriChildIdx(Heap* pheap, int idx) {
	if (GetLeftChildIdx(idx) > pheap->NumOfData)return 0;
	else if (GetLeftChildIdx(idx) == pheap->NumOfData)return GetLeftChildIdx(idx);
	else {
		if (pheap->comp(pheap->arr[GetLeftChildIdx(idx)], pheap->arr[GetRightChildIdx(idx)]) < 0)
			//���⼭�� �� ������ RightChild�켱���� - LeftChild�켱����
			//���� ������ RightChild�켱������ �� ����(���� ��)
			return GetRightChildIdx(idx);
		else return GetLeftChildIdx(idx);//�񱳰� ����� LeftChild�켱������ �� ����
	}
}
void HeapInsert(Heap* pheap, char data) {//������ ����
	int idx = pheap->NumOfData + 1;//�� �� �ڸ��� �ִ´�
	while (idx != 1) {//��Ʈ�� �ƴϸ� �ݺ�
		if (pheap->comp(data, pheap->arr[GetParentIdx(idx)]) > 0) {
			//���� parent�� data - �Է� data �� ����� �Է� data�� �켱������ ����(�� ���� ��)
			pheap->arr[idx] = pheap->arr[GetParentIdx(idx)];//parent�ڸ��� data�� child�ڸ��� �ű�
			idx = GetParentIdx(idx);//parent�� ��ġ�� ��
		}
		else break;//�ڸ� ã���� break
	}
	pheap->arr[idx] = data;//�´� �ڸ��� data ����
	pheap->NumOfData += 1;//�Է� ������ �� �ϳ� ����
}
char HeapDelete(Heap* pheap) {//��Ʈ ������ �����ϰ� �� �ڿ��� ����ְ� �ڸ� ã�ư�
	char removeData = pheap->arr[1];//������ ��Ʈ ������
	char lastElem = pheap->arr[pheap->NumOfData];//��Ʈ �ڸ��� �� ������ ������
	int ParentIdx = 1;
	int ChildIdx;
	while (ChildIdx = GetHighPriChildIdx(pheap, ParentIdx)) {//���� �켱����Child�� Child���� ����
		//���� Child�� ������ (0��ȯ) �ݺ��� ��ž
		if (pheap->comp(lastElem, pheap->arr[ChildIdx]) >= 0)break;//���� �ڸ� �� ã���� ��ž
		pheap->arr[ParentIdx] = pheap->arr[ChildIdx];
		ParentIdx = ChildIdx;
	}
	pheap->arr[ParentIdx] = lastElem;//������ ��ġ�� ����
	pheap->NumOfData -= 1;//������ �ϳ� ����
	return removeData;
}
int DataPriorityComp(char ch1, char ch2) {//�켱���� ���� ����, ���ϴ´�� �ٲ㾲�� ��
	return ch2 - ch1;
}
int main(void) {
	Heap heap;
	HeapInit(&heap, DataPriorityComp);
	char a, b;
	printf("���ĺ� 5�� �Է�\n");
	for (int i = 0; i < 5; i++) {
		printf("���ĺ� : ");
		scanf("%c", &a);
		scanf("%c", &b);
		HeapInsert(&heap, a);
	}
	while (!HeapIsEmpty(&heap))printf("%c\n", HeapDelete(&heap));
	return 0;
}
