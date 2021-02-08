#include <stdio.h>

int InterpolationSearch(int arr[], int first, int last, int target) {
	int mid;
	if (arr[first]>target||arr[last]<target)return -1;
	//ch2 RecursiveBinarySearch와의 차이점!!
	//만약 if(first>last)return -1;이면 {1,3,5,7,9}에서 2 찾기 동작 제대로 안함
	mid = ((double)(target - arr[first]) / (arr[last] - arr[first])) * (last - first) + first;
	//ch2 RecursiveBinarySearch와의 차이점!! - 공식!
	//mid변수이름이 여기서는 중간값을 의미하진 않지만 그냥 씀
	if (arr[mid] == target)return mid;
	else if (target < arr[mid])return InterpolationSearch(arr, first, mid - 1, target);//재귀
	else return InterpolationSearch(arr, mid + 1,last, target);//재귀
}
int main(void) {
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	int idx,num;
	printf("찾을 숫자(1~10) : ");
	scanf("%d", &num);
	idx = InterpolationSearch(arr, 0, sizeof(arr) / sizeof(int)-1, num);
	if (idx == -1)printf("탐색실패!\n");
	else printf("타겟 저장 인덱스 : %d\n", idx);
	return 0;
}