#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_of_life.h"

typedef int Data;
struct Elem {
    Data l;
    Data c;
    struct Elem* next;
};
typedef struct Elem Cell;

struct Element {
    Cell* generatie;
    struct Element* next1;
};
typedef struct Element Node;

void adaugare_in_lista(Cell **head, Data l, Data c) {
    Cell *headcopy = *head;
    Cell* newnode = (Cell*)malloc(sizeof(Cell));
    newnode->l = l;
    newnode->c = c;
    newnode->next = NULL;
    if (*head == NULL || l < ((*head)->l) || (l == (*head)->l && c < (*head)->c)) {
        newnode->next = *head;
        *head = newnode;
        return;
    }
    while (headcopy->next != NULL && (headcopy->next->l < l || (headcopy->next->l == l && headcopy->next->c < c)))
        headcopy = headcopy->next;
    newnode->next = headcopy->next;
    headcopy->next = newnode;
}

void push(Node **top, Cell *generatie) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->generatie = generatie;
    newnode->next1 = *top;
    *top = newnode;
}

void compara_generatii(char **copie, char **matr, int n, int m, Cell **lista) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (copie[i][j] != matr[i][j])
                adaugare_in_lista(lista, i, j);
}

void afisare_lista(Node *top, FILE *file) {
    int nr_gen = 1;
    while (top != NULL) {
        fprintf(file, "%d", nr_gen);  
        Cell *node =top->generatie;
        while (node != NULL) {
            fprintf(file, " %d %d", node->l, node->c);  
            node = node->next;
        }
        fprintf(file, "\n");  
        top =top->next1;
        nr_gen++;
    }
}
Cell* copiaza_lista(Cell* list_node) {
    if (list_node == NULL) 
             return NULL;
    Cell *new_head = NULL, *new_tail = NULL;
    while (list_node != NULL) {
        Cell* new_node = (Cell*)malloc(sizeof(Cell));
        new_node->l = list_node->l;
        new_node->c = list_node->c;
        new_node->next = NULL;

        if (new_head == NULL) {
            new_head = new_node;
            new_tail = new_node;
        } else {
            new_tail->next = new_node;
            new_tail = new_node;
        }
        list_node = list_node->next;
    }
    return new_head;
}

Node* inversare_stiva(Node* top) {
    Node* prev = NULL;
    while (top) {
        Node* next = top->next1;
        top->next1 = prev;
        prev = top;
        top = next;
    }
    return prev;
}

void eliberare_lista(Cell *head) {
    while (head != NULL) {
        Cell *aux = head;
        head = head->next;
        free(aux);
    }
}

void eliberare_stiva(Node *top) {
    while (top != NULL) {
        Node *aux = top;
        top = top->next1;
        eliberare_lista(aux->generatie);
        free(aux);
    }
}


int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Utilizare: %s input.in output.out\n", argv[0]);
        exit(1);
    }

    int n, m, k, t;
    char **matr = citire_din_fisier(argv[1], &n, &m, &k, &t);

    Node *stack = NULL;

    for (int i = 0; i < k; i++) {
        char **copie = copie_matr(matr, n, m);
        prelucrare(matr, n, m);

        Cell *lista = NULL;
        compara_generatii(copie, matr, n, m, &lista);

        Cell *copie_lista = copiaza_lista(lista);
        push(&stack, copie_lista);
        eliberare_lista(lista);  
        eliberare_memorie(copie, n);
    }

    FILE *file = fopen(argv[2], "w");
    if (file == NULL) {
    printf("Eroare la deschiderea fișierului de output %s\n", argv[2]);
    return 1;
}
    stack = inversare_stiva(stack);
    afisare_lista(stack, file);
    fclose(file);

    eliberare_stiva(stack);
    eliberare_memorie(matr, n);

    return 0;
}
