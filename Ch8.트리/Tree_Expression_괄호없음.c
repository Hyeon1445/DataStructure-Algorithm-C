#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BinaryTreeNode {
	int data;
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;
}TNode;

typedef struct _node {
	int data;
	struct _node* next;
}SNode;

typedef struct ListStack {
	SNode* head;
}Stack;

void StackInit(Stack* pstack) {
	pstack->head = NULL;
}

int StackIsEmpty(Stack* pstack) {
	if (pstack->head == NULL)return 1;
	else return 0;
}

void StackPush(Stack* pstack, int data) {
	SNode* newNode = (SNode*)malloc(sizeof(SNode));
	newNode->data = data;
	newNode->next = pstack->head;
	pstack->head = newNode;
}

int StackPop(Stack* pstack) {
	int removeData;
	SNode* removeNode;
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

TNode* MakeBinaryTreeNode(void) {
	TNode* nd = (TNode*)malloc(sizeof(TNode));
	nd->left = NULL;
	nd->right = NULL;
	return nd;
}

int GetData(TNode* bt) {
	return bt->data;
}

void SetData(TNode* bt, int data) {
	bt->data = data;
}

TNode* GetLeftSubTree(TNode* bt) {
	return bt->left;
}

TNode* GetRightSubTree(TNode* bt) {
	return bt->right;
}

void MakeLeftSubTree(TNode* main, TNode* sub) {
	if (main->left != NULL)free(main->left);
	main->left = sub;
}

void MakeRightSubTree(TNode* main, TNode* sub) {
	if (main->right != NULL)free(main->right);
	main->right = sub;
}

int StackPeek(Stack* pstack) {
	if (StackIsEmpty(pstack)) {
		printf("Stack is Empty!\n");
		exit(-1);
	}
	return pstack->head->data;
}

TNode* MakeExpTree(char exp[]) {//수식 입력
	Stack stack;
	TNode* pnode;
	int expLen = strlen(exp);
	int i;
	StackInit(&stack);
	for (i = 0; i < expLen; i++) {
		pnode = MakeBinaryTreeNode();
		if (isdigit(exp[i]))SetData(pnode, exp[i] - '0');
		else {
			MakeRightSubTree(pnode, StackPop(&stack));
			MakeLeftSubTree(pnode, StackPop(&stack));
			SetData(pnode, exp[i]);
		}
		StackPush(&stack, pnode);//만들어진 서브노드를 또 하나의 노드라고 생각하고 Push
	}
	return StackPop(&stack);//만들어진 전체 트리 Pop반환
}

typedef void VisitFuncPtr(int data);

void InorderTraverse(TNode* bt,VisitFuncPtr action) {
	if (bt == NULL)return;
	InorderTraverse(bt->left,action);
	action(bt->data);
	InorderTraverse(bt->right,action);
}

void PreorderTraverse(TNode* bt,VisitFuncPtr action) {
	if (bt == NULL)return;
	action(bt->data);
	PreorderTraverse(bt->left,action);
	PreorderTraverse(bt->right,action);
}

void PostorderTraverse(TNode* bt,VisitFuncPtr action) {
	if (bt == NULL)return;
	PostorderTraverse(bt->left,action);
	PostorderTraverse(bt->right,action);
	action(bt->data);
}

void ShowNodeData(int data) {
	if (0 <= data && data <= 9)printf("%d ", data);
	else printf("%c ", data);
}

int EvaluateExpTree(TNode* bt) {//수식 계산
	int op1, op2;
	if (GetLeftSubTree(bt) == NULL && GetRightSubTree(bt) == NULL)return GetData(bt);
	op1 = EvaluateExpTree(GetLeftSubTree(bt));
	op2 = EvaluateExpTree(GetRightSubTree(bt));
	switch (GetData(bt)) {
	case '+':
		return op1 + op2;
	case '-':
		return op1 - op2;
	case '*':
		return op1 * op2;
	case '/':
		return op1 / op2;
	}
	return 0;
}

void ShowPrefixTypeExp(TNode* bt) {//전위 표기법
	PreorderTraverse(bt, ShowNodeData);
}

void ShowInfixTypeExp(TNode* bt) {//중위 표기법
	InorderTraverse(bt, ShowNodeData);
}

void ShowPostfixTypeExp(TNode* bt) {//후위 표기법
	PostorderTraverse(bt, ShowNodeData);
}

int main(void) {
	char exp[100];
	printf("수식 입력(postfix) :");
	scanf("%s", exp);
	TNode* eTree = MakeExpTree(exp);
	printf("\n\n전위 표기법 수식 : ");
	ShowPrefixTypeExp(eTree);
	printf("\n\n중위 표기법의 수식 : ");
	ShowInfixTypeExp(eTree);
	printf("\n\n후위 표기법의 수식 : ");
	ShowPostfixTypeExp(eTree);
	printf("\n\n연산의 결과 : %d\n\n", EvaluateExpTree(eTree));
}