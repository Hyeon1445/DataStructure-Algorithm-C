#include <stdio.h>
void HanoiTower(int num, char from, char by, char to) {
	if (num == 1) {
		printf("����%d��/�� %c���� %c�� �̵�\n", num, from, to);
	}
	else {
		HanoiTower(num - 1, from, to, by);
		printf("����%d��/�� %c���� %c�� �̵�\n", num, from, to);
		HanoiTower(num - 1, by, from, to);
	}
}
int main(void) {
	int n;
	printf("The Tower of Hanoi\n");
	printf("���� A�� �����ִ� ���� n���� ���� C�� �ű��!\n");
	printf("n = ");
	scanf("%d", &n);
	HanoiTower(n, 'A', 'B', 'C');
	return 0;
}

