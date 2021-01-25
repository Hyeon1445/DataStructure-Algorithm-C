#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct _node {
	int data;
	struct _node* next;
}Node;

typedef struct CircularLinkedList {
	Node* tail;
	Node* cur;
	Node* before;
	int numOfData;
}List;

void ListInit(List* plist) {//����Ʈ �ʱ�ȭ(ó���� ȣ��)
	plist->tail = NULL;
	plist->cur = NULL;
	plist->before = NULL;
	plist->numOfData = 0;
}

void LInsert(List* plist, int data) {//tail�� �����ϴ� ���
	Node* newNode = (Node*)malloc(sizeof(Node));//�����
	newNode->data = data;//������ �Է�
	if (plist->tail == NULL){//ó�� insert�ϴ� ���
		plist->tail = newNode;//List�� tail�ڸ��� insert
		newNode->next = newNode; //���� ���� ����Ʈ(ó���� ���� �̾���)
	}
	else {//ó���� �ƴ� ��
		newNode->next = plist->tail->next;//���� ����� ������ tail->next(head)
		plist->tail->next = newNode;//head��ġ(tail�� ����)�� newNode : ������� ���� head��ġ�� ���Ե�
		plist->tail = newNode;//tail�� newNode�� �̵� : tail��ġ�� ���Ե�
	}
	(plist->numOfData)++;//����Ʈ�� ��� ����
}

void LInsertFront(List* plist, int data) {//head�� �����ϴ� ���
	Node* newNode = (Node*)malloc(sizeof(Node));//�� ��� �Ҵ�
	newNode->data = data;//������ �Է�
	if (plist->tail == NULL) {//ó�� �Է��ϴ� ���
		plist->tail = newNode;
		newNode->next = newNode;
	}
	else {//ó�� �ƴ� ���
		newNode->next = plist->tail->next;
		plist->tail->next = newNode;//tail��ġ�� �� ��� ����
	}
	(plist->numOfData)++;//����Ʈ�� ��� ����
}

int LFirst(List* plist, int* pdata) {
	if (plist->tail == NULL)return FALSE;//��� �ϳ��� ����
	else {//��� �ּ� �ϳ��� ����
		plist->before = plist->tail;//head �� ��ġ�� tail
		plist->cur = plist->tail->next;//����� tail�� next(head)
		*pdata = plist->cur->data;//�����Ͱ� ����
		return TRUE;
	}
}
int LNext(List* plist, int* pdata) {
	if (plist->tail == NULL)return FALSE;//��� �ϳ��� ������ �ȵ�
	else {//��� �ϳ� �̻��� ��� �� ���� ���ѹݺ�
		plist->before = plist->cur;
		plist->cur = plist->cur->next;//��ĭ�� �������� �ű�
		*pdata = plist->cur->data;
		return TRUE;
	}
}
int LRemove(List* plist) {//��� ����
	Node* removeNode = plist->cur;//������ ��
	int removeData = removeNode->data;//������ ������

	if (removeNode == plist->tail) {//���1)������ ��尡 ������ġ
		if (plist->tail == plist->tail->next) {//���1-1)��� �ϳ���
			plist->tail = NULL;
		}
		else {//���1-2)��� ������
			plist->tail = plist->before;
		}
	}
	plist->before->next = plist->cur->next;
	plist->cur = plist->before;//������ �� �� ���� �յ� ���� �̾���
	free(removeNode);//�� ������ ���ų�� �޸� ����
	(plist->numOfData)--;//��� ����
	return removeData;
}
int LCount(List* plist) {
	return plist->numOfData;
}

int main(void) {
	List list;
	int data, i, nodeNum;
	ListInit(&list);


	//�� �Է�
	LInsert(&list, 4);
	LInsert(&list, 5);
	LInsert(&list, 6);
	LInsert(&list, 7);
	LInsertFront(&list, 3);
	LInsertFront(&list, 2);
	LInsertFront(&list, 1);
	
	
	//5���� �ݺ����
	if (LFirst(&list, &data)) {
		printf("%d ", data);
		for (i = 0; i < LCount(&list) * 5; i++) {
			if (LNext(&list, &data)) {
				printf("%d ", data);
			}
		}
	}
	printf("\n\n\n");


	//3�� ����� ����
	nodeNum = LCount(&list);
	if (nodeNum != 0) {
		LFirst(&list, &data);
		if (data % 3 == 0)LRemove(&list);
		for (i = 0; i < nodeNum - 1; i++) {
			LNext(&list, &data);
			if (data % 3 == 0)LRemove(&list);
		}
	}

	//��ü �� ���
	if (LFirst(&list, &data)) {
		printf("%d ", data);
		for (i = 0; i < LCount(&list) - 1; i++) {
			if (LNext(&list, &data))printf("%d ", data);
		}
	}
	return 0;
}