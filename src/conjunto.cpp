#include "../include/avl.h"
#include "../include/conjunto.h"
#include "../include/iterador.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>

struct repConjunto {
  TAvl conj;
};

TConjunto crearConjunto() {
  TConjunto res = new repConjunto;
  res->conj = NULL;
  return res;
}

TConjunto singleton(nat elem) {
  TConjunto res = crearConjunto();
  res->conj = insertarEnAvl(elem, res->conj);
  return res;
}

TConjunto unionDeConjuntos(TConjunto c1, TConjunto c2) {
  TConjunto res;
  TIterador iter_may;
  TIterador iter_men;

  nat i = 0;
  nat a = cardinalidad(c1);
  nat b = cardinalidad(c2);
  nat* array = new nat [a + b];

  if (a>b) {
    iter_may = iteradorDeConjunto(c1);
    iter_men = iteradorDeConjunto(c2);
  } else {
    iter_men = iteradorDeConjunto(c1);
    iter_may = iteradorDeConjunto(c2);
  }
  iter_may = reiniciarIterador(iter_may);
  iter_men = reiniciarIterador(iter_men);
  while (estaDefinidaActual(iter_may) || estaDefinidaActual(iter_men)) {
    if (estaDefinidaActual(iter_may)) {
      if (estaDefinidaActual(iter_men) && (actualEnIterador(iter_men) < actualEnIterador(iter_may))) {
        array[i] = actualEnIterador(iter_men);
        iter_men = avanzarIterador(iter_men);
      } else if (estaDefinidaActual(iter_men) && (actualEnIterador(iter_men) == actualEnIterador(iter_may))) {
        array[i] = actualEnIterador(iter_men);
        iter_men = avanzarIterador(iter_men);
        iter_may = avanzarIterador(iter_may);
      } else {
        array[i] = actualEnIterador(iter_may);
        iter_may = avanzarIterador(iter_may);
      }
    } else {
      array[i] = actualEnIterador(iter_men);
      iter_men = avanzarIterador(iter_men);
    }
    i = i + 1;
  }
  liberarIterador(iter_may);
  liberarIterador(iter_men);
  res = arregloAConjunto(array, i);
  delete [] array;
  return res;
}

TConjunto diferenciaDeConjuntos(TConjunto c1, TConjunto c2) {
  TConjunto res;

  TIterador iter_c1;
  TIterador iter_c2;

  nat i = 0;
  nat* array = new nat [cardinalidad(c1)];

  iter_c1 = iteradorDeConjunto(c1);
  iter_c2 = iteradorDeConjunto(c2);
  iter_c1 = reiniciarIterador(iter_c1);
  iter_c2 = reiniciarIterador(iter_c2);

  while (estaDefinidaActual(iter_c1)) {
    if (estaDefinidaActual(iter_c2)) {
      if (actualEnIterador(iter_c1) < actualEnIterador(iter_c2)) {
        array[i] = actualEnIterador(iter_c1);
        iter_c1 = avanzarIterador(iter_c1);
        i = i + 1;
      } else if (actualEnIterador(iter_c1) == actualEnIterador(iter_c2)) {
        iter_c1 = avanzarIterador(iter_c1);
        iter_c2 = avanzarIterador(iter_c2);
      } else {
        iter_c2 = avanzarIterador(iter_c2);
      }
    } else {
      array[i] = actualEnIterador(iter_c1);
      iter_c1 = avanzarIterador(iter_c1);
      i = i + 1;
    }
  }
  liberarIterador(iter_c1);
  liberarIterador(iter_c2);
  if (i == 0) {
    res = crearConjunto();
  } else {
    res = arregloAConjunto(array, i);
  }
  delete [] array;
  return res;
}


bool perteneceAConjunto(nat elem, TConjunto c) {
  TAvl res = buscarEnAvl(elem, c->conj);
  return (res != NULL);
}

bool estaVacioConjunto(TConjunto c) {
  return estaVacioAvl(c->conj);
}

nat cardinalidad(TConjunto c) {
  return cantidadEnAvl(c->conj);
}

TConjunto arregloAConjunto(nat *elems, nat n) {
  TConjunto res = crearConjunto();
  res->conj = arregloAAvl(elems, n);
  return res;
}

TIterador iteradorDeConjunto(TConjunto c) {
  TIterador res = enOrdenAvl(c->conj);
  return res;
}

void liberarConjunto(TConjunto c) {
  if (c != NULL) {
    liberarAvl(c->conj);
    delete c;
    c = NULL;
  }
}
