#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    char * line;
    char * key;
    struct Node * right;
    struct Node * left;
} Node;

int plus_memory (char ** line, int  * count, char * some_letter) {
    *count += strlen(some_letter);
    *line = realloc(*line, *count * sizeof(char));
    
    return 0;
}

Node * Search (char * key, Node * root) {
    int exit = 0;
    Node * elem = root;
        
    while (exit == 0) {
        if (elem && elem->line != NULL) {
            if (strcmp(key, elem->key) == 0) {
                return elem;
            } else if (strcmp(key, elem->key) > 0) {
                elem = elem->right;
            } else {
                elem = elem->left;
            }
        } else
            exit = 1;
    }
        
    return NULL;
}

Node * Search_Parent (char * key, Node * root) {
    if (strcmp(key, root->key) == 0) {
        return NULL;
    } else {
        Node * elem = root;
        
        while (1) {
            if (strcmp(key, elem->key) > 0) {
                if (strcmp(elem->right->key, key) == 0) {
                    return elem;
                } else {
                    elem = elem->right;
                }
            } else {
                if (strcmp(elem->left->key, key) == 0) {
                    return elem;
                } else {
                    elem = elem->left;
                }
            }
        }
    }
}

Node * Delete (char * key, Node * root) {
    Node * parent = Search_Parent(key, root);
    
    if (!parent) {
        printf("\nroot\n");
        
        if (!(root->right) && !(root->left)) {
            free(root->key);
            free(root->line);
            free(root);
            root = NULL;
        } else if (!(root->right) && root->left) {
            free(root->key);
            free(root->line);
            return root->left;
        } else if (!(root->left) && root->right) {
            free(root->key);
            free(root->line);
            return root->right;
        } else {
            Node * border_left_elem = root->right;
            
            while (border_left_elem->left) {
                border_left_elem = border_left_elem->left;
            }
            
            parent = Search_Parent(border_left_elem->key, root);
            
            if (!(border_left_elem->right) && !(border_left_elem->left)) {
                
                if (strcmp(border_left_elem->key, parent->key) > 0) {
                    parent->right = NULL;
                } else {
                    parent->left = NULL;
                }
            } else if (!(border_left_elem->right) && border_left_elem->left) {
                
                if (strcmp(border_left_elem->key, parent->key) > 0) {
                    parent->right = border_left_elem->left;
                } else {
                    parent->left = border_left_elem->left;
                }
            } else if (!(border_left_elem->left) && border_left_elem->right) {
                
                if (strcmp(border_left_elem->key, parent->key) > 0) {
                    parent->right = border_left_elem->right;
                } else {
                    parent->left = border_left_elem->right;
                }
            }
         
            free(root->key);
            root->key = border_left_elem->key;
            free(root->line);
            root->line = border_left_elem->line;
            free(border_left_elem);
        }
        
    } else {
        Node * elem = Search(key, root);
        
        if (!(elem->right) && !(elem->left)) {
            free(elem->key);
            free(elem->line);
            
            if (strcmp(key, parent->key) > 0) {
                free(parent->right);
                parent->right = NULL;
            } else {
                free(parent->left);
                parent->left = NULL;
            }
        } else if (!(elem->right) && elem->left) {
            free(elem->key);
            free(elem->line);
            
            if (strcmp(key, parent->key) > 0) {
                free(parent->right);
                parent->right = elem->left;
            } else {
                free(parent->left);
                parent->left = elem->left;
            }
        } else if (!(elem->left) && elem->right) {
            free(elem->key);
            free(elem->line);
            
            if (strcmp(key, parent->key) > 0) {
                free(parent->right);
                parent->right = elem->right;
            } else {
                free(parent->left);
                parent->left = elem->right;
            }
        } else {
            Node * border_left_elem = elem->right;
            
            while (border_left_elem->left) {
                border_left_elem = border_left_elem->left;
            }
            
            parent = Search_Parent(border_left_elem->key, root);
            
            if (!(border_left_elem->right) && !(border_left_elem->left)) {
                
                if (strcmp(border_left_elem->key, parent->key) > 0) {
                    parent->right = NULL;
                } else {
                    parent->left = NULL;
                }
            } else if (!(border_left_elem->right) && border_left_elem->left) {
                
                if (strcmp(border_left_elem->key, parent->key) > 0) {
                    parent->right = border_left_elem->left;
                } else {
                    parent->left = border_left_elem->left;
                }
            } else if (!(border_left_elem->left) && border_left_elem->right) {
                
                if (strcmp(border_left_elem->key, parent->key) > 0) {
                    parent->right = border_left_elem->right;
                } else {
                    parent->left = border_left_elem->right;
                }
            }
         
            free(elem->key);
            elem->key = border_left_elem->key;
            free(elem->line);
            elem->line = border_left_elem->line;
            free(border_left_elem);
        }
    }
    
    return root;
}

int Add (Node * root) {
    char * line = calloc(1, sizeof(char));
    char * key = calloc(1, sizeof(char));
    
    printf("\n[key] => ");
    Input(key);
    printf("'%s'\n", key);
    
    if (strlen(key) == 0) {
        printf("[-] Error! Can't enter blank key!\n");
        
        free(key);
        free(line);
        
        return 0;
    }
    
    if (!Search(key, root)) {
        Node * new = calloc(1, sizeof * new);
        
        new->key = key;
        printf("[info] => ");
        Input(line);
        new->line = line;
        new->right = NULL;
        new->left = NULL;
        
        if (root->line != NULL) {
            Node * elem = root;
        
            while (1) {
                if (strcmp(key, elem->key) > 0) {
                    if (!elem->right) {
                        elem->right = new;
                        break;
                    } else
                        elem = elem->right;
                } else {
                    if (!elem->left) {
                        elem->left = new;
                        break;
                    } else
                        elem = elem->left;
                }
            }
        } else {
            
            root->key = key;
            root->line = line;
            root->right = NULL;
            root->left = NULL;
            
            free(new);
        }
        
    } else {
        printf("[-] Error! An element with this key already exists!\n");
    }
    
    return 0;
}

int Input (char * line) {
    int sc = 1;
    char buf[11];
    int count = 1;
    
    do {
            sc = scanf("%10[^\n]", buf);
        
            if (sc == -1) break;
            else if (sc == 1) {
                plus_memory(&line, &count, buf);
                strcat(line, buf);
                memset(buf, 0, sizeof(buf) * sizeof(char));
            
            } else {
                scanf("%*c");
                sc = -1;
            }
    
        } while (sc != -1);
    
    return 0;
}

void Show (Node * elem, int level) {
    if (elem) {
        Show(elem->left, level + 1);
        for (int i = 0; i < level; i++)
            printf("   ");
        printf("%s\n", elem->key);
        Show(elem->right, level + 1);
    }
}

void Clean (Node * root) {
    Node * elem;
    
    if (root->key == NULL)
        free(root);
    else {
        while (1) {
            elem = Delete(root->key, root);
            printf("\nqwe\n");
            
            if (elem != root) {
                if (elem == NULL) {
                    printf("\nOK!!!!\n");
                    break;
                    
                } else {
//                                free(root->key);
//                                free(root->line);
                    free(root);
                    root = elem;
                }
            }
        }
    }
}

//void D_Timing(Node * root) {
//    int n = 10;
//    int k;
//    int cnt = 1000000;
//    int i;
//    int m;
//    int key[10000];
//
//
//    char line[2] = "a";
//
//    clock_t first;
//    clock_t last;
//
//    srand(time(NULL));
//
//    while (n-- > 0) {
//        for (i = 0; i < 10000; ++i) {
//            key[i] = rand() % 1000000;
//        }
//
//        for (i = 0; i < cnt; ) {
//            char * s1 = calloc(200, sizeof(char));
//            k = rand() % 1000000;
//            sprintf(s1, "%d", k);
//            if (Add(s1, line)) {
//                ++i;
//            }
//            free(s1);
//        }
//
//        m = 0;
//        first = clock();
//
//        for (i = 0; i < 10000; ++i) {
//            char * s1 = calloc(200, sizeof(char));
//            sprintf(s1,"%d", key[i]);
//            if (find(s1, 1) == 0) {
//                ++m;
//            }
//            free(s1);
//        }
//
//        last = clock();
//        printf("%d items was found\n", m);
//        printf("test #%d, number of nodes = %d, time = %ld\n", 10 - n, cnt, last - first);
//        cnt += 1000000;
//
//        Clean(root);
//        root = calloc(1, sizeof * root);
//        root->key = NULL;
//        root->line = NULL;
//        root->right = NULL;
//        root->left = NULL;
//
//    }
//}

int main () {
    int sc = 1;
    int com = 0;
    char * key;
    Node * elem;
    
    Node * root = calloc(1, sizeof * root);
    
    root->key = NULL;
    root->line = NULL;
    root->right = NULL;
    root->left = NULL;
    
    do {
    
        printf("\n{1} -> Add\t{3} -> Search\n{2} -> Show\t{4} -> Delete\t{5} -> Exit\n\n|=> ");
        sc = scanf("%d", &com);
        scanf("%*c");
        
        if (sc == -1) break;
        else if (sc == 1) {
            switch (com) {
                case 1:
                    Add(root);
                    break;
                case 2:
                    key = calloc(1, sizeof(char));
                    printf("\n[key] => ");
                    Input(key);
                    if (strlen(key) == 0) {
                        free(key);
                        key = root->key;
                        elem = Search(key, root);
                    } else {
                        elem = Search(key, root);
                        free(key);
                    }
                    
                    printf("\n");
                    Show(elem, 1);
                    printf("\n%p / %p\n", root->left, root->right);
                    
                    break;
                case 3:
                    key = calloc(1, sizeof(char));
                    printf("\n[key] => ");
                    Input(key);
                    elem = Search(key, root);
                    if (elem)
                        printf("[line] => %s\n[right] => %p\n[left] => %p\n", elem->line, elem->right, elem->left);
                    else
                        printf("\n[-] Error! Key not found!\n");
                    free(key);
                    break;
                case 4:
                    key = calloc(1, sizeof(char));
                    printf("\n[key] => ");
                    Input(key);
                    
                    if (Search(key, root)) {
                        elem = Delete(key, root);
                        
                        if (elem != root) {
                            if (elem == NULL) {
                                printf("\nOK!!!!\n");
                                
                                root = calloc(1, sizeof * root);
                                root->key = NULL;
                                root->line = NULL;
                                root->right = NULL;
                                root->left = NULL;
                            } else {
                                free(root);
                                root = elem;
                            }
                        }
                        
                    } else {
                        printf("\n[-] Error! Key not found!\n");
                    }
                    
                    free(key);
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
    
    Clean(root);
    
//    root = calloc(1, sizeof * root);
//    root->key = NULL;
//    root->line = NULL;
//    root->right = NULL;
//    root->left = NULL;
//
//    D_Timing(root);
    
    return 0;
}
