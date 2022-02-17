#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define Max 100

#define Free 0
#define Used 1
#define Del  2

#define SIZE 1009
typedef struct no {
char matricula[6];
struct no *next;
} No;
typedef No *Tabela[SIZE];

// fazer o 2,3 ,6,7,8,9,19

//EX 1 A-SOMA OS VALORES ASCII DOS NUMEROS
int hash(char matricula[6]) 
{
    int h = 0 ,i=0;
    for (i=0;i<6;i++) 
    {
        
        if (isdigit (matricula[i])) 
        { 
        h+= (matricula[i]);
        }
    }
    return h;
}

 void printarr(char arr [],int N) {
     int i =0;
     for (i=0;i<N;i++){
         printf ("%c \n",arr[i]);
     }
 }


// EX 1b

int insert(Tabela t, char matricula[6]) 
{
    int k = hash (matricula);
     No *aux= t[k], *new;
    while (strcmp(aux->matricula,matricula)!=0 && aux) 
    {
        aux = aux->next ;
    } 
    if (aux) 
    {
        return 0 ;
    }
    else {
        new = malloc (sizeof (struct no));
        strcpy(new->matricula, matricula) ;
        new->next = t[k];
        t[k] = new; 
    }
    return 1  ;

}


//2 
typedef struct no5 {
int info;
int bal;
struct no5 *esq, *dir;
} No5;
typedef No5 *Arvore;


Arvore rr(Arvore arv) {
    if (!arv || !(arv->esq)) return NULL;
else 
    {
    No5 *aux = malloc(sizeof(struct no5));
    aux=arv->esq;
    arv->esq=aux->dir;
    aux->dir = arv ;
    arv = aux; 
    }
return arv;

}

//5

#define TAM5 10
typedef int Heap5[TAM5];
typedef struct nodo5 {
int val;
struct nodo5 *esq, *dir;
} Nodo5, *Tree5;


Nodo5 * help (int Heap5[],int n ,int i) 
{
    Tree5 aux = malloc(sizeof(struct nodo5));
    if (i<n) 
    {
    aux->val =Heap5[i];
    aux->esq = help(Heap5,n , 2*i+1);
    aux->dir =help(Heap5,n , 2*i+2);
    }
    return aux;
}


void insere (int Heap5[],int n) {

    help(Heap5,n ,0);
}




//EX 6

typedef struct s {
char *sin;
struct s *next;
} Sin;

typedef struct p {
char *pal;
Sin *sins;
struct p *next;
} Pal;

#define TAM 200
typedef Pal *Dic[TAM];


int hash(char *pal);


void sinonimos(Dic d,char *pal) 
{
    int k = hash (pal) ; 
    Pal *aux = d[k];
    while ((strcmp (pal,aux->pal) !=0) && aux->next)
    {
        aux=aux->next;
    }
    if (strcmp (pal,aux->pal)==0)
    {
        Sin *auxs = aux->sins ;
        while (auxs->sin && auxs ->next) 
        {
            printf ("%s\n",auxs->sin);
            auxs=auxs ->next;
        }
        if (auxs->sin) printf ("%s\n",auxs->sin);
    }
    else return;
}


typedef int Heap2[TAM];
typedef struct nodo2 {
int val;
struct nodo2 *esq, *dir;
} Nodo2, *Tree;



//5

Tree convert (int *Heap2,int p )
 { 
    int i=0;
    Tree arv= malloc (sizeof (struct nodo2));
    if (TAM>0 && p<TAM) 
    {
    arv->val = Heap2 [p] ;
    arv->esq = convert(Heap2 ,p*2+1) ;
    arv->dir = convert( Heap2 , p*2+2);
    }
    return (arv);
}


//10

typedef struct nodo *ABPInt;
struct nodo {
int valor;
ABPInt esq, dir;
};

int procura (ABPInt a,int l, int u) 
 {
     int result =0;
     if (a) 
    { 
        if (l > u ) return 0 ;
        if (a->valor> l && a->valor < u ) result = 1 ;
        else if (a->valor < l )  result = procura (a->dir , l , u);
        else result = procura (a->esq , l, u);
        return result ;
    }
 }

/*
11 
Melhor caso : o primeiro elemento , ou seja a raiz está no intervalo ;
Pior caso : Não existe nenhum elemento e algum ramo é percorrido até ao fim ;
*/

//12 
#define MaxH 200
typedef struct mHeap {
int tamanho;
int heap [MaxH];
} MinHeap;

int maxMinheap  (MinHeap m)  
{
int i,max =0,size = m.tamanho;
int aux[size];

for (i=0;i<size;i++)
    {
    aux[i] = m.heap[i];
    }
i=(size+1)/2 ;
max = aux[0];

for (i ;i<size ;i++) 
    {
        if (aux[i]>max) max = aux[i];
    }
return max ;
}
//13

typedef struct avlnode {
  int value,balance;
  struct avlnode *esq,*dir;
} *AVL;

int rdir(AVL *tptr) {
    if ((*tptr) && (*tptr)->esq) 
    {
        AVL aux = (*tptr)->esq;
        (*tptr)->esq = aux->dir;
        aux ->dir = (*tptr) ;
        *tptr = aux;
        return 1 ;
    }
    return 0 ;
}

//14 
/*

          40
      /        \
    20          70
   /  \        /
 10   30      50
*/


//15

//a) N 
//b  SOMATORIO DESDE I ATÉ N-1 * O NÚMERO DE ELEMNTOS DA LISTA LIGADA 
// ASSIM SEŔA N²
//c) quando pretendemos aceder aos daados através de uma procura de tempo constante.


//16 

//  [14,1,15,3,9,5,27]


/*
17


                        3
                /            \
               2              7
             /            /        \
            1            5          8
                       /   \         \
                      4     6         9


*/


// 18 
// Fator de carga é a taxa de ocupaçao de uma tabela de hash  ou seja posiçoes ocupadas /posiçoes totasi

typedef struct minheap4 {
int size;
int used;
int *values;
} *MinHeap4;

void swap ( int *h,int a, int b ) {
    int temp = h[a] ;
    h[a] = h[b];
    h[b] = temp ;
}

//19 
int *ordenados (MinHeap4 h) {

    int tam = h->size;
    int *arr ; 
    arr = malloc (sizeof (int) * tam);
    for (int i=0;i<tam;i++)
    {
        arr[i] = h->values[0];
        swap(h->values,0,h->size-1);
        h->size --;
      //  bubbledown(h->values,0,h->size);
    }
    free (h->values);
    free(h);
    return arr;
}

 // 20 

typedef struct entryC {
  char key[10];
  void *info;
  struct entryC *next;
} * EntryChain;

typedef struct hashT {
  int hashsize;
  EntryChain *table;
} *HashTableChain;


float loadFactorC (HashTableChain t) 
{
    int count =0,lf=0;
   EntryChain aux ;
    for (int i=0; i< t->hashsize ; i++) 
    {
       aux = t->table[i];
        while (aux) {
            count ++;
            aux = aux->next;
        }
    }
    lf = (count / t->hashsize);
    return lf;
}


//21
//weird but ok 
/*
 int hasher (int size,char arr[]) 
 {

     int p =0;
     for (int i =0;arr[i]!= '\0' ; i++) 
     {
         p += rank (arr[i]);
     }
     return p %size;
 }
*/

//22

// adicionar 23,30,31,17,33

//23 
/*
Inicial:      [4,10,21,45,13,25,22,60,100,20]
Remoção do 4: [10,13,21,45,20,25,22,60,100]
Remoção do 10:[13,20,21,45,100,25,22,60]
*/

//B) em termos de complexidade é linear para cada ramo , ou seja N+N SERA 2 N  LOGO 0 (N)


//24


#define STATUS_FREE 0
#define STATUS_USED 1
#define STATUS_DELETED 2
typedef struct entryO {
int status;
char *key;
void *info;
} EntryOAdd;


typedef struct hashTab {
int size;
int used;
EntryOAdd *table;
} *HashTableOAddr;



 void doubleTable (HashTableOAddr h) 
 {
    h->size=2*(h->size);
    h->table = realloc(h->table,h->size*(sizeof(struct hashTab)));

 }

 //25
//hash table
/* 

typedef struct entryO {
int status;
int ;
int ocorr;
} EntryOAdd;


typedef struct hashTab {
int size;
EntryOAdd *table;
} *HashTableOAddr;


pode ser isto com uma função de hash que ordene por tamanho

*/

//26
typedef struct minheap26 {
int size;
int used;
int values[];
} *MinHeap26;

int min26 ( int arr[],int i ,int size ) {

int left=0,right=0;
if (i<size) {
    if (arr[i]>arr[i*2+1])return 0;
left = min26(arr,i*2+1,size);
    if (arr[i]>arr[i*2+2])return 0;
right = min26(arr,i*2+2,size);
}
 if (right ==1 && left ==1)return 1;


}

int minHeapOK (MinHeap26 h)
{
    int i=0;
return (min26 (h->values,i,h->used));
}

//27

typedef struct entry2 {
char key[10];
void *info;
struct entry *next;
} *Entry2;

typedef struct hashT27 {
int hashsize;
Entry2 *table;
} *HashTable2;


HashTable2 newTable(int hashsize) {
    HashTable2 a = malloc(sizeof (struct hashT27));
    a->hashsize = hashsize;
    a->table = malloc (hashsize*sizeof(struct entry2));
    for (int i=0;i<hashsize;a->table[i++] = NULL);
    return a;
}


//28

//[10, , ,1,25,38,6]


//29 

#define Bal 0 // Balanceada
#define Esq -1 // Esq mais pesada
#define Dir 1 // Dir mais pesada
typedef struct avlNode2 *AVL2;

struct avlNode2 {
int bal; // Bal/Esq/Dir
int valor;
struct avlNode2 *esq,*dir;
};


int altura(AVL2 a) 
{
    int res=0;
if (!a) return 0;
else {
    if (a->bal == -1) res= 1+altura (a->esq);
    else res= 1+altura (a->dir);
    return res ;
}
} 

//30

typedef struct nodo30{
int valor;
int altura;
struct nodo30 *esq, *dir;
} Node30, *AVL30;

void diminui (AVL30 a)  {
    AVL30 aux = a;
    while (aux) {
        aux->altura --;
        diminui (aux->esq);
        diminui (aux->dir);
    }
}
void aumenta (AVL30 a)  {
    AVL30 aux = a;
    while (aux) {
        a->altura ++;
        aumenta (a->dir);
        aumenta(a->esq);
    }
}

AVL30 rotateLeft (AVL30 a) 
 {
if (!a || !(a->dir) ) return  a;
else {
AVL30 aux = a->dir ;
a->dir = aux ->esq ;
aux->esq = a ;
aux->altura ++ ;
diminui (a->esq) ; 
aumenta (a->dir);
}
}


//31 rever

/*
#define Livre 0
#define Ocupado 1
#define Apagado 2
typedef struct key *Key;
struct celula31 {
Key k;
void *info;
int estado; //Livre/Ocupado/Apagado
} *celula55;


typedef shash {
int tamanho, ocupados, apagados;
struct celula31 *Tabela;
} *THash31;


typedef struct bucket {
int status; // Free | Used | Del
char *chave; int ocorr;
} * THash [Size];


void remApagados (THash h) 
{   int i,k=0;
    struct celula aux = malloc(sizeof (struct celula)*Size);
    for (i=0;i<h->tamanho ;aux[i++]=NULL);

    for (i=0;i<h->tamanho ;i++)
    {
        if ((h->Tabela[i])->estado ==1)  
        {
        p = where ((h->Tabela[i])->chave,aux);
        aux[p]->estado = 1;
        aux[p].chave= (h->Tabela[i])->chave ;
    }
    h->Tabela = aux;
    h->ocupados = h->ocupados-h->apagados;
} 
*/

//32

// estranho pq em ambas as posições , uma está apagada e outra está livre ?? logo retornaria -1 e -1 ;

// 33

int altura2 (AVL2 a) {
 if (!a) return 0;
 if (a->bal ==-1) return (1+altura (a->dir));
 else return (1+altura (a->esq));
}


//34
/*
                    40
                  /    \   
                20      60
               /  \     / \
            10     30  50  70
*/

/*
//35                  Jose1
                    /        \
                  JOAQ         m2
                /     \        / \
              ANT    jose2    m3  pa
              /                   / \
            ANDRE               M1   pedr

*/


//b) 
typedef struct data {
int dados;
} Data;
typedef struct node {
int balance; // -1 left higher,
// 0 balanced,
// 1 right higher
char key[11];
Data info;
struct node *left, *right;
} Node;

typedef Node *Dictionary;


int allCopies(Dictionary dic, char key[11]) 
{
    int count =0;
    if (!dic) return count;
    if (strcmp(dic->key,key) == 0) count = 1 + allCopies (dic->left,key)+ allCopies (dic->right ,key); // se fizer a rotação pode ficar à direita
    if (strcmp(dic->key,key) > 0) count = allCopies (dic->left,key);
    if (strcmp(dic->key,key) < 0) count = allCopies (dic->right,key);
    return count ;

}

//36

typedef struct node44 {
int value;
struct node44 *left, *right;
} Node44, *BTree44;

int heapOK (BTree44 a) 
{
    if (!a)return 0 ;
    int p = a->value,sonL=-1,sonR =-1,esq=0;
    if (a->left) {
        sonL=a->left->value;
        if (p<sonL) heapOK(a->left);
        else return 0;
    }
    if (a->right) {
        sonL=a->right->value;
        if (p<sonR) heapOK(a->right);
        else return 0;
    }
    return 1;
}



//37


typedef struct {
int size;
int used;
int *heap;
} Heap;



void bubbleup (int *h , int fim,int size ) 
{
    int pai =fim-1/2;
    while (h[pai]>h[fim] && pai >0) 
    {
        swap (h,pai,fim);
        fim = pai ;
        pai =fim-1/2;
    }
}


void insertHeap(Heap *h, int x) 
{
if (h->size == h->used)
{
h->size = h->size*2 ;
h->heap = realloc (h->heap, h->size * sizeof(int));
}
else {
    h->heap[h->used] = x ;
    bubbleup (h->heap,h->used,h->size);
    h->used ++;
}
}


//38

//array final [2,13,12,50,20,42]

//40 

#define HSIZE 1000

typedef struct lista {
int valor;
struct lista *prox;
} *HashChain[HSIZE];



typedef struct celula31 {
int estado; // 0 - Livre // 1 - Ocupado // 2 - Removido
int valor;
} HashOpen[HSIZE];

int hash40 (int i ,int k ){
    int j = i%k;

    return j;
}



void insertHopen (HashOpen h2,int i) {
    int k = hash40(i,HSIZE);

    if (h2[k].estado!=0)
    for(k;k<HSIZE && h2[k].estado !=0;k++);
    
    if (h2[k].estado ==0) {
        h2[k].estado = 1;
        h2[k].valor = i;
    }
    else printf ("tabela cheia \n");
}


int fromChain (HashChain h1,HashOpen h2)
{
struct lista *aux ;
int i=0,k;
for (i=0;i<HSIZE;i++) h2[i].estado = 0;
for (i=0;i<HSIZE;i++) 
{
    if (h1[i])
    {
        aux = h1[i];
        while (aux) 
        {
        insertHopen(h2,aux->valor);
        aux=aux->prox;
        }
    }
    
}
return 0;
}

//41  [260,40,80,54,65,_,60,_,_,_,140,_,_]

//42

#define LEFT 1
#define BAL 0
#define RIGHT -1
typedef struct avl42 {
int value;
int bal;
struct avl42 *left, *right;
} *AVL42;

AVL42 maisProfundo (AVL42 a) 
{
 if (!a) return NULL ;
 if (!(a->left) && !(a->right)) return a;
 else {
     AVL42 aux =a;
     if (aux->bal == 0 || aux->bal ==1 ) maisProfundo (aux->left) ; 
     else (maisProfundo (aux->right));
 }    
} 
//42
/*
            20
        /       \
       10        30
        \       /  \
         15    29   40
                      \
                       50

//43   [0,_,16,9,_,_,13,7,_,_,_,_,_,_,_]


//45                  
/* 
                   50
 tamanho =1 .
 inserir o 1 
 hash (1 %1 =0 ) logo 
 [0] ;
 tocup = 100%
 ---------
 tamanho = 2*1+1 = 3
 inserir o 3 
 hash 3 = 3%3 = 0 
 logo ficamos com 

 [0 , 3 , _]
 tocup = 2/3= 0.66 
 ---------- 
 tamanho = 2*3 + 1 = 7 ;
 inserir o 5 
 hash 5 = 5%7 = 5
 logo ficamos com ;

 [ 0 , 3 ,__,__,__,5 ,_]

 tocup = 3/7 = 0.42 
 ---------
inserir o 8 
hash 8 = 8%7 = 1; colisão , logo fica na pos 2 ;
ficamos com ;
[0 , 3 , 8 ,__ ,__,5,__]
tocup = 4/7 ;

---------
size = 2*7+1 = 15 
inserir o 10 ;
hash 10 = 10%15 =10
ficamos com ;
[0 , 3 , 8 ,__ ,__,5,__,__,__,__,10,__,__,__,__]
tocup = 5/15 = 0,3333>0.33
----------
inserir o 15 
hash (15) = 15%15 = 0 , logo fica na posiçao 3 

[0 , 3 , 8 ,15 ,__,5,__,__,__,__,10,__,__,__,__]
tocup = 6/15 = 0.4;
-------------
remover o 5 
hash 5 = 5%size = 5;
ir à posição 5 e libertar o 5 ;
[0 , 3 , 8 ,15 ,__,__,__,__,__,__,10,__,__,__,__]
tocup = 5/15 = 0,3333>0.33 
--------------

reover o 15 ;
hash 15 = 0 ;andar até ecnontrar o 15 ;
[0 , 3 , 8 ,__,__,__,__,__,__,__,10,__,__,__,__]
tocup = 4/15 <33 
size = 2*size /3 = 10


array final :[0 , 3 , 8 ,__,__,__,__,__,__,__]

*/


//46 acho q ta bem 

int hash46 (int i , int size) 
{
int h = i%size ;
return h ;
}

#define LIVRE 0
#define APAGADO 1
#define OCUPADO 2
struct entry {
int value, status;
};
typedef struct thash {
int ocupados, tamanho;
struct entry *tabela;
} *THash;

int remove46 (THash t , int i) 
{
    int h = hash46 (i,t->tamanho) ; 
    while ((t[h].tabela)->value !=i && h<t->tamanho) h= h+1;
    if ((t[h].tabela)->value ==i)
    {
        if ((t[h].tabela)->status ==2) 
        {
            ((t[h].tabela)->status =1) ;
            return 1;
        }
    }
    return 0;
}

//47

typedef struct nodo47 {
int valor;
struct nodo47 *esq, *dir;
} *ABin;


void rotateRight (ABin *a) 
{
    if ((*a) && (*a)->dir){
        ABin aux = (*a)->esq;
        (*a)->esq = aux->dir;
        aux->dir = *a;
        (*a)=aux;
    }
}

//a mais 

#define MAX 100
typedef int GraphM[MAX][MAX];

int DFRec (GraphM g, int or,int n,int v[],int p[],int l[])
 {
    int i, j, a ,cona =0;
i=1;
v[or]=-1;
for (a=g[or][j];j<n&& a!=0;j++)
if (!v[j]){
p[j] = or;
l[j] = 1+l[or];
i+=DFRec(g,j,n,v,p,l);
}
v[or]=1;

for (i=0;i<n;i++) {
    if (v[i]==1) 
        cona++;
}
return cona;
}


int count_reachable (GraphM g, int s, int n) 
{
    int vis[n],pai[n],l[n],i;
    for (i;i<n;i++){
    vis[i]=-1;
    pai[i] = -2 ;
    l[i]=-1;
    }
   return( DFRec(g,s,n,vis,pai,l));  

}


int main () 
{
    int a = strcmp("joao","jose");
    int b= strcmp("joao","joao");
    int c= strcmp ("j" , "a");
    char arr[6] = {'1','9','A','B','4','6'};
    char arr2[6] = {'9','9','A','B','9','9'};
    int k =hash(arr2);
    printf ("o k é : %d",k);
    printf ("o a é : %d\n",a);
    printf ("o c é : %d\n",b);
    printf ("o b é : %d\n ",c);
}