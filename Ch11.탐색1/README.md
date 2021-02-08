# 탐색

* 순차 탐색 (정렬되지 않은 대상을 탐색함)
* 이진 탐색 (정렬된 대상을 탐색함) / 찾는 대상의 위치에 따라서 탐색의 효율 차이 발생
<br>

# 보간 탐색 Interpolation Search

이진 탐색의 비효율성을 개선시킨 알고리즘, 탐색대상을 줄이는 속도가 이진 탐색보다 뛰어남

__중앙부터 탐색을 시작하지 않고, 만약 탐색 대상이 앞쪽에 있으면 앞쪽부터 탐색을 시작!__

ex : 전화번호부, 사전

* low : 시작 인덱스
* high : 끝 인덱스
* target : 찾을 대상 인덱스
<br>

```C
A=arr[high]-arr[low]

Q=arr[target]-arr[low]

A : Q=(high-low) : (target-low)

(arr[high]-arr[low]) : (arr[target]-arr[low]) = (high-low) : (target-low)
```

<br>
과정

```C
A(target-low) = Q(high-low)

target-low=(Q/A)*(high-low)

target = (Q/A)*(high-low)+low

target=(arr[target]-arr[low])/(arr[high]-arr[low])*(high-low)+low
```

방법 : 찾을 대상인 arr[target]값을 넣고 그 위치인 target인덱스를 찾는 것

주의 : 나눗셈 연산이 진행되므로 정수형이 아닌 실수형 나눗셈으로 진행!!!!(보간 탐색의 단점)

```C
typedef struct item{
	int searchKey; //탐색키, 고유한 값, NULL안됨 ex) 사번
	double searchData; //탐색데이터  ex) 직원정보
}Item;
```
<br>
핵심뽀인뜨!

```C

mid=((double)(target-arr[first])/(arr[last]-arr[first])*(last-first)+first;

//나눗셈부분 double 중요!!
//ch2. RecursiveBinarySearch와의 차이점!!

```

# 이진 탐색 트리

* 저장된 key(데이터값)는 유일
* 루트 노드의 키가 왼쪽 sub tree의 어떤 노드의 키보다 크다
* 루트노드의 키가 오른쪽  sub tree의 어떤 노드의 키보다 작다
* 왼쪽과 오른쪽 서브 트리도 이진 탐색 트리
* 탐색 연산 O(log2(n))

<br>
key의 크기
<br>
LeftChild < Parent < RightChild
<br>

삽입 ) 루트부터 시작해 비교대상이 없을 때까지 내려간 뒤 저장! (비교 : 작으면 Leftchild 크면 Rightchild로 이동)

삭제 ) 단순X, 최대 6가지 경우의 수 (루트냐 아니냐 까지 따지면)
* 경우 1. 삭제할 노드가 단말 노드 (child 가 없다)
* 경우 2. 삭제할 노드가 하나의 sub tree를 갖는 경우
* 경우 3. 삭제할 노드가 두개의 sub tree를 갖는 경우
	* 왼쪽 서브 트리에서 가장 큰 값 또는 오른쪽 서브 트리에서 가장 작은 값이 대체
	* (예시 코드에서는 오른쪽 서브 트리의 가장 작은 값을 가진 노드가 삭제 노드 대체)
	* 1단계 : 삭제할 노드를 대체할 노드 찾기
	* 2단계 : 대체할 노드에 저장된 값을 삭제할 노드에 대입
	* 3단계 : 대체할 노드의 부모 노드와 자식 노드를 연결
<br>
이진 트리의 단점 
저장 순서에 따라 탐색의 성능에 차이 -> 해결) 균형 잡힌 이진 트리
