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
int encontraMenorValor(Lista *);

void insereNaFila(Lista *, int);
int removeDaFila(Lista *);
int filaVazia(Lista *);
void mostraFila(Lista *);
int tamanhoFila(Lista *);
int primeiroFila(Lista *);
void removeFila(Lista *);

int main() {

  Lista *filaPrioridade;
  filaPrioridade = alocaMemoriaLista();
  insereNaFila(filaPrioridade, 20);
  insereNaFila(filaPrioridade, 13);
  insereNaFila(filaPrioridade, 4);
  insereNaFila(filaPrioridade, 2);
  insereNaFila(filaPrioridade, 18);
  insereNaFila(filaPrioridade, 40);
  insereNaFila(filaPrioridade, 2);
  insereNaFila(filaPrioridade, 19);
  insereNaFila(filaPrioridade, 1);
  mostraFila(filaPrioridade);
  
  removeFila(filaPrioridade);
  printf("\n");
  mostraFila(filaPrioridade);
  removeFila(filaPrioridade);
  printf("\n");
  mostraFila(filaPrioridade);
  removeFila(filaPrioridade);
  printf("\n");
  mostraFila(filaPrioridade);
  removeFila(filaPrioridade);
  printf("\n");
  mostraFila(filaPrioridade);
  removeFila(filaPrioridade);
  printf("\n");
  mostraFila(filaPrioridade);
  
  
   
  return 0;
}

Nodo *alocaMemoriaNodo() { return (Nodo *)malloc(sizeof(Nodo)); }

Lista *alocaMemoriaLista() { return (Lista *)malloc(sizeof(Lista)); }


void insereNaFila(Lista *lista, int placa) {
  insereElementoNaLista(lista, lista->tail, placa);
}

void removeFila(Lista *fila) {
    int menorValor = encontraMenorValor(fila);
    Nodo *noRemover = buscaElemento(fila, menorValor);
    removeElementoDaLista(fila, noRemover);
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

int encontraMenorValor(Lista *lista) {
  if (lista->size == 0) {
    printf("Lista Vazia!\n");
  }

  Nodo *nodo = lista->head;
  int menorValor = nodo->dado;

  while (nodo != NULL) {
    if (nodo->dado < menorValor) {
      menorValor = nodo->dado;
    }
    nodo = nodo->next;
  }

  return menorValor;
}