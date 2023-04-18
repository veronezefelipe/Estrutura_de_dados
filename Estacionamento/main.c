#include <stdio.h>
#include <stdlib.h>

typedef struct sNodo {
  int dado;
  struct sNodo *next;
  struct sNodo *prev;
} Nodo;

typedef struct sLista {
  struct sNodo *head;
  struct sNodo *tail;
  int size;
} Lista;


Nodo *alocaMemoriaNodo();
Lista *alocaMemoriaLista();
Nodo *criaNodo(int);
Lista *criaLista();
int insereElementoNaLista(Lista *, Nodo *, int);
void percorreListaHeadTail(Lista *);
int removeElementoDaLista(Lista *, Nodo *);
Nodo *buscaElemento(Lista *, int);

void insereNaFila(Lista *, int);
int removeDaFila(Lista *);
int filaVazia(Lista *);
void mostraFila(Lista *);
int tamanhoFila(Lista *);
int primeiroFila(Lista *);


void insereEstacionamento(Lista *, Lista *, int);
void removeEstacionamento(Lista *, Lista *);
void rotacionaEstacionamento(Lista *, Lista *, int);

int main() {

  Lista *estacionamentoPrin;
  estacionamentoPrin = alocaMemoriaLista();

  Lista *estacionamentoEspera;
  estacionamentoEspera = alocaMemoriaLista();
  
    int esc;
    int plc;
    printf("Bem vindo ao estacionamento do Vero, digite qual operacao deseja fazer! \n");
    printf("1 = Inserir veiculo \n");
    printf("2 = Remover veiculo \n");
    printf("3 = Ver o estacionamento principal \n");
    printf("4 = Ver a fila de espera \n");
    printf("5 = Rotacionar o estacionamento \n");
    printf("0 = Sair \n");
    
    do{
        scanf("%d", &esc);
        
        switch(esc){
            case 1 : 
                printf("Informe a placa do veiculo \n");
                scanf("%d", &plc);
                insereEstacionamento(estacionamentoPrin, estacionamentoEspera, plc);
                break;
            case 2 :
                removeEstacionamento(estacionamentoPrin, estacionamentoEspera);
                printf("Veiculo removido!");
                break;
            case 3 :
                printf("Inicio: ");
                mostraFila(estacionamentoPrin);
                printf(" Fim!\n");
                break;
            case 4 :
                mostraFila(estacionamentoEspera);
                break;
            case 5 :
                printf("Informe a placa do veiculo a ser removido \n");
                scanf("%d", &plc);
                rotacionaEstacionamento(estacionamentoPrin, estacionamentoEspera, plc);
                break;
            default :
                if (esc > 5){
                    printf("Escolha uma opcao valida!");
                } else{
                    if (esc == 0){
                        printf("Encerrando...");
                    }
                }
        }
    } while(esc !=0);
    
        
    
    
    
  /*insereEstacionamento(estacionamentoPrin, estacionamentoEspera, 1);
  insereEstacionamento(estacionamentoPrin, estacionamentoEspera, 2);
  insereEstacionamento(estacionamentoPrin, estacionamentoEspera, 3);
  insereEstacionamento(estacionamentoPrin, estacionamentoEspera, 4);
  insereEstacionamento(estacionamentoPrin, estacionamentoEspera, 5);
  insereEstacionamento(estacionamentoPrin, estacionamentoEspera, 6);
  insereEstacionamento(estacionamentoPrin, estacionamentoEspera, 7);
  insereEstacionamento(estacionamentoPrin, estacionamentoEspera, 8);
  insereEstacionamento(estacionamentoPrin, estacionamentoEspera, 9);
  insereEstacionamento(estacionamentoPrin, estacionamentoEspera, 10);
  insereEstacionamento(estacionamentoPrin, estacionamentoEspera, 11);
  insereEstacionamento(estacionamentoPrin, estacionamentoEspera, 12);
  insereEstacionamento(estacionamentoPrin, estacionamentoEspera, 13);

  removeEstacionamento(estacionamentoPrin, estacionamentoEspera);
  mostraFila(estacionamentoPrin);
  mostraFila(estacionamentoEspera);

  rotacionaEstacionamento(estacionamentoPrin, estacionamentoEspera, 5);
  mostraFila(estacionamentoPrin);
  mostraFila(estacionamentoEspera);*/

  return 0;
}

Nodo *alocaMemoriaNodo() { return (Nodo *)malloc(sizeof(Nodo)); }

Lista *alocaMemoriaLista() { return (Lista *)malloc(sizeof(Lista)); }

void insereEstacionamento(Lista *estacionamentoPrin,
                          Lista *estacionamentoEspera, int placa) {
  if (estacionamentoPrin->size < 10) {
    insereNaFila(estacionamentoPrin, placa);
  } else {
    insereNaFila(estacionamentoEspera, placa);
  }
}

void removeEstacionamento(Lista *estacionamentoPrin,
                          Lista *estacionamentoEspera) {
  int placa;
  if ((tamanhoFila(estacionamentoPrin) > 9) &&
      (filaVazia(estacionamentoEspera) != 0)) {
    removeDaFila(estacionamentoPrin);
    placa = removeDaFila(estacionamentoEspera);
    insereNaFila(estacionamentoPrin, placa);
  } else {
    removeDaFila(estacionamentoPrin);
  }
}

void rotacionaEstacionamento(Lista *estacionamentoPrin, Lista *estacionamentoEspera, int placa) {
  int aux = primeiroFila(estacionamentoPrin);
  int auxB;
  int auxC = aux;
  
  if(placa == aux){
    removeEstacionamento(estacionamentoPrin, estacionamentoEspera);
  } else{
    while(placa != auxC){
      auxB = removeDaFila(estacionamentoPrin);
      insereNaFila(estacionamentoPrin, auxB);
      auxC = primeiroFila(estacionamentoPrin);
    }
    removeDaFila(estacionamentoPrin);
    while(auxC != aux){
        auxB = removeDaFila(estacionamentoPrin);
        insereNaFila(estacionamentoPrin, auxB);
        auxC = primeiroFila(estacionamentoPrin);
    }
    auxB = removeDaFila(estacionamentoEspera);
    insereNaFila(estacionamentoPrin, auxB);
  }
   
}

void insereNaFila(Lista *lista, int placa) {
  insereElementoNaLista(lista, lista->tail, placa);
}

int removeDaFila(Lista *lista) {
  return removeElementoDaLista(lista, lista->head);
}

int filaVazia(Lista *lista) {
  if (lista->size == 0)
    return 0;
  else
    return 1;
}

int primeiroFila(Lista *lista) {
  Nodo *nodo = lista->head;
  int placa;
  placa = lista->head->dado;
  return placa;
}

void mostraFila(Lista *lista) { percorreListaHeadTail(lista); }

int tamanhoFila(Lista *lista) { return lista->size; }

Nodo *criaNodo(int dado) {
  Nodo *nodo = alocaMemoriaNodo();
  if (nodo != NULL) {
    nodo->dado = dado;
    nodo->next = NULL;
  }
  return nodo;
}

Lista *criaLista() {
  Lista *lista = alocaMemoriaLista();
  if (lista != NULL) {
    lista->head = NULL;
    lista->tail = NULL;
    lista->size = 0;
  }
  return lista;
}

int insereElementoNaLista(Lista *lista, Nodo *pivo, int dado) {
  Nodo *novo = criaNodo(dado);
  if (novo == NULL) {
    return -1; // n possivel alocar memoria
  }

  if ((pivo == NULL) && (lista->size != 0)) {
    printf("só aceita pivo NULL na inserção do primeiro elemento\n");
  }

  if (lista->size == 0) {
    lista->head = novo;
    lista->tail = novo;
  } else {
    novo->next = pivo->next;
    novo->prev = pivo;
    if (pivo->next == NULL) {
      lista->tail = novo;
    } else {
      pivo->next->prev = novo;
    }
    pivo->next = novo;
  }

  lista->size++;
  return lista->size;
}

void percorreListaHeadTail(Lista *lista) {
  Nodo *nodo = lista->head;

  if (nodo == NULL)
    printf("Lista Vazia!\n");
  while (nodo != NULL) {
    printf("%i == ", nodo->dado);
    nodo = nodo->next;
  }
}

int removeElementoDaLista(Lista *lista, Nodo *nodoRemover) {
  Nodo *antigo;
  int dado;
  if ((nodoRemover != NULL) && (lista->size != 0)) {
    if (nodoRemover == lista->head) {
      antigo = lista->head;
      lista->head = nodoRemover->next;
      if (lista->head == NULL) {
        antigo = lista->tail;
        lista->tail = NULL;
      } else {
        antigo = nodoRemover->next->prev;
        nodoRemover->next->prev = NULL;
      }
    } else {
      nodoRemover->prev->next = nodoRemover->next;
      if (nodoRemover->next == NULL) {
        antigo = lista->tail;
        lista->tail = nodoRemover->prev;
      } else {
        antigo = nodoRemover->next->prev;
        nodoRemover->next->prev = nodoRemover->prev;
      }
    }
    dado = antigo->dado;
    free(nodoRemover);
    lista->size--;
  }
  return dado;
}

Nodo *buscaElemento(Lista *lista, int n) {
  Nodo *nodo = lista->head;

  if (nodo == NULL)
    return NULL;
  while (nodo != NULL) {
    if (nodo->dado == n) {
      return nodo;
    }

    nodo = nodo->next;
  }
  return NULL;
}