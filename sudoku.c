#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct n{
    void* data;
    struct n* next;
    struct n* prev;
} node;

struct List{
    node* first;
    node* last;
    node* current;
    int size;
};

typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int i, j, k;
  //filas
  for (i = 0; i < 9; i++){
    int index[10] = {0};
    for (j = 0; j < 9; j++){
      int valor = n->sudo[i][j];
      if (valor != 0){
        if (index[valor] == 1) return 0;
        index[valor] = 1;
      }
    }
  }
  //columnas
  for (j = 0; j < 9; j++){
    int index[10] = {0};
    for (i = 0; i < 9; i++){
      int valor = n->sudo[i][j];
      if (valor != 0){
        if (index[valor] == 1) return 0;
        index[valor] = 1;
      }
    }
  }
  // submatrices
  for (i = 0; i < 9; i += 3){
    for (j = 0; j < 9; j += 3){
      int index[10] = {0};
      for (k = 0; k < 9; k++){
        int fila = i + k /3;
        int col = j + k % 3;
        int valor = n->sudo[fila][col];
        if (valor != 0){
          if (index[valor] == 1) return 0;
          index[valor] = 1;
        }
      }
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  int fila = -1, col = -1;
  for (int i = 0; i < 9 && fila == -1; i++){
    for (int j = 0; j < 9;j++){
      if (n->sudo[i][j] == 0){
        fila = i;
        col = j;
        break;
      }
    }
  }
  if (fila == -1) return list;
  for(int valor = 1; valor <= 9; valor++){
    Node* NueNodo = copy(n);
    NueNodo->sudo[fila][col] = valor;
    is_valid(NueNodo) ? pushBack(list, NueNodo): free(NueNodo);
  }
  return list;
}


int is_final(Node* n){
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      if (n->sudo[i][j] == 0) return 0;
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  *cont = 0;
  Stack* stack = createStack();
  push(stack, initial);
  while (!is_empty(stack)){
    (*cont)++;
    Node* aux = (Node*) top(stack);
    pop(stack);

    if (is_final(aux)){
      clean(stack);
      free(stack);
      return aux;
    }

    List* adj = get_adj_nodes(aux);
    node* current = adj->first;

    while (current != NULL){
      push(stack, current->data);
      current = current->next;
    }
    free(adj);
    free(current);
  }
  free(stack);
  return NULL;
}



/*int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/