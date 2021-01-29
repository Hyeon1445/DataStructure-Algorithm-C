#include <stdio.h>
#include <stdlib.h>

#define TRUE 1;
#define FALSE 0;

typedef struct _node {
	int data;
	struct _node* next;
}Node;
typedef struct ListStack {
	Node* head;
}Stack;
void StackInit(Stack* pstack) {//�ʱ�ȭ
	pstack->head = NULL;
}
int StackIsEmpty(Stack* pstack) {
	if (pstack->head == NULL) {
		return TRUE;//��������� TRUE
	}
	else {
		return FALSE;//�ϳ� �̻� ������ FALSE
	}
}
void SPush(Stack* pstack, int data) {//������ �ֱ�(head�ʿ� �߰�)
	Node* newNode = (Node*)malloc(sizeof(Node));//�޸� �Ҵ�
	newNode->data = data;//data�Է�
	newNode->next = pstack->head;//head�ʿ� ����
	pstack->head = newNode;//����尡 head�� ��
}
int SPop(Stack* pstack) {
	int removeData;
	Node* removeNode;
	if (StackIsEmpty(&pstack)) {
		printf("Stack is Empty!\n");
		exit(-1);
	}
	removeData = pstack->head->data;
	removeNode = pstack->head;
	
	pstack->head = pstack->head->next;//head ��ĭ �ڷ� �ű��
	free(removeNode);//��� ����
	return removeData;//������ �����Ͱ� ��ȯ
}
int SPeek(Stack* pstack) {
	if (StackIsEmpty(&pstack)) {
		printf("Stack Is Empty!\n");
		exit(-1);
	}
	return pstack->head->data;
}

int main(void) {
	Stack stack;
	StackInit(&stack);//���� �ʱ�ȭ
	int num, input;
	printf("���� �� �� �Է�? : ");
	scanf("%d", &num);
	for (int i = 0; i < num; i++) {
		printf("���� �Է� : ");
		scanf("%d", &input);
		SPush(&stack, input);
	}
	while (!StackIsEmpty(&stack)) {
		printf("%d ", SPop(&stack));
	}
	return 0;
}