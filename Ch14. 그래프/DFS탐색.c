#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define STACK_LEN 50

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


//연결리스트 함수들 위에 작성

typedef struct ArrayStack {
	int arr[STACK_LEN];
	int TopIndex;
}Stack;
void StackInit(Stack* pstack) {
	pstack->TopIndex = -1;//(첫 칸 index=0) TopIndex=-1은 비어있는 상태
}
int StackIsEmpty(Stack* pstack) {
	if (pstack->TopIndex == -1) return TRUE;//TopIndex가 -1 이면 비어있음
	else return FALSE;//그 이외에는 한개 이상 데이터 있음
}
void SPush(Stack* pstack, int data) {//넣기
	(pstack->TopIndex)++;//TopIndex하나 증가
	pstack->arr[pstack->TopIndex] = data;//data 넣기
}
int SPop(Stack* pstack) {//꺼내기
	int removeIdx;
	if (StackIsEmpty(pstack)) {//스택이 비어 있는 경우
		printf("Stack is Empty!\n");
		exit(-1);
	}
	removeIdx = pstack->TopIndex;//TopIndex값 저장
	(pstack->TopIndex)--;//TopIndex줄어들음
	return pstack->arr[removeIdx];//삭제된 값
}
int SPeek(Stack* pstack) {//들여다보기
	if (StackIsEmpty(pstack)) {
		printf("Stack is Empty!\n");
		exit(-1);
	}
	return pstack->arr[pstack->TopIndex];//맨 나중에 넣은거 반환
}
//스택 함수들

enum {A,B,C,D,E,F,G,H,I,J};
typedef struct _graph {
	int numV;//정점 개수
	int numE;//간선 개수
	List* adjList;//간선 정보
	int* visitInfo;//방문여부(배열)
}ALGraph; //Adjacent List Graph

void GraphInit(ALGraph* pg, int numV) {//그래프 초기화
	int i;
	pg->adjList = (List*)malloc(sizeof(List) * numV);//간선정보 저장할 리스트 생성
	pg->numV = numV;//정점 수는 입력된 numV수
	pg->numE = 0;//간선 수는 처음엔 0개(연결 전)
	for (i = 0; i < numV; i++) {
		ListInit(&(pg->adjList[i]));//정점 생성된 리스트 초기화
		SetSortRule(&(pg->adjList[i]), WhoIsPrecede);//리스트 정렬기준
	}
	pg->visitInfo = (int*)malloc(sizeof(int) * pg->numV);//정점의 수만큼을 길이로 할당
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);//배열의 모든 요소 0으로 초기화!
}
void GraphDestroy(ALGraph* pg) {//그래프 리소스 해제/ 연결 리스트 소멸
	if (pg->adjList != NULL)free(pg->adjList);
	if (pg->visitInfo != NULL)free(pg->visitInfo);
}
void AddEdge(ALGraph* pg, int fromV, int toV) {//간선의 추가 from -> to
	LInsert(&(pg->adjList[fromV]), toV);
	LInsert(&(pg->adjList[toV]), fromV);
	(pg->numE)++;
}
void ShowGraphEdgeInfo(ALGraph* pg) {//간선 정보 출력
	int i;
	int vx;
	for (i = 0; i < pg->numV; i++) {
		if (LFirst(&(pg->adjList[i]), &vx)) {
			printf("%c 와 연결된 정점 : ", i + 65);
			printf("%c ", vx + 65);
			while (LNext(&(pg->adjList[i]), &vx))printf("%c ", vx + 65);
		}
		printf("\n");
	}
}

void DFSShowGraphVertex(ALGraph* pg, int startV) {
	Stack stack;//되돌아갈 때 쓸 스택
	int visitV = startV;//처음 정점부터 시작
	int nextV;
	StackInit(&stack);//스택 초기화
	VisitVertex(pg, visitV);//첫 번째 정점 방문
	SPush(&stack, visitV);//스택에 방문한 정점 저장
	while(LFirst(&(pg->adjList[visitV]), &nextV) == TRUE) {//모든 정점을 방문, nextV에 정점 정보 저장
		int visitFlag = FALSE;
		if (VisitVertex(pg, nextV) == TRUE) {//방문 여부 확인 -> 방문 성공
			SPush(&stack, visitV);//스택에 PUSH
			visitV = nextV;
			visitFlag = TRUE;
		}
		else {
			while (LNext(&(pg->adjList[visitV]), &nextV) == TRUE) {//LFirst에서 방문 실패한 경우 LNext로 정점 방문
				if (VisitVertex(pg, nextV) == TRUE) {//방문여부 확인 -> 방문 성공
					SPush(&stack, visitV);
					visitV = nextV;
					visitFlag = TRUE;
					break;
				}
			}
		}
		if (visitFlag == FALSE) {//정점 방문에 실패
			if (StackIsEmpty(&stack) == TRUE)break;//프로그램 종료
			else visitV = SPop(&stack);//길 되돌아가기!
		}
	}
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);//이후의 탐색을 위해 탐색 정보 초기화!
}

int VisitVertex(ALGraph* pg, int visitV)
{
	if (pg->visitInfo[visitV] == 0) {//만약 방문 전이면
		pg->visitInfo[visitV] = 1;//방문한 표시
		printf("%c ", visitV + 65);
		return TRUE;//방문성공
	}
	return FALSE;//방문실패
}
int main(void) {
	ALGraph graph;
	GraphInit(&graph, 7);//그래프 초기화, 정점 5개 A,B,C,D,E
	AddEdge(&graph, A, B);
	AddEdge(&graph, A, D);
	AddEdge(&graph, B, C);
	AddEdge(&graph, D, C);
	AddEdge(&graph, D, E);
	AddEdge(&graph, E, F);
	AddEdge(&graph, E, G);
	ShowGraphEdgeInfo(&graph);
	DFSShowGraphVertex(&graph, A);
	printf("\n");
	DFSShowGraphVertex(&graph, C);
	printf("\n");
	DFSShowGraphVertex(&graph, E);
	printf("\n");
	DFSShowGraphVertex(&graph, G);
	printf("\n");
	GraphDestroy(&graph);
	return 0;
}
