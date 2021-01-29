#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

typedef struct _node {
	int data;
	struct _node* next;
}Node;

typedef struct ListStack {
	Node* head;
}Stack;

void StackInit(Stack* pstack) {
	pstack->head = NULL;
}
int StackIsEmpty(Stack* pstack) {
	if (pstack->head == NULL)return TRUE;
	else return FALSE;
}
void Push(Stack* pstack, int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = pstack->head;
	pstack->head = newNode;
}
int Pop(Stack* pstack) {
	int removeData;
	Node* removeNode;
	if (StackIsEmpty(pstack)) {
		printf("Stack is Empty!\n");
		exit(-1);
	}
	removeData = pstack->head->data;
	removeNode = pstack->head;
	pstack->head = pstack->head->next;
	free(removeNode);
	return removeData;
}
int Peek(Stack* pstack) {
	if (StackIsEmpty(pstack)) {
		printf("Stack is Empty!\n");
		exit(-1);
	}
	return pstack->head->data;
}

int GetOpPrec(char op) {//������(,/,*,+,-,)�� �켱���� ���� ��ȯ
	if (op == '*' || op == '/')return 3;
	else if (op == '+' || op == '-')return 2;
	else if (op == '(') return 1;
	else return -1;//������ �̿��� ��
}
int WhoPrecOp(char op1, char op2) {//������ �켱���� ��
	int op1Prec = GetOpPrec(op1);
	int op2Prec = GetOpPrec(op2);
	if (op1Prec > op2Prec)return 1;
	else if (op1Prec < op2Prec)return -1;
	else return 0;//���� �켱����
}
void ConvToPostfix(char exp[]) {//���� ǥ����� ���� ǥ������� �ٲ۴�
	Stack stack;
	int expLen = strlen(exp);//���� ǥ��� ����
	char* convExp = (char*)malloc(expLen + 1);

	int i, idx = 0;
	char tok, popOp;

	memset(convExp, 0, sizeof(char) * expLen + 1);//convExp�� 0���� ä���
	//void * memset(void *ptr,int val, size_t len) : ptr�� ���޵� �ּ��� �޸𸮿������� len����Ʈ�� val������ ä���.
	StackInit(&stack); // ���� �ʱ�ȭ
	
	for (i = 0; i < expLen; i++) {
		tok = exp[i];
		if (isdigit(tok)) {//10������ tok�� ����
			convExp[idx++] = tok;
		}
		else {
			switch (tok) {
			case '('://'('������ ���ÿ� �ֱ�
				Push(&stack, tok);
				break;
			
			case ')'://')'������ ���ÿ��� '('���� ����
				while (1) {
					popOp = Pop(&stack);
					if (popOp == '(')break;
					convExp[idx++] = popOp;//'('������ ������ ����pop������ �����ڸ� ����ǥ�⿡ ����
				}
				break;

			case '+': case '-':
			case '*': case '/':
				while (!StackIsEmpty(&stack) && WhoPrecOp(Peek(&stack), tok) >= 0)convExp[idx++] = Pop(&stack);
				Push(&stack, tok);
				break;
			}
		}
	}
	while (!StackIsEmpty(&stack))convExp[idx++] = Pop(&stack);
	strcpy(exp, convExp);
	free(convExp);
}

int CalPostfix(char exp[]){//���� ǥ�� ����ؼ� ����� ��ȯ
	Stack stack;
	int expLen = strlen(exp);
	int i;
	char tok, op1, op2;
	StackInit(&stack);//�����ʱ�ȭ
	for (i = 0; i < expLen; i++) {//���� ǥ��� ���̸�ŭ �ݺ�
		tok = exp[i];
		if (isdigit(tok)) {//�������� Ȯ��
			Push(&stack, tok - '0');//�ƽ�Ű�ڵ� �̿�('0'��ŭ�� ���� ���� ���ڰ� �����)
		}
		else {
			op2 = Pop(&stack);//���� ������ �ݴ�� �����ؾ���
			op1 = Pop(&stack);//(���� 4,2,1������ ��������� 4�� 2�� ������ 2+4)
		}
		if (tok == '+')Push(&stack, op1 + op2);
		else if (tok == '-')Push(&stack, op1 - op2);
		else if (tok == '*')Push(&stack, op1 * op2);
		else if (tok == '/')Push(&stack, op1 / op2);
	}
	return Pop(&stack);//����� ��ȯ
}

int main(void) {
	char exp[100];
	for (int i = 0; i < 3; i++) {
		printf("���� ǥ��(infix notation) : ");
		scanf("%s", exp);
		ConvToPostfix(exp);
		printf("���� ǥ��(postfix notation) : %s\n", exp);
		printf("����� : %d\n\n", CalPostfix(exp));
	}
	return 0;
}