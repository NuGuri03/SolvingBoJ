#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char ch;
    struct node *previous;
    struct node *next;
}node;

void create_linked_list(node **head, node **tail, char input) {
    node *new_node = (node*)malloc(sizeof(node));
    new_node->ch = input;
    new_node->next = NULL;

    if (*head == NULL) {
        new_node -> previous = NULL;

        *head = new_node;
        *tail = new_node;
    }
    else {
        new_node -> previous = *tail;
        (*tail) -> next = new_node;

        *tail = new_node;
    }
}

void P(node **cursor, node **head, node **tail, char x) {
    node *new_node = (node*)malloc(sizeof(node));
    new_node -> ch = x;

    if ((*cursor) == NULL) {
        new_node -> previous = *tail;
        new_node -> next = NULL;

        (*tail) -> next = new_node;
        (*tail) = new_node;
    }
    else if ((*cursor) -> previous == NULL) {
        new_node -> previous = NULL;
        new_node -> next = *cursor;

        (*cursor) -> previous = new_node;
        (*head) = new_node;
    }
    else {
        new_node -> previous = (*cursor)->previous;
        new_node -> next = *cursor;

        (*cursor) -> previous -> next = new_node;
        (*cursor) -> previous = new_node;
    }
}

void B(node **cursor, node **head, node **tail) {
    if ((*tail) -> previous == NULL || ((*cursor) != NULL && (*cursor)->previous == NULL)) return;

    node *to_del;
    if ((*cursor) == NULL) {
        if (*tail == NULL) {
            return;
        }
        to_del = *tail;
        
        (*tail) = (*tail)->previous;
        (*tail) -> next = NULL;
    }
    else if ((*cursor) -> previous == *head) {
        to_del = *head;
        
        (*cursor) -> previous = NULL;
        (*head) = *cursor;
    }
    else {
        to_del = (*cursor) -> previous;

        (*cursor) -> previous -> previous -> next = (*cursor);
        (*cursor) -> previous = (*cursor) -> previous -> previous;
    }

    free(to_del);
}

void L(node **cursor, node** tail) {
    if (*cursor == NULL) {
        *cursor = *tail;
        return;
    }
    if ((*cursor) -> previous == NULL) return;
    *cursor = (*cursor)->previous;
}

void D(node **cursor) {
    if (*cursor == NULL) return;
    *cursor = (*cursor)->next;
}

void print_list(node *start) {    
    node *current = start;
    while (current != NULL) {
        printf("%c", current->ch);
        current = current->next;
    }
    //printf("\n");
}

int main() {
    char str[100000];
    scanf("%s", str);
    node *head = NULL, *tail = NULL;
    for (int i = 0; i < strlen(str); i++) {
        create_linked_list(&head, &tail, str[i]);
    }

    int m;
    scanf("%d", &m);
    int cnt = 1;
    node *cursor = NULL;
    for (int i = 0; i < m; i++) {
        char op;
        scanf(" %c", &op);
        switch (op) {
            case ('P'):
            char ch;
            scanf(" %c", &ch);
            P(&cursor, &head, &tail, ch);
            break;
            
            case ('L'):
            L(&cursor, &tail);
            break;

            case ('D'):
            D(&cursor);
            break;

            case ('B'):
            B(&cursor, &head, &tail);
            break;
        }
        // printf("%d : ", cnt++);
        // print_list(head);
        // printf(" %c\n", cursor != NULL ? cursor ->ch : '@');
    }
    print_list(head);
    printf("\n");
}