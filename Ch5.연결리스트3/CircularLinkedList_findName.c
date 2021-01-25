#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct _node {
	int data;
	char name[100];
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

void LInsert(List* plist, int data,char name[]) {//tail�� �����ϴ� ���
	Node* newNode = (Node*)malloc(sizeof(Node));//�����
	newNode->data = data;//������ �Է�
	strcpy(newNode->name, name);

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

int LFirst(List* plist, int* pdata,char*name) {
	if (plist->tail == NULL)return 0;//��� �ϳ��� ����
	else {//��� �ּ� �ϳ��� ����
		plist->before = plist->tail;//head �� ��ġ�� tail
		plist->cur = plist->tail->next;//����� tail�� next(head)
		*pdata = plist->cur->data;//�����Ͱ� ����
		if (strcmp(name, plist->cur->name) == 0) {
			return 2;
		}

		return 1;
	}
}
int LNext(List* plist, int* pdata,char*name) {
	if (plist->tail == NULL)return 0;//��� �ϳ��� ������ �ȵ�
	else {//��� �ϳ� �̻��� ��� �� ���� ���ѹݺ�
		plist->before = plist->cur;
		plist->cur = plist->cur->next;//��ĭ�� �������� �ű�
		*pdata = plist->cur->data;
		if (strcmp(name, plist->cur->name) == 0)return 2;
		return 1;
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

void printName(List* plist) {
	printf("%s�Դϴ�(��� : %d)\n",plist->cur->name,plist->cur->data);
	
}

int main(void) {
	List list;
	int data, i, nodeNum,num;
	char name[100];
	ListInit(&list);


	//�� �Է�
	printf("4���� ���� �Է�\n");
	for (i = 0; i < 4; i++) {
		printf("�̸� : ");
		scanf("%s", name);
		printf("��� : ");
		scanf("%d", &data);
		LInsert(&list, data, name);
	}
	printf("\n\n\n");
	printf("�̸��� ���ڸ� �Է��ؼ� 000 ���� ?�� �� ������ ��� ����ϱ�\n");
	printf("�̸� : ");
	scanf("%s", name);
	if (LFirst(&list, &data, name)) {
		if (LFirst(&list, &data, name) == 2) {
			printf("%s�� ����� %d\n ", name, data);
		}
		else {
			while (1) {
				if (LNext(&list, &data, name) == 2)break;
			}
			printf("%s�� ����� %d\n", name, data);
		}
	}
	printf("���� �Է� : ");
	scanf("%d", &num);
	for (i = 0; i < num; i++) {
		LNext(&list, &data, name);
	}
	printf("%d�� �� ������ ",num);
	printName(&list);

	return 0;
}