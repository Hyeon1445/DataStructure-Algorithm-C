#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

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
	
	printf("���� ������ ��: %d\n", LCount(&list));

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
	printf("���� �������� ��: %d \n", LCount(&list));
	if (LFirst(&list, &data)) {
		printf("%d ", data);
		while (LNext(&list, &data))printf("%d ", data);
	}
	printf("\n\n");
	return 0;
}