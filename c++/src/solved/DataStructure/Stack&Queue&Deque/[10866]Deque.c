#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100000

typedef struct {
    int front;
    int rear;
    int data[MAX_SIZE];
} deque;

deque* init_deque() {
    deque *d = (deque*)malloc(sizeof(deque));
    d -> front = 0; d -> rear = 0;
    for (int i = 0; i < MAX_SIZE; i++) d -> data[i] = 0;
    return d;
}

int is_empty(deque *d) {
    return d -> front == d -> rear;
}
int is_full(deque *d) {
    return (d -> front == (d -> rear + 1) % MAX_SIZE);
}
int get_size(deque *d) {
    return (d -> rear - d -> front + MAX_SIZE) % MAX_SIZE;
}

int get_front(deque *d) {
    if (is_empty(d)) return -1;
    return d -> data[(d -> front + 1) % MAX_SIZE];
}
int get_back(deque *d) {
    if (is_empty(d)) return -1;
    return d -> data[d -> rear];
}

void push_front(deque *d, int X) {
    if (is_full(d)) return;
    d -> data[d -> front] = X;
    d -> front = (d -> front - 1 + MAX_SIZE) % MAX_SIZE;
}
void push_back(deque *d, int X) {
    if (is_full(d)) return;
    d -> rear = (d -> rear + 1) % MAX_SIZE;
    d -> data[d -> rear] = X;
}

int pop_front(deque *d) {
    if (is_empty(d)) return -1;
    d -> front = (d -> front + 1) % MAX_SIZE;
    int X = d -> data[d -> front];
    return X;
}
int pop_back(deque *d) {
    if (is_empty(d)) return -1;
    int X = d -> data[d -> rear];
    d -> rear = (d -> rear - 1 + MAX_SIZE) % MAX_SIZE;
    return X;
}

int main() {
    int N;
    scanf("%d", &N);

    deque *d = init_deque();

    for (int i = 0; i < N; i++) {
        char str[20];
        scanf("%s", str);

        if (strcmp(str, "push_front") == 0) {
            int X;
            scanf("%d", &X);
            push_front(d, X);
        } 

        else if (strcmp(str, "push_back") == 0) {
            int X;
            scanf("%d", &X);
            push_back(d, X);
        } 

        else if (strcmp(str, "front") == 0) {
            printf("%d\n", get_front(d));
        } 

        else if (strcmp(str, "back") == 0) {
            printf("%d\n", get_back(d));
        } 

        else if (strcmp(str, "size") == 0) {
            printf("%d\n", get_size(d));
        }

        else if (strcmp(str, "empty") == 0) {
            printf("%d\n", is_empty(d));
        }

        else if (strcmp(str, "pop_front") == 0) {
            printf("%d\n", pop_front(d));
        }

        else if (strcmp(str, "pop_back") == 0) {
            printf("%d\n", pop_back(d));
        }
    }

}