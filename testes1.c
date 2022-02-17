//  TESTES DE ALGORITMOS E COMPLEXIDADE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


//10
typedef struct nodo *ABPInt;

struct nodo {
  int valor;
  ABPInt esq, dir;
};

int procura (ABPInt a, int l, int u){
  int r = 0;
  if (a){
    if (a->valor >l &&  a->valor<u) r=1;
    else if (a->valor < l || a->valor==u) r=procura(a->esq, l, u);
    else r=procura(a->dir, l, u);
  }
  return r;
}

//11
Melhor caso: o primeiro elemento está no intervalo
Pior caso: não existe nenhum elemento

//12

#define MaxH 20
typedef struct mHeap {
  int tamanho;
  int heap [MaxH];
} MinHeap;

int max (MinHeap m){
  heap h=m->heap;
  int i,max=h[0];
  for (i=(m->tamanho+1)/2; i<m->tamanho;i++) if (h[i]>max) max=h[i];
  return max;
}

//13

typedef struct avlnode {
  int value,balance;
  struct avlnode *esq,*dir;
} *AVL;

int rdir(AVL *a){
  int r=-1;
  AVL aux;
  if ((*a)&&(*a)->esq){
    r=0;
    aux = (*a)->esq;
    (*a)->esq=aux->dir;
    aux->dir=(*a);
    (*a)=aux;
  }
  return r;
}

//14

          40
      /        \
    20          70
   /  \        /
 10   30      50


 //15

 a) N
 b) N^2
 c) Quando é necessária procura  (tempo médio constante)

 //16

[14,1,15,3,9,5,27]

//17

                      3
                /            \
               2              7
             /            /        \
            1            5          8
                       /   \         \
                      4     6         9

//18
50%
Melhor caso: 1
Pior caso: N/2

//19

typedef struct minheap {
  int size;
  int used;
  int *values;
} *MinHeap;

int *ordenados (MinHeap h){
  int *ord = malloc (h->used * sizeof(int));
  int i;
  for (i=0; h->used ; i++){
    ord[i]=h->values[0];
    swap(h->values, 0, used-1);
    (h->used) --;
    bubbleDown(h);
  }
  return
   ord;
}

//20

typedef struct entryC {
  char key[10];
  void *info;
  struct entryC *next;
} * EntryChain;

typedef struct hashT {
  int hashsize;
  EntryChain *table;
} *HashTableChain;

float loadFactorC (HashTableChain t){
  int i,r=0;
  for (i=0; i<t->hashsize; i++){
    EntryChain c=t->table[i];
    while (c){
      r++;
      c=c->next;
    }
  }
  return (r/hashsize);
}

//21

//assumindo que são só minusculas
int hash (int size, char *p){
  int hash=0;
  for(i=0;p[i];i++) hash+=i*rank[p[i]-'a'];
  return hash%size;
}

//22
Ex: 30,25,35,40

//23
a)
Inicial:      [4,10,21,45,13,25,22,60,100,20]
Remoção do 4: [10,13,21,45,20,25,22,60,100]
Remoção do 10:[13,20,21,45,100,25,22,60]

b) N

//24
#define STATUS_FREE 0
#define STATUS_USED 1
#define STATUS_DELETED 2

typedef struct entryO {
  int status;
  char *key;
  void *info;
} EntryOAdd;

typedef struct hashT {
  int size;
  int used;
  EntryOAdd *table;
} *HashTableOAddr;

 void doubleTable (HashTableOAddr h){
   EntryOAdd[h->used] aux;int i,j=0,N=h->used;
   for (i=0; i<N; i++) if (h->table[i].status==1) aux[j++]=h->table[i];
   N=j;
   h->size*=2;
   freeTable(h->table);
   h->table=malloc(size*sizeof(EntryOAdd));
   for (i=0; i<N; i++) insert(aux[i],h->table);
 }

 //25
 Tabela de hash e árvore binária

 //26

typedef struct minheap {
  int size;
  int used;
  int values[];
} *MinHeap;

a) [4,6,21,45,10,25,22,60,100,20,13]

int minHeapOKaux (MinHeap h, int i, int min){
  int r=1;
  if (i<h->used)
    if (h->values[i]<min) r=0;
    else r=minHeapOK(h,i*2 +1,h->values[i]) && minHeapOK(h,i*2 +2,h->values[i]);
  return r;
}

int minHeapOK (MinHeap h){
  int r=1;
  if (h->used >1)r=minHeapOKaux(h,1,h->values[0]) && minHeapOKaux(h,1,h->values[1]);
  if (h->used == 1) r= minHeapOKaux(h,1,h->values[0]);
  return r;
}

//27

typedef struct entry {
  char key[10];
  void *info;
  struct entry *next;
} *Entry;

typedef struct hashT {
  int hashsize;
  Entry *table;
} *HashTable;

int hash(int hashsize, int key[]);

HashTable newTable(int hashsize){
  Hashtable h = malloc (sizeof(struct hashT));
  h->hashsize = hashsize;
  h->table = malloc(hashsize* sizeof(struct entry));
  for (int i=0; i<hashsize; i++) h->table[i]=NULL;
  return h;
}

//28
[10, , ,1,25,38,6]

//29

#define Bal 0 // Balanceada
#define Esq -1 // Esq mais pesada
#define Dir 1 // Dir mais pesada

typedef struct avlNode *AVL;

struct avlNode {
  int bal; // Bal/Esq/Dir
  int valor;
  struct avlNode *esq,*dir;
};

int altura (AVL a){
  int h=0;
  if (a)
    if (a->bal == 1) h=2+altura(a->esq);
    else h=1+altura(a->esq);
  return h;
}

//30

typedef struct nodo{
  int valor;
  int altura;
  struct nodo *esq, *dir;
} Node, *AVL;

AVL rotateLeft (AVL a){
  AVL aux=a;
  if (a && a->dir){
    aux=a->dir;
    a->dir=aux->esq;
    aux->esq=a;
    a->altura--; //não é bem assim, tem que se verificar os filhos
    aux->altura ++; //não é bem assim, tem que se verificar os filhos
  }
  return aux;
}


//32
-1 e -1
