//Everton da Silva Coelho  101937
//Gabriel Borin Takahashi 101953
//Pedro Manhez Naresi 105615

//backtrace: pegar end da pilha do processo
// ou phread_self

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <dlfcn.h>

#define MaxNumVertices  100
#define MaxNumArestas   4500
#define FALSE           0
#define TRUE            1

#define MAX 100;


typedef int TVertice;

typedef int TAresta;

typedef struct{
    int vert;
    struct TCelula *proximo;
}TCelula;

typedef struct{
    int tamanho;
    TCelula *primeiro;
    TCelula *ultimo;
}TLista;

typedef struct{
    TVertice vertice;
    TAresta aresta;
}TAdjacencia;

typedef struct{
    TLista *Adj[100];
    int NVertices;
    int NArestas;
}TGrafo;

TLista *tlista_inicia(){
    TLista *pLista = (TLista*)malloc(sizeof(TLista));
    pLista->primeiro=NULL;
    pLista->ultimo=NULL;
    pLista->tamanho=0;
    return pLista;
}

void lista_inicia(TGrafo *pgrafo, int nvertices){
    int i;
    for(i=0;i<nvertices;i++){
        pgrafo->Adj[i]=tlista_inicia();
    }
}

void lista_insere(TGrafo *pgrafo, int u, int v){
    TCelula *nova = (TCelula*)malloc(sizeof(TCelula));
    nova->vert=v;
    nova->proximo=NULL;
    if(pgrafo->Adj[u-1]->tamanho == 0)
    {
        pgrafo->Adj[u-1]->primeiro=nova;
        pgrafo->Adj[u-1]->ultimo=nova;
    }
    else
    {
        pgrafo->Adj[u-1]->ultimo->proximo=nova;
        pgrafo->Adj[u-1]->ultimo=nova;
    }
    pgrafo->Adj[u-1]->tamanho++;

}
void tgrafo_inicia(TGrafo *pgrafo, int NVertices){
    int i;

    pgrafo->NVertices=NVertices;
    pgrafo->NArestas=0;

    for(i=0;i<pgrafo->NVertices;i++){
        pgrafo->Adj[i]=tlista_inicia();
    }

}

int tgrafo_inserearesta(TGrafo *pgrafo, int u, int v){
    lista_insere(pgrafo, u, v);
    pgrafo->NArestas++;
    return 0;
}
/*
// do a depth first search
void do_dfs(Vertex *vertex, int* count) {
    Node* p = vertex->list;
    vertex->mark = ++(*count);
    visit (vertex);
    while (p != 0) {
        if (!p->vertex->mark) {
            do_dfs (p->vertex, count);
        }
        p = p->next;
    }
}
void dfs(Vertex *graph[]) {
    int i;
    int count = 0;
    // set all to unvisited
    for (i = 0; i < NUM_VERTEX; i ++) {
        graph[i]->mark = 0;
    }
    // each vertex dfs it
    for (i = 0; i < NUM_VERTEX; i ++) {
        if (graph[i]->mark == 0) {
            do_dfs (graph[i], &count);
        }
    }
}*/

long vertices[MaxNumVertices];
int quantidade_de_vertices = 0;

int converteVertice(long valor_do_vertice){
    int i;
    for(i = 0; i < quantidade_de_vertices; i++){
        if(vertices[i] == valor_do_vertice){
            quantidade_de_vertices++;
            return i;
        }
    }
    quantidade_de_vertices++;
    vertices[i] = valor_do_vertice;
    return i;
}

TGrafo grafo;
int aux = 0;

int (*_sem_wait)(sem_t *) = NULL;

int sem_wait(sem_t *sem) {
	int r;
	if (!_sem_wait) {
		_sem_wait = dlsym(RTLD_NEXT, "sem_wait");
		/* Irá apontar para o sem_wait original*/
	}
	if (aux == 0){
		aux = 1;
		tgrafo_inicia(&grafo, MaxNumVertices);
	}
	tgrafo_inserearesta(&grafo, converteVertice((size_t)sem), converteVertice(pthread_self()));
	printf("\t Semaforo %ld na thread %ld\n", (size_t)sem, pthread_self());
	printf("\t Dentro da sem_wait()... faça o que quiser aqui!\n");
	r = _sem_wait(sem);
	return(r);
}
