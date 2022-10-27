#include "selecciones.h"

struct Node{
  team vipd;
  struct Node *siguiente;
};
typedef struct Node nodo;

typedef struct{
  nodo *acceso;
  nodo *cursor;
  nodo *cursoraux;
} listateam;

void init_lista_team(listateam *aux){
  (*aux).acceso = NULL;
  (*aux).cursoraux = NULL;
  (*aux).cursor = NULL;
}

void insert_lista_team(listateam *aux, team var){
  nodo *nuevo;
  nuevo = (nodo*)malloc(sizeof(nodo));
  if ((*aux).cursor == (*aux).acceso){
    (*aux).acceso = nuevo;
    (*nuevo).siguiente = (*aux).cursor;
    (*aux).cursor = nuevo;
    (*aux).cursoraux = nuevo;
  }
  else{
    aux->cursoraux->siguiente = nuevo;
    (*nuevo).siguiente = (*aux).cursor;
    (*aux).cursor = nuevo;
  }
  aux->cursor->vipd = var;
}


void suppress_lista_team(listateam *aux){
  if ((*aux).cursor == (*aux).acceso){
    (*aux).acceso = (*aux).acceso->siguiente;
    (*aux).cursor = (*aux).acceso;
    free((*aux).cursoraux);
    ((*aux).cursoraux) = ((*aux).cursor);
  }
  else{
    (*aux).cursoraux->siguiente = (*aux).cursor->siguiente;
    free((*aux).cursor);
    (*aux).cursor = (*aux).cursoraux->siguiente;
  }
}


int isFull_lista(listateam *aux){
  nodo *n = (nodo*)malloc(sizeof(nodo));
  if ( n == NULL){
    return 1;
  }
  else{
    free (n);
    return 0;
  }
}



int isEmpty_lista(listateam aux){
  if (aux.acceso == NULL)
     return 1;
  else
    return 0;
}


void reset_lista(listateam *aux){
  (*aux).cursor = (*aux).acceso;
  (*aux).cursoraux = (*aux).acceso;
}

void forward_lista(listateam *aux){
  (*aux).cursoraux = (*aux).cursor;
  (*aux).cursor = (*aux).cursor->siguiente;
}

team copy_lista(listateam aux){
  return aux.cursor->vipd;
}

int isOos_lista(listateam aux){
  if (aux.cursor == NULL)
    return 1;
  else
    return 0;
}