#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_LEN 100
#define NAME_LEN 30
#define PHONE_LEN 30

typedef struct __Arraylist {
	int arr[LIST_LEN];
	int numofData;
	int curPosition;
}List;

void ListInit(List* plist) {
	(plist->numofData) = 0;
	(plist->curPosition) = -1;
}
void LInsert(List* plist, int data) {
	if ((plist->numofData) >= LIST_LEN) {
		printf("저장 불가\n");
	}
	else {
		plist->arr[plist->numofData] = data;
		(plist->numofData)++;
	}
}
int LFirst(List* plist, int* pdata) {
	if (plist->numofData == 0) {
		return 0;
	}
	else {
		*pdata = (plist->arr[0]);
		(plist->curPosition) = 0;
		return 1;
	}
}
int LNext(List* plist, int* pdata) {
	if (plist->curPosition >= (plist->numofData) - 1) {
		return 0;
	}
	else {
		(plist->curPosition)++;
		*pdata = plist->arr[plist->curPosition];
		return 1;
	}
}
int LRemove(List* plist) {
	int removePosition = (plist->curPosition);
	int rdata = plist->arr[removePosition];
	for (int i = removePosition; i < (plist->numofData) - 1; i++) {
		plist->arr[i] = plist->arr[i + 1];
	}
	(plist->numofData)--;
	(plist->curPosition)--;
	return rdata;
}
int LCount(List* plist) {
	return (plist->numofData);
}

typedef struct __namecard
{
	char name[NAME_LEN];
	char phone[PHONE_LEN];
} NameCard;

NameCard* MakeNameCard(char* name, char* phone)//NameCard 구조체 변수의 동적 할당 및 초기화 후 주소 값 반환
{
	NameCard* nc = (NameCard*)malloc(sizeof(NameCard));
	strcpy(nc->name, name);
	strcpy(nc->phone, phone);
	return nc;
}
void ShowNameCardInfo(NameCard* pcard)//NameCard 구조체 변수의 정보 출력
{
	printf("이름 : %s\n", pcard->name);
	printf("번호 : %s\n", pcard->phone);
}
int NameCompare(NameCard* pcard, char* name)//이름이 같으면 0, 다르면 0이 아닌 값 반환
{
	return strcmp(pcard->name, name);
}
void ChangePhoneNum(NameCard* pcard, char* phone)//전화번호 정보를 변경
{
	strcpy(pcard->phone, phone);
}

int main() {
	List list;
	ListInit(&list);
	NameCard* nc;
	int num,i,a;
	printf("입력할 사람 수 : ");
	scanf("%d", &num);
	char name[20], phone[20];

	for (i = 0; i < num; i++) {
		printf("%d.이름 : ",i+1);
		scanf("%s", name);
		printf("%d.번호 : ",i+1);
		scanf("%s", phone);
		nc = MakeNameCard(name, phone);
		LInsert(&list, nc);
	}
	printf("\n");
	printf("이름(정보출력) : ");
	scanf("%s", name);
	
	a = 1;
	if (LFirst(&list, &nc)) {
		if (NameCompare(nc, name) == 0) {
			printf("1.이름 : %s 번호 : %s\n", nc->name, nc->phone);
		}
		else {
			while (LNext(&list, &nc)) {
				a++;
				if (NameCompare(nc, name) == 0) {
					printf("%d.이름 : %s 번호 : %s\n", a, nc->name, nc->phone);
					break;
				}
			}
		}
	}
	if ((a == num)&&NameCompare(nc,name)!=0) {
		printf("탐색 실패!없는 이름\n");
	}
	//특정 이름을 대상으로 탐색 진행, 정보 출력


	printf("\n\n");
	printf("이름(번호변경) : ");
	scanf("%s", name);
	printf("번호입력 : ");
	scanf("%s", phone);

	a = 1;
	if (LFirst(&list, &nc)) {
		if (NameCompare(nc, name) == 0) {
			ChangePhoneNum(nc,phone);
			printf("1.이름 : %s 변경후번호 : %s\n", nc->name, nc->phone);
		}
		else {
			while (LNext(&list, &nc)) {
				a++;
				if (NameCompare(nc, name) == 0) {
					ChangePhoneNum(nc, phone);
					printf("%d.이름 : %s 변경후번호 : %s\n", a, nc->name, nc->phone);
					break;
				}
			}
		}
	}
	if ((a == num) && NameCompare(nc, name) != 0) {
		printf("탐색 실패!없는 이름\n");
	}
	printf("\n\n");
	//특정 이름을 대상으로 탐색 진행, 전화번호 정보 변경


	printf("이름(삭제) : ");
	scanf("%s", name);

	a = 1;
	if (LFirst(&list, &nc)) {
		if (NameCompare(nc, name) == 0) {
			LRemove(&list);
		}
		else {
			while (LNext(&list, &nc)) {
				a++;
				if (NameCompare(nc, name) == 0) {
					LRemove(&list);
					break;
				}
			}
		}
	}
	if ((a == num) && NameCompare(nc, name) != 0) {
		printf("탐색 실패!없는 이름\n");
	}
	//특정 이름을 대상으로 탐색 후 삭제

	printf("\n\n");
	printf("전체 출력\n");
	
	if (LFirst(&list, &nc)) {
		printf("1.이름 : %s 번호 : %s\n", nc->name, nc->phone);
		while (LNext(&list, &nc)) {
			printf("%d.이름 : %s 번호 : %s\n", a, nc->name, nc->phone);
		}
	}
	//전체 출력
	return 0;
}
