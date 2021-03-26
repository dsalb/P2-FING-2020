#include "../include/colaAvls.h"
#include "../include/avl.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>

typedef struct nodoavl *TLocAvl;

struct nodoavl {
  TLocAvl sig;
  TLocAvl ant;
  TAvl info;
};

struct repColaAvls {
  TLocAvl inicio;
  TLocAvl final;
};

TColaAvls crearColaAvls() {
  TColaAvls res = new repColaAvls;
  res-> inicio = res->final = NULL;
  return res;
}

TColaAvls encolar(TAvl avl, TColaAvls c) {
  TLocAvl aux = new nodoavl;
  aux->info = avl;
  if (estaVaciaColaAvls(c)) {
    c->inicio = c->final = aux;
    aux->sig = aux->ant = NULL;
  } else {
    c->inicio->ant = aux;
    aux->sig = c->inicio;
    aux->ant = NULL;
    c->inicio = aux;
  }
  return c;
}

TColaAvls desencolar(TColaAvls c) {
  TLocAvl aux = c->final;
  if (!estaVaciaColaAvls(c)) {
    if (c->final == c->inicio) {
      c->final = c->inicio = NULL;
    } else {
      c->final = c->final->ant;
    }
  }
  delete aux;
  return c;
}

void liberarColaAvls(TColaAvls c) {
  TLocAvl a_borrar;
  while (c->inicio != NULL) {
    a_borrar = c->inicio;
    c->inicio = c->inicio->sig;
    delete a_borrar;
  }
  delete c;
}

bool estaVaciaColaAvls(TColaAvls c) {
  return ((c->inicio == NULL) && (c->final == NULL));
}

TAvl frente(TColaAvls c) {
  assert(!estaVaciaColaAvls(c));
  return (c->final->info);
}
