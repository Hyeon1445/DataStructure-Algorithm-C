#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define STACK_LEN 50
#define HEAP_LEN 100

typedef struct _node {//List�� �̷�� �ִ� node�� ���� ����
	int data;
	struct _node* next;
}Node;

typedef struct  linkedlist {//List�� ���� ����
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
	plist->numOfData = 0;//���� �Է� �� ����
}

void FInsert(List* plist, int data) {//�� �տ� newNode ����
	Node* newNode = (Node*)malloc(sizeof(Node));//newNode
	newNode->data = data;//data�Է�
	newNode->next = plist->head->next;//newNode->next�� dummy�� next(������ ù node)
	plist->head->next = newNode;//dummy->next�� �� ���(�� ��尡 ù ��° ��尡 ��)
	(plist->numOfData)++;//��� �� ����
}

void SInsert(List* plist, int data) {//�߰��� ����
	Node* newNode = (Node*)malloc(sizeof(Node));
	Node* pred = plist->head;//��ġ ã�� ���� node pred
	newNode->data = data;//data�Է�
	while (pred->next != NULL && plist->comp(data, pred->next->data) != 0) {//data<list�� data(������ġ�� ����node)�� stop
		pred = pred->next;//��ġã��
	}
	newNode->next = pred->next;//ã�� ��ġ�� ����
	pred->next = newNode;
	(plist->numOfData)++;//node�� ����
}

void LInsert(List* plist, int data) {
	if (plist->comp == NULL)FInsert(plist, data);//ó�� insert
	else SInsert(plist, data);//�߰��� insert
}

int LFirst(List* plist, int* pdata) {
	if (plist->head->next == NULL)return FALSE;//ù ��° node���°��(�Է� X)
	else {//ù ��° ��尪����!
		plist->before = plist->head;//ù ��° �� (dummy Node)�� before �� ����Ŵ
		plist->cur = plist->head->next;//���� ��ġ ù��° ���
		*pdata = plist->cur->data;//data���� ����(ù��°) ����� data
		return TRUE;
	}
}
int LNext(List* plist, int* pdata) {//���� ���� �� ĭ�� �̵��ϱ�
	if (plist->cur->next == NULL) return FALSE;//���� �� ������ ��
	else {
		plist->before = plist->cur;//����node�� before������ ����Ŵ
		plist->cur = plist->cur->next;//����node�� ���� node�� ����Ŵ(�� ĭ�� �ڷ� �̵�)
		*pdata = plist->cur->data;//������pdata�� ���� node�� data�� ����
		return TRUE;
	}
}
int LRemove(List* plist) {
	Node* removeNode = plist->cur;//���� ��� ����
	int removeData = removeNode->data;//���� �� ����
	plist->before->next = plist->cur->next;//���� node ���̶� �ĸ� ����(���� ��� ������)
	plist->cur = plist->before;//���� ��ġ before������
	free(removeNode);//���� ��� �޸� ����
	(plist->numOfData)--;//��� �ϳ� �پ��
	return removeData;//������ data�� ��ȯ
}
int LCount(List* plist) {
	return plist->numOfData;//��� ���� ��ȯ
}
void SetSortRule(List* plist, int(*comp)(int d1, int d2)) {
	plist->comp = comp;//(*comp)(d1,d1)�� �� �� ����(d1<d2�� 0, d1>=d2�� 1)
}
int WhoIsPrecede(int d1, int d2) {//������ �� ���� ����
	if (d1 < d2)return 0;
	else return 1;
}


//���Ḯ��Ʈ �Լ��� ���� �ۼ�

typedef struct ArrayStack {
	int arr[STACK_LEN];
	int TopIndex;
}Stack;
void StackInit(Stack* pstack) {
	pstack->TopIndex = -1;//(ù ĭ index=0) TopIndex=-1�� ����ִ� ����
}
int StackIsEmpty(Stack* pstack) {
	if (pstack->TopIndex == -1) return TRUE;//TopIndex�� -1 �̸� �������
	else return FALSE;//�� �̿ܿ��� �Ѱ� �̻� ������ ����
}
void SPush(Stack* pstack, int data) {//�ֱ�
	(pstack->TopIndex)++;//TopIndex�ϳ� ����
	pstack->arr[pstack->TopIndex] = data;//data �ֱ�
}
int SPop(Stack* pstack) {//������
	int removeIdx;
	if (StackIsEmpty(pstack)) {//������ ��� �ִ� ���
		printf("Stack is Empty!\n");
		exit(-1);
	}
	removeIdx = pstack->TopIndex;//TopIndex�� ����
	(pstack->TopIndex)--;//TopIndex�پ����
	return pstack->arr[removeIdx];//������ ��
}
int SPeek(Stack* pstack) {//�鿩�ٺ���
	if (StackIsEmpty(pstack)) {
		printf("Stack is Empty!\n");
		exit(-1);
	}
	return pstack->arr[pstack->TopIndex];//�� ���߿� ������ ��ȯ
}
//���� �Լ���

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
int QPeek(Queue* pq) {
	if (QIsEmpty(pq)) {
		printf("Queue is Empty!\n");
		exit(-1);
	}
	else {
		return pq->Front->data;
	}
}
//ť �Լ���

//heap�ڵ�� �� �Ȱ���(�Լ� �̸��� �ٸ�), PriorityQueue�� heap ����


typedef int PriorityComp (Edge d1, Edge d2);

typedef struct _heap {
	PriorityComp* comp;
	int NumOfData;
	Edge arr[HEAP_LEN];
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
void HeapInsert(Heap* pheap, Edge data) {//������ ����
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
Edge HeapDelete(Heap* pheap) {//��Ʈ ������ �����ϰ� �� �ڿ��� ����ְ� �ڸ� ã�ư�
	Edge removeData = pheap->arr[1];//������ ��Ʈ ������
	Edge lastElem = pheap->arr[pheap->NumOfData];//��Ʈ �ڸ��� �� ������ ������
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
//�� �Լ�

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
//�켱����ť �Լ�

enum {A,B,C,D,E,F,G,H,I,J};
typedef struct _graph {
	int numV;//���� ����
	int numE;//���� ����
	List* adjList;//���� ����
	int* visitInfo;//�湮����(�迭)
	PQueue pqueue;//������ ����ġ ���� ����
}ALGraph; //Adjacent List Graph

int PQWeightComp(Edge d1, Edge d2) {
	return d1.weight - d2.weight;
}

void GraphInit(ALGraph* pg, int numV) {//�׷��� �ʱ�ȭ//�ٸ� �ڵ� ���ϵ�� ���̰� ����!
	int i;
	pg->adjList = (List*)malloc(sizeof(List) * numV);//�������� ������ ����Ʈ ����
	pg->numV = numV;//���� ���� �Էµ� numV��
	pg->numE = 0;//���� ���� ó���� 0��(���� ��)
	for (i = 0; i < numV; i++) {
		ListInit(&(pg->adjList[i]));//���� ������ ����Ʈ �ʱ�ȭ
		SetSortRule(&(pg->adjList[i]), WhoIsPrecede);//����Ʈ ���ı���
	}
	pg->visitInfo = (int*)malloc(sizeof(int) * pg->numV);//������ ����ŭ�� ���̷� �Ҵ�
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);//�迭�� ��� ��� 0���� �ʱ�ȭ!
	PQueueInit(&(pg->pqueue), PQWeightComp);//���Ⱑ �߰��� �κ�
}

void GraphDestroy(ALGraph* pg) {//�׷��� ���ҽ� ����/ ���� ����Ʈ �Ҹ�
	if (pg->adjList != NULL)free(pg->adjList);
	if (pg->visitInfo != NULL)free(pg->visitInfo);
}
void AddEdge(ALGraph* pg, int fromV, int toV,int weight) {//������ �߰� from -> to//�ٸ� �ڵ� ���ϵ�� ���̰� ����!
	Edge edge = { fromV,toV,weight };
	LInsert(&(pg->adjList[fromV]), toV);
	LInsert(&(pg->adjList[toV]), fromV);
	(pg->numE)++;
	PEnqueue(&(pg->pqueue), edge);//������ ����ġ ������ �켱���� ť�� ����
}
void ShowGraphEdgeInfo(ALGraph* pg) {//���� ���� ���
	int i;
	int vx;
	for (i = 0; i < pg->numV; i++) {
		if (LFirst(&(pg->adjList[i]), &vx)) {
			printf("%c �� ����� ���� : ", i + 65);
			printf("%c ", vx + 65);
			while (LNext(&(pg->adjList[i]), &vx))printf("%c ", vx + 65);
		}
		printf("\n");
	}
}

void DFSShowGraphVertex(ALGraph* pg, int startV) {
	Stack stack;//�ǵ��ư� �� �� ����
	int visitV = startV;//ó�� �������� ����
	int nextV;
	StackInit(&stack);//���� �ʱ�ȭ
	VisitVertex(pg, visitV);//ù ��° ���� �湮
	SPush(&stack, visitV);//���ÿ� �湮�� ���� ����
	while(LFirst(&(pg->adjList[visitV]), &nextV) == TRUE) {//��� ������ �湮, nextV�� ���� ���� ����
		int visitFlag = FALSE;
		if (VisitVertex(pg, nextV) == TRUE) {//�湮 ���� Ȯ�� -> �湮 ����
			SPush(&stack, visitV);//���ÿ� PUSH
			visitV = nextV;
			visitFlag = TRUE;
		}
		else {
			while (LNext(&(pg->adjList[visitV]), &nextV) == TRUE) {//LFirst���� �湮 ������ ��� LNext�� ���� �湮
				if (VisitVertex(pg, nextV) == TRUE) {//�湮���� Ȯ�� -> �湮 ����
					SPush(&stack, visitV);
					visitV = nextV;
					visitFlag = TRUE;
break;
				}
			}
		}
		if (visitFlag == FALSE) {//���� �湮�� ����
			if (StackIsEmpty(&stack) == TRUE)break;//���α׷� ����
			else visitV = SPop(&stack);//�� �ǵ��ư���!
		}
	}
	memset(pg->visitInfo, 0, sizeof(int)* pg->numV);//������ Ž���� ���� Ž�� ���� �ʱ�ȭ!
}


void BFSShowGraphVertex(ALGraph* pg, int startV) {
	Queue queue;
	int visitV = startV;
	int nextV;
	QueueInit(&queue);//ť �ʱ�ȭ
	VisitVertex(pg, visitV);//ù ��° ���� �湮
	while (LFirst(&(pg->adjList[visitV]), &nextV) == TRUE) {//visitV�� ����� ��� ������ �湮
		if (VisitVertex(pg, nextV) == TRUE)Enqueue(&queue, nextV);//���� �湮�����ϸ� Queue�� ����
		while (LNext(&(pg->adjList[visitV]), &nextV) == TRUE) {
			if (VisitVertex(pg, nextV) == TRUE)Enqueue(&queue, nextV);//���� �湮�����ϸ� Queue�� ����
		}
		if (QIsEmpty(&queue) == TRUE)break;//ť�� ��� Ž�� ����
		else visitV = Dequeue(&queue);//ť���� �ϳ� ������ while�� �ٽ� ����
	}
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);//���� Ž���� ���� �ʱ�ȭ
}

int VisitVertex(ALGraph* pg, int visitV)
{
	if (pg->visitInfo[visitV] == 0) {//���� �湮 ���̸�
		pg->visitInfo[visitV] = 1;//�湮�� ǥ��
		printf("%c ", visitV + 65);
		return TRUE;//�湮����
	}
	return FALSE;//�湮����
}


void RemoveWayEdge(ALGraph* pg, int fromV, int toV) {//���� ������ ���� �Ҹ�
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

void RemoveEdge(ALGraph* pg, int fromV, int toV) {//���� �Ҹ�
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
	while (pg->numE + 1 > pg->numV) {//MST������ ��+1 = ������ �� �϶� ��
		edge = PDequeue(&(pg->pqueue));//�켱���� ť���� ����ġ�� ���� ���� ������ ���� ������
		RemoveEdge(pg, edge.v1, edge.v2);//�켱���� ť���� ���� ������ ������ �׷������� ����

		if (!IsConnVertex(pg, edge.v1, edge.v2)) {//������ �����ϰ� ���� �� ������ �����ϴ� ��ΰ� �ִ��� Ȯ��
			RecoverEdge(pg, edge.v1, edge.v2, edge.weight);//��ΰ� ������ ������ ������ ����
			recoverEdge[edgeIdx++] = edge;//�����߱� ������ +1
		}

	}
	for (i = 0; i < edgeIdx; i++) {
		PEnqueue(&(pg->pqueue), recoverEdge[i]);//�켱���� ť���� ������ ������ ������ ȸ��
	}
}
void ShowGraphEdgeWeightInfo(ALGraph* pg) {//������ ����ġ ���� ���
	PQueue copyPQ = pg->pqueue;
	Edge edge;
	while (!PQIsEmpty(&copyPQ)) {
		edge = PDequeue(&copyPQ);
		printf("( %c - %c ), weight : %d )\n", edge.v1 + 65, edge.v2 + 65, edge.weight);
	}
}

int main(void) {
	ALGraph graph;
	GraphInit(&graph, 6);//�׷��� �ʱ�ȭ, ���� 6�� A,B,C,D,E,F
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
	
	ConKruskalMST(&graph);//�ּ� ���� Ʈ���� ��ȯ
	printf("\n\n");
	ShowGraphEdgeInfo(&graph);
	printf("\n\n");
	ShowGraphEdgeWeightInfo(&graph);
	
	GraphDestroy(&graph);
	return 0;
}
