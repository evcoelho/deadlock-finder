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

int (*_sem_wait)(sem_t *) = NULL;

int sem_wait(sem_t *sem) {
	int r;
	if (!_sem_wait) {
		_sem_wait = dlsym(RTLD_NEXT, "sem_wait");
		/* Irá apontar para o sem_wait original*/
	}
	
	int** cmd_matrix = (int**) calloc(max_linha*sizeof(int**), 1);
	
	//cmd_matrix[i] = (int*) calloc(sizeof(token)*sizeof(int*), 1);

	printf("\t Dentro da sem_wait()... faça o que quiser aqui!\n");
	r = _sem_wait(sem);
	return(r);
}