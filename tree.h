#include <stdio.h>
#ifndef ARBORE_H
#define ARBORE_H
typedef int Data;
struct N{
    Data i;
    Data j;
    struct N* next;
};
typedef struct N ListNode;

struct Elem {
    ListNode* coordonate;
    struct Elem* left, *right;
};
typedef struct Elem TreeNode;

void prelucrare_noua(char** matr, int n, int m);
void add_in_list(ListNode** head, Data i, Data j);
void initTree(TreeNode** root);
void compara_generatii(char** copie, char** matr, int n, int m, ListNode** lista);
void eliberare_lista(ListNode* head);
void eliberare_arbore(TreeNode* node);
void schimba(char** matr, ListNode* coord);
void tree(TreeNode* node, char** matr, int n, int m, int k, int level);
#endif