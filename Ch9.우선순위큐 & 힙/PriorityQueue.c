#include <stdio.h>
#include <stdlib.h>

#define HEAP_LEN 100
//heap코드랑 다 똑같음(함수 이름만 다름), PriorityQueue에 heap 적용

typedef int PriorityComp(char d1, char d2);
typedef struct _heap {
	PriorityComp* comp;
	int NumOfData;
	char arr[HEAP_LEN];
}PriorityQueue;

void PriorityQueueInit(PriorityQueue* pheap, PriorityComp pc) {
	pheap->NumOfData = 0;
	pheap->comp = pc;//비교 함수
}
int PriorityQueueIsEmpty(PriorityQueue* pheap) {
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
int GetHighPriChildIdx(PriorityQueue* pheap, int idx) {
	if (GetLeftChildIdx(idx) > pheap->NumOfData)return 0;
	else if (GetLeftChildIdx(idx) == pheap->NumOfData)return GetLeftChildIdx(idx);
	else {
		if (pheap->comp(pheap->arr[GetLeftChildIdx(idx)], pheap->arr[GetRightChildIdx(idx)]) < 0)
			//여기서는 비교 조건이 RightChild우선순위 - LeftChild우선순위
			//만약 음수면 RightChild우선순위가 더 높다(작은 값)
			return GetRightChildIdx(idx);
		else return GetLeftChildIdx(idx);//비교값 양수면 LeftChild우선순위가 더 높다
	}
}
void PriorityEnqueue(PriorityQueue* pheap, char data) {//데이터 삽입
	int idx = pheap->NumOfData + 1;//맨 뒷 자리에 넣는다
	while (idx != 1) {//루트가 아니면 반복
		if (pheap->comp(data, pheap->arr[GetParentIdx(idx)]) > 0) {
			//만약 parent의 data - 입력 data 가 양수면 입력 data의 우선순위가 높다(더 작은 값)
			pheap->arr[idx] = pheap->arr[GetParentIdx(idx)];//parent자리의 data를 child자리로 옮김
			idx = GetParentIdx(idx);//parent의 위치로 감
		}
		else break;//자리 찾으면 break
	}
	pheap->arr[idx] = data;//맞는 자리에 data 저장
	pheap->NumOfData += 1;//입력 데이터 수 하나 증가
}
char PriorityDequeue(PriorityQueue* pheap) {//루트 데이터 삭제하고 맨 뒤에꺼 집어넣고 자리 찾아감
	char removeData = pheap->arr[1];//삭제할 루트 데이터
	char lastElem = pheap->arr[pheap->NumOfData];//루트 자리로 들어갈 마지막 데이터
	int ParentIdx = 1;
	int ChildIdx;
	while (ChildIdx = GetHighPriChildIdx(pheap, ParentIdx)) {//높은 우선순위Child를 Child값에 저장
		//만약 Child가 없으면 (0반환) 반복문 스탑
		if (pheap->comp(lastElem, pheap->arr[ChildIdx]) >= 0)break;//만약 자리 잘 찾으면 스탑
		pheap->arr[ParentIdx] = pheap->arr[ChildIdx];
		ParentIdx = ChildIdx;
	}
	pheap->arr[ParentIdx] = lastElem;//적당한 위치에 저장
	pheap->NumOfData -= 1;//데이터 하나 감소
	return removeData;
}
int DataPriorityComp(char ch1, char ch2) {//우선순위 조건 지정, 원하는대로 바꿔쓰면 됨
	return ch2 - ch1;
}
int main(void) {
	PriorityQueue pQ;
	PriorityQueueInit(&pQ, DataPriorityComp);
	char a, b;
	printf("알파벳 5개 입력\n");
	for (int i = 0; i < 5; i++) {
		printf("알파벳 : ");
		scanf("%c", &a);
		scanf("%c", &b);
		PriorityEnqueue(&pQ, a);
	}
	while (!PriorityQueueIsEmpty(&pQ))printf("%c\n", PriorityDequeue(&pQ));
	return 0;
}
