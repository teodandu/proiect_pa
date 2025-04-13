#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "game_of_life.h"
char **alocare(int n, int m) {
    char **matr = (char **)malloc(n * sizeof(char *));
    if (matr == NULL) {
        printf("Eroare la alocare!\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        matr[i] = (char *)malloc((m + 1) * sizeof(char));
    }
    return matr;
}

char **citire_din_fisier(const char *fisier_input, int *n, int *m, int *k, int *t) {
    FILE *file = fopen(fisier_input, "rt");
    if (file == NULL) {
        puts("Fisierul nu poate fi deschis!");
        exit(1);
    }

    fscanf(file, "%d", t);
    fscanf(file, "%d %d", n, m);
    fscanf(file, "%d", k);
    char **matr = alocare(*n, *m);
    for (int i = 0; i < *n; i++) {
        fscanf(file, "%100s", matr[i]);
    }
    fclose(file);
    return matr;
}

void eliberare_memorie(char **matr, int n) {
    for (int i = 0; i < n; i++) {
        free(matr[i]);
    }
    free(matr);
}

char **copie_matr(char **matr, int n, int m) {
    char **copie_m = alocare(n, m);
    for (int i = 0; i < n; i++) {
        strcpy(copie_m[i], matr[i]);
    }
    return copie_m;
}
 

void prelucrare(char **matr, int n, int m) {
    int i,j;
    char **temp=copie_matr(matr,n,m);
    if(matr[0][0]=='+' && matr[0][1]=='X' && matr[1][0]=='X' && matr[1][1]=='X')
            temp[0][0]='X';

    if(matr[n-1][0]=='+' && matr[n-1][1]=='X' && matr[n-2][0]=='X' && matr[n-2][1]=='X')
            temp[n-1][0]='X';
   
    if(matr[0][m-1]=='+' && matr[0][m-2]=='X' && matr[1][m-1]=='X' && matr[1][m-2]=='X')
          temp[0][m-1]='X';
   
   
    if(matr[n-1][m-1]=='+' && matr[n-1][m-2]=='X' && matr[n-2][m-2]=='X' && matr[n-2][m-1]=='X')
          temp[n-1][m-1]='X';
     

    if((matr[0][0]=='X' && matr[0][1]=='X' && matr[1][0]=='X' && matr[1][1]=='+')||(matr[0][0]=='X' && matr[0][1]=='+' && matr[1][0]=='X' && matr[1][1]=='X')||(matr[0][0]=='X' && matr[0][1]=='X' && matr[1][0]=='+' && matr[1][1]=='X')){
        temp[0][0]='X';
    }else{
        temp[0][0]='+';
    }
    if((matr[n-1][0]=='X' && matr[n-1][1]=='X' && matr[n-2][0]=='X' && matr[n-2][1]=='+')||(matr[n-1][0]=='X' && matr[n-1][1]=='+' && matr[n-2][0]=='X' && matr[n-2][1]=='X')||(matr[n-1][0]=='X' && matr[n-1][1]=='X' && matr[n-2][0]=='+' && matr[n-2][1]=='X')){
       temp[n-1][0]='X';
    }else{
       temp[n-1][0]='+';
    }
    if((matr[0][m-1]=='X' && matr[0][m-2]=='X' && matr[1][m-1]=='X' && matr[1][m-2]=='+')||(matr[0][m-1]=='X' && matr[0][m-2]=='+' && matr[1][m-1]=='X' && matr[1][m-2]=='X')||(matr[0][m-1]=='X' && matr[0][m-2]=='X' && matr[1][m-1]=='+' && matr[1][m-2]=='X')){
      temp[0][m-1]='X';
    }else{
      temp[0][m-1]='+';
    }

    if((matr[n-1][m-1]=='X' && matr[n-1][m-2]=='X' && matr[n-2][m-2]=='X' && matr[n-2][m-1]=='+')||(matr[n-1][m-1]=='X' && matr[n-1][m-2]=='+' && matr[n-2][m-2]=='X' && matr[n-2][m-1]=='X')||(matr[n-1][m-1]=='X' && matr[n-1][m-2]=='X' && matr[n-2][m-2]=='+' && matr[n-2][m-1]=='X')){
      temp[n-1][m-1]='X';
    }else{
      temp[n-1][m-1]='+';
    }
 
   
    if(matr[0][0]=='X' && matr[0][1]=='X' && matr[1][0]=='X' && matr[1][1]=='X'){
       temp[0][0]='X';
    }else{
      temp[0][0]='+';
    }
    if(matr[n-1][0]=='X' && matr[n-1][1]=='X' && matr[n-2][0]=='X' && matr[n-2][1]=='X'){
       temp[n-1][0]='X';
    }else{
       temp[n-1][0]='+';
    }
    if(matr[0][m-1]=='X' && matr[0][m-2]=='X' && matr[1][m-1]=='X' && matr[1][m-2]=='X'){
       temp[0][m-1]='X';
    }else{
       temp[0][m-1]='+';
    }
    if(matr[n-1][m-1]=='X' && matr[n-1][m-2]=='X' && matr[n-2][m-2]=='X' && matr[n-2][m-1]=='X'){
       temp[n-1][m-1]='X';
    }else{
       temp[n-1][m-1]='+';

    }
   
      
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
        if(nr==3 && matr[0][j]=='+')
             temp[0][j]='X';
        if(matr[0][j]=='X' && nr>3)
             temp[0][j]='+';
        if((matr[0][j]=='X' && nr==3)||(matr[0][j]=='X' && nr==2))
             temp[0][j]='X';
        if(matr[0][j]=='X' && nr<2)
             temp[0][j]='+';
        
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
       if(matr[i][m-1]=='+' && nr1==3)
              temp[i][m-1]='X';
       if(matr[i][m-1]=='X' && nr1>3)
              temp[i][m-1]='+';
       if((matr[i][m-1]=='X' && nr1==3)||(matr[i][m-1]=='X' && nr1==2))
              temp[i][m-1]='X';
       if(matr[i][m-1]=='X' && nr1<2)
              temp[i][m-1]='+';
       
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
       
        if(matr[n-1][j]=='+' && nr2==3)
               temp[n-1][j]='X';
        if(matr[n-1][j]=='X' && nr2>3)
               temp[n-1][j]='+';
        if((matr[n-1][j]=='X' && nr2==3)||(matr[n-1][j]=='X' && nr2==2))
               temp[n-1][j]='X';
        if(matr[n-1][j]=='X' && nr2<2)
               temp[n-1][j]='+';
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
       if(matr[i][0]=='+' && nr3==3)
             temp[i][0]='X';
       if(matr[i][0]=='X' && nr3>3)
             temp[i][0]='+';
       if((matr[i][0]=='X' && nr3==3)||(matr[i][0]=='X' && nr3==2))
             temp[i][0]='X';
       if(matr[i][0]=='X' && nr3<2)
             temp[i][0]='+';
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
           if(nr4<2 && matr[i][j]=='X')
                  temp[i][j]='+';
           if(nr4==2 && matr[i][j]=='X')
                  temp[i][j]='X';
           if(nr4==3 && matr[i][j]=='X')
                  temp[i][j]='X';
           if(nr4>3 && matr[i][j]=='X')
                  temp[i][j]='+';        
           if(nr4==3 && matr[i][j]=='+')
                  temp[i][j]='X';
   }
for(i=0;i<n;i++){
       for(j=0;j<m;j++){
     matr[i][j]=temp[i][j];
}
}
    eliberare_memorie(temp, n);
}