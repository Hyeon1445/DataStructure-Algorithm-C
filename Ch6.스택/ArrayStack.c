#include <stdio.h>

#define STACK_LEN 100
#define TRUE 1
#define FALSE 0

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

int main(void) {
	Stack stack;
	StackInit(&stack);
	int num,input;
	printf("���� � �Է�? : ");
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
