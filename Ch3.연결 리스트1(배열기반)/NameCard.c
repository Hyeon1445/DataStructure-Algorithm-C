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
		printf("���� �Ұ�\n");
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

NameCard* MakeNameCard(char* name, char* phone)//NameCard ����ü ������ ���� �Ҵ� �� �ʱ�ȭ �� �ּ� �� ��ȯ
{
	NameCard* nc = (NameCard*)malloc(sizeof(NameCard));
	strcpy(nc->name, name);
	strcpy(nc->phone, phone);
	return nc;
}
void ShowNameCardInfo(NameCard* pcard)//NameCard ����ü ������ ���� ���
{
	printf("�̸� : %s\n", pcard->name);
	printf("��ȣ : %s\n", pcard->phone);
}
int NameCompare(NameCard* pcard, char* name)//�̸��� ������ 0, �ٸ��� 0�� �ƴ� �� ��ȯ
{
	return strcmp(pcard->name, name);
}
void ChangePhoneNum(NameCard* pcard, char* phone)//��ȭ��ȣ ������ ����
{
	strcpy(pcard->phone, phone);
}

int main() {
	List list;
	ListInit(&list);
	NameCard* nc;
	int num,i,a;
	printf("�Է��� ��� �� : ");
	scanf("%d", &num);
	char name[20], phone[20];

	for (i = 0; i < num; i++) {
		printf("%d.�̸� : ",i+1);
		scanf("%s", name);
		printf("%d.��ȣ : ",i+1);
		scanf("%s", phone);
		nc = MakeNameCard(name, phone);
		LInsert(&list, nc);
	}
	printf("\n");
	printf("�̸�(�������) : ");
	scanf("%s", name);
	
	a = 1;
	if (LFirst(&list, &nc)) {
		if (NameCompare(nc, name) == 0) {
			printf("1.�̸� : %s ��ȣ : %s\n", nc->name, nc->phone);
		}
		else {
			while (LNext(&list, &nc)) {
				a++;
				if (NameCompare(nc, name) == 0) {
					printf("%d.�̸� : %s ��ȣ : %s\n", a, nc->name, nc->phone);
					break;
				}
			}
		}
	}
	if ((a == num)&&NameCompare(nc,name)!=0) {
		printf("Ž�� ����!���� �̸�\n");
	}
	//Ư�� �̸��� ������� Ž�� ����, ���� ���


	printf("\n\n");
	printf("�̸�(��ȣ����) : ");
	scanf("%s", name);
	printf("��ȣ�Է� : ");
	scanf("%s", phone);

	a = 1;
	if (LFirst(&list, &nc)) {
		if (NameCompare(nc, name) == 0) {
			ChangePhoneNum(nc,phone);
			printf("1.�̸� : %s �����Ĺ�ȣ : %s\n", nc->name, nc->phone);
		}
		else {
			while (LNext(&list, &nc)) {
				a++;
				if (NameCompare(nc, name) == 0) {
					ChangePhoneNum(nc, phone);
					printf("%d.�̸� : %s �����Ĺ�ȣ : %s\n", a, nc->name, nc->phone);
					break;
				}
			}
		}
	}
	if ((a == num) && NameCompare(nc, name) != 0) {
		printf("Ž�� ����!���� �̸�\n");
	}
	printf("\n\n");
	//Ư�� �̸��� ������� Ž�� ����, ��ȭ��ȣ ���� ����


	printf("�̸�(����) : ");
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
		printf("Ž�� ����!���� �̸�\n");
	}
	//Ư�� �̸��� ������� Ž�� �� ����

	printf("\n\n");
	printf("��ü ���\n");
	
	if (LFirst(&list, &nc)) {
		printf("1.�̸� : %s ��ȣ : %s\n", nc->name, nc->phone);
		while (LNext(&list, &nc)) {
			printf("%d.�̸� : %s ��ȣ : %s\n", a, nc->name, nc->phone);
		}
	}
	//��ü ���
	return 0;
}