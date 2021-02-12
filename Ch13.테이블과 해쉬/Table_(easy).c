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
		printf("\n\n사번 :");
		scanf("%d", &(ei.employeeNum));
		printf("나이 : ");
		scanf("%d", &(ei.age));
		arr[ei.employeeNum] = ei;
	}
	printf("\n\n\n찾을 직원의 사번 : ");
	scanf("%d", &num);
	ei = arr[num];
	printf("사번 %d, 나이 %d", ei.employeeNum, ei.age);
	return 0;
}