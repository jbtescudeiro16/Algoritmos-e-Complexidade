#include <stdio.h>
#include <stdlib.h>

#define NV 5

typedef struct aresta {
int dest; int custo;
struct aresta *prox;
} *LAdj, *GrafoL [NV];

typedef int GrafoM [NV][NV];


void fromMat (GrafoM in, GrafoL out) {
    for (int i =0;i<NV ;i++) 
    {
        for (int j =0 ;j<NV ;j++) 
        {
            if (in[i][j]!=0)
            {
                LAdj aux = malloc (sizeof (struct aresta));
                aux-> dest = j;
                aux ->custo  = in[i][j];
                aux ->prox = out [i];
                out [i] = aux ;
            }
        }
    }
}



void inverte (GrafoL in, GrafoL out) 
{
    LAdj aux,new;
    for (int i =0;i<NV ;i++) 
    {
        aux = in[i];
        while (aux)
        {
            new = malloc(sizeof (struct aresta));
            new->dest = i;
            new->custo = aux->custo;
            new->prox =  out[aux->dest];
            out[aux->dest] = new;
            aux = aux->prox;
        }
    }
}


int inDegree (GrafoL g) 
{
    LAdj aux;
   int arr[NV] ;
   int max =0;
   for (int i =0;i<NV ;i++)
   {
       arr[i]=0;
   }
   for (int j=0;j<NV ; j++) 
   {
       aux = g[j];
       while (aux)
       {
           arr[aux->dest]++;
           aux=aux->prox ;
       }
   }
   for (int i=0;i<NV;i++) {
       if (arr[i] >max) max = arr[i];
   }
   return max ;
}



int colorOK (GrafoL g, int cor[])
{
    int res = 1;
    LAdj aux;
    for (int i=0;i<NV;i++) {
        aux = g[i] ;
        while (aux && res !=0) 
        {
            if (cor[i] == cor[aux->dest]) res =0 ; 
            aux =aux->prox;
        }
    }
    return res;
}
