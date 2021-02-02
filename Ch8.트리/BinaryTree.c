#include <stdio.h>
#include <stdlib.h>

typedef struct _BinaryTreeNode {
	int data;
	struct _BinaryTreeNode* left;
	struct _BinaryTreeNode* right;
}Node;

Node* MakeBinaryTreeNode(void) {//���� Ʈ�� ��� ���� �� �ʱ�ȭ
	Node* nd = (Node*)malloc(sizeof(Node));
	nd->left = NULL;
	nd->right = NULL;
	return nd;
}

int GetData(Node* bt) {//��忡 ����� ������ ��ȯ
	return bt->data;
}

void SetData(Node* bt, int data) {//��忡 ������ ����
	bt->data = data;
}

Node* GetLeftSubTree(Node* bt) {//���� ���� Ʈ�� �ּҰ� ��ȯ
	return bt->left;
}

Node* GetRightSubTree(Node* bt) {//������ ���� Ʈ�� �ּҰ� ��ȯ
	return bt->right;
}

void MakeLeftSubTree(Node* main, Node* sub) {//subƮ���� mainƮ���� ���ʿ� ����
	if (main->left != NULL)free(main->left);//������ ������� ������ �������(������ ��ȸ�ϸ鼭 �� �Ʒ� ��带 �� ��������)
	main->left = sub;//���ʿ� ����Ʈ�� �ֱ�
}

void MakeRightSubTree(Node* main, Node* sub) {//subƮ���� mainƮ���� �����ʿ� ����
	if (main->right != NULL)free(main->right);//�������� ������� ������ �������(������ ��ȸ�ϸ鼭 �� �Ʒ� ��带 �� ��������)
	main->right = sub;//�����ʿ� ����Ʈ�� �ֱ�
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
	//		  �� ��
	//		 2	   3
	//	  ��
	//	 4
	
	
	return 0;
}