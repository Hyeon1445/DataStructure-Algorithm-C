# Queue큐

선입선출, 선착순

FIFO(First-in, First-Out)

* enqueue 큐에 데이터 넣기

(꼬리에 데이터 넣음)

* dequeue 큐에서 데이터 꺼내기

(머리에서 데이터 꺼냄)

# Circular Queue

(배열큐에서 효율적으로 사용)

원형큐에서는 머리와 꼬리 위치로는 꽉 찬 경우와 텅 빈 경우를 구분할 수 없다

따라서 배열의 길이가 N이면 최대 N-1개까지만 채운다

# Deque덱

double-ended Queue

앞뒤로 넣고 앞뒤로 뺄 수 있는 자료구조

Deque 코드

DequeInit(&dq)의 pdeq->tail=NULL에서

Stack around the variable 'dq'was corrupted 에러 뜸
