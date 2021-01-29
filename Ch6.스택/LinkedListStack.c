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
void StackInit(Stack* pstack) {//초기화
	pstack->head = NULL;
}
int StackIsEmpty(Stack* pstack) {
	if (pstack->head == NULL) {
		return TRUE;//비어있으면 TRUE
	}
	else {
		return FALSE;//하나 이상 있으면 FALSE
	}
}
void SPush(Stack* pstack, int data) {//데이터 넣기(head쪽에 추가)
	Node* newNode = (Node*)malloc(sizeof(Node));//메모리 할당
	newNode->data = data;//data입력
	newNode->next = pstack->head;//head쪽에 연결
	pstack->head = newNode;//새노드가 head가 됨
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
	
	pstack->head = pstack->head->next;//head 한칸 뒤로 옮기기
	free(removeNode);//노드 삭제
	return removeData;//삭제한 데이터값 반환
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
	StackInit(&stack);//스택 초기화
	int num, input;
	printf("숫자 몇 개 입력? : ");
	scanf("%d", &num);
	for (int i = 0; i < num; i++) {
		printf("숫자 입력 : ");
		scanf("%d", &input);
		SPush(&stack, input);
	}
	while (!StackIsEmpty(&stack)) {
		printf("%d ", SPop(&stack));
	}
	return 0;
}