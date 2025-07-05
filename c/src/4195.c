#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 30

int get_index(char **friend_name, int f, char *user) {
    for (int i = 0; i < f; i++) {
        if (strcmp(friend_name[i], user) == 0) {
            return i;
        }
    }
    return -1;
}

int find(int *parent, int x) {
    if (parent[x] != x) {
        parent[x] = find(parent, parent[x]);
    }
    return parent[x];
}

int union_set(int *parent, int *size, int x, int y) {
    int a = find(parent, x);
    int b = find(parent, y);
    
    if (a != b) {
        parent[b] = a;
        size[a] += size[b];
    } 
    return size[a];
}

int main() {
    int test_case;
    scanf("%d", &test_case);

    for (int _ = 0; _ < test_case; _++) {
        int f;
        scanf("%d", &f);

        int *result = (int*)calloc(f, sizeof(int));

        int friend_count = 2 * f + 1;
        int *parent = (int*)malloc(friend_count * sizeof(int));
        int *size = (int*)calloc(friend_count, sizeof(int));
        char **friend_name = (char**)malloc(friend_count * sizeof(char*));
        
        for (int i = 0; i < friend_count; i++) {
            parent[i] = i;
            size[i] = 1;
            friend_name[i] = (char*)calloc(MAX_NAME_LEN, sizeof(char));
        }

        int idx = 0;
        for (int i = 0; i < f; i++) {
            char user1[MAX_NAME_LEN];
            char user2[MAX_NAME_LEN];
    
            scanf("%s %s", user1, user2);
            int user1_idx = get_index(friend_name, idx, user1);
            if (user1_idx == -1) {
                user1_idx = idx;
                strcpy(friend_name[idx++], user1);
            } 
            int user2_idx = get_index(friend_name, idx, user2);
            if (user2_idx == -1) {
                user2_idx = idx;
                strcpy(friend_name[idx++], user2);
            }
    
            result[i] = union_set(parent, size, user1_idx, user2_idx);
        }

        for (int i = 0; i < f; i++) {
            printf("%d\n", result[i]);
        }

        for (int i = 0; i < friend_count; i++) {
            free(friend_name[i]);
        }
        free(friend_name);
        free(parent);
        free(size);
        free(result);
    }
}