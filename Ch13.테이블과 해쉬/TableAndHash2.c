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
enum SlotStatus { EMPTY,DELETED,INUSE };


typedef int Key;//키 : 주민등록번호
typedef Person* Value; // 값 : Person 구조체 변수의 주소 값

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

void TBLInit(Table* pt, HashFunc* f) {//테이블 초기화
	int i;
	for (i = 0; i < MAX_TBL; i++)(pt->tbl[i]).status = EMPTY;//모든 슬롯 EMPTY로 초기화
	pt->hashFunction = f;//해쉬 함수 등록
}
void TBLInsert(Table* pt, Key k, Value v) {//테이블에 키와 값을 저장
	int hashValue = pt->hashFunction(k);
	pt->tbl[hashValue].val = v;
	pt->tbl[hashValue].key = k;
	pt->tbl[hashValue].status = INUSE;
}
Value TBLDelete(Table* pt, Key k) {//키를 근거로 테이블에서 데이터 삭제
	int hashValue = pt->hashFunction(k);
	if (pt->tbl[hashValue].status != INUSE)return NULL;//INUSE 아니면 NULL반환(삭제할 거 없음!)
	else {//INUSE상태일 때
		(pt->tbl[hashValue]).status = DELETED;//DELETED 상태로 바꿈
		return (pt->tbl[hashValue]).val;//삭제 값 반환
	}
}
Value TBLSearch(Table* pt, Key k) {//키를 근거로 테이블에서 데이터 탐색
	int hashValue = pt->hashFunction(k);
	if ((pt->tbl[hashValue]).status != INUSE)return NULL;//INUSE상태 아니면 반환할 값 없음!
	else return (pt->tbl[hashValue]).val;//찾은 값 있으면(INUSE 상태인 경우) 반환
}

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
	NewPerson = MakePersonData(20180003, "LEE", "SEOUL");
	TBLInsert(&myTBL, GetNum(NewPerson), NewPerson);

	NewPerson = MakePersonData(20190012, "KIM", "INCHEON");
	TBLInsert(&myTBL, GetNum(NewPerson), NewPerson);

	NewPerson = MakePersonData(20210049, "PARK", "JEJU");
	TBLInsert(&myTBL, GetNum(NewPerson), NewPerson);


	//데이터 탐색
	printf("데이터 탐색 결과\n");
	SearchPerson = TBLSearch(&myTBL, 20180003);
	if (SearchPerson != NULL)ShowPersonInfo(SearchPerson);

	printf("\n");
	SearchPerson = TBLSearch(&myTBL, 20190012);
	if (SearchPerson != NULL)ShowPersonInfo(SearchPerson);

	printf("\n");
	SearchPerson = TBLSearch(&myTBL, 20210049);
	if (SearchPerson != NULL)ShowPersonInfo(SearchPerson);


	//데이터 삭제
	RemovePerson = TBLDelete(&myTBL, 20180003);
	if (RemovePerson != NULL)free(RemovePerson);

	RemovePerson = TBLDelete(&myTBL, 20190012);
	if (RemovePerson != NULL)free(RemovePerson);

	RemovePerson = TBLDelete(&myTBL, 20210049);
	if (RemovePerson != NULL)free(RemovePerson);

	return 0;
}