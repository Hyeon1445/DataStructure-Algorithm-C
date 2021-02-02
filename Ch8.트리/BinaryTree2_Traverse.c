#include <stdio.h>
#include <stdlib.h>

typedef struct _BinaryTreeNode {
	int data;
	struct _BinaryTreeNode* left;
	struct _BinaryTreeNode* right;
}Node;

Node* MakeBinaryTreeNode(void) {//이진 트리 노드 생성 및 초기화
	Node* nd = (Node*)malloc(sizeof(Node));
	nd->left = NULL;
	nd->right = NULL;
	return nd;
}

int GetData(Node* bt) {//노드에 저장된 데이터 반환
	return bt->data;
}

void SetData(Node* bt, int data) {//노드에 데이터 저장
	bt->data = data;
}

Node* GetLeftSubTree(Node* bt) {//왼쪽 서브 트리 주소값 반환
	return bt->left;
}

Node* GetRightSubTree(Node* bt) {//오른족 서브 트리 주소값 반환
	return bt->right;
}

void MakeLeftSubTree(Node* main, Node* sub) {//sub트리를 main트리의 왼쪽에 연결
	if (main->left != NULL)free(main->left);//왼쪽이 비어있지 않으면 비워버림(원래는 순회하면서 그 아래 노드를 다 지워야함)
	main->left = sub;//왼쪽에 서브트리 넣기
}

void MakeRightSubTree(Node* main, Node* sub) {//sub트리를 main트리의 오른쪽에 연결
	if (main->right != NULL)free(main->right);//오른쪽이 비어있지 않으면 비워버림(원래는 순회하면서 그 아래 노드를 다 지워야함)
	main->right = sub;//오른쪽에 서브트리 넣기
}

void InorderTraverse(Node* bt) {//중위 순회 : Left -> Root -> Right
	if (bt == NULL) return;//NULL인 노드면 반환(함수 탈출)
	InorderTraverse(bt->left);
	printf("%d\n", bt->data);
	InorderTraverse(bt->right);
}

void PreorderTraverse(Node* bt) {//전위 순회 : Root -> Left -> Right
	if (bt==NULL)return; //NULL인 노드면 반환(함수 탈출)
	printf("%d\n", bt->data);
	PreorderTraverse(bt->left);
	PreorderTraverse(bt->right);
}

void PostorderTraverse(Node* bt) {//후위 순회 : Left -> Right -> Root
	if (bt == NULL)return;
	PostorderTraverse(bt->left);
	PostorderTraverse(bt->right);
	printf("%d\n", bt->data);
}

int main(void) {
	Node* bt1 = MakeBinaryTreeNode();
	Node* bt2 = MakeBinaryTreeNode();
	Node* bt3 = MakeBinaryTreeNode();
	Node* bt4 = MakeBinaryTreeNode();
	
	SetData(bt1, 1);
	SetData(bt2, 2);
	SetData(bt3, 3);
	SetData(bt4, 4);

	MakeLeftSubTree(bt1, bt2);
	MakeRightSubTree(bt1, bt3);
	MakeLeftSubTree(bt2, bt4);

	printf("%d\n", GetData(bt1));
	printf("%d\n", GetData(GetLeftSubTree(bt1)));
	printf("%d\n", GetData(GetRightSubTree(bt1)));
	printf("%d\n", GetData(GetLeftSubTree(GetLeftSubTree(bt1))));


	//			1
	//		  ↙ ↘
	//		 2	   3
	//	  ↙
	//	 4
	

	printf("\n\nInorder Traverse\n");
	InorderTraverse(bt1);
	printf("\n\nPreorder Traverse\n");
	PreorderTraverse(bt1);
	printf("\n\nPostorder Traverse\n");
	PostorderTraverse(bt1);
	return 0;
}