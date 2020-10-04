#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char * line;
    char * key;
    struct Node * right;
    struct Node * left;
} Node;

Node * root = NULL;

int Plus_Memory (char ** line, int  * count, char * some_letter) {
    *count += strlen(some_letter);
    *line = realloc(*line, *count * sizeof(char));

    return 0;
}

Node * Search (char * key) {
    int exit = 0;
        
    while (exit == 0) {
        if (root) {
            if (strcmp(key, root->key) == 0) {
                exit = 1;
            } else if (strcmp(key, root->key) > 0) {
                root = root->right;
            } else {
                root = root->left;
            }
        } else
            exit = 1;
    }
        
    return root;
}

void Show (){
    printf("%s %s %p %p\n", root->key, root->line, root->right, root->left);
}

char * Input (char * line) {
    int sc = 1;
    char buf[11];
    int count = 1;

    do {
        sc = scanf("%10[^\n]", buf);

        if (sc == -1) break;
        else if (sc == 1) {
            Plus_Memory(&line, &count, buf);
            strcat(line, buf);
            memset(buf, 0, sizeof(buf) * sizeof(char));
        } else {
            scanf("%*c");
            sc = -1;
        }

    } while (sc != -1);
    
    return line;
}

int Add () {
    char * line = calloc(1, sizeof(char));
    char * key = calloc(1, sizeof(char));
    
    printf("[key] => ");
    key = Input(key);
    printf("'%s'\n", key);
    
    if (strlen(key) == 0) {
        printf("[-] Error! Can't enter blank key!\n");
        
        free(key);
        free(line);
        
        return 0;
    }
    
    if (!Search(key)) {
        Node * new = calloc(1, sizeof *new);
        
        new->key = key;
        printf("[info] => ");
        line = Input(line);
        new->line = line;
        new->right = NULL;
        new->left = NULL;
        
        if (root) {
            Node * elem = root;
        
            while (elem) {
                if (strcmp(key, elem->key) > 0) {
                    elem = elem->right;
                } else {
                    elem = elem->left;
                }
            }
            elem = new;
        } else
            root = new;
        
    } else {
        printf("[-] Error! An element with this key already exists!\n");
    }
    
    return 0;
}

int Menu () {
    int command;
    
    printf("=> ");
    scanf("%d", &command);
    
    switch (command) {
        case 1:
            scanf("%*c");
            Add();
//            printf("%s %s\n", root->key, root->line);
            break;
            
        case 2:
            Show();
            break;
            
        case 7:
            return 1;
            
        default:
            printf("[-] Error! Еhe command doesn't exist!\n");
            break;
    }
    
    return 0;
}

int main() {
    int exit = 0;
    
    while (exit == 0)
        exit = Menu();
    
    return 0;
}


/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char * line;
    char * key;
    struct Node * right;
    struct Node * left;
} Node;

int Input (char * line) {
    do {
            sc = scanf("%10[^\n]", buf);
        
            if (sc == -1) break;
            else if (sc == 1) {
                plus_memory(&line, &count, buf);
                strcat(line, buf);
                memset(buf, 0, sizeof(buf) * /sizeof(char));
            
            } else {
                scanf("%*c");
                sc = -1;
            }
    
        } while (sc != -1);
    
    return 0;
}

int main () {
    int sc = 1;
    int command = 0;
    
    do {
    
        printf("{1} -> Add\t{3} -> Synonyms\n{2} -> Delete\t{4} -> Show\t{5} -> Exit\n\n|=> ");
        sc = scanf("%d", &com);
        printf("\n");
        
        if (sc == -1) break;
        else if (sc == 1) {
            switch (com) {
                case 1:
                    add(table);
                    break;
                case 2:
                    delete_elem(table);
                    break;
                case 3:
                    synonyms(table);
                    break;
                case 4:
                    show(table);
                    break;
                case 5:
                    sc = -1;
                    break;
                default:
                    printf("[-] Error! Enter a number {1-5}!\n\n");
            }
        } else {
            scanf("%*c");
        }
        
    } while (sc != -1);
    
    return 0;
}*/
