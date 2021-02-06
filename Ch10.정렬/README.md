# 버블 정렬 BubbleSort

옆에 붙어 있는 값과 비교하기

```C

for (i=0;i<n-1;i++){
      for(j=0;j<(n-i)-1;j++){
	//비교, 자리바꾸기
	}
}
```

__Bubble Sort : O(n^2)__

# 선택 정렬 Selection Sort

첫 번째 올 데이터를 탐색해 첫 번째 자리로 옮기고

두 번째 올 데이터를 탐색해 두 번째 자리로 옮기고....반복

**Selection Sort : O(n^2)**

# 삽입 정렬 Insertion Sort

하나씩 자리 찾아서 옮겨넣기

정렬이 완료된 영역의 다음에 위치한 데이터가 그 다음 정렬대상이다

**Insertion Sort : O(n^2) (숫자 n개 & 자리찾기)**

# 힙 정렬

ch9 참고

시간 복잡도

힙 저장 시간 복잡도 : O(log2(n))

힙 삭제 시간 복잡도 : O(log2(n))

저장+삭제 ->O(2*log2(n))인데 2는 무시 -> O(log2(n))

**Heap Sort : n개의 데이터 정렬 : O(n*log2(n))**

# 병합 정렬 Merge Sort

1. 분할 Divide : 하나씩 나눠질 때까지 분할

2. 정복 Conquer : 문제 해결 단계 (여기서는 정렬)

3. 결합 Combine

재귀함수를 이용해서 정렬!

```C
void MergeSort(int arr[], int left, int right) {//재귀함수가 핵심!
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		MergeSort(arr, left, mid);
		MergeSort(arr, mid + 1, right);
		MergeTwoArea(arr, left, mid, right);
	}
}
```

데이터 n개일 때

각 병합 단계마다 최대 n번의 비교연산이 진행된다!

그리고 병합 과정은 log2(n)번 진행(ex : 데이터 8개일 때 병합 3단계, 데이터 16개일때 병합 4단계...)

O(nlog2(n))

임시 배열에 옮겼다가 다시 원래 배열로 옮기는 과정 : 2번씩(배열 병합 정렬은 임시 메모리가 필요함!/연결 리스트는 임시 메모리 안필요함)

따라서 O(2*nlog2(n))인데

**MergeSort : O(nlog2(n))** 로 표현 가능!

# 퀵 정렬 Quick Sort

재귀함수!

* left : 제일 왼쪽 위치

* right : 제일 오른쪽 위치

* pivot : 중심점, 중심축 위치 (여기서는 left를 pivot으로 정해서 씀, 다른 데이터를 pivot으로 써도 됨)

* low : pivot 제외 가장 왼쪽 위치 / pivot보다 큰 값(우선순위 낮은 값)을 만날 때까지 오른쪽으로 이동

* high : pivot 제외 가장 오른쪽 위치 / pivot보다 작은 값(우선순위 높은 값)을 만날 때까지 왼쪽으로 이동

low와 high이동 후 그 둘의 데이터를 바꿈 

-> low와 high가 교차되는 상황에서는 바꾸지 않는다 

-> pivot과 high 데이터를 바꾼다 (그러면 pivot을 중심으로 왼쪽은 작은값, 오른쪽은 큰 값이 있음, 정렬은 불완전 )

-> 왼쪽 영역과 오른쪽 영역 각각 pivot 정하고 QuickSort 진행

-> left > right 일 때 left와 right가 교차되는 상황 : 더 이상 정렬할 대상이 없다

QuickSort 시간 복잡도

하나의 pivot이 제자리를 찾아가는데 필요한 비교연산횟수=데이터수n

분할횟수 log2(n)번

**QuickSort : O(nlog2(n))** 

원래 최악의 경우를 기준으로 빅오를 계산해야 하지만 여기서는 퀵정렬은 예외적으로 최선, 평균적인 빅오를 계산함

최악의 경우를 계산한다면 O(n^2)

QuickSort는 데이터의 이동이 데이터의 비교에 비해 적게 일어나고, 별도의 메모리 공간이 필요없으므로 

동일한 빅오를 갖는 다른 정렬 알고리즘 중에서 평균적으로 가장 빠른 속도를 가짐

# 기수 정렬 Radix Sort

* 비교연산을 하지 않는다 (장)

* O(nlog2(n))의 한계를 넘어설 수 있는 알고리즘 (장)

* 적용할 수 있는 범위가 제한적이다 (단) (데이터의 길이가 같아야 한다!-안맞으면 강제로 맞춰서 해야함...0을 붙인다던지....)

만약 10진수로 표현된 값이면 10개의 bucket이 필요하고, 5진수로 표현된 값이면 5개의 bucket이 필요

(ex : 3자리 수 5진수 정렬인 경우 5개의 bucket이 필요)

LSD : Least Significant Digit : 일의 자리부터 기준으로 삼아 bucket에 넣고, bucket에 여러 값이 있으면 들어간 순서대로 나온다

MSD : Most Significant Digit : 가장 큰 자릿수부터 정렬 진행 but 중간에 맞는 결과가 나오고 끝까지 두면 잘못된 순서로 정렬되므로 계속 검토 필요!, LSD에 비해 난이도 높다

Radix Sort(LSD)의 시간 복잡도

maxLen*num

**Radix Sort(LSD) : O(l*n)**

l은 정렬 대상의 길이(최대 길이로 동일하다고 생각), n은 입력 데이터 개수










