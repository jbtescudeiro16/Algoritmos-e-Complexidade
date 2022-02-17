#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define Max 100
#define Size 20

#define Free 0
#define Used 1
#define Del  2

typedef struct pQueue {
    int valores [Max];
    int tamanho;
} PriorityQueue;

void swap (int v[], int x, int y){
  int  aux = v[x];
  v[x]=v[y];
  v[y]=aux;
}

void bubbleUp (int i, int h[],int N){
  while (i>0 && h[(i-1)/2]>h[i]) {
    swap(h,i,(i-1)/2);
    i=(i-1)/2;
  }
}

void bubbleDown (int i, int h[], int N){
  int aux;
  while ((i<(N+1)/2  && h[i]>h[2*i+1])|| (2*i+2<N &&  h[i]>h[2*i+2])) {
    aux=i;
    if (2*i+2<N && h[2*i+1]>h[2*i+2]) i=2*i+2;
    else i = 2*i+1;
    swap(h,aux,i);
  }
}

void printV (int v[], int N){
    int i;
    for (i=0; i<N; printf("%3d ", v[i++]))
        ;
    putchar('\n');
}

void emptyQ (PriorityQueue *q){
  q->tamanho = 0;
}

int isEmptyQ (PriorityQueue *q){
  return !(q->tamanho);
}

int addQ (int x, PriorityQueue *q){
  if (q->tamanho >= Max-1) return 1;
  else{
    q->valores[q->tamanho] =x;
    bubbleUp(q->tamanho,q->valores,q->tamanho+1);
    (q->tamanho) ++;
    return 0;
  }
}

int removeQ (PriorityQueue *q, int *rem){
  int i=0, N=q->tamanho, *v=q->valores;
  if (!N) return 1;
  else{
    *rem=v[0];
    swap(v,N-1,0);
    q->tamanho --;
    bubbleDown(0,v,N-1);
    return 0;
  }
}

void heapifyTop (int v[], int N){
  int i;
  for (i=0; i<N; i++) bubbleUp(i,v,i+1);
}

void heapifyBottom (int v[], int N){
  int i;
  for (i=(N+1)/2; i>=0; i--) bubbleDown(i,v,N);
}

void ordenaHeap (int h[], int N) {
  int i;
  for (i=N-1; i>0; i--){
    swap(h,0,i);
    bubbleDown(0,h,i);
  }
}



/**************************/

unsigned hash(char *str){
   unsigned hash = 5381;
   int c;

   while ((c = *str++))
      hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

   return hash;
}

typedef struct nodo {
    char *chave; int ocorr;
    struct nodo *prox;
} *Nodo, *THashC [Size];

void initEmptyC (THashC t){
  for (int i=0;i<Size; t[i++]=NULL) ;
}

void addC (char *s, THashC t){
  unsigned int h = hash(s)%Size;
  Nodo aux = t[h],new;
  while (aux && strcmp(s,aux->chave) &&  aux->prox) aux = aux->prox;
  if (!strcmp(s,aux->chave)) (aux->ocorr) ++;
  else {
    new=malloc(sizeof(struct nodo));
    new->chave = s;
    new->ocorr = 1;
    new->prox = NULL;
    if (aux) aux->prox=new;
    else t[h] = new;
  }
}

int lookupC (char *s, THashC t){
  unsigned int h = hash(s)%Size;
  Nodo aux = t[h];
  while (aux && strcmp(s,aux->chave)) aux = aux->prox;
  if (aux) return aux->ocorr;
  else return 0;
}

int removeC (char *s, THashC t){
  unsigned int h = hash(s)%Size;
  Nodo *aux = &t[h],a;
  while ((*aux) && strcmp(s,(*aux)->chave)) aux = &((*aux)->prox);
  if (*aux){
    if ((*aux)->ocorr > 1) (*aux)->ocorr --;
    else {
      a=*aux;
      (*aux) = (*aux)->prox;
      free(a);
    }
    return 0;
  }
  else return 1;
}

/************************/

typedef struct bucket {
    int status; // Free | Used | Del
    char *chave; int ocorr;
} THashO [Size];

int where (char *s, THashO t){
  unsigned int h = hash(s)%Size;
  while (t[h].status && strcmp(s,t[h].chave)) h++;
  return h;
}

void initEmptyO (THashO t){
    for (int i=0;i<Size; t[i++].status=0);
}

void addO (char *s, THashO t){
    int p = where(s,t);
    if (t[p].status) t[p].ocorr ++;
    else {t[p].status = 1;t[p].chave=s; t[p].ocorr = 1;}

}

int lookupO (char *s, THashO t){
    int p = where(s,t);
    if (t[p].status == 1) return t[p].ocorr;
    else return 0;
}

int removeO (char *s, THashO t){
    int p = where(s,t);
    if (t[p].status == 1){
      if (t[p].ocorr==1) t[p].status = 2;
      else t[p].ocorr --;
      return 0;
    }
    else return 1;
}


/************************/

typedef struct bucketRR {
    int probC;
    int status; // Free | Used | Del
    char *chave; int ocorr;
} THashRR [Size];

int where2 (char *s, THashO t, int *c){
  unsigned int h = hash(s)%Size;
  while (t[h].status && strcmp(s,t[h].chave)) {h++;(*c)++;}
  return h;
}

void addO2 (char *s, THashO t){
    int count = 0, p = where2(s,t,&count);
    if (t[p].status) t[p].ocorr ++;
    else {t[p].status = 1;t[p].chave=s; t[p].ocorr = 1;}

}

int main () {
 int v[100] = {10,15,11,16,22,35,20,21,23,34,37,80,43,22,25,24,28,14};
 int aux;
 printV(v,17);
 bubbleUp(17, v, 18);
 printV(v,18);
 v[0] = 32;
 bubbleDown(0,v,18);
 printV(v,18);
 PriorityQueue q;
 emptyQ(&q);
 printf("ISEMPTY:%d\n", isEmptyQ(&q));
 addQ(10, &q);
 addQ(15, &q);
 addQ(14, &q);
 addQ(17, &q);
 addQ(6, &q);
 addQ(12, &q);
 removeQ(&q,&aux);
 printf("REMOVEU:%d\n", aux);
return 0;
}
