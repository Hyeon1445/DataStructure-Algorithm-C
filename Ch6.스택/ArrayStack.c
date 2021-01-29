#include <stdio.h>

#define STACK_LEN 100
#define TRUE 1
#define FALSE 0

typedef struct ArrayStack {
	int arr[STACK_LEN];
	int TopIndex;
}Stack;
void StackInit(Stack* pstack) {
	pstack->TopIndex = -1;//(첫 칸 index=0) TopIndex=-1은 비어있는 상태
}
int StackIsEmpty(Stack* pstack) {
	if (pstack->TopIndex == -1) return TRUE;//TopIndex가 -1 이면 비어있음
	else return FALSE;//그 이외에는 한개 이상 데이터 있음
}
void SPush(Stack* pstack, int data) {//넣기
	(pstack->TopIndex)++;//TopIndex하나 증가
	pstack->arr[pstack->TopIndex] = data;//data 넣기
}
int SPop(Stack* pstack) {//꺼내기
	int removeIdx;
	if (StackIsEmpty(pstack)) {//스택이 비어 있는 경우
		printf("Stack is Empty!\n");
		exit(-1);
	}
	removeIdx = pstack->TopIndex;//TopIndex값 저장
	(pstack->TopIndex)--;//TopIndex줄어들음
	return pstack->arr[removeIdx];//삭제된 값
}
int SPeek(Stack* pstack) {//들여다보기
	if (StackIsEmpty(pstack)) {
		printf("Stack is Empty!\n");
		exit(-1);
	}
	return pstack->arr[pstack->TopIndex];//맨 나중에 넣은거 반환
}

int main(void) {
	Stack stack;
	StackInit(&stack);
	int num,input;
	printf("숫자 몇개 입력? : ");
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
