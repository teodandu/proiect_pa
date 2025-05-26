#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tree.h"
#include "game_of_life.h"
typedef struct{
    int V,E;
    int **a;
}Graph;

Graph* create(ListNode* head, ListNode*** out_nodes){
    int V=0;
    int i,j;
    ListNode* aux=head;
    while(aux!=NULL){
           V++;
     aux=aux->next;
    }
    ListNode** noduri=malloc(V*sizeof(ListNode*));
    aux=head;
    int nr=0;
    while(aux!=NULL){
       noduri[nr++]=aux;
     aux=aux->next;
    }
    Graph *g=(Graph*)malloc(sizeof(Graph));
    g->V=V;
    g->a=(int**)malloc(g->V*sizeof(int*));
    for(i=0; i<g->V; i++)
         g->a[i]=(int*)calloc(g->V,sizeof(int));

    for(i=0; i<g->V; i++)
      for(j=0; j<g->V; j++){
         int delta_x=abs(noduri[i]->i-noduri[j]->i);
         int delta_y=abs(noduri[i]->j-noduri[j]->j);
         if((delta_x==1 && delta_y==0) || (delta_x==0 && delta_y==1)){
                g->a[i][j]=g->a[j][i]=1;
         }
    }
    *out_nodes = noduri;
    return g;
}
void free_graph(Graph* g) {
    for(int i = 0; i < g->V; i++) {
        free(g->a[i]);
    }
    free(g->a);
    free(g);
}

void DFS_scan(Graph *g, int visited[], int group[], int i, int group_index){
    int j;
    visited[i]=1;
    group[i]=group_index;
    for(j=0; j<g->V; j++) 
        if(g->a[i][j]==1 && visited[j]==0)
            DFS_scan(g, visited, group, j, group_index);
}

int DFS(Graph *g, int group[]){
    int i, comp_conexe=0, visited[g->V];
    for(i=0; i<g->V; i++)
        visited[i]=0;
    for(i=0;i<g->V;i++) 
        if(visited[i]==0) {
            DFS_scan(g, visited, group, i, comp_conexe);
            comp_conexe++;
            
        }
    return comp_conexe;
}

void dfs_hamiltonian(Graph* g, int node, int* visited, int* path, int length,int* max_length, int* max_path,int* max_path_length,ListNode** nodes){
    visited[node]= 1;
    path[length]=node;
    int ok=0;
    if(length+1>*max_length) {
        ok=1;
    }else 
     if(length+1==*max_length){
        for(int i=0; i<=length; i++){
        int current_i=nodes[path[i]]->i;
        int current_j=nodes[path[i]]->j;
        int max_i=nodes[max_path[i]]->i;
        int max_j=nodes[max_path[i]]->j;

        if(current_i<max_i||(current_i==max_i&&current_j<max_j)) {
            ok=1;
            break;
        } else if(current_i>max_i||(current_i==max_i&&current_j>max_j)) {
            break;
        }
    }
}


    if(ok) {
        *max_length=length+ 1;
        for(int i=0; i<=length; i++) {
            max_path[i]=path[i];
        }
        *max_path_length=length+1;
    }

    for(int i=0; i<g->V; i++){
        if(g->a[node][i] && !visited[i]){
            dfs_hamiltonian(g, i, visited, path, length+1, max_length, max_path, max_path_length,nodes);
        }
    }
    visited[node] = 0;
}


int best_chain(Graph* g, ListNode** nodes, FILE* fout){
    if(g->V==0) {
        fprintf(fout,"-1\n");
        return -1;
    }

    int* group=malloc(g->V * sizeof(int));
    int n_comp=DFS(g, group);

    int max_length=-1;
    int* final_path=NULL;

    for(int j=0; j<n_comp; j++){
        int nr=0;
        for(int i=0; i<g->V; i++)
            if(group[i]==j)
                nr++;

        if(nr<=1) continue;

        int* index=malloc(nr*sizeof(int));
        int index_pos=0;
        for(int i=0; i<g->V; i++)
            if(group[i]==j)
                index[index_pos++]=i;

        int* visited=calloc(g->V, sizeof(int));
        int* path=malloc(g->V*sizeof(int));
        int* max_path=malloc(g->V*sizeof(int));
        int longest_chain= 0;

       for(int i=0; i<nr; i++){
         for(int j=0; j<g->V; j++){
                visited[j]=0;
              }
        int max_path_length=0;
        dfs_hamiltonian(g, index[i], visited, path, 0, &longest_chain, max_path, &max_path_length, nodes);
    }

        if(longest_chain>max_length) {
            max_length=longest_chain;
        if(final_path) free(final_path);
        final_path=malloc(g->V*sizeof(int));
        for(int i= 0; i<longest_chain; i++)
                final_path[i]=max_path[i];
       
        }else if(longest_chain==max_length) {
          int ok=0;
          for(int i=0; i<longest_chain; i++) {
          int current_row=nodes[max_path[i]]->i;
          int current_col=nodes[max_path[i]]->j;
          int max_row=nodes[final_path[i]]->i;
          int max_col=nodes[final_path[i]]->j;

        if(current_row<max_row|| (current_row==max_row && current_col<max_col)) {
            ok=1;
            break;
        } else if (current_row>max_row || (current_row==max_row && current_col>max_col)) {
            break;
        }
    }
    if(ok){
        for(int i= 0; i<longest_chain; i++)
            final_path[i]=max_path[i];
       }
   }
        free(index);
        free(visited);
        free(path);
        free(max_path);
}

    if(max_length==-1) {
        fprintf(fout, "-1\n");
    } else {
        fprintf(fout, "%d\n", max_length);
        for (int p=0; p<max_length; p++){
            int i=nodes[final_path[p]]->i;
            int j=nodes[final_path[p]]->j;
            fprintf(fout, "(%d,%d)", i, j);
            if(p<max_length-1){
                fprintf(fout," ");
            }else{
                fprintf(fout,"\n");
            }
        }
    }

    free(group);
    free(final_path);
    return max_length;
}

void parcurgere_arbore(TreeNode* root, FILE* fout) {
    if (!root) return;
    ListNode** noduri;
    Graph* g=create(root->coordonate, &noduri);
    best_chain(g, noduri, fout);
    free(noduri);
    free_graph(g);

    parcurgere_arbore(root->left, fout);
    parcurgere_arbore(root->right, fout);
}




int main(int argc, char** argv){
    if(argc!=3){
        printf("Utilizare: %s input.in output.out\n", argv[0]);
        return 1;
    }

    int n, m, k, t;
    char** matr=citire_din_fisier(argv[1], &n, &m, &k, &t);

    TreeNode* root;
    initTree(&root);
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(matr[i][j]=='X')
                add_in_list(&root->coordonate, i, j);

    tree(root, matr, n, m, k, 0);

    FILE* fout = fopen(argv[2], "w");
    if (!fout) {
        perror("Eroare la deschiderea fișierului de ieșire");
        return 1;
    }
    parcurgere_arbore(root, fout);
    fclose(fout);
    eliberare_arbore(root);
    eliberare_memorie(matr, n);
    return 0;
}
