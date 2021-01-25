#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct _node {
	int data;
	char name[100];
	struct _node* next;
}Node;

typedef struct CircularLinkedList {
	Node* tail;
	Node* cur;
	Node* before;
	int numOfData;
}List;

void ListInit(List* plist) {//리스트 초기화(처음에 호출)
	plist->tail = NULL;
	plist->cur = NULL;
	plist->before = NULL;
	plist->numOfData = 0;
}

void LInsert(List* plist, int data,char name[]) {//tail에 삽입하는 경우
	Node* newNode = (Node*)malloc(sizeof(Node));//새노드
	newNode->data = data;//데이터 입력
	strcpy(newNode->name, name);

	if (plist->tail == NULL){//처음 insert하는 경우
		plist->tail = newNode;//List의 tail자리에 insert
		newNode->next = newNode; //원형 연결 리스트(처음과 끝을 이어줌)
	}
	else {//처음이 아닐 때
		newNode->next = plist->tail->next;//삽입 노드의 다음은 tail->next(head)
		plist->tail->next = newNode;//head위치(tail의 다음)가 newNode : 여기까지 보면 head위치에 삽입됨
		plist->tail = newNode;//tail을 newNode로 이동 : tail위치에 삽입됨
	}
	(plist->numOfData)++;//리스트의 노드 증가
}

void LInsertFront(List* plist, int data) {//head에 삽입하는 경우
	Node* newNode = (Node*)malloc(sizeof(Node));//새 노드 할당
	newNode->data = data;//데이터 입력
	if (plist->tail == NULL) {//처음 입력하는 경우
		plist->tail = newNode;
		newNode->next = newNode;
	}
	else {//처음 아닌 경우
		newNode->next = plist->tail->next;
		plist->tail->next = newNode;//tail위치에 새 노드 삽입
	}
	(plist->numOfData)++;//리스트의 노드 증가
}

int LFirst(List* plist, int* pdata,char*name) {
	if (plist->tail == NULL)return 0;//노드 하나도 없음
	else {//노드 최소 하나라도 있음
		plist->before = plist->tail;//head 전 위치는 tail
		plist->cur = plist->tail->next;//현재는 tail의 next(head)
		*pdata = plist->cur->data;//데이터값 저장
		if (strcmp(name, plist->cur->name) == 0) {
			return 2;
		}

		return 1;
	}
}
int LNext(List* plist, int* pdata,char*name) {
	if (plist->tail == NULL)return 0;//노드 하나도 없으면 안됨
	else {//노드 하나 이상인 경우 끝 없이 무한반복
		plist->before = plist->cur;
		plist->cur = plist->cur->next;//한칸씩 다음으로 옮김
		*pdata = plist->cur->data;
		if (strcmp(name, plist->cur->name) == 0)return 2;
		return 1;
	}
}
int LRemove(List* plist) {//노드 제거
	Node* removeNode = plist->cur;//제거할 거
	int removeData = removeNode->data;//제거할 데이터

	if (removeNode == plist->tail) {//경우1)제거할 노드가 꼬리위치
		if (plist->tail == plist->tail->next) {//경우1-1)노드 하나뿐
			plist->tail = NULL;
		}
		else {//경우1-2)노드 여러개
			plist->tail = plist->before;
		}
	}
	plist->before->next = plist->cur->next;
	plist->cur = plist->before;//제거할 거 쏙 빼고 앞뒤 서로 이어줌
	free(removeNode);//쏙 빼버린 제거노드 메모리 제거
	(plist->numOfData)--;//노드 감소
	return removeData;
}
int LCount(List* plist) {
	return plist->numOfData;
}

void printName(List* plist) {
	printf("%s입니다(사번 : %d)\n",plist->cur->name,plist->cur->data);
	
}

int main(void) {
	List list;
	int data, i, nodeNum,num;
	char name[100];
	ListInit(&list);


	//값 입력
	printf("4명의 정보 입력\n");
	for (i = 0; i < 4; i++) {
		printf("이름 : ");
		scanf("%s", name);
		printf("사번 : ");
		scanf("%d", &data);
		LInsert(&list, data, name);
	}
	printf("\n\n\n");
	printf("이름과 숫자를 입력해서 000 당직 ?일 후 당직인 사람 출력하기\n");
	printf("이름 : ");
	scanf("%s", name);
	if (LFirst(&list, &data, name)) {
		if (LFirst(&list, &data, name) == 2) {
			printf("%s의 사번은 %d\n ", name, data);
		}
		else {
			while (1) {
				if (LNext(&list, &data, name) == 2)break;
			}
			printf("%s의 사번은 %d\n", name, data);
		}
	}
	printf("숫자 입력 : ");
	scanf("%d", &num);
	for (i = 0; i < num; i++) {
		LNext(&list, &data, name);
	}
	printf("%d일 후 당직은 ",num);
	printName(&list);

	return 0;
}