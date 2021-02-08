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
void BSTInsert(Node** pRoot, int data) {//Binary Search Tree�� ������� ������ ����(����� �������� ����)//Node**pRoot ����!**
	Node* parentNode = NULL;
	Node* currentNode = *pRoot;
	Node* newNode = NULL;
	while (currentNode != NULL) {//newNode�� ����� ��ġ ã�� (���� ���κ� ����ִ� �ڸ��� �� ����)
		if (data == GetData(currentNode))return;//�ߺ� ��� X
		parentNode = currentNode;
		if (GetData(currentNode) > data)currentNode = GetLeftSubTree(currentNode);//�Է� data�� parent��� data���� ������ �������� �̵�
		else currentNode = GetRightSubTree(currentNode);//�Է� data�� parent��� data���� ũ�� ���������� �̵�
	}
	newNode = MakeBinaryTreeNode();//�� ��� �Ҵ�
	SetData(newNode, data);//�� ��忡 data�� �Է�
	if (parentNode != NULL) {//�� ��尡 ��Ʈ ��尡 �ƴϸ�
		if (data < GetData(parentNode))MakeLeftSubTree(parentNode, newNode);//data�� parent�� data���� ������ ���ʿ� insert
		else MakeRightSubTree(parentNode, newNode);//data�� parent�� data���� ũ�� �����ʿ� insert
	}
	else {//�� ��尡 ��Ʈ ����
		*pRoot = newNode;
	}
}
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
	BSTMakeAndInit(&bstRoot);//�ʱ�ȭ
	int n, num,i;
	printf("�Է� ���� : ");
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		printf("���� �Է� : ");
		scanf("%d", &num);
		BSTInsert(&bstRoot, num);
	}
	printf("\n\n�Է� �Ϸ�!\n");
	BSTShowAll(bstRoot);
	while (1) {
		printf("\n\n������ �� �Է� : ");
		scanf("%d", &num);
		if (num <= 0)break;
		searchNode = BSTRemove(&bstRoot, num);
		free(searchNode);
		BSTShowAll(bstRoot);
		printf("\n");
	}
	return 0;
}