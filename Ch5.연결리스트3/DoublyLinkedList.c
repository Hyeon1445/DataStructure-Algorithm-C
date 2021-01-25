#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct _node {
	int data;
	struct _node* next;
	struct _node* prev;//����� ���� ����Ʈ
}Node;

typedef struct DoubleLinkedList {
	Node* head;
	Node* cur;
	int numOfData;
}List;

void ListInit(List* plist) {//�ʱ�ȭ
	plist->head = NULL;
	plist->numOfData = 0;
}
void LInsert(List* plist, int data) {//head��ġ�� ��� ����
	Node* newNode = (Node*)malloc(sizeof(Node));//�޸� �Ҵ�
	newNode->data = data;

	newNode->next = plist->head;
	if (plist->head != NULL) {//���� ù ��° ��� ������ �ƴϸ�
		plist->head->prev = newNode;//head�� ���� �����
	}
	newNode->prev = NULL;//����尡 ���� ���̹Ƿ� ���� �������
	plist->head = newNode;//head�� ������!
	(plist->numOfData)++;//��� ����
}
int LFirst(List* plist, int* pdata) {
	if (plist->head == NULL)return FALSE;//��� �ϳ��� ������ FALSE��ȯ
	else {//��� �ּ� �ϳ�
		plist->cur = plist->head;
		*pdata = plist->cur->data;
		return TRUE;//��� �ϳ� �̻��̸� TRUE ��ȯ
	}
}
int LNext(List* plist, int* pdata) {
	if (plist->cur->next == NULL) {//���� ��� ������ FALSE��ȯ
		return FALSE;
	}
	else {//���� ��� ������
		plist->cur = plist->cur->next;//�ڷ� �� ĭ �̵�
		*pdata = plist->cur->data;
		return TRUE;
	}
}
int LPrevious(List* plist, int* pdata) {
	if (plist->cur->prev == NULL) {//�� ��� ������ FALSE��ȯ
		return FALSE;
	}
	else {//�� ��� ������
		plist->cur = plist->cur->prev;//������ �� ĭ �̵�
		*pdata = plist->cur->data;
		return TRUE;
	}
}
int LCount(List* plist) {
	return plist->numOfData;
}

int main(void) {
	List list;
	int data;
	ListInit(&list);
	LInsert(&list, 1);
	LInsert(&list, 2);
	LInsert(&list, 3);
	LInsert(&list, 4);
	LInsert(&list, 5);
	LInsert(&list, 6);
	LInsert(&list, 7);
	LInsert(&list, 8);

	if (LFirst(&list, &data)) {
		printf("%d ", data);
		while (LNext(&list, &data)) {
			printf("%d ", data);
		}
		while (LPrevious(&list, &data)) {
			printf("%d ", data);
		}
		printf("\n\n");
	}
	return 0;
}