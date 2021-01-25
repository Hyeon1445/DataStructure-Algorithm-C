#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int data;
	struct _node *next;
}Node;

int main() {
	Node* head = NULL;
	Node* tail = NULL;
	Node* cur = NULL;
	Node* newNode = NULL;
	int readData;

	while (1) {//������ �Է¹ޱ�
		printf("�ڿ��� �Է�: ");
		scanf("%d", &readData);
		if (readData <= 0)break;

		newNode = (Node*)malloc(sizeof(Node));
		newNode->data = readData;
		newNode->next = NULL;
		if (head == NULL) head = newNode;
		else tail->next = newNode;
		tail = newNode;
	}
	printf("\n\n\n");
	printf("��ü���!\n");
	if (head == NULL)printf("����� ���� ����!");
	else {
		cur = head;
		while (cur != NULL) {
			printf("%d  ", cur->data);
			cur = cur->next;
		}
	}
	printf("\n\n\n");

}
