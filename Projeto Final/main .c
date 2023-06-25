#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 53

typedef struct sNodo {
  struct sNodo *next;
  struct sNodo *prev;
  char dado[30];
} Nodo;

typedef struct sLista {
  struct sNodo *head;
  struct sNodo *tail;
  struct sLista *next;
  struct sLista *prev;
  int chave;
  int size;
} Lista;

typedef struct sTabela {
  struct sLista *head;
  struct sLista *tail;
  int chave;
  int size;
} Tabela;

int funcaoHash(char *dado);
Nodo *alocaMemoriaNodo(char *dado);
Lista *alocaMemoriaLista(int chave);
Tabela *alocaMemoriaTabela();
Nodo *buscarNodo(Lista *lista, char *dado);
int totalNomesLista(Lista *lista, char *dado);
void insereLista(Lista *lista, Nodo *pivo, char *dado);
Lista *buscaLista(Tabela *tabela, int chave);
void removeNodo(Tabela *tabela, char *dado);
void imprimirLista(Lista *lista);
void insereTabela(Tabela *tabela, Lista *pivo, char *dado);
void removeListaDaTabela(Tabela *tabela, Lista *lista);
void imprimirTabela(Tabela *tabela);
int totalNomes(Tabela *tabela);
void insereNome(Tabela *tabela, char *dado);
void insereArquivo(Tabela *tabela);
int pesquisaNome(Tabela *tabela, char *dado);
void swap(Nodo *A, Nodo *B);
Nodo *divideNodo(Lista *lista, Nodo *left, Nodo *pivo);
void quickSort(Lista *lista, Nodo *left, Nodo *right, int i);

int main() {
  Tabela *tabela = alocaMemoriaTabela();
  Lista *lista;
  insereArquivo(tabela);
  int escolha, chave, whi = 0;
  char nome[50];

  do {
    printf("1 = Adicionar nome\n");
    printf("2 = Pesquisar nome\n");
    printf("3 = Remover nome\n");
    printf("4 = Imprime nomes por lista\n");
    printf("5 = Imprimir todos os nomes\n");
    printf("6 = Total de nomes em uma lista\n");
    printf("7 = Total de nomes\n");
    printf("8 = Quick sort dos nomes\n");

    scanf("%d", &escolha);

    switch (escolha) {
    case 1:
      printf("\nInforme o nome: ");
      scanf("%s", nome);

      insereNome(tabela, nome);

      break;
    case 2:
      printf("\nInforme o nome: ");
      scanf("%s", nome);

      int busca = pesquisaNome(tabela, nome);

      if (busca > 0) {
        printf("\n%d encontrado na lista", busca);
      } else {
        printf("\nao encontrado");
      }
      break;

    case 3:
      printf("\nInforme o nome: ");
      scanf("%s", nome);

      removeNodo(tabela, nome);

      break;

    case 4:
      printf("\nLista:");
      scanf("%d", &chave);

      lista = buscaLista(tabela, chave);

      if (lista == NULL) {
        printf("Não existe");
      } else {
        imprimirLista(lista);
      }

      break;

    case 5:
      imprimirTabela(tabela);

      break;

    case 6:
      printf("\nLista: ");
      scanf("%d", &chave);

      lista = buscaLista(tabela, chave);
      if (lista == NULL) {
        printf("Não existe uma lista criada com essa chave");
      } else {
        printf("\nQuantidade de nomes na lista %d: %d\n", chave, lista->size);
      }

      break;

    case 7:
      printf("\nTotal de nomes: %d\n", totalNomes(tabela));

      break;

    case 8:
      lista = tabela->head;
      for (int i = 0; i < tabela->size; i++) {
        lista = buscaLista(tabela, lista->chave);
        quickSort(lista, lista->head, lista->tail, 0);

        lista = lista->next;
      }

      break;
    }
    printf("\n");
  } while (whi == 0);

  free(lista);
  free(tabela);

  return 0;
}

int funcaoHash(char *dado) {
  int i, chave = 0;
  for (i = 0; i < strlen(dado); i++) {
    chave += dado[i] * 7;
  }
  return (chave % M);
}

Nodo *alocaMemoriaNodo(char *dado) {
  Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));

  strcpy(nodo->dado, dado);
  nodo->next = NULL;
  nodo->prev = NULL;

  return nodo;
}

Lista *alocaMemoriaLista(int chave) {
  Lista *lista = (Lista *)malloc(sizeof(Lista));

  lista->next = NULL;
  lista->prev = NULL;
  lista->chave = chave;
  lista->size = 0;

  return lista;
}

Tabela *alocaMemoriaTabela() {
  Tabela *tabela = (Tabela *)malloc(sizeof(Tabela));

  tabela->head = NULL;
  tabela->tail = NULL;
  tabela->size = 0;

  return tabela;
}

void insereArquivo(Tabela *tabela) {
  FILE *file;
  char nome[50];

  file = fopen("nomes.txt", "r");

  while (fgets(nome, 50, file) != NULL) {
    strcpy(nome, strtok(nome, "\n"));
    insereNome(tabela, nome);
  }
}

Nodo *buscarNodo(Lista *lista, char *dado) {
  Nodo *nodo = lista->head;

  while (nodo != NULL) {
    if (strcmp(nodo->dado, dado) == 0) {
      return nodo;
    }

    nodo = nodo->next;
  }

  return NULL;
}

int totalNomesLista(Lista *lista, char *dado) {
  Nodo *nodo = lista->head;
  int cont = 0;

  while (nodo != NULL) {
    if (strcmp(nodo->dado, dado) == 0) {
      cont++;
    }

    nodo = nodo->next;
  }

  return cont;
}

void insereLista(Lista *lista, Nodo *pivo, char *dado) {
  Nodo *adicionaNodo = alocaMemoriaNodo(dado);

  if ((pivo == NULL) && (lista->size != 0)) {
    adicionaNodo->next = lista->head;
    adicionaNodo->next->prev = adicionaNodo;
    lista->head = adicionaNodo;

  } else if (lista->size == 0) {
    lista->head = adicionaNodo;
    lista->tail = adicionaNodo;

  } else {
    adicionaNodo->next = pivo->next;
    adicionaNodo->prev = pivo;

    if (pivo->next == NULL) {
      lista->tail = adicionaNodo;
    } else {
      pivo->next->prev = adicionaNodo;
    }

    pivo->next = adicionaNodo;
  }

  lista->size++;
}

Lista *buscaLista(Tabela *tabela, int chave) {
  Lista *lista = tabela->head;

  while (lista != NULL) {
    if (lista->chave == chave) {
      return lista;
    }

    lista = lista->next;
  }

  return NULL;
}

void removeNodo(Tabela *tabela, char *dado) {
  int chave = funcaoHash(dado);

  Lista *lista = buscaLista(tabela, chave);
  if (lista == NULL) {
    printf("Não possui nodo");

    return;
  }

  Nodo *nodo = buscarNodo(lista, dado);
  if (nodo == NULL) {
    printf("Não possui nodo");

    return;
  }

  if ((lista != NULL) && (nodo != NULL)) {
    if ((nodo != NULL) && (lista->size != 0)) {
      if (nodo == lista->head) {
        lista->head = nodo->next;

        if (lista->head == NULL) {
          lista->tail = NULL;
        } else {
          nodo->next->prev = NULL;
        }
      } else {
        nodo->prev->next = nodo->next;

        if (nodo->next == NULL) {
          lista->tail = nodo->prev;
        } else {
          nodo->next->prev = nodo->prev;
        }
      }

      free(nodo);
      lista->size--;

      if (lista->size == 0) {
        removeListaDaTabela(tabela, lista);
      }
    }
  }
}

void imprimirLista(Lista *lista) {
  if (lista != NULL) {
    Nodo *nodo = lista->head;

    printf("Chave %d \n", lista->chave);
    while (nodo != NULL) {
      printf("%s\n", nodo->dado);
      nodo = nodo->next;
    }

    printf("\n");
  }
}

void imprimirTabela(Tabela *tabela) {
  for (int i = 0; i < M; i++) {
    Lista *lista = buscaLista(tabela, i);

    if (lista != NULL) {
      imprimirLista(lista);
    }
  }
}

int totalNomes(Tabela *tabela) {
  Lista *lista = tabela->head;
  int qtdNomes = 0;

  while (lista != NULL) {
    qtdNomes += lista->size;
    lista = lista->next;
  }

  return qtdNomes;
}

void insereNome(Tabela *tabela, char *dado) {
  int chave = funcaoHash(dado);
  Lista *lista = buscaLista(tabela, chave);
  insereTabela(tabela, lista, dado);
}

int pesquisaNome(Tabela *tabela, char *dado) {
  int chave = funcaoHash(dado);
  Lista *lista = buscaLista(tabela, chave);
  int cont = 0;

  if (lista != NULL) {
    cont = totalNomesLista(lista, dado);
  }

  if (cont > 0) {
    return cont;
  }

  return -1;
}

void insereTabela(Tabela *tabela, Lista *pivo, char *dado) {
  int chave = funcaoHash(dado);

  Lista *lista = buscaLista(tabela, chave);

  if (lista == NULL) {
    lista = alocaMemoriaLista(chave);

    if ((pivo == NULL) && (tabela->size != 0)) {
      lista->next = tabela->head;
      lista->next->prev = lista;
      tabela->head = lista;

    } else if (tabela->size == 0) {
      tabela->head = lista;
      tabela->tail = lista;

    } else {
      lista->next = pivo->next;
      lista->prev = pivo;

      if (pivo->next == NULL) {
        tabela->tail = lista;
      } else {
        pivo->next->prev = lista;
      }

      pivo->next = lista;
    }

    tabela->size++;
  }

  insereLista(lista, lista->tail, dado);
}

void removeListaDaTabela(Tabela *tabela, Lista *lista) {
  if ((lista != NULL) && (tabela->size != 0)) {
    if (lista == tabela->head) {
      tabela->head = lista->next;

      if (tabela->head == NULL) {
        tabela->tail = NULL;
      } else {
        lista->next->prev = NULL;
      }
    } else {
      lista->prev->next = lista->next;

      if (lista->next == NULL) {
        tabela->tail = lista->prev;
      } else {
        lista->next->prev = lista->prev;
      }
    }

    free(lista);
    tabela->size--;
  }
}

void swap(Nodo *A, Nodo *B) {
  char temp[30];
  strcpy(temp, A->dado);
  strcpy(A->dado, B->dado);
  strcpy(B->dado, temp);
}

Nodo *divideNodo(Lista *lista, Nodo *left, Nodo *pivo) {
  Nodo *aux = left->prev;

  for (Nodo *i = left; i != pivo; i = i->next) {
    if (strcmp(i->dado, pivo->dado) < 0) {
      if (aux) {
        aux = aux->next;
      } else {
        aux = left;
      }

      swap(aux, i);
    }
  }

  if (aux) {
    aux = aux->next;
  } else {
    aux = left;
  }

  swap(aux, pivo);

  return aux;
}

void quickSort(Lista *lista, Nodo *left, Nodo *right, int i) {
  if (right != NULL && left != NULL && left != right && left != right->next) {
    Nodo *pivo = divideNodo(lista, left, right);
    quickSort(lista, left, pivo->prev, i + 1);
    quickSort(lista, pivo->next, right, i + 1);
  }
}
