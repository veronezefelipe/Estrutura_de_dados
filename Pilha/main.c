#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo {
  struct sNodo *next;
  char dado;
} Nodo;

typedef struct sPilha {
  struct sNodo *head;
  struct sNodo *tail;
  int size;
} Pilha;

Pilha *alocaMemoriaPilha();
Nodo *alocaMemoriaNodo();
Pilha *novaPilha();
Nodo *criaNodo(char);
void empilha(Pilha *, char);
char desempilha(Pilha *);
char primeiroPilha(Pilha *);
void comparaChar(Pilha *, char array[]);
void destroiPilha(Pilha *);
int pilhaVazia(Pilha *);

int main() {
  Pilha *pilha = novaPilha();
  char array[50] = "";

  printf("Bem vindo ao empilhamento do Vero informe a expressao:\n");
  scanf(" %[^\n]", array);
  comparaChar(pilha, array);
  destroiPilha(pilha);

  return 0;
}

Pilha *alocaMemoriaPilha() { return (Pilha *)malloc(sizeof(Pilha)); }

Nodo *alocaMemoriaNodo() { return (Nodo *)malloc(sizeof(Nodo)); }

Pilha *novaPilha() {
  Pilha *pilha = alocaMemoriaPilha();
  if (pilha == NULL) {
    printf("Memoria nao alocada");
  }
  pilha->head = NULL;
  pilha->tail = NULL;
  pilha->size = 0;
  return pilha;
}

void empilha(Pilha *pilha, char dado) {
  Nodo *novo = criaNodo(dado);
  novo->next = pilha->head;
  pilha->head = novo;
  pilha->size++;
}

char desempilha(Pilha *pilha) {
  Nodo *remove = pilha->head;
  char dado;
  if (pilha->size == 0) {
    printf("Pilha vazia");
  } else {
    pilha->head = remove->next;
    remove->next = NULL;
  }
  dado = remove->dado;
  free(remove);
  pilha->size--;
  return dado;
}

char primeiroPilha(Pilha *pilha) {
  char primeiro;
  if (pilha->size != 0) {
    primeiro = pilha->head->dado;
    return primeiro;
  } else {
    exit(0);
  }
}

void comparaChar(Pilha *pilha, char array[]) {
  int i;
  char aux;
  for (i = 0; i < 50; i++) {
    if (array[i] == '(') {
      empilha(pilha, '(');
    } else if (array[i] == '[') {
      empilha(pilha, '[');
    } else if (array[i] == '{') {
      empilha(pilha, '{');
    } else if (array[i] == ')') {
      aux = primeiroPilha(pilha);
      if (aux == '(') {
        desempilha(pilha);
      } else {
        printf("Expressao invalida");
        exit(0);
      }
    } else if (array[i] == ']') {
      aux = primeiroPilha(pilha);
      if (aux == '[') {
        desempilha(pilha);
      } else {
        printf("Expressao invalida");
        exit(0);
      }
    } else if (array[i] == '}') {
      aux = primeiroPilha(pilha);
      if (aux == '{') {
        desempilha(pilha);
      } else {
        printf("Expressao invalida");
        exit(0);
      }
    }
  }
  if (pilhaVazia(pilha) == 0) {
    printf("\nExpressao valida!\n");
  } else {
    printf("\nExpressao invalida!\n");
  }
}

Nodo *criaNodo(char dado) {
  Nodo *Nodo = alocaMemoriaNodo();
  Nodo->next = NULL;
  Nodo->dado = dado;
  return Nodo;
}

void destroiPilha(Pilha *pilha) {
  while (pilha->size != 0) {
    desempilha(pilha);
  }
  free(pilha);
}

int pilhaVazia(Pilha *pilha) {
  if (pilha->size == 0) {
    return 0;
  } else {
    return 1;
  }
}