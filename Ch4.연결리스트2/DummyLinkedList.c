#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct _node {//List를 이루고 있는 node에 대한 정보
	int data;
	struct _node* next;
}Node;

typedef struct  linkedlist {//List에 대한 정보
	Node* head;
	Node* cur;
	Node* before;
	int numOfData;
	int (*comp)(int d1, int d2);
}List; 

void ListInit(List* plist) {
	plist->head = (Node*)malloc(sizeof(Node));//dummy node
	plist->head->next = NULL;
	plist->comp = NULL;
	plist->numOfData = 0;//아직 입력 값 없음
}

void FInsert(List* plist, int data) {//맨 앞에 newNode 삽입
	Node* newNode = (Node*)malloc(sizeof(Node));//newNode
	newNode->data = data;//data입력
	newNode->next = plist->head->next;//newNode->next는 dummy의 next(원래의 첫 node)
	plist->head->next = newNode;//dummy->next는 새 노드(새 노드가 첫 번째 노드가 됨)
	(plist->numOfData)++;//노드 수 증가
}

void SInsert(List* plist, int data) {//중간에 삽입
	Node* newNode = (Node*)malloc(sizeof(Node));
	Node* pred = plist->head;//위치 찾기 위한 node pred
	newNode->data = data;//data입력
	while (pred->next != NULL && plist->comp(data, pred->next->data) != 0) {//data<list의 data(현재위치의 다음node)면 stop
		pred = pred->next;//위치찾기
	}
	newNode->next = pred->next;//찾은 위치에 연결
	pred->next = newNode;
	(plist->numOfData)++;//node수 증가
}

void LInsert(List* plist, int data) {
	if (plist->comp == NULL)FInsert(plist, data);//처음 insert
	else SInsert(plist, data);//중간에 insert
}

int LFirst(List* plist, int* pdata) {
	if (plist->head->next == NULL)return FALSE;//첫 번째 node없는경우(입력 X)
	else {//첫 번째 노드값으로!
		plist->before = plist->head;//첫 번째 전 (dummy Node)를 before 이 가리킴
		plist->cur = plist->head->next;//현재 위치 첫번째 노드
		*pdata = plist->cur->data;//data값은 현재(첫번째) 노드의 data
		return TRUE;
	}
}
int LNext(List* plist, int* pdata) {//다음 노드로 한 칸씩 이동하기
	if (plist->cur->next == NULL) return FALSE;//다음 값 없으면 끝
	else {
		plist->before = plist->cur;//현재node를 before값으로 가리킴
		plist->cur = plist->cur->next;//다음node를 현재 node로 가리킴(한 칸씩 뒤로 이동)
		*pdata = plist->cur->data;//포인터pdata에 현재 node의 data값 저장
		return TRUE;
	}
}
int LRemove(List* plist) {
	Node* removeNode = plist->cur;//지울 노드 저장
	int removeData = removeNode->data;//지울 값 저장
	plist->before->next = plist->cur->next;//지울 node 전이랑 후를 연결(지울 노드 빼버림)
	plist->cur = plist->before;//현재 위치 before값으로
	free(removeNode);//지울 노드 메모리 제거
	(plist->numOfData)--;//노드 하나 줄어듦
	return removeData;//제거한 data값 반환
}
int LCount(List* plist) {
	return plist->numOfData;//노드 개수 반환
}
void SetSortRule(List* plist, int(*comp)(int d1, int d2)) {
	plist->comp = comp;//(*comp)(d1,d1)에 비교 값 저장(d1<d2면 0, d1>=d2면 1)
}
int WhoIsPrecede(int d1, int d2) {//정렬할 때 기준 정의
	if (d1 < d2)return 0;
	else return 1;
}

 
int main(void) {
	List list;
	int data;
	ListInit(&list);

	SetSortRule(&list, WhoIsPrecede);

	LInsert(&list, 11);
	LInsert(&list, 11);
	LInsert(&list, 22);
	LInsert(&list, 22);
	LInsert(&list, 33);
	
	printf("현재 데이터 수: %d\n", LCount(&list));

	if (LFirst(&list, &data)) {
		printf("%d ", data);
		while (LNext(&list, &data))printf("%d ", data);
	}
	printf("\n\n\n");
	if (LFirst(&list, &data)) {
		if (data == 22)LRemove(&list);
		while (LNext(&list, &data)) {
			if (data == 22)LRemove(&list);
		}
	}
	printf("현재 데이터의 수: %d \n", LCount(&list));
	if (LFirst(&list, &data)) {
		printf("%d ", data);
		while (LNext(&list, &data))printf("%d ", data);
	}
	printf("\n\n");
	return 0;
}