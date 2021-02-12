#include <stdio.h>

typedef struct employeeInfo {
	int employeeNum;
	int age;
}Info;
int GetHashValue(int empNum) {//�����ڸ� ���� �̷���� ������ ����� �� �ڸ� ���� ����
	return empNum % 100;
}
int main(void) {
	Info arr[100];
	Info emp1 = { 20170003,42 };
	Info emp2 = { 20190012,33 };
	Info emp3 = { 20210049,27 };

	Info r1, r2, r3;

	//Ű(���)�� �ε��� ������ �̿��ؼ� ����
	//�ε��� = ���%100
	arr[GetHashValue(emp1.employeeNum)] = emp1;
	arr[GetHashValue(emp2.employeeNum)] = emp2;
	arr[GetHashValue(emp3.employeeNum)] = emp3;

	//Ű�� �ε��� ������ �̿��ؼ� Ž��
	r1 = arr[GetHashValue(20170003)];
	r2 = arr[GetHashValue(20190012)];
	r3 = arr[GetHashValue(20210049)];


	//��� ���
	printf("��� %d & ���� %d\n", r1.employeeNum, r1.age);
	printf("��� %d & ���� %d\n", r2.employeeNum, r2.age);
	printf("��� %d & ���� %d\n", r3.employeeNum, r3.age);
	return 0;
}