#include "../include/iterador.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>

typedef struct nodoIt *PNodoIt;

struct nodoIt {
  nat elem;
  PNodoIt sig;
};

struct repIterador {
  PNodoIt inicio,fin, actual;
  bool bloqueado;
};

TIterador crearIterador () {
  TIterador res = new repIterador;
  res->actual = res->inicio = res->fin = NULL;
  res->bloqueado = false;
  return res;
}

TIterador agregarAIterador(nat elem, TIterador iter) {
  if (iter->bloqueado == false) {
    PNodoIt aux = new nodoIt;
    aux->elem = elem;
    aux->sig = NULL;
    if (iter->inicio == NULL) {
      iter->inicio = iter->fin = aux;
    } else {
      iter->fin->sig = aux;
      iter->fin = aux;
    }
  }
  return iter;
}

TIterador reiniciarIterador(TIterador iter) {
  if (iter->inicio != NULL) {
    iter->actual = iter->inicio;
  }
  iter->bloqueado = true;
  return iter;
}

TIterador avanzarIterador(TIterador iter) {
  if (estaDefinidaActual(iter)) {
    if (iter->actual->sig == NULL) {
      iter->actual = NULL;
    } else {
      iter->actual = iter->actual->sig;
    }
  }
  return iter;
}

nat actualEnIterador(TIterador iter) {
  assert(estaDefinidaActual(iter));
  return iter->actual->elem;
}

bool estaDefinidaActual(TIterador iter) {
  if (iter->actual != NULL) {
    return true;
  } else {
    return false;
  }
}

void liberarIterador(TIterador iter) {
  while (iter->inicio != iter->fin) {
    PNodoIt aux = iter->inicio;
    iter->inicio = iter->inicio->sig;
    delete aux;
  }
  PNodoIt aux = iter->inicio;
  iter->inicio = iter->fin = iter->actual = NULL;
  delete aux;
  delete iter;
}
