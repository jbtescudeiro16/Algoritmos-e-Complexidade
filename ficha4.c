#include <stdio.h>
#include <stdlib.h>

#define NV 5

typedef struct aresta {
int dest; int custo;
struct aresta *prox;
} *LAdj, *GrafoL [NV];

typedef int GrafoM [NV][NV];

void fromMat (GrafoM in, GrafoL out){
  LAdj aux;
  for (int i=0; i<NV; i++){
    out[i]=NULL;
    for (int j=NV-1; j>=0; j--){
      if (in[i][j]!=-1){
        aux=malloc(sizeof (struct aresta));
        aux->dest = j;
        aux->custo = in[i][j];
        aux->prox = out[i];
        out[i]=aux;
      }
    }
  }
}

void inverte (GrafoL in, GrafoL out){
  LAdj aux,new; int i;
  for (i=0; i<NV; i++)
    out[i]=NULL;
  for (i=0; i<NV; i++){
    aux=in[i];
    while (aux) {
      new=malloc(sizeof (struct aresta));
      new->dest = i;
      new->custo = aux->custo;
      new->prox = out[aux->dest];
      out[aux->dest]=new;
      aux=aux->prox;
    }
  }
}

int inDegree (GrafoL g){
  int max=0, i;LAdj aux; int v[NV];
  for (i=0; i<NV; v[i++]=0);
  for (i=0; i<NV; i++)
    for (aux=g[i];aux; aux=aux->prox) v[aux->dest]++;
  for (i=0; i<NV; i++)
    if (v[i]>max) max=v[i];
  return max;
}

int colorOK (GrafoL g, int cor[]) {
 LAdj aux; int i,r=1;
 for (i=0; i<NV && r; i++)
  for (aux=g[i];aux &&  r; aux=aux->prox)
     if (cor[i]==cor[aux->dest]) r=0;
 return 0;
}

int existe (int orig, int dest, GrafoL g){
  LAdj aux; int r=0;
  for (aux=g[orig];aux&&!r;aux=aux->prox) if (aux->dest==dest) r=1;
  return r;
}

int homomorfOK (GrafoL g, GrafoL h, int f[]){
  int i,r=1;;LAdj aux;
  for (i=0; i<NV &&r; i++)
    for (aux=g[i];aux&&r; aux=aux->prox)
      if (!existe(f[i],f[aux->dest],h)) r=0;
  return r;
}

int DFRec (GrafoL g, int or,int v[],int p[],int l[]){
  int i; LAdj a;
  i=1;
  v[or]=-1;
  for (a=g[or];a!=NULL;a=a->prox)
    if (!v[a->dest]){
      p[a->dest] = or;
      l[a->dest] = 1+l[or];
      i+=DFRec(g,a->dest,v,p,l);
    }
  v[or]=1;
  return i;
}

int DF (GrafoL g, int or,int v[],int p[],int l[]){
  int i;
  for (i=0; i<NV; i++) {
    v[i]=0;
    p[i] = -1;
    l[i] = -1;
  }
  p[or] = -1; l[or] = 0;
  return DFRec (g,or,v,p,l);
}


int BF (GrafoL g, int or,int v[],int p[],int l[]){
  int i, x; LAdj a;
  int q[NV], front, end;
  for (i=0; i<NV; i++) {
    v[i]=0;
    p[i] = -1;
    l[i] = -1;
  }
  front = end = 0;
  q[end++] = or; //enqueue
  v[or] = 1; p[or]=-1;l[or]=0;
  i=1;
  while (front != end){
    x = q[front++]; //dequeue
    for (a=g[x]; a!=NULL; a=a->prox)
      if (!v[a->dest]){
        i++;
        v[a->dest]=1;
        p[a->dest]=x;
        l[a->dest]=1+l[x];
        q[end++]=a->dest; //enqueue
      }
  }
  return i;
}

int removeAresta(int n, LAdj *l){
  int r;
  for (r=1;(*l)&&r;l=&((*l)->prox))
    if ((*l)->dest == n){
      r=0;
      (*l)=(*l)->prox;
    }
  return r;
}

int maisLonga (GrafoL g, int or, int p[]){
  int v[NV],ps[NV], l[NV];
  BF(g,or,v,ps,l); int i,max=0,n=or;
  for (i=0; i<NV; i++) if (l[i]>max) {max=l[i];n=i;}
  if (max>0) p[max-1]=n;
  for (i=max-2; i>=0; i-- ) {p[i]=ps[n]; n=ps[n];}
  return max;
}

int componentes (GrafoL g, int c[]) {
  int i, x,n=0; LAdj a;
  int q[NV],v[NV], front, end;
  for (i=0;i<NV;c[i++]=-1) v[i]=0;
  for (i=0; i<NV; i++){
    front=end=0;
    if (c[i]==-1){
        q[end++] = i;
        v[i]=1;
        while (front != end){
          x = q[front++]; //dequeue
          if (c[x]==-1) c[x]=n;
          for (a=g[x]; a!=NULL; a=a->prox)
            if (!v[a->dest])  {
              v[a->dest]=1;
              q[end++]=a->dest; //enqueue
            }
        }
      n++;
    }
  }
  return n;
}

int ordTop (GrafoL g, int ord[]){
  int i,j;LAdj aux; int v[NV];
  for (i=0; i<NV; v[i++]=0);
  for (i=0; i<NV; i++)
    for (aux=g[i];aux; aux=aux->prox)
      v[aux->dest]++;
  for (i=0; i<NV; i++){
    for (j=0;j<NV; j++)
      if (v[j]==0){
        v[j]=-1;
        ord[i]=j;
        for (aux=g[j];aux;aux=aux->prox) v[aux->dest]--;
        break;
      }
    if (j==NV) return 1;
  }
  return 0;
}


void printfGrafoM (GrafoM g){
  printf("GRAFOM\n");
  for (int i=0; i<NV; i++){
    for (int j=0; j<NV; j++)
      printf("%d ",g[i][j]);
    putchar('\n');
  }
  printf("\n\n\n");
}

void printfGrafoL (GrafoL g){
  LAdj aux;
  printf("GRAFOL\n");
  for (int i=0; i<NV; i++){
    printf("NODO %d ->", i);aux=g[i];
    while (aux) {
      printf(" %d(%d)", aux->dest, aux->custo);
      aux=aux->prox;
    }
    putchar('\n');
  }
  printf("\n\n\n");
}

int main (){
  GrafoM g1 = {{-1,-1,3,-1,-1},{-1,-1,-1,-1,-1},{1,2,-1,-1,5},{1,-1,4,-1,-1},{1,0,5,-1,-1}};
  GrafoM g4 = {{-1,-1,-1,-1,-1},{1,-1,-1,1,-1},{-1,1,-1,-1,-1},{-1,-1,-1,-1,-1},{1,-1,1,-1,-1}};
  printfGrafoM(g1);
  GrafoL g2,g3,g5;
  fromMat(g1,g2);
  fromMat(g4,g5);
  printfGrafoL(g2);
  inverte(g2,g3);
  printfGrafoL(g3);
  printfGrafoL(g5);
  int v[NV];
  printf("GRAU: %d\n",inDegree(g3) );
  int vertice=4, x = maisLonga(g2,vertice,v);
  printf("MAIS LONGA: %d\n%d",x, vertice );
  for (int i=0; i<x; i++) printf(" -> %d", v[i]);
  putchar('\n');
  x= componentes(g2,v);
  printf("COMPONENTES(%d):\n", x);
  for (int i=0; i<NV; i++) printf("v[%d]:%d\n", i,v[i]);
  x= ordTop(g5,v);
  printf("ORDENA(%d):\n", x);
  for (int i=0; i<NV; i++) printf("v[%d]:%d\n", i,v[i]);
}
