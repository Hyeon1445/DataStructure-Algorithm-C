#include <stdio.h>

typedef struct employeeInfo {
	int employeeNum;
	int age;
}Info;
int GetHashValue(int empNum) {//여덟자리 수로 이루어진 직원의 사번을 두 자리 수로 변경
	return empNum % 100;
}
int main(void) {
	Info arr[100];
	Info emp1 = { 20170003,42 };
	Info emp2 = { 20190012,33 };
	Info emp3 = { 20210049,27 };

	Info r1, r2, r3;

	//키(사번)를 인덱스 값으로 이용해서 저장
	//인덱스 = 사번%100
	arr[GetHashValue(emp1.employeeNum)] = emp1;
	arr[GetHashValue(emp2.employeeNum)] = emp2;
	arr[GetHashValue(emp3.employeeNum)] = emp3;

	//키를 인덱스 값으로 이용해서 탐색
	r1 = arr[GetHashValue(20170003)];
	r2 = arr[GetHashValue(20190012)];
	r3 = arr[GetHashValue(20210049)];


	//결과 출력
	printf("사번 %d & 나이 %d\n", r1.employeeNum, r1.age);
	printf("사번 %d & 나이 %d\n", r2.employeeNum, r2.age);
	printf("사번 %d & 나이 %d\n", r3.employeeNum, r3.age);
	return 0;
}