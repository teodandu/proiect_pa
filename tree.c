#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tree.h"
#include "game_of_life.h"

void prelucrare_noua(char** matr, int n, int m){
    int i,j;
    char **temp=copie_matr(matr,n,m);
    if((matr[0][0]=='+' && matr[0][1]=='X' && matr[1][0]=='X' && matr[1][1]=='+')||(matr[0][0]=='X' && matr[0][1]=='X' && matr[1][0]=='+' && matr[1][1]=='X')||(matr[0][0]=='X' && matr[0][1]=='+' && matr[1][0]=='X' && matr[1][1]=='X'))
            temp[0][0]='X';

    if((matr[n-1][0]=='+' && matr[n-1][1]=='X' && matr[n-2][0]=='X' && matr[n-2][1]=='+')||(matr[n-1][0]=='X' && matr[n-1][1]=='X' && matr[n-2][0]=='+' && matr[n-2][1]=='X')||(matr[n-1][0]=='X' && matr[n-1][1]=='+' && matr[n-2][0]=='X' && matr[n-2][1]=='X'))
            temp[n-1][0]='X';
   
    if((matr[0][m-1]=='+' && matr[0][m-2]=='X' && matr[1][m-1]=='X' && matr[1][m-2]=='+')||(matr[0][m-1]=='X' && matr[0][m-2]=='X' && matr[1][m-1]=='+' && matr[1][m-2]=='X')||(matr[0][m-1]=='X' && matr[0][m-2]=='+' && matr[1][m-1]=='X' && matr[1][m-2]=='X'))
          temp[0][m-1]='X';
   
   
    if((matr[n-1][m-1]=='+' && matr[n-1][m-2]=='X' && matr[n-2][m-2]=='X' && matr[n-2][m-1]=='+')||(matr[n-1][m-1]=='X' && matr[n-1][m-2]=='X' && matr[n-2][m-2]=='+' && matr[n-2][m-1]=='X')||(matr[n-1][m-1]=='X' && matr[n-1][m-2]=='+' && matr[n-2][m-2]=='X' && matr[n-2][m-1]=='X'))
          temp[n-1][m-1]='X';
    

    for(j=1;j<m-1;j++){
        int nr=0;
        if(matr[0][j-1]=='X')
                  nr++;
        if(matr[0][j+1]=='X')
                  nr++;
        if(matr[1][j]=='X')
                  nr++;
        if(matr[1][j-1]=='X')
                  nr++;
        if(matr[1][j+1]=='X')
                  nr++;
        if(matr[0][j]=='+' && nr==2)
                  temp[0][j]='X';
             
    }
    for(i=1;i<n-1;i++){
        int nr1=0;
        if(matr[i-1][m-1]=='X')
                   nr1++;
        if(matr[i-1][m-2]=='X')
                   nr1++;
        if(matr[i][m-2]=='X')
                   nr1++;
        if(matr[i+1][m-2]=='X')
                   nr1++;
        if(matr[i+1][m-1]=='X')
                   nr1++;
        if(matr[i][m-1]=='+' && nr1==2)
                   temp[i][m-1]='X';
            
    }
        
    for(j=m-2;j>=1;j--){
        int nr2=0;
        if(matr[n-1][j+1]=='X')
                    nr2++;
        if(matr[n-2][j]=='X')
                    nr2++;
        if(matr[n-2][j+1]=='X')
                    nr2++;
        if(matr[n-2][j-1]=='X')
                    nr2++;
        if(matr[n-1][j-1]=='X')
                    nr2++;
        if(matr[n-1][j]=='+' && nr2==2)
                    temp[n-1][j]='X';
    }
     
    for(i=n-2;i>=1;i--){
        int nr3=0;
        if(matr[i+1][0]=='X')
                    nr3++;
        if(matr[i-1][0]=='X')
                    nr3++;
        if(matr[i+1][1]=='X')
                    nr3++;
        if(matr[i-1][1]=='X')
                    nr3++;
        if(matr[i][1]=='X')
                    nr3++;
        if(matr[i][0]=='+' && nr3==2)
                  temp[i][0]='X';
    }
    for(i=1;i<=n-2;i++)
        for(j=1;j<=m-2;j++){
           int nr4=0;
           if(matr[i-1][j-1]=='X')
                  nr4++;
           if(matr[i-1][j]=='X')
                  nr4++;
           if(matr[i-1][j+1]=='X')
                  nr4++;
           if(matr[i][j-1]=='X')
                  nr4++;
           if(matr[i][j+1]=='X')
                  nr4++;
           if(matr[i+1][j-1]=='X')
                  nr4++;
           if(matr[i+1][j]=='X')
                  nr4++;
           if(matr[i+1][j+1]=='X')
                  nr4++;
           if(nr4==2 && matr[i][j]=='+')
                  temp[i][j]='X';
}
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            matr[i][j]=temp[i][j];
       }
    }
    eliberare_memorie(temp, n);
}

void add_in_list(ListNode** head, Data i, Data j){
    ListNode* newnode=(ListNode*)malloc(sizeof(ListNode));
    newnode->i=i;
    newnode->j=j;
    newnode->next=*head;
    *head=newnode;
}

void initTree(TreeNode** root){
    *root=(TreeNode*)malloc(sizeof(TreeNode));
    (*root)->left=(*root)->right=NULL;
    (*root)->coordonate=NULL;
}

void compara_generatii(char** copie, char** matr, int n, int m, ListNode** lista) {
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(copie[i][j]!=matr[i][j])
                add_in_list(lista, i, j);
}



void eliberare_lista(ListNode* head){
    while(head){
        ListNode* aux=head;
        head=head->next;
        free(aux);
    }
}

void eliberare_arbore(TreeNode* node){
    if(node==NULL) return;
    eliberare_arbore(node->left);
    eliberare_arbore(node->right);
    eliberare_lista(node->coordonate);
    free(node);
}
void schimba(char** matr, ListNode* coord){
    int i,j;
    while(coord!= NULL){
        i=coord->i;
        j=coord->j;
        if(matr[i][j]=='X') {
            matr[i][j]='+';
        } else{
            matr[i][j]='X';
        }
        coord=coord->next;
    }
}

void tree(TreeNode* node, char** matr, int n, int m, int k, int level){
    if(level >= k) return;

    char** left_copy=copie_matr(matr, n, m);
    char** right_copy=copie_matr(matr, n, m);

    initTree(&(node->left));
    initTree(&(node->right));

    prelucrare_noua(left_copy, n, m);
    prelucrare(right_copy, n, m);

    compara_generatii(matr, left_copy, n, m, &(node->left->coordonate));
    compara_generatii(matr, right_copy, n, m, &(node->right->coordonate));

    tree(node->left, left_copy, n, m, k, level + 1);
    tree(node->right, right_copy, n, m, k, level + 1);

    eliberare_memorie(left_copy, n);
    eliberare_memorie(right_copy, n);
}
