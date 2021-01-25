#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int data;
	struct _node *next;
}Node;

int main() {
	Node* head = NULL;
	Node* tail = NULL;
	Node* cur = NULL;
	Node* newNode = NULL;
	int readData;

	while (1) {//데이터 입력받기
		printf("자연수 입력: ");
		scanf("%d", &readData);
		if (readData <= 0)break;

		newNode = (Node*)malloc(sizeof(Node));
		newNode->data = readData;
		newNode->next = NULL;
		if (head == NULL) head = newNode;
		else tail->next = newNode;
		tail = newNode;
	}
	printf("\n\n\n");
	printf("전체출력!\n");
	if (head == NULL)printf("저장된 숫자 없음!");
	else {
		cur = head;
		while (cur != NULL) {
			printf("%d  ", cur->data);
			cur = cur->next;
		}
	}
	printf("\n\n\n");

}
