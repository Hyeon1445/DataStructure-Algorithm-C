#include <stdio.h>

typedef struct employeeInfo {
	int employeeNum;
	int age;
}Info;
int main(void) {
	Info arr[1000];
	Info ei;
	int num,i;
	for (i = 0; i < 3; i++) {
		printf("\n\n��� :");
		scanf("%d", &(ei.employeeNum));
		printf("���� : ");
		scanf("%d", &(ei.age));
		arr[ei.employeeNum] = ei;
	}
	printf("\n\n\nã�� ������ ��� : ");
	scanf("%d", &num);
	ei = arr[num];
	printf("��� %d, ���� %d", ei.employeeNum, ei.age);
	return 0;
}