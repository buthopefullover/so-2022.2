#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPROCESSES 5      //Numero maximo de processos
#define MAXTIME 5          //tempo maximo que o processo pode ter

//Estrutura do Processo
typedef struct Processo
{
    int pArrivalTime;          //momento que o processo chega na fila
    char status[10];           //status
    int pId;                   //process identification
    int pExecTime;             //tempo de processo
    struct Processo *next;     //proximo processo na fila
}Processo;

struct Processo* insertAtEnd(Processo * last, Processo* newProcess) {
  
  // se a lista esta vazia o processo irá apontar pra ele mesmo
  if (last == NULL) {
    last = newProcess;
    newProcess -> next = last;
    return last;
  }

  // novo processo aponta para a cabeca da lista já que ele agora será o ultimo
  newProcess->next = last->next;

  // o antigo ultimo processo aponta para o novo processo
  last->next = newProcess;

  // faz o novo processo ser o ultimno
  last = newProcess;

  return last;

  
}

void changeHead(struct Processo** last) {
  // faz a cabeca ser o ultimo processo
  *last = (*last)->next;
}

void deleteHead(struct Processo** last) {
  // checa se a lista esta vazia, ou seja não tem nada a ser deletado
  if (*last == NULL) return;

  // checa se a lista tem apenas
  if ((*last)->next == *last) {
    free(*last);
    *last = NULL;
    return;
  }

  struct Processo *d;

  
  d = (*last)->next;
  (*last)->next = d->next;
  free(d);

}



//imprime os dados do processo na tela
void printProcess(Processo *P){
    printf("Processo: %d    Status: %s      Tempo Restante: %d      Tempo Chegada: %d     Proximo: %d\n", P->pId, P->status, P->pExecTime, P->pArrivalTime, P->next->pId);
}

void createProcesses (Processo **P) {
    for (int i=0; i<MAXPROCESSES; i++) {
        Processo *process = (Processo *) malloc(sizeof(Processo));      //alocação do processo
        int rTime = rand() % MAXTIME + 1;                                  //valor aleatorio de 1 até MAXTIME 
        int tempoC = rand() % MAXTIME;                      // DE 0 ATÉ 4 
        process->pArrivalTime = tempoC;                     //TEMPO EM QUE O PROCESSO CHEGA A FILA
        process->pExecTime = rTime;                                            //tempo de execução que o processo precisa
        process->pId = i;
        if (i==0){strcpy(process->status,"Execucao");}
        else strcpy(process->status,"Espera");

        P[i] = process;
        
    }
}

void traverse(struct Processo* last) {
  struct Processo* p;

  if (last == NULL) {
  printf("A lista esta vazia.\n");
  return;
  }

  p = last->next;

  do {
  printf("PID: %d ", p->pId);
  p = p->next;

  } while (p != last->next);

  printf("\n");
}