#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct BinaryTreeNode {
	int data;
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;
}Node;

Node* MakeBinaryTreeNode(void) {//노드를 동적으로 할당해서 그 노드의 주소값 반환
	Node* node = (Node*)malloc(sizeof(Node));
	node->left = NULL;
	node->right = NULL;
	return node;
}
int GetData(Node* bt) {//노드에 저장된 데이터 반환
	return bt->data;
}

void SetData(Node* bt, int data) {//인자로 전달된 데이터를 노드에 저장
	bt->data = data;
}

Node* GetLeftSubTree(Node* bt) {//인자로 전달된 노드의 왼쪽 자식 노드의 주소값 반환
	return bt->left;
}
Node* GetRightSubTree(Node* bt) {//인자로 전달된 노드의 오른쪽 자식 노드의 주소값 반환
	return bt->right;
}

void MakeLeftSubTree(Node* main, Node* sub) {//인자로 전달된 노드의 왼쪽 자식 노드를 교체
	if (main->left != NULL)free(main->left);//왼쪽 비어있지 않으면 일단 비운다
	main->left = sub;//left에 subtree연결
}
void MakeRightSubTree(Node* main, Node* sub) {//인자로 전달된 노드의 오른쪽 자식 노드를 교체
	if (main->right != NULL)free(main->right);//오른쪽 비어있지 않으면 일단 비온다
	main->right=sub;//right에 subtree연결
}



typedef void VisitFuncPtr(int data);
void PreorderTraverse(Node* bt, VisitFuncPtr action) {//main -> left ->right
	if (bt == NULL)return;//비어있으면 끝
	action(bt->data);
	PreorderTraverse(bt->left, action);
	PreorderTraverse(bt->right, action);
}
void InorderTraverse(Node* bt, VisitFuncPtr action) {//left -> main -> right
	if (bt == NULL)return;//비어있으면 끝
	InorderTraverse(bt->left, action);
	action(bt->data);
	InorderTraverse(bt->right, action);
}
void PostorderTraverse(Node* bt, VisitFuncPtr action) { //left -> right -> main
	if (bt == NULL)return;//비어있으면 끝
	PostorderTraverse(bt->left, action);
	PostorderTraverse(bt->right, action);
	action(bt->data);
}
Node* RemoveLeftSubTree(Node* bt) {//왼쪽 서브트리 삭제
	Node* deleteNode=NULL;
	if (bt != NULL) {
		deleteNode = bt->left;
		bt->left = NULL;
	}
	return deleteNode;
}
Node* RemoveRightSubTree(Node* bt) {//오른쪽 서브트리 삭제
	Node* deleteNode=NULL;
	if (bt != NULL) {
		deleteNode = bt->right;
		bt->right = NULL;
	}
	return deleteNode;
}
void ChangeLeftSubTree(Node* main, Node* sub) {
	main->left = sub;//왼쪽에 서브트리 연결
}
void ChangeRightSubTree(Node* main, Node* sub) {
	main->right = sub;//오른쪽에 서브트리 연결
}

//BST=Binary Search Tree
void BSTMakeAndInit(Node** pRoot) {//Binary Search Tree 생성 및 초기화//Node**pRoot 주의!**
	*pRoot = NULL;
}
int BSTGetNodeData(Node* bst) {//노드에 저장된 데이터 반환
	return GetData(bst);
}
void BSTInsert(Node** pRoot, int data) {//Binary Search Tree를 대상으로 데이터 저장(노드의 생성과정 포함)//Node**pRoot 주의!**
	Node* parentNode = NULL;
	Node* currentNode = *pRoot;
	Node* newNode = NULL;
	while (currentNode != NULL) {//newNode가 저장될 위치 찾기 (제일 끝부분 비어있는 자리에 쏙 저장)
		if (data == GetData(currentNode))return;//중복 허용 X
		parentNode = currentNode;
		if (GetData(currentNode) > data)currentNode = GetLeftSubTree(currentNode);//입력 data가 parent노드 data보다 작으면 왼쪽으로 이동
		else currentNode = GetRightSubTree(currentNode);//입력 data가 parent노드 data보다 크면 오른쪽으로 이동
	}
	newNode = MakeBinaryTreeNode();//새 노드 할당
	SetData(newNode, data);//새 노드에 data값 입력
	if (parentNode != NULL) {//새 노드가 루트 노드가 아니면
		if (data < GetData(parentNode))MakeLeftSubTree(parentNode, newNode);//data가 parent의 data보다 작으면 왼쪽에 insert
		else MakeRightSubTree(parentNode, newNode);//data가 parent의 data보다 크면 오른쪽에 insert
	}
	else {//새 노드가 루트 노드면
		*pRoot = newNode;
	}
}
Node* BSTSearch(Node* bst, int target) {//Binary Search Tree 를 대상으로 데이터 탐색
	Node* currentNode = bst;
	int currentData;
	while (currentNode != NULL) {
		currentData = GetData(currentNode);
		if (target == currentData)return currentNode;//타겟에 도달//현재 노드 반환
		else if (target < currentData)currentNode = GetLeftSubTree(currentNode);//target이 currentData보다 작음. 왼쪽으로 이동
		else currentNode = GetRightSubTree(currentNode);//target이 currentData보다 큼. 오른쪽으로 이동
	}
	return NULL;//탐색 대상 없음
}
Node* BSTRemove(Node** pRoot, int target) {//트리에서 노드를 제거하고 제거된 노드의 주소 값 반환 //이 부분 복잡!
	Node* pVirtualRoot = MakeBinaryTreeNode();//가상의 루트 노드  
	Node* parentNode = pVirtualRoot;
	Node* currentNode = *pRoot;
	Node* deleteNode;
	//(현재 루트가 VirtualRoot의 오른쪽 child로 달려 있다고 생각) - 루트가 삭제될 경우를 대비
	//		VR(가상의 루트)
	//	     ↘
	//			Root (실제 루트) 
	ChangeRightSubTree(pVirtualRoot, *pRoot);//가상의 루트노드의 오른쪽에 현재 루트 넣기

	//삭제 대상인 노드 탐색하기
	while (currentNode != NULL && GetData(currentNode) != target) {//현재노드가 비어있지 않고 타겟과 같지 않을때까지 반복
		parentNode = currentNode;
		if (target < GetData(currentNode))currentNode = GetLeftSubTree(currentNode);
		else currentNode = GetRightSubTree(currentNode);
	}
	if (currentNode == NULL)return NULL;//못찾으면 NULL 반환
	deleteNode = currentNode;//삭제노드 저장


	//경우1. 삭제 대상이 단말 노드 (child없음!)
	if (GetLeftSubTree(deleteNode) == NULL && GetRightSubTree(deleteNode) == NULL) {//child둘다 없다 -> parent에게서 그냥 삭제
		if (GetLeftSubTree(parentNode) == deleteNode)RemoveLeftSubTree(parentNode);//만약 삭제대상이 왼쪽에 달려있는 서브트리면 parent의 왼쪽 지운다
		else RemoveRightSubTree(parentNode);//만약 삭제대상이 오른쪽에 달려있는 서브트리면 parent의 오른쪽 지운다
	}

	//경우2. 삭제 대상이 child 하나 가진다
	else if (GetLeftSubTree(deleteNode) == NULL || GetRightSubTree(deleteNode) == NULL) {//child 둘중 하나 없다 -> 지울 대상의 parent와 child 연결
		Node* deleteChildNode;
		if (GetLeftSubTree(deleteNode) != NULL)deleteChildNode = GetLeftSubTree(deleteNode);//왼쪽이 비어있지 않으면 왼쪽 sub저장
		else deleteChildNode = GetRightSubTree(deleteNode);//오른쪽이 비어있지 않으면 오른쪽 sub 저장
		if (GetLeftSubTree(parentNode) == deleteNode)ChangeLeftSubTree(parentNode, deleteChildNode);
		//만약 삭제대상이 왼쪽에 달려있으면 삭제 대상의 parent의 왼쪽에 childsub연결
		else ChangeRightSubTree(parentNode, deleteChildNode);
		//만약 삭제대상이 오른쪽에 달려있으면 삭제 대상의 parent의 오른쪽에 childsub연결
	}


	// 경우3. 삭제 대상이 두개의 child를 가진다
	// 방법 : 왼쪽 subtree의 가장 큰 값이나 오른쪽 subtree의 가장 작은 값을 삭제 위치에 넣는다(여기선 오른쪽 최소값)
	// 1단계 : 삭제할 노드를 대체할 노드 찾기
	// 2단계 : 대체할 노드에 저장된 값을 삭제할 노드에 대입
	// 3단계 : 대체할 노드의 부모 노드와 자식 노드를 연결
	else {
		Node* repNode = GetRightSubTree(deleteNode);//대체 노드에 일단 삭제 대상인 노드의 오른쪽subtree를 저장
		Node* repparentNode = deleteNode;//대체 노드의 부모노드는 삭제할 노드
		int deleteData;
		while (GetLeftSubTree(repNode) != NULL) {//오른쪽subtree의 가장 작은 값(제일 왼쪽 끝에 위치한 값) 찾기
			repparentNode = repNode;
			repNode = GetLeftSubTree(repNode);
		}
		deleteData = GetData(deleteNode);
		SetData(deleteNode, GetData(repNode));//대체할 값을 넣는다(노드는 그대로, 값만 바꿔치기)
		if (GetLeftSubTree(repparentNode) == repNode)ChangeLeftSubTree(repparentNode, GetRightSubTree(repNode));
		//만약 대체노드가 부모의 왼쪽에 달려 있는 경우(여기서는 대체 노드가 삭제 바로 아래가 아닌 더 아래 있는 노드일때)
		//대체노드의 자식노드(여기서는 만약 있으면 오른쪽 child)를 부모노드의 왼쪽에 연결
		else ChangeRightSubTree(repparentNode, GetRightSubTree(repNode));
		//만약 대체노드가 부모의 오른쪽에 달려 있는 경우(여기서는 이 경우가 삭제 바로 아래 노드가 대체노드일때)
		//대체노드의 자식노드(여기서는 만약 있으면 오른쪽 child)를 부모노드의 오른쪽에 연결
		deleteNode = repNode;
		SetData(deleteNode, deleteData);//백업 데이터 복원
	}

	if (GetRightSubTree(pVirtualRoot) != *pRoot)*pRoot = GetRightSubTree(pVirtualRoot);
	//만약 삭제된 노드가 루트 노드인 경우
	//포인터이기 때문에 삭제 과정 뒤 루트 노드의 주소값이 현재 루트 노드를 가리키지 않는다
	//따라서 제대로 루트를 지정해 준다.
	free(pVirtualRoot);
	return deleteNode;
}
void ShowIntData(int data) {
	printf("%d  ", data);
}
void BSTShowAll(Node* bst) {
	InorderTraverse(bst, ShowIntData);
}





int main(void) {
	Node* bstRoot;
	Node* searchNode;
	BSTMakeAndInit(&bstRoot);//초기화
	int n, num,i;
	printf("입력 개수 : ");
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		printf("숫자 입력 : ");
		scanf("%d", &num);
		BSTInsert(&bstRoot, num);
	}
	printf("\n\n입력 완료!\n");
	BSTShowAll(bstRoot);
	while (1) {
		printf("\n\n삭제할 값 입력 : ");
		scanf("%d", &num);
		if (num <= 0)break;
		searchNode = BSTRemove(&bstRoot, num);
		free(searchNode);
		BSTShowAll(bstRoot);
		printf("\n");
	}
	return 0;
}