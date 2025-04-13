#include<stdio.h>
#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H
char **citire_din_fisier(const char *fisier_input, int *n, int *m, int *k, int *t);
void eliberare_memorie(char **matr, int n);
char **alocare(int n,int m);
void prelucrare(char **matr, int n, int m);
char **copie_matr(char **matr, int n, int m);
#endif