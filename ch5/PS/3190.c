#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT_SIZE 10

typedef struct {
    int time_to_pass;
    int apple;
    int direction;
} Board;

typedef struct {
    int x;
    int y;
    int length;
    int direction;
} Snake;

typedef struct {
    int x;
    int y;
} Point;
typedef struct {
    Point data[MAX_ELEMENT_SIZE];
    int rear;
    int front;
} Queue;

Board board[101][101] = {};

// 0부터 동 남 서 북
int next_X[4] = {1, 0, -1, 0};
int next_Y[4] = {0, 1, 0, -1};

void error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void init_queue(Queue *q) {
    q->front = q->rear = 0;
}

int queue_next_idx(int i) {
    return (i + 1) % MAX_ELEMENT_SIZE;
}

int is_full(Queue *q) {
    return (queue_next_idx(q->rear) == q->front);
}

int is_empty(Queue *q) {
    return (q->front == q->rear);
}

void enqueue(Queue *q, Point e) {
    if (is_full(q)) {
        error("큐 포화 에러");
    }
    q->rear = (++q->rear) % MAX_ELEMENT_SIZE;
    q->data[q->rear] = e;
}

Point dequeue(Queue *q) {
    if (is_empty(q)) {
        error("큐 공백 에러");
    }
    q->front = queue_next_idx(q->front);
    return q->data[q->front];
}

Point peek(Queue *q) {
    if (is_empty(q)) {
        error("큐 공백 에러");
    }
    return q->data[queue_next_idx(q->front)];
}

void snake_move(Queue *path) {
    for (int i = queue_next_idx(path->front); i <= path->rear; i = queue_next_idx(i)) {
        Point body = path->data[i];
        board[body.x][body.y].time_to_pass--;
    }
}

void snake_eat_apple(Queue *path) {
    for (int i = queue_next_idx(path->front); i <= path->rear; i = queue_next_idx(i)) {
        Point body = path->data[i];
        board[body.x][body.y].time_to_pass++;
    }
}

int main(void) {
    Snake snake = {1, 1, 1, 0};
    Queue path;
    init_queue(&path);

    char Ls[100] = {};
    int X[100] = {}, C[100] = {};
    int N, K, L, clock = 0;
    int a_x, a_y;

    // 입력
    scanf("%d", &N);
    scanf("%d", &K);
    for (int i = 0; i < K; i++) {
        scanf("%d %d", &a_x, &a_y);
        board[a_x][a_y].apple = 1;
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
    board[1][1].time_to_pass = 1;

    while (0 < snake.x && snake.x < 101 && 0 < snake.y && snake.y < 101) {
        Point p = {snake.x, snake.y};
        Board *now = &board[p.x][p.y];

        // 시간 흐름
        clock++;

        // 몸통 움직임
        snake_move(&path);

        //꼬리 제거
        Point tail = peek(&path);
        if (board[tail.x][tail.y].time_to_pass == 0) dequeue(&path);

        /*  머리 이동 시작 */
        // 만약 머리가 몸통에 닿는다면
        if (now->time_to_pass > 0)
            break;

        // 사과가 있으면
        if (now->apple) {
            snake_eat_apple(&path);
            snake.length++;
        }

        // 만약 방향을 움직일 시간이면
        if (Ls[clock]) {
            switch (Ls[clock]) {
                case 'L':
                    snake.direction = (snake.direction == 0) ? 3 : snake.direction - 1;
                    break;
                case 'D':
                    snake.direction = (snake.direction + 1) % 4;
            }
        }

        snake.x += next_X[snake.direction];
        snake.y += next_Y[snake.direction];

        enqueue(&path, p);
        now->time_to_pass = snake.length;
        /*  머리 이동 끝 */
    }

    printf("%d", clock);

    return 0;
}