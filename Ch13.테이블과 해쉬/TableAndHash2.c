#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 50
#define MAX_TBL 100//TBL = table


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
enum SlotStatus { EMPTY,DELETED,INUSE };


typedef int Key;//Ű : �ֹε�Ϲ�ȣ
typedef Person* Value; // �� : Person ����ü ������ �ּ� ��

typedef struct _slot {
	int key;
	Value val;
	enum SlotStatus status;
}slot;

typedef int HashFunc(Key k);

typedef struct _table {
	slot tbl[MAX_TBL];
	HashFunc* hashFunction;
}Table;

void TBLInit(Table* pt, HashFunc* f) {//���̺� �ʱ�ȭ
	int i;
	for (i = 0; i < MAX_TBL; i++)(pt->tbl[i]).status = EMPTY;//��� ���� EMPTY�� �ʱ�ȭ
	pt->hashFunction = f;//�ؽ� �Լ� ���
}
void TBLInsert(Table* pt, Key k, Value v) {//���̺� Ű�� ���� ����
	int hashValue = pt->hashFunction(k);
	pt->tbl[hashValue].val = v;
	pt->tbl[hashValue].key = k;
	pt->tbl[hashValue].status = INUSE;
}
Value TBLDelete(Table* pt, Key k) {//Ű�� �ٰŷ� ���̺��� ������ ����
	int hashValue = pt->hashFunction(k);
	if (pt->tbl[hashValue].status != INUSE)return NULL;//INUSE �ƴϸ� NULL��ȯ(������ �� ����!)
	else {//INUSE������ ��
		(pt->tbl[hashValue]).status = DELETED;//DELETED ���·� �ٲ�
		return (pt->tbl[hashValue]).val;//���� �� ��ȯ
	}
}
Value TBLSearch(Table* pt, Key k) {//Ű�� �ٰŷ� ���̺��� ������ Ž��
	int hashValue = pt->hashFunction(k);
	if ((pt->tbl[hashValue]).status != INUSE)return NULL;//INUSE���� �ƴϸ� ��ȯ�� �� ����!
	else return (pt->tbl[hashValue]).val;//ã�� �� ������(INUSE ������ ���) ��ȯ
}

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
	NewPerson = MakePersonData(20180003, "LEE", "SEOUL");
	TBLInsert(&myTBL, GetNum(NewPerson), NewPerson);

	NewPerson = MakePersonData(20190012, "KIM", "INCHEON");
	TBLInsert(&myTBL, GetNum(NewPerson), NewPerson);

	NewPerson = MakePersonData(20210049, "PARK", "JEJU");
	TBLInsert(&myTBL, GetNum(NewPerson), NewPerson);


	//������ Ž��
	printf("������ Ž�� ���\n");
	SearchPerson = TBLSearch(&myTBL, 20180003);
	if (SearchPerson != NULL)ShowPersonInfo(SearchPerson);

	printf("\n");
	SearchPerson = TBLSearch(&myTBL, 20190012);
	if (SearchPerson != NULL)ShowPersonInfo(SearchPerson);

	printf("\n");
	SearchPerson = TBLSearch(&myTBL, 20210049);
	if (SearchPerson != NULL)ShowPersonInfo(SearchPerson);


	//������ ����
	RemovePerson = TBLDelete(&myTBL, 20180003);
	if (RemovePerson != NULL)free(RemovePerson);

	RemovePerson = TBLDelete(&myTBL, 20190012);
	if (RemovePerson != NULL)free(RemovePerson);

	RemovePerson = TBLDelete(&myTBL, 20210049);
	if (RemovePerson != NULL)free(RemovePerson);

	return 0;
}