#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char ch;
    struct node* left;
    struct node* right;
}node;

void create(node **cursor, node **head, node **tail, char ch) {
    node *new_node = (node*)malloc(sizeof(node));
    new_node -> ch = ch;

    if (*head == NULL) {
        new_node -> left = NULL;
        new_node -> right = NULL;

        *head = new_node;
        *tail = new_node;
    }
    else {
        if (*cursor == NULL) {
            new_node -> left = *tail;
            new_node -> right = NULL;

            (*tail) -> right = new_node;
            *tail = new_node;
        }
        else if (*cursor == *head) {
            new_node -> left = NULL;
            new_node -> right = *head;

            (*head) -> left = new_node;
            *head = new_node;
        }
        else {
            new_node -> left = (*cursor) -> left;
            new_node -> right = *cursor;

            (*cursor) -> left -> right = new_node;
            (*cursor) -> left = new_node; 
        }
    }
}

void move_cursor(node **cursor, node **head, node** tail, char ch) {
    if (*head == NULL) return;
    
    if (ch == '<') {
        if (*cursor == NULL) {
            *cursor = *tail;
            return;
        }
        if ((*cursor) -> left == NULL) return;

        *cursor = (*cursor) -> left;
    }   
    else if (ch == '>') {
        if (*cursor == NULL) return;

        *cursor = (*cursor) -> right;
    }
}

void del(node **cursor, node **head, node **tail) {
    if (*head == NULL || *cursor == *head) return;

    node *to_del;
    if (*cursor == NULL) {
        to_del = *tail;

        if ((*tail) -> left != NULL) {
            (*tail) -> left -> right = NULL;
            *tail = (*tail) -> left;
        }
        else {
            *head = NULL;
            *tail = NULL;
        }
    }
    else {
        to_del = (*cursor) -> left;
        (*cursor) -> left -> left -> right = (*cursor);
        (*cursor) -> left = (*cursor) -> left -> left;
    }
    
    free(to_del);
}

int main() {
    int n;
    scanf("%d\n", &n);

    char str[1000];
    for (int i = 0; i < n; i++) {
        node* head = NULL, *tail = NULL, *cursor = NULL;
    
        scanf("%s", str);
        char ch;
        for (int i = 0; i < strlen(str); i++) {
            ch = str[i];
            if (ch == '<' || ch == '>') {
                move_cursor(&cursor, &head, &tail, ch);
            }
            else if (ch == '-') {
                del(&cursor, &tail, &tail);
            }
            else {
                create(&cursor, &head, &tail, ch);
            }
        }
        //printf("cursor == %c\n", cursor != NULL ? cursor -> ch : '@');
        node *current = head;
        while (current != NULL) {
            printf("%c", current -> ch);
            current = current -> right;
        }
        printf("\n");
    }
}