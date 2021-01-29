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

int GetOpPrec(char op) {//연산자(,/,*,+,-,)의 우선순위 정보 반환
	if (op == '*' || op == '/')return 3;
	else if (op == '+' || op == '-')return 2;
	else if (op == '(') return 1;
	else return -1;//연산자 이외의 값
}
int WhoPrecOp(char op1, char op2) {//연산자 우선순위 비교
	int op1Prec = GetOpPrec(op1);
	int op2Prec = GetOpPrec(op2);
	if (op1Prec > op2Prec)return 1;
	else if (op1Prec < op2Prec)return -1;
	else return 0;//같은 우선순위
}
void ConvToPostfix(char exp[]) {//중위 표기법을 후위 표기법으로 바꾼다
	Stack stack;
	int expLen = strlen(exp);//중위 표기법 길이
	char* convExp = (char*)malloc(expLen + 1);

	int i, idx = 0;
	char tok, popOp;

	memset(convExp, 0, sizeof(char) * expLen + 1);//convExp를 0으로 채운다
	//void * memset(void *ptr,int val, size_t len) : ptr로 전달된 주소의 메모리에서부터 len바이트를 val값으로 채운다.
	StackInit(&stack); // 스택 초기화
	
	for (i = 0; i < expLen; i++) {
		tok = exp[i];
		if (isdigit(tok)) {//10진수면 tok에 저장
			convExp[idx++] = tok;
		}
		else {
			switch (tok) {
			case '('://'('나오면 스택에 넣기
				Push(&stack, tok);
				break;
			
			case ')'://')'나오면 스택에서 '('까지 빼기
				while (1) {
					popOp = Pop(&stack);
					if (popOp == '(')break;
					convExp[idx++] = popOp;//'('나오기 전까지 스택pop순서로 연산자를 후위표기에 저장
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

int CalPostfix(char exp[]){//후위 표기 계산해서 결과값 반환
	Stack stack;
	int expLen = strlen(exp);
	int i;
	char tok, op1, op2;
	StackInit(&stack);//스택초기화
	for (i = 0; i < expLen; i++) {//후위 표기식 길이만큼 반복
		tok = exp[i];
		if (isdigit(tok)) {//정수인지 확인
			Push(&stack, tok - '0');//아스키코드 이용('0'만큼의 값을 빼서 숫자값 만들기)
		}
		else {
			op2 = Pop(&stack);//스택 순서랑 반대로 연산해야함
			op1 = Pop(&stack);//(만약 4,2,1순서로 들어있으면 4와 2를 꺼내서 2+4)
		}
		if (tok == '+')Push(&stack, op1 + op2);
		else if (tok == '-')Push(&stack, op1 - op2);
		else if (tok == '*')Push(&stack, op1 * op2);
		else if (tok == '/')Push(&stack, op1 / op2);
	}
	return Pop(&stack);//결과값 반환
}

int main(void) {
	char exp[100];
	for (int i = 0; i < 3; i++) {
		printf("중위 표기(infix notation) : ");
		scanf("%s", exp);
		ConvToPostfix(exp);
		printf("후위 표기(postfix notation) : %s\n", exp);
		printf("결과값 : %d\n\n", CalPostfix(exp));
	}
	return 0;
}