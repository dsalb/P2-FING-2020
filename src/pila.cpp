#include "../include/pila.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>

struct repPila {
  nat* array;
  nat tope;
  nat max;
};

TPila crearPila(nat tamanio) {
  assert(tamanio > 0);
  TPila res = new repPila;
  res->tope = 0;
  res->array = new nat [tamanio];
  res->max = tamanio;
  return res;
}

TPila apilar(nat num, TPila p) {
  if (!estaLlenaPila(p)) {
    p->array[p->tope] = num;
    p->tope = p->tope + 1;
  }
  return p;
}

TPila desapilar(TPila p) {
  if (!estaVaciaPila(p)) {
    p->tope = p->tope - 1;
  }
  return p;
}

void liberarPila(TPila p) {
  delete[] p->array;
  delete p;
}

bool estaVaciaPila(TPila p) {
  return (p->tope == 0);
}

bool estaLlenaPila(TPila p) {
  return (p->tope == p->max);
}

nat cima(TPila p) {
  assert(!estaVaciaPila(p));
  return p->array[p->tope-1];
}
