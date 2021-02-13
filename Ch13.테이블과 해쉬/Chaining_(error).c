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
	printf("�ֹε�Ϲ�ȣ : %d\n", p->num);
	printf("�̸� : %s\n", p->name);
	printf("�ּ� : %s\n", p->address);
}
Person* MakePersonData(int num, char* name, char* address) {
	Person* newPerson = (Person*)malloc(sizeof(Person));
	newPerson->num = num;
	strcpy(newPerson->name, name);
	strcpy(newPerson->address, address);
	return newPerson;
}


//enum SlotStatus { EMPTY, DELETED, INUSE }; �ʿ����!


typedef int Key;//Ű : �ֹε�Ϲ�ȣ
typedef Person* Value; // �� : Person ����ü ������ �ּ� ��

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

void TBLInit(Table* pt, HashFunc* f) {//���̺� �ʱ�ȭ
	int i;
	for (i = 0; i < MAX_TBL; i++) {
		ListInit(&(pt->tbl[i]));
	}
	pt->hf = f;
}
void TBLInsert(Table* pt, Key k, Value v) {//���̺� Ű�� ���� ����
	int hv = pt->hf(k);
	Slot ns = { k, v };
	/*if (TBLSearch(pt, k) != NULL) {//���� �ڵ��ε� ������....�Ф�
		printf("Ű �ߺ� ���� �߻�\n");
		return;
	}
	else {
		LInsert(&(pt->tbl[hv]), ns);
	}*/
	LInsert(&(pt->tbl[hv]), ns);//�̷��� �ٲ�
}
Value TBLDelete(Table* pt, Key k) {//Ű�� �ٰŷ� ���̺��� ������ ����
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
Value TBLSearch(Table* pt, Key k) {//Ű�� �ٰŷ� ���̺��� ������ Ž��
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
	TBLInit(&myTBL, MyHashFunc);//���̺� �ʱ�ȭ

	//������ �Է�
	NewPerson = MakePersonData(900254, "LEE", "SEOUL");
	TBLInsert(&myTBL, GetNum(NewPerson), NewPerson);

	NewPerson = MakePersonData(900139, "KIM", "INCHEON");
	TBLInsert(&myTBL, GetNum(NewPerson), NewPerson);

	NewPerson = MakePersonData(900827, "PARK", "JEJU");
	TBLInsert(&myTBL, GetNum(NewPerson), NewPerson);


	//������ Ž��
	printf("������ Ž�� ���\n");
	SearchPerson = TBLSearch(&myTBL, 900254);
	if (SearchPerson != NULL)ShowPersonInfo(SearchPerson);

	printf("\n");
	SearchPerson = TBLSearch(&myTBL, 900139);
	if (SearchPerson != NULL)ShowPersonInfo(SearchPerson);

	printf("\n");
	SearchPerson = TBLSearch(&myTBL, 900827);
	if (SearchPerson != NULL)ShowPersonInfo(SearchPerson);


	//������ ����
	RemovePerson = TBLDelete(&myTBL, 900254);
	if (RemovePerson != NULL)free(RemovePerson);

	RemovePerson = TBLDelete(&myTBL, 900139);
	if (RemovePerson != NULL)free(RemovePerson);

	RemovePerson = TBLDelete(&myTBL, 900827);
	if (RemovePerson != NULL)free(RemovePerson);
	
	return 0;
}