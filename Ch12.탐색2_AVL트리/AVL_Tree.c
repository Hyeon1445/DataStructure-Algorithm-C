#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct BinaryTreeNode {
	int data;
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;
}Node;

Node* MakeBinaryTreeNode(void) {//��带 �������� �Ҵ��ؼ� �� ����� �ּҰ� ��ȯ
	Node* node = (Node*)malloc(sizeof(Node));
	node->left = NULL;
	node->right = NULL;
	return node;
}
int GetData(Node* bt) {//��忡 ����� ������ ��ȯ
	return bt->data;
}

void SetData(Node* bt, int data) {//���ڷ� ���޵� �����͸� ��忡 ����
	bt->data = data;
}

Node* GetLeftSubTree(Node* bt) {//���ڷ� ���޵� ����� ���� �ڽ� ����� �ּҰ� ��ȯ
	return bt->left;
}
Node* GetRightSubTree(Node* bt) {//���ڷ� ���޵� ����� ������ �ڽ� ����� �ּҰ� ��ȯ
	return bt->right;
}

void MakeLeftSubTree(Node* main, Node* sub) {//���ڷ� ���޵� ����� ���� �ڽ� ��带 ��ü
	if (main->left != NULL)free(main->left);//���� ������� ������ �ϴ� ����
	main->left = sub;//left�� subtree����
}
void MakeRightSubTree(Node* main, Node* sub) {//���ڷ� ���޵� ����� ������ �ڽ� ��带 ��ü
	if (main->right != NULL)free(main->right);//������ ������� ������ �ϴ� ��´�
	main->right=sub;//right�� subtree����
}



typedef void VisitFuncPtr(int data);
void PreorderTraverse(Node* bt, VisitFuncPtr action) {//main -> left ->right
	if (bt == NULL)return;//��������� ��
	action(bt->data);
	PreorderTraverse(bt->left, action);
	PreorderTraverse(bt->right, action);
}
void InorderTraverse(Node* bt, VisitFuncPtr action) {//left -> main -> right
	if (bt == NULL)return;//��������� ��
	InorderTraverse(bt->left, action);
	action(bt->data);
	InorderTraverse(bt->right, action);
}
void PostorderTraverse(Node* bt, VisitFuncPtr action) { //left -> right -> main
	if (bt == NULL)return;//��������� ��
	PostorderTraverse(bt->left, action);
	PostorderTraverse(bt->right, action);
	action(bt->data);
}
Node* RemoveLeftSubTree(Node* bt) {//���� ����Ʈ�� ����
	Node* deleteNode=NULL;
	if (bt != NULL) {
		deleteNode = bt->left;
		bt->left = NULL;
	}
	return deleteNode;
}
Node* RemoveRightSubTree(Node* bt) {//������ ����Ʈ�� ����
	Node* deleteNode=NULL;
	if (bt != NULL) {
		deleteNode = bt->right;
		bt->right = NULL;
	}
	return deleteNode;
}
void ChangeLeftSubTree(Node* main, Node* sub) {
	main->left = sub;//���ʿ� ����Ʈ�� ����
}
void ChangeRightSubTree(Node* main, Node* sub) {
	main->right = sub;//�����ʿ� ����Ʈ�� ����
}

//BST=Binary Search Tree
void BSTMakeAndInit(Node** pRoot) {//Binary Search Tree ���� �� �ʱ�ȭ//Node**pRoot ����!**
	*pRoot = NULL;
}
int BSTGetNodeData(Node* bst) {//��忡 ����� ������ ��ȯ
	return GetData(bst);
}


//AVL Tree �Լ��� ����

int GetHeight(Node* bst) {//Ʈ�� ���� ���
	int leftH;
	int rightH;
	if (bst == NULL)return 0;
	leftH = GetHeight(GetLeftSubTree(bst));//���� ���� Ʈ�� ���� ���
	rightH = GetHeight(GetRightSubTree(bst));//������ ���� Ʈ�� ���� ���
	//���� ���� ���� ��α��� ���̸� �����ϱ� ���� ����Լ� ���!
	if (leftH > rightH) return leftH + 1;//�ѹ� ��͵ɶ����� +1
	else return rightH + 1;//�ѹ� ��͵ɶ����� +1
}
int GetHeightDiff(Node* bst) {//���� �μ� = ���� ���� Ʈ���� ���� - ������ ���� Ʈ���� ����
	int LeftSubTreeHeight, RightSubTreeHeight;
	if (bst == NULL)return 0;//Ʈ�� ����ִ�
	LeftSubTreeHeight = GetHeight(GetLeftSubTree(bst));
	RightSubTreeHeight = GetHeight(GetRightSubTree(bst));
	return LeftSubTreeHeight - RightSubTreeHeight;
}

Node* RotateLL(Node* bst) {
	Node* parentNode;
	Node* childNode;
	parentNode = bst;
	childNode = GetLeftSubTree(parentNode);

	//LLȸ��
	ChangeLeftSubTree(parentNode, GetRightSubTree(childNode));//�ٽ�
	ChangeRightSubTree(childNode, parentNode);//�ٽ�

	return childNode;
}

Node* RotateRR(Node* bst) {
	Node* parentNode;
	Node* childNode;
	parentNode = bst;
	childNode = GetRightSubTree(parentNode);

	//RRȸ��
	ChangeRightSubTree(parentNode, GetLeftSubTree(childNode));//�ٽ�
	ChangeLeftSubTree(childNode, parentNode);//�ٽ�

	return childNode;
}
Node* RotateLR(Node* bst) {//RRȸ�� -> LLȸ��
	Node* parentNode;
	Node* childNode;
	parentNode = bst;
	childNode = GetLeftSubTree(parentNode);//LRȸ���� ���� ������ ��ġ�� ����Ű�� �Ѵ�

	//LRȸ�� = RRȸ�� -> LLȸ��
	ChangeLeftSubTree(parentNode, RotateRR(childNode));//�κ��� RRȸ��
	return RotateLL(parentNode);//LLȸ��
}
Node* RotateRL(Node* bst) {//RLȸ�� = LLȸ�� -> RRȸ��
	Node* parentNode;
	Node* childNode;

	parentNode = bst;
	childNode = GetRightSubTree(parentNode);//RLȸ���� ���� ������ ��ġ�� ����Ű�� �Ѵ�


	//RLȸ�� = LLȸ�� -> RRȸ��
	ChangeRightSubTree(parentNode, RotateLL(childNode));//�κ��� LLȸ��
	return RotateRR(parentNode);//RRȸ��
}
Node* Rebalance(Node** pRoot) {
	int heightDiff = GetHeightDiff(*pRoot);

	//�����μ��� +2�̻��̸� LL�Ǵ� LR
	if (heightDiff > 1) {
		if (GetHeightDiff(GetLeftSubTree(*pRoot)) > 0)*pRoot = RotateLL;
		else *pRoot = RotateLR(*pRoot);
	}
	//�����μ��� -2���ϸ� RR�Ǵ� RL
	if (heightDiff < -1) {
		if (GetHeightDiff(GetRightSubTree(*pRoot)) < 0)*pRoot = RotateRR(*pRoot);
		else *pRoot = RotateRL(*pRoot);
	}
	return *pRoot;
}


Node* BSTInsert(Node** pRoot, int data) {
	if (*pRoot == NULL) {//ù insert
		*pRoot = MakeBinaryTreeNode();
		SetData(*pRoot, data);
	}
	else if (data < GetData(*pRoot)) {//�߿�
		BSTInsert(&((*pRoot)->left), data);
		*pRoot = Rebalance(pRoot);
	}
	else if (data > GetData(*pRoot)) {//�߿�
		BSTInsert(&((*pRoot)->right), data);
		*pRoot = Rebalance(pRoot);
	}
	else {
		return NULL;//�ߺ� �ȵ�
	}
	return *pRoot;
}

//������� AVL Tree �Լ��� 


Node* BSTSearch(Node* bst, int target) {//Binary Search Tree �� ������� ������ Ž��
	Node* currentNode = bst;
	int currentData;
	while (currentNode != NULL) {
		currentData = GetData(currentNode);
		if (target == currentData)return currentNode;//Ÿ�ٿ� ����//���� ��� ��ȯ
		else if (target < currentData)currentNode = GetLeftSubTree(currentNode);//target�� currentData���� ����. �������� �̵�
		else currentNode = GetRightSubTree(currentNode);//target�� currentData���� ŭ. ���������� �̵�
	}
	return NULL;//Ž�� ��� ����
}
Node* BSTRemove(Node** pRoot, int target) {//Ʈ������ ��带 �����ϰ� ���ŵ� ����� �ּ� �� ��ȯ //�� �κ� ����!
	Node* pVirtualRoot = MakeBinaryTreeNode();//������ ��Ʈ ���  
	Node* parentNode = pVirtualRoot;
	Node* currentNode = *pRoot;
	Node* deleteNode;
	//(���� ��Ʈ�� VirtualRoot�� ������ child�� �޷� �ִٰ� ����) - ��Ʈ�� ������ ��츦 ���
	//		VR(������ ��Ʈ)
	//	     ��
	//			Root (���� ��Ʈ) 
	ChangeRightSubTree(pVirtualRoot, *pRoot);//������ ��Ʈ����� �����ʿ� ���� ��Ʈ �ֱ�

	//���� ����� ��� Ž���ϱ�
	while (currentNode != NULL && GetData(currentNode) != target) {//�����尡 ������� �ʰ� Ÿ�ٰ� ���� ���������� �ݺ�
		parentNode = currentNode;
		if (target < GetData(currentNode))currentNode = GetLeftSubTree(currentNode);
		else currentNode = GetRightSubTree(currentNode);
	}
	if (currentNode == NULL)return NULL;//��ã���� NULL ��ȯ
	deleteNode = currentNode;//������� ����


	//���1. ���� ����� �ܸ� ��� (child����!)
	if (GetLeftSubTree(deleteNode) == NULL && GetRightSubTree(deleteNode) == NULL) {//child�Ѵ� ���� -> parent���Լ� �׳� ����
		if (GetLeftSubTree(parentNode) == deleteNode)RemoveLeftSubTree(parentNode);//���� ��������� ���ʿ� �޷��ִ� ����Ʈ���� parent�� ���� �����
		else RemoveRightSubTree(parentNode);//���� ��������� �����ʿ� �޷��ִ� ����Ʈ���� parent�� ������ �����
	}

	//���2. ���� ����� child �ϳ� ������
	else if (GetLeftSubTree(deleteNode) == NULL || GetRightSubTree(deleteNode) == NULL) {//child ���� �ϳ� ���� -> ���� ����� parent�� child ����
		Node* deleteChildNode;
		if (GetLeftSubTree(deleteNode) != NULL)deleteChildNode = GetLeftSubTree(deleteNode);//������ ������� ������ ���� sub����
		else deleteChildNode = GetRightSubTree(deleteNode);//�������� ������� ������ ������ sub ����
		if (GetLeftSubTree(parentNode) == deleteNode)ChangeLeftSubTree(parentNode, deleteChildNode);
		//���� ��������� ���ʿ� �޷������� ���� ����� parent�� ���ʿ� childsub����
		else ChangeRightSubTree(parentNode, deleteChildNode);
		//���� ��������� �����ʿ� �޷������� ���� ����� parent�� �����ʿ� childsub����
	}


	// ���3. ���� ����� �ΰ��� child�� ������
	// ��� : ���� subtree�� ���� ū ���̳� ������ subtree�� ���� ���� ���� ���� ��ġ�� �ִ´�(���⼱ ������ �ּҰ�)
	// 1�ܰ� : ������ ��带 ��ü�� ��� ã��
	// 2�ܰ� : ��ü�� ��忡 ����� ���� ������ ��忡 ����
	// 3�ܰ� : ��ü�� ����� �θ� ���� �ڽ� ��带 ����
	else {
		Node* repNode = GetRightSubTree(deleteNode);//��ü ��忡 �ϴ� ���� ����� ����� ������subtree�� ����
		Node* repparentNode = deleteNode;//��ü ����� �θ���� ������ ���
		int deleteData;
		while (GetLeftSubTree(repNode) != NULL) {//������subtree�� ���� ���� ��(���� ���� ���� ��ġ�� ��) ã��
			repparentNode = repNode;
			repNode = GetLeftSubTree(repNode);
		}
		deleteData = GetData(deleteNode);
		SetData(deleteNode, GetData(repNode));//��ü�� ���� �ִ´�(���� �״��, ���� �ٲ�ġ��)
		if (GetLeftSubTree(repparentNode) == repNode)ChangeLeftSubTree(repparentNode, GetRightSubTree(repNode));
		//���� ��ü��尡 �θ��� ���ʿ� �޷� �ִ� ���(���⼭�� ��ü ��尡 ���� �ٷ� �Ʒ��� �ƴ� �� �Ʒ� �ִ� ����϶�)
		//��ü����� �ڽĳ��(���⼭�� ���� ������ ������ child)�� �θ����� ���ʿ� ����
		else ChangeRightSubTree(repparentNode, GetRightSubTree(repNode));
		//���� ��ü��尡 �θ��� �����ʿ� �޷� �ִ� ���(���⼭�� �� ��찡 ���� �ٷ� �Ʒ� ��尡 ��ü����϶�)
		//��ü����� �ڽĳ��(���⼭�� ���� ������ ������ child)�� �θ����� �����ʿ� ����
		deleteNode = repNode;
		SetData(deleteNode, deleteData);//��� ������ ����
	}

	if (GetRightSubTree(pVirtualRoot) != *pRoot)*pRoot = GetRightSubTree(pVirtualRoot);
	//���� ������ ��尡 ��Ʈ ����� ���
	//�������̱� ������ ���� ���� �� ��Ʈ ����� �ּҰ��� ���� ��Ʈ ��带 ����Ű�� �ʴ´�
	//���� ����� ��Ʈ�� ������ �ش�.
	free(pVirtualRoot);
	*pRoot=Rebalance(pRoot);//�����ϰ� Rebalancing (AVL Tree)
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
	BSTMakeAndInit(&avlRoot);//�ʱ�ȭ
	int n, num,i;
	printf("�Է� ���� : ");
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		printf("���� �Է� : ");
		scanf("%d", &num);
		BSTInsert(&avlRoot, num);
	}
	printf("\n\n��Ʈ ��� : %d\n",GetData(avlRoot));
	currentLeftNode = GetLeftSubTree(avlRoot);   //2, ��Ʈ 4�� ����
	currentRightNode = GetRightSubTree(avlRoot);  //6, ��Ʈ 4�� ������
	printf("%d, %d \n", GetData(currentLeftNode), GetData(currentRightNode));

	currentLeftNode2 = GetLeftSubTree(currentLeftNode);    //1, 2�� ����
	currentRightNode2 = GetRightSubTree(currentLeftNode);   //3, 2�� ������
	printf("%d, %d \n", GetData(currentLeftNode2), GetData(currentRightNode2));

	currentLeftNode2 = GetLeftSubTree(currentRightNode);    //5, 3�� ����
	currentRightNode2 = GetRightSubTree(currentRightNode);   //8, 3�� ������
	printf("%d, %d \n", GetData(currentLeftNode2), GetData(currentRightNode2));

	currentLeftNode3 = GetLeftSubTree(currentRightNode2);   //7, 8�� ����
	currentRightNode3 = GetRightSubTree(currentRightNode2);  //9, 8�� ������
	printf("%d, %d \n", GetData(currentLeftNode3), GetData(currentRightNode3));
	return 0;
}