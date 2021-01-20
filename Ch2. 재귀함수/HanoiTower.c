#include <stdio.h>
void HanoiTower(int num, char from, char by, char to) {
	if (num == 1) {
		printf("원반%d을/를 %c에서 %c로 이동\n", num, from, to);
	}
	else {
		HanoiTower(num - 1, from, to, by);
		printf("원반%d을/를 %c에서 %c로 이동\n", num, from, to);
		HanoiTower(num - 1, by, from, to);
	}
}
int main(void) {
	int n;
	printf("The Tower of Hanoi\n");
	printf("막대 A에 꽂혀있는 원반 n개를 막대 C로 옮기기!\n");
	printf("n = ");
	scanf("%d", &n);
	HanoiTower(n, 'A', 'B', 'C');
	return 0;
}

