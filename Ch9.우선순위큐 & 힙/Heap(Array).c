#include <stdio.h>
#include <stdlib.h>

#define HEAP_LEN 100


//우선순위가 높은 값(1에 가까울수록 높음)이 루트에 저장!
//같은 우선순위 값이 들어올 수 있음!

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

int HeapIsEmpty(Heap* pheap) { //비어있으면 1,비어있지 않으면 0 
	if (pheap->NumOfData == 0) return 1;
	else return 0;
}
int GetParentIdx(int idx) {
	return idx / 2;
}
int GetLeftChildIdx(int idx) {//왼쪽 child 인덱스값 반환
	return idx * 2;
}
int GetRightChildIdx(int idx) {//오른쪽 child 인덱스 값 반환
	return idx * 2+1;
}
int GetHighPriorityChildIdx(Heap* pheap, int idx) {//Child중 더 높은 우선순위(더 작은값)인 Child의 인덱스 반환
	if (GetLeftChildIdx(idx) > pheap->NumOfData)return 0;//왼쪽 인덱스가 비어있으면 0반환
	else if (GetLeftChildIdx(idx) == pheap->NumOfData)return GetLeftChildIdx(idx); //만약 LeftChild가 가장 끝이면 LeftChild의 인덱스 반환(오른쪽 없음)
	else {
		if (pheap->arr[GetLeftChildIdx(idx)].priority > pheap->arr[GetRightChildIdx(idx)].priority)return GetRightChildIdx(idx);
		//만약 LeftChild의 우선순위가 RightChild의 우선순위보다 크면 RightChild의 인덱스 반환(더 높은 우선순위 반환)
		else return GetLeftChildIdx(idx);
		//만약 LeftChild의 우선순위가 RightChild의 우선순위보다 작으면 LeftChild의 인덱스 반환(더 높은 우선순위 반환)
	}
}
void HeapInsert(Heap* pheap, char data, int priority) {//맨 뒤에 데이터 넣고 자리 찾아가기!
	int idx = pheap->NumOfData + 1;//맨 끝 다음 인덱스 저장
	HeapElem elem = { priority,data };//새 element
	while (idx != 1) {//루트까지 가면 멈춤
		if (priority < (pheap->arr[GetParentIdx(idx)].priority)) {//삽입값 우선순위가 Parent보다 크면
			pheap->arr[idx] = pheap->arr[GetParentIdx(idx)];//현재 위치(child)에 parent에 저장된 값 저장
			idx = GetParentIdx(idx);//현재 위치는 Parent의 인덱스값이 됨
		}
		else break;//순서에 맞는 자리 들어갔으면 스탑
	}
	pheap->arr[idx] = elem;//최종으로 들어갈 자리에 입력값 저장
	pheap->NumOfData+=1;//삽입 후 데이터수 1증가
}
char HeapDelete(Heap* pheap) {//루트 빼고 맨 뒤 우선순위 값을 채워넣은 뒤에 순서 바꾸기
	char RemoveData = (pheap->arr[1]).data;//제거할 값은 루트에 저장된 char값
	HeapElem lastElem = pheap->arr[pheap->NumOfData];//마지막 우선순위의 값 저장
	int parentIdx = 1;
	int childIdx;
	while (childIdx = GetHighPriorityChildIdx(pheap, parentIdx)) {//Child가 비어있지 않을때까지(비어있으면 0)
		if (lastElem.priority <= pheap->arr[childIdx].priority)break;//만약 마지막 우선순위가 child의 우선순위보다 작으면 스탑 (자리 잘 찾아감, 끝)
		pheap->arr[parentIdx] = pheap->arr[childIdx];//자리 찾아가는 과정, parent값에 child값 넣음
		parentIdx = childIdx;
	}
	pheap->arr[parentIdx] = lastElem;//적당한 위치에 lastElem넣기
	pheap->NumOfData -= 1;//데이터 하나 감소
	return RemoveData;//제거된 data값 반환
}
int main(void) {
	Heap heap;
	HeapInit(&heap);
	int priority;
	char a,b;
	for (int i = 0; i < 5; i++) {
		printf("알파벳 입력 : ");
		scanf("%c" ,&a);
		scanf("%c", &b);//\n 없애주기
		printf("우선순위 입력 : ");
		scanf("%d", &priority);
		scanf("%c", &b);//\n없애주기
		HeapInsert(&heap, a, priority);
	}
	while (!HeapIsEmpty(&heap))printf("%c \n", HeapDelete(&heap));
	return 0;
}