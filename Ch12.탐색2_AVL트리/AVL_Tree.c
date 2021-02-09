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


//AVL Tree 함수들 시작

int GetHeight(Node* bst) {//트리 높이 계산
	int leftH;
	int rightH;
	if (bst == NULL)return 0;
	leftH = GetHeight(GetLeftSubTree(bst));//왼쪽 서브 트리 높이 계산
	rightH = GetHeight(GetRightSubTree(bst));//오른쪽 서브 트리 높이 계산
	//가장 깊이 뻗은 경로까지 길이를 측정하기 위해 재귀함수 사용!
	if (leftH > rightH) return leftH + 1;//한번 재귀될때마다 +1
	else return rightH + 1;//한번 재귀될때마다 +1
}
int GetHeightDiff(Node* bst) {//균형 인수 = 왼쪽 서브 트리의 높이 - 오른쪽 서브 트리의 높이
	int LeftSubTreeHeight, RightSubTreeHeight;
	if (bst == NULL)return 0;//트리 비어있다
	LeftSubTreeHeight = GetHeight(GetLeftSubTree(bst));
	RightSubTreeHeight = GetHeight(GetRightSubTree(bst));
	return LeftSubTreeHeight - RightSubTreeHeight;
}

Node* RotateLL(Node* bst) {
	Node* parentNode;
	Node* childNode;
	parentNode = bst;
	childNode = GetLeftSubTree(parentNode);

	//LL회전
	ChangeLeftSubTree(parentNode, GetRightSubTree(childNode));//핵심
	ChangeRightSubTree(childNode, parentNode);//핵심

	return childNode;
}

Node* RotateRR(Node* bst) {
	Node* parentNode;
	Node* childNode;
	parentNode = bst;
	childNode = GetRightSubTree(parentNode);

	//RR회전
	ChangeRightSubTree(parentNode, GetLeftSubTree(childNode));//핵심
	ChangeLeftSubTree(childNode, parentNode);//핵심

	return childNode;
}
Node* RotateLR(Node* bst) {//RR회전 -> LL회전
	Node* parentNode;
	Node* childNode;
	parentNode = bst;
	childNode = GetLeftSubTree(parentNode);//LR회전을 위해 적절한 위치를 가리키게 한다

	//LR회전 = RR회전 -> LL회전
	ChangeLeftSubTree(parentNode, RotateRR(childNode));//부분적 RR회전
	return RotateLL(parentNode);//LL회전
}
Node* RotateRL(Node* bst) {//RL회전 = LL회전 -> RR회전
	Node* parentNode;
	Node* childNode;

	parentNode = bst;
	childNode = GetRightSubTree(parentNode);//RL회전을 위해 적절한 위치를 가리키게 한다


	//RL회전 = LL회전 -> RR회전
	ChangeRightSubTree(parentNode, RotateLL(childNode));//부분적 LL회전
	return RotateRR(parentNode);//RR회전
}
Node* Rebalance(Node** pRoot) {
	int heightDiff = GetHeightDiff(*pRoot);

	//균형인수가 +2이상이면 LL또는 LR
	if (heightDiff > 1) {
		if (GetHeightDiff(GetLeftSubTree(*pRoot)) > 0)*pRoot = RotateLL;
		else *pRoot = RotateLR(*pRoot);
	}
	//균형인수가 -2이하면 RR또는 RL
	if (heightDiff < -1) {
		if (GetHeightDiff(GetRightSubTree(*pRoot)) < 0)*pRoot = RotateRR(*pRoot);
		else *pRoot = RotateRL(*pRoot);
	}
	return *pRoot;
}


Node* BSTInsert(Node** pRoot, int data) {
	if (*pRoot == NULL) {//첫 insert
		*pRoot = MakeBinaryTreeNode();
		SetData(*pRoot, data);
	}
	else if (data < GetData(*pRoot)) {//중요
		BSTInsert(&((*pRoot)->left), data);
		*pRoot = Rebalance(pRoot);
	}
	else if (data > GetData(*pRoot)) {//중요
		BSTInsert(&((*pRoot)->right), data);
		*pRoot = Rebalance(pRoot);
	}
	else {
		return NULL;//중복 안됨
	}
	return *pRoot;
}

//여기까지 AVL Tree 함수들 


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
	*pRoot=Rebalance(pRoot);//삭제하고 Rebalancing (AVL Tree)
	return deleteNode;
}
void ShowIntData(int data) {
	printf("%d  ", data);
}
void BSTShowAll(Node* bst) {
	InorderTraverse(bst, ShowIntData);
}





int main(void) {
	Node* avlRoot;
	Node* currentLeftNode;
	Node* currentRightNode;
	Node* currentLeftNode2;
	Node* currentRightNode2;
	Node* currentLeftNode3;
	Node* currentRightNode3;
	BSTMakeAndInit(&avlRoot);//초기화
	int n, num,i;
	printf("입력 개수 : ");
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		printf("숫자 입력 : ");
		scanf("%d", &num);
		BSTInsert(&avlRoot, num);
	}
	printf("\n\n루트 노드 : %d\n",GetData(avlRoot));
	currentLeftNode = GetLeftSubTree(avlRoot);   //2, 루트 4의 왼쪽
	currentRightNode = GetRightSubTree(avlRoot);  //6, 루트 4의 오른쪽
	printf("%d, %d \n", GetData(currentLeftNode), GetData(currentRightNode));

	currentLeftNode2 = GetLeftSubTree(currentLeftNode);    //1, 2의 왼쪽
	currentRightNode2 = GetRightSubTree(currentLeftNode);   //3, 2의 오른쪽
	printf("%d, %d \n", GetData(currentLeftNode2), GetData(currentRightNode2));

	currentLeftNode2 = GetLeftSubTree(currentRightNode);    //5, 3의 왼쪽
	currentRightNode2 = GetRightSubTree(currentRightNode);   //8, 3의 오른쪽
	printf("%d, %d \n", GetData(currentLeftNode2), GetData(currentRightNode2));

	currentLeftNode3 = GetLeftSubTree(currentRightNode2);   //7, 8의 왼쪽
	currentRightNode3 = GetRightSubTree(currentRightNode2);  //9, 8의 오른쪽
	printf("%d, %d \n", GetData(currentLeftNode3), GetData(currentRightNode3));
	return 0;
}