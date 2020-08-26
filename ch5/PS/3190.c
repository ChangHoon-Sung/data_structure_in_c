// BOJ 3190 뱀
// Assign: ChangHoon Sung
//
// INPUT
// N: 보드의 크기 (2 <= N <= 100)
// K: 사과의 개수 (0 <= K <= 100)
// L: 방향 전환의 횟수 (1 <= L <= 100)
// X, C: X초에 C방향으로 전환 (1 <= X <= 10,000, C == 'L' || 'D')

/*
TRY #1 (대실패) - 몸통에 따른 맵-시간 카운팅
몸통의 길이에 따라 몇 초 뒤에 맵을 벗어나는지 카운트하는 방식. 머리가 지나온 길을 큐가 저장했다.
문제는 이 처리를 하는 것 자체가 너무 비효율적이고 작성자에게도 헷갈리기만 했다.
결국 문제의 본질에 다가서지 못하고 실패. 내가 짜놓고도 보기가 싫어서 며칠동안 놀았다.

TRY #2 (정답 확인) - 맵에 상태 마킹
그냥 위에처럼 할 필요없이 1. 머리가 지나간 곳에 체크, 2. 몸통은 그 경로를 담고, 3. 꼬리가 pop할 때 그 마킹을 지워주면 그만이었다.
바보같이 굴긴..

이번 문제에서 배운 점.

- 상태같은 경우 #define으로 작성하면 편리하다.
- 문자열 매칭과 마찬가지로, 어떤 상태나 패턴 확인은 함수로 분리해두면 가독성이 좋아진다.

- 또, 뱀의 움직임을 체크할 때 반복문의 처음과 끝을 작성하다가 머리가 먼저인지 꼬리가 먼저인지 헷갈리는 상황을 경험했다.
반복문의 시작과 끝을 잘 정하자. 문제에서 알려준 그!대!로! 하면 된다.
init - 몸통의 시작점을 미리 담아두고
loop - 머리의 새로운 위치가 이동 가능한 곳인지 판단하고,
     - 머리를 새로 둘 곳의 사과 유무에 따라 처리하고
     - 시간에 따라 방향을 설정하고
     - 그 방향에 맞게 머리를 이동한다.

실질적으로 머리가 이동(enqueue)되는 순간은 마지막이다.
코드를 먼저 짜지 말고, 흐름을 먼저 파악하자.

문제는 나를 괴롭히려는게 아니라, 최대한 깔끔하게 짤 수 있도록 준비되어있다.
수능 문제를 생각해보자. 작정하고 더러운 문제보다 아름답게 풀 수 있는 문제가 더 많지 않던가?
*/
#include <stdio.h>

#define MAX_ELEMENT_SIZE 100
#define APPLE 1
#define SNAKE -1

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point head;
    int direction;
} Snake;

typedef struct {
    Point data[MAX_ELEMENT_SIZE];
    int rear;
    int front;
} Queue;

void init_queue(Queue *q) {
    q->front = q->rear = 0;
}

int is_full(Queue *q) {
    return ((q->rear + 1) % MAX_ELEMENT_SIZE == q->front);
}

int is_empty(Queue *q) {
    return (q->front == q->rear);
}

void enqueue(Queue *q, Point e) {
    q->rear = (++q->rear) % MAX_ELEMENT_SIZE;
    q->data[q->rear] = e;
}

Point dequeue(Queue *q) {
    q->front = (q->front + 1) % MAX_ELEMENT_SIZE;
    return q->data[q->front];
}

int board[101][101] = {};
int N;

int canMove(int dx, int dy) {
    return 0 < dx && dx <= N && 0 < dy && dy <= N && board[dx][dy] != -1;
}

// 0부터 동 남 서 북
int next_X[4] = {1, 0, -1, 0};
int next_Y[4] = {0, 1, 0, -1};

int main(void) {
    Snake snake = {{1, 1}, 0};
    Queue path;
    init_queue(&path);

    char Ls[10000] = {};
    int X[100] = {}, C[100] = {};
    int K, L, clock;
    int a_x, a_y, dx, dy;

    // 입력
    scanf("%d", &N);
    scanf("%d", &K);
    for (int i = 0; i < K; i++) {
        scanf("%d %d", &a_x, &a_y);
        board[a_y][a_x] = APPLE;
    }
    scanf("%d", &L);
    for (int i = 0; i < L; i++) {
        int idx;
        scanf("%d", &idx);
        scanf(" %c", &Ls[idx]);
    }

    // 게임 시작
    Point p = {1, 1};
    enqueue(&path, p);
    board[1][1] = -1;

    for (clock = 1;; clock++) {
        dx = snake.head.x + next_X[snake.direction];
        dy = snake.head.y + next_Y[snake.direction];

        // 맵의 끝이거나 몸통에 부딪히면
        if (!canMove(dx, dy)) break;

        snake.head.x = dx;
        snake.head.y = dy;

        // 사과가 없으면
        if (board[dx][dy] != APPLE) {
            Point tail = dequeue(&path);
            board[tail.x][tail.y] = 0;
        }

        // 만약 방향을 움직일 시간이면
        if (Ls[clock]) {
            switch (Ls[clock]) {
                case 'L':
                    snake.direction = (snake.direction + 3) % 4;
                    break;
                case 'D':
                    snake.direction = (snake.direction + 1) % 4;
            }
        }

        // 머리 이동
        board[dx][dy] = SNAKE;
        p.x = dx, p.y = dy;
        enqueue(&path, p);
    }

    printf("%d", clock);

    return 0;
}