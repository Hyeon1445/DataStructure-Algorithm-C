#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 50
#define MAX_TBL 100//TBL = table
#define TRUE 1
#define FALSE 0
#define MAX_TBL 100



typedef struct _person {
	int num;
	char name[STR_LEN];
	char address[STR_LEN];
}Person;
int GetNum(Person* p) {
	return p->num;
}
void ShowPersonInfo(Person* p) {
	printf("주민등록번호 : %d\n", p->num);
	printf("이름 : %s\n", p->name);
	printf("주소 : %s\n", p->address);
}
Person* MakePersonData(int num, char* name, char* address) {
	Person* newPerson = (Person*)malloc(sizeof(Person));
	newPerson->num = num;
	strcpy(newPerson->name, name);
	strcpy(newPerson->address, address);
	return newPerson;
}


//enum SlotStatus { EMPTY, DELETED, INUSE }; 필요없음!


typedef int Key;//키 : 주민등록번호
typedef Person* Value; // 값 : Person 구조체 변수의 주소 값

typedef struct _slot {
	int key;
	Value val;
}Slot;



typedef Slot LData;

typedef struct _node {
	LData data;
	struct _node* next;
}Node;

typedef struct _linkedList {
	Node* head;
	Node* cur;
	Node* before;
	int numOfData;
	int (*comp)(LData d1, LData d2);
}LinkedList;

typedef LinkedList List;

void ListInit(List* plist) {
	plist->head = (Node*)malloc(sizeof(Node));
	plist->head->next = NULL;
	plist->numOfData = 0;
}
void LInsert(List* plist, LData data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = plist->head->next;
	plist->head->next = newNode;
	(plist->numOfData)++;
}
int LFirst(List* plist, LData* pdata) {
	if (plist->head->next == NULL)return FALSE;
	plist->before = plist->head;
	plist->cur = plist->head->next;
	*pdata = plist->cur->data;
	return TRUE;
}
int LNext(List* plist, LData* pdata) {
	if (plist->cur->next == NULL)return FALSE;
	plist->before = plist->cur;
	plist->cur = plist->cur->next;
	*pdata = plist->cur->data;
	return TRUE;
}
LData LRemove(List* plist) {
	Node* rpos = plist->cur;
	LData rdata = rpos->data;
	plist->before->next = plist->cur->next;
	plist->cur = plist->before;
	free(rpos);
	(plist->numOfData)--;
	return rdata;
}
int LCount(List* plist) {
	return plist->numOfData;
}


//DLinkedList.h

typedef int HashFunc(Key k);

typedef struct _table {
	Slot tbl[MAX_TBL];
	HashFunc* hf;
}Table;

void TBLInit(Table* pt, HashFunc* f) {//테이블 초기화
	int i;
	for (i = 0; i < MAX_TBL; i++) {
		ListInit(&(pt->tbl[i]));
	}
	pt->hf = f;
}
void TBLInsert(Table* pt, Key k, Value v) {//테이블에 키와 값을 저장
	int hv = pt->hf(k);
	Slot ns = { k, v };
	/*if (TBLSearch(pt, k) != NULL) {//원래 코드인데 오류남....ㅠㅠ
		printf("키 중복 오류 발생\n");
		return;
	}
	else {
		LInsert(&(pt->tbl[hv]), ns);
	}*/
	LInsert(&(pt->tbl[hv]), ns);//이렇게 바꿈
}
Value TBLDelete(Table* pt, Key k) {//키를 근거로 테이블에서 데이터 삭제
	int hv = pt->hf(k);
	Slot cSlot;
	if (LFirst(&(pt->tbl[hv]), &cSlot)) {
		LRemove(&(pt->tbl[hv]));
		return cSlot.val;
	}
	else {
		while (LNext(&(pt->tbl[hv]), &cSlot)) {
			if (cSlot.key == k) {
				LRemove(&(pt->tbl[hv]));
				return cSlot.val;
			}
		}
	}
	return NULL;
}
Value TBLSearch(Table* pt, Key k) {//키를 근거로 테이블에서 데이터 탐색
	int hv = pt->hf(k);
	Slot cSlot;
	if (LFirst(&(pt->tbl[hv]), &cSlot)) {
		if (cSlot.key == k) {
			return cSlot.val;
		}
		else {
			while (LNext(&(pt->tbl[hv]), &cSlot)) {
				if (cSlot.key == k)return cSlot.val;
			}
		}
	}
	return NULL;
}

//table2.h

int MyHashFunc(int k) {
	return k % 100;
}

int main(void) {
	Table myTBL;
	Person* NewPerson;
	Person* SearchPerson;
	Person* RemovePerson;
	TBLInit(&myTBL, MyHashFunc);//테이블 초기화

	//데이터 입력
	NewPerson = MakePersonData(900254, "LEE", "SEOUL");
	TBLInsert(&myTBL, GetNum(NewPerson), NewPerson);

	NewPerson = MakePersonData(900139, "KIM", "INCHEON");
	TBLInsert(&myTBL, GetNum(NewPerson), NewPerson);

	NewPerson = MakePersonData(900827, "PARK", "JEJU");
	TBLInsert(&myTBL, GetNum(NewPerson), NewPerson);


	//데이터 탐색
	printf("데이터 탐색 결과\n");
	SearchPerson = TBLSearch(&myTBL, 900254);
	if (SearchPerson != NULL)ShowPersonInfo(SearchPerson);

	printf("\n");
	SearchPerson = TBLSearch(&myTBL, 900139);
	if (SearchPerson != NULL)ShowPersonInfo(SearchPerson);

	printf("\n");
	SearchPerson = TBLSearch(&myTBL, 900827);
	if (SearchPerson != NULL)ShowPersonInfo(SearchPerson);


	//데이터 삭제
	RemovePerson = TBLDelete(&myTBL, 900254);
	if (RemovePerson != NULL)free(RemovePerson);

	RemovePerson = TBLDelete(&myTBL, 900139);
	if (RemovePerson != NULL)free(RemovePerson);

	RemovePerson = TBLDelete(&myTBL, 900827);
	if (RemovePerson != NULL)free(RemovePerson);
	
	return 0;
}