#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER_OF_WORKER 3
#define BUSINESS_TIME 50
#define MAX_ELEMENT_SIZE 100

typedef struct {
    int id;
    int todo_time;
} task;

typedef task element;
typedef struct {
    element data[MAX_ELEMENT_SIZE];
    int rear;
    int front;
    int size;
    int working_time;
} Deque;

void error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void init_deque(Deque *deq) {
    deq->rear = deq->front = deq->size = deq->working_time = 0;
}

int is_full(Deque *deq) {
    return ((deq->rear + 1) % MAX_ELEMENT_SIZE == deq->front);
}

int is_empty(Deque *deq) {
    return (deq->front == deq->rear);
}

void add_rear(Deque *deq, element e) {
    if (is_full(deq)) {
        error("덱 포화 에러");
    }
    deq->size++;
    deq->rear = (deq->rear + 1) % MAX_ELEMENT_SIZE;
    deq->data[deq->rear] = e;
}

void add_front(Deque *deq, element e) {
    if (is_full(deq)) {
        error("덱 포화 에러");
    }
    deq->size++;
    deq->data[deq->front] = e;
    deq->front = (deq->front - 1 + MAX_ELEMENT_SIZE) % MAX_ELEMENT_SIZE;
}

element delete_rear(Deque *deq) {
    int prev = deq->rear;
    if (is_empty(deq)) {
        error("덱 공백 에러");
    }
    deq->size--;
    deq->rear = (deq->rear - 1 + MAX_ELEMENT_SIZE) % MAX_ELEMENT_SIZE;
    return deq->data[prev];
}

element delete_front(Deque *deq) {
    if (is_empty(deq)) {
        error("덱 공백 에러");
    }
    deq->size--;
    deq->front = (deq->front + 1) % MAX_ELEMENT_SIZE;
    return deq->data[deq->front];
}

element get_rear(Deque *deq) {
    if (is_empty(deq)) {
        error("덱 공백 에러");
    }
    return deq->data[deq->rear];
}

element get_front(Deque *deq) {
    if (is_empty(deq)) {
        error("덱 공백 에러");
    }
    return deq->data[(deq->front + 1) % MAX_ELEMENT_SIZE];
}

void print_remain_task(Deque *worker, int n) {
    int idx = (worker->front + 2) % MAX_ELEMENT_SIZE;
    printf("\t\t일꾼 %d의 남은 작업[", n);
    while (idx != (worker->rear + 1) % MAX_ELEMENT_SIZE) {
        printf("%d, ", worker->data[idx].id);
        idx = (idx + 1) % MAX_ELEMENT_SIZE;
    }
    printf("]\n");
}

int main(void) {
    Deque Worker[NUMBER_OF_WORKER];
    int remain_times[NUMBER_OF_WORKER] = {};
    int selected;
    int task_id = 0, total_task_time = 0;
    task new_task;

    for (int i = 0; i < NUMBER_OF_WORKER; i++) {
        init_deque(&Worker[i]);
    }

    srand(time(NULL));

    // 각 워커는 단위 시간동안 '할당과 착수', '작업하기', 그리고 '빼앗기'를 할 수 있다.
    // 즉, 할당받거나 빼앗은 작업은 그 다음 작업 시간부터 '작업하기'를 수행할 수 있다.
    for (int clock = 0; clock < BUSINESS_TIME; clock++) {
        printf("\n작업 시간 %d\n", clock);
        // 일은 시간당 50% 확률로 무작위 워커에게 들어온다. 수행시간이 5시간 이하인 작업이 할당된다.
        if (!(rand() % 2)) {
            selected = rand() % NUMBER_OF_WORKER;
            new_task.id = task_id++, new_task.todo_time = (rand() % 4) + 1;
            add_rear(&Worker[selected], new_task);
            printf("일꾼 %d이(가) %d시간짜리 작업 %d를 할당받았습니다.\n", selected, new_task.todo_time, new_task.id);
        }

        // 유휴 워커는 바쁜 워커의 일을 빼앗을 수 있다.
        // 유휴 워커가 없도록 모든 워커를 순회한다.
        for (int idle = 0; idle < NUMBER_OF_WORKER; idle++) {
            if (Worker[idle].size == 0) {
                for (int busy = 0; busy < NUMBER_OF_WORKER; busy++) {
                    if (Worker[busy].size > 1) {
                        add_rear(&Worker[idle], delete_rear(&Worker[busy]));
                        printf("선량한 일꾼 %d이(가) 바쁜 일꾼 %d의 작업 %d을(를) 빼았았습니다.\n", idle, busy, get_rear(&Worker[idle]).id);
                        break;
                    }
                }
            }
        }

        // 각 워커가 작업을 수행한다.
        for (int busy = 0; busy < NUMBER_OF_WORKER; busy++) {
            Deque *current_worker = &Worker[busy];

            if (current_worker->size > 0) {
                task current_task = get_front(current_worker);

                if (remain_times[busy] == 0) {
                    remain_times[busy] = current_task.todo_time;
                } else {
                    printf("일꾼 %d이(가) 작업 %d을(를) 수행중입니다. (%d/%d)",
                           busy, current_task.id, current_task.todo_time - remain_times[busy] + 1, current_task.todo_time);
                    if (current_worker->size > 1)
                        print_remain_task(current_worker, busy);
                    else
                        printf("\n");

                    remain_times[busy]--;
                    current_worker->working_time++;
                    total_task_time++;
                }

                if (remain_times[busy] == 0) {
                    delete_front(current_worker);
                }
            }
        }
    }

    printf("\n--------------------------------------------------\n\n");
    printf("오늘도 하루 일과가 끝났습니다.\n");
    printf("각 부서는 보안결산을 시행하고, 일과 보고서를 작성해주시기 바랍니다.\n\n");

    printf("==================================================\n");
    printf("\t\t 일 과 보 고 서 \t\t\n");
    printf("==================================================\n");
    printf("주어진 일과 시간: %d시간\n", BUSINESS_TIME);
    printf("주어진 작업의 수: %d개\n\n", task_id - 1);

    for (int i = 0; i < NUMBER_OF_WORKER; i++) {
        printf("일꾼 %d가 일한 시간: %d시간\n", i, Worker[i].working_time);
    }
    printf("\n");

    float avg_working_time = 0;
    for (int i = 0; i < NUMBER_OF_WORKER; i++) {
        avg_working_time += Worker[i].working_time;
    }
    avg_working_time = avg_working_time / NUMBER_OF_WORKER;

    printf("혼자서 했다면 걸렸을 시간: %d\n", total_task_time);
    printf("일꾼 평균 작업 시간: %.2lf시간\n", avg_working_time);
    printf("혼자가 아닌 %d명에서 팀워크를 발휘했기 때문에 여러분은 같은 작업을 %.2lf%%나 빨리 끝냈습니다.\n", NUMBER_OF_WORKER, 100 - (avg_working_time / total_task_time * 100));
    printf("앞으로도 서로를 생각하는 마음으로 업무를 잘 분배합시다.\n");

    return 0;
}