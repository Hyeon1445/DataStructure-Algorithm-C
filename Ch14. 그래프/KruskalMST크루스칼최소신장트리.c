#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define STACK_LEN 50
#define HEAP_LEN 100

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

typedef struct _edge {
	int v1;
	int v2;
	int weight;
}Edge;


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
int QPeek(Queue* pq) {
	if (QIsEmpty(pq)) {
		printf("Queue is Empty!\n");
		exit(-1);
	}
	else {
		return pq->Front->data;
	}
}
//큐 함수들

//heap코드랑 다 똑같음(함수 이름만 다름), PriorityQueue에 heap 적용


typedef int PriorityComp (Edge d1, Edge d2);

typedef struct _heap {
	PriorityComp* comp;
	int NumOfData;
	Edge arr[HEAP_LEN];
}Heap;

void HeapInit(Heap* pheap, PriorityComp pc) {
	pheap->NumOfData = 0;
	pheap->comp = pc;//비교 함수
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
			//여기서는 비교 조건이 RightChild우선순위 - LeftChild우선순위
			//만약 음수면 RightChild우선순위가 더 높다(작은 값)
			return GetRightChildIdx(idx);
		else return GetLeftChildIdx(idx);//비교값 양수면 LeftChild우선순위가 더 높다
	}
}
void HeapInsert(Heap* pheap, Edge data) {//데이터 삽입
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
Edge HeapDelete(Heap* pheap) {//루트 데이터 삭제하고 맨 뒤에꺼 집어넣고 자리 찾아감
	Edge removeData = pheap->arr[1];//삭제할 루트 데이터
	Edge lastElem = pheap->arr[pheap->NumOfData];//루트 자리로 들어갈 마지막 데이터
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
//힙 함수

typedef Heap PQueue;
void PQueueInit(PQueue* ppq, PriorityComp pc) {
	HeapInit(ppq, pc);
}
int PQIsEmpty(PQueue* ppq) {
	return HeapIsEmpty(ppq);
}
void PEnqueue(PQueue* ppq, Edge data) {
	HeapInsert(ppq,data);
}
Edge PDequeue(PQueue* ppq) {
	return HeapDelete(ppq);
}
//우선순위큐 함수

enum {A,B,C,D,E,F,G,H,I,J};
typedef struct _graph {
	int numV;//정점 개수
	int numE;//간선 개수
	List* adjList;//간선 정보
	int* visitInfo;//방문여부(배열)
	PQueue pqueue;//간선의 가중치 정보 저장
}ALGraph; //Adjacent List Graph

int PQWeightComp(Edge d1, Edge d2) {
	return d1.weight - d2.weight;
}

void GraphInit(ALGraph* pg, int numV) {//그래프 초기화//다른 코드 파일들과 차이가 있음!
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
	PQueueInit(&(pg->pqueue), PQWeightComp);//여기가 추가된 부분
}

void GraphDestroy(ALGraph* pg) {//그래프 리소스 해제/ 연결 리스트 소멸
	if (pg->adjList != NULL)free(pg->adjList);
	if (pg->visitInfo != NULL)free(pg->visitInfo);
}
void AddEdge(ALGraph* pg, int fromV, int toV,int weight) {//간선의 추가 from -> to//다른 코드 파일들과 차이가 있음!
	Edge edge = { fromV,toV,weight };
	LInsert(&(pg->adjList[fromV]), toV);
	LInsert(&(pg->adjList[toV]), fromV);
	(pg->numE)++;
	PEnqueue(&(pg->pqueue), edge);//간선의 가중치 정보를 우선순위 큐에 저장
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
	memset(pg->visitInfo, 0, sizeof(int)* pg->numV);//이후의 탐색을 위해 탐색 정보 초기화!
}


void BFSShowGraphVertex(ALGraph* pg, int startV) {
	Queue queue;
	int visitV = startV;
	int nextV;
	QueueInit(&queue);//큐 초기화
	VisitVertex(pg, visitV);//첫 번째 정점 방문
	while (LFirst(&(pg->adjList[visitV]), &nextV) == TRUE) {//visitV와 연결된 모든 정점에 방문
		if (VisitVertex(pg, nextV) == TRUE)Enqueue(&queue, nextV);//만약 방문성공하면 Queue에 저장
		while (LNext(&(pg->adjList[visitV]), &nextV) == TRUE) {
			if (VisitVertex(pg, nextV) == TRUE)Enqueue(&queue, nextV);//만약 방문성공하면 Queue에 저장
		}
		if (QIsEmpty(&queue) == TRUE)break;//큐가 비면 탐색 종료
		else visitV = Dequeue(&queue);//큐에서 하나 꺼내서 while문 다시 시작
	}
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);//다음 탐색을 위해 초기화
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


void RemoveWayEdge(ALGraph* pg, int fromV, int toV) {//한쪽 방향의 간선 소멸
	int edge;
	if (LFirst(&(pg->adjList[fromV]), &edge)) {
		if (edge == toV) {
			LRemove(&(pg->adjList[fromV]));
			return;
		}
		while (LNext(&(pg->adjList[fromV]), &edge)) {
			if (edge == toV) {
				LRemove(&(pg->adjList[fromV]));
				return;
			}
		}
	}
}

void RemoveEdge(ALGraph* pg, int fromV, int toV) {//간선 소멸
	RemoveWayEdge(pg, fromV, toV);
	RemoveWayEdge(pg, toV, fromV);
	(pg->numE)--;
}

void RecoverEdge(ALGraph* pg, int fromV, int toV, int weight) {
	LInsert(&(pg->adjList[fromV]), toV);
	LInsert(&(pg->adjList[toV]), fromV);
	(pg->numE)++;
}
int IsConnVertex(ALGraph* pg, int v1, int v2) {
	Stack stack;
	int visitV = v1;
	int nextV;
	StackInit(&stack);
	VisitVertex(pg, visitV);
	SPush(&stack, visitV);
	while (LFirst(&(pg->adjList[visitV]), &nextV) == TRUE) {
		int visitFlag = FALSE;
		if (nextV == v2) {
			memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
			return TRUE;
		}
		if (VisitVertex(pg, nextV) == TRUE) {
			SPush(&stack, visitV);
			visitV = nextV;
			visitFlag = TRUE;
		}
		else {
			while (LNext(&(pg->adjList[visitV]), &nextV) == TRUE) {
				if (nextV == v2) {
					memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
					return TRUE;
				}
				if (VisitVertex(pg, nextV) == TRUE) {
					SPush(&stack, visitV);
					visitV = nextV;
					visitFlag = TRUE;
					break;
				}
			}
		}
		if (visitFlag == FALSE) {
			if (StackIsEmpty(&stack) == TRUE)break;
			else {
				visitV = SPop(&stack);
			}
		}
	}
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
	return FALSE;
}

void ConKruskalMST(ALGraph* pg) {
	Edge recoverEdge[20];
	Edge edge;
	int edgeIdx = 0;
	int i;
	while (pg->numE + 1 > pg->numV) {//MST간선의 수+1 = 정점의 수 일때 끝
		edge = PDequeue(&(pg->pqueue));//우선순위 큐에서 가중치가 제일 높은 간선의 정보 꺼내기
		RemoveEdge(pg, edge.v1, edge.v2);//우선순위 큐에서 꺼낸 간선을 실제로 그래프에서 삭제

		if (!IsConnVertex(pg, edge.v1, edge.v2)) {//간선을 삭제하고 나서 두 정점을 연결하는 경로가 있는지 확인
			RecoverEdge(pg, edge.v1, edge.v2, edge.weight);//경로가 없으면 삭제한 간선을 복원
			recoverEdge[edgeIdx++] = edge;//복원했기 때문에 +1
		}

	}
	for (i = 0; i < edgeIdx; i++) {
		PEnqueue(&(pg->pqueue), recoverEdge[i]);//우선순위 큐에서 삭제된 간선의 정보를 회복
	}
}
void ShowGraphEdgeWeightInfo(ALGraph* pg) {//간선의 가중치 정보 출력
	PQueue copyPQ = pg->pqueue;
	Edge edge;
	while (!PQIsEmpty(&copyPQ)) {
		edge = PDequeue(&copyPQ);
		printf("( %c - %c ), weight : %d )\n", edge.v1 + 65, edge.v2 + 65, edge.weight);
	}
}

int main(void) {
	ALGraph graph;
	GraphInit(&graph, 6);//그래프 초기화, 정점 6개 A,B,C,D,E,F
	AddEdge(&graph, A, B,9);
	AddEdge(&graph, B, C,2);
	AddEdge(&graph, A, C,12);
	AddEdge(&graph, A, D,8);
	AddEdge(&graph, D, C,6);
	AddEdge(&graph, A, F,11);
	AddEdge(&graph, F, D,4);
	AddEdge(&graph, D, E, 3);
	AddEdge(&graph, E, C, 7);
	AddEdge(&graph, F, E, 13);
	
	ConKruskalMST(&graph);//최소 신장 트리로 변환
	printf("\n\n");
	ShowGraphEdgeInfo(&graph);
	printf("\n\n");
	ShowGraphEdgeWeightInfo(&graph);
	
	GraphDestroy(&graph);
	return 0;
}
