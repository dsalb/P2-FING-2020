#include "../include/colaAvls.h"
#include "../include/pila.h"
#include "../include/avl.h"
#include "../include/iterador.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct repAvl {
  nat elem;
  nat altura;
  nat cant;
  TAvl izq;
  TAvl der;
};

static int maximo (int a, int b) {
  if (a>b) {
    return a;
  } else {
    return b;
  }
}

static TAvl RSI(TAvl avl) {
  TAvl aux = avl->izq;
  aux->cant = avl->cant;
  avl->cant = cantidadEnAvl(avl->der) + cantidadEnAvl(aux->der) + 1;
  avl->izq = aux->der;
  aux->der = avl;
  avl->altura = maximo(alturaDeAvl(avl->izq), alturaDeAvl(avl->der)) + 1;
  aux->altura = maximo(alturaDeAvl(aux->izq), alturaDeAvl(aux->der)) + 1;
  return aux;
}

static TAvl RSD(TAvl avl) {
  TAvl aux = avl->der;
  aux->cant = avl->cant;
  avl->cant = cantidadEnAvl(avl->izq) + cantidadEnAvl(aux->izq) + 1;
  avl->der = aux->izq;
  aux->izq = avl;
  avl->altura = maximo(alturaDeAvl(avl->izq), alturaDeAvl(avl->der)) + 1;
  aux->altura = maximo(alturaDeAvl(aux->izq), alturaDeAvl(aux->der)) + 1;
  return aux;
}

static TAvl RDD(TAvl avl) {
  avl->der = RSI(avl->der);
  avl = RSD(avl);
  return avl;
}

static TAvl RDI(TAvl avl) {
  avl->izq = RSD(avl->izq);
  avl = RSI(avl);
  return avl;
}

static TAvl balanceo(TAvl avl) {
  if ((alturaDeAvl(avl->izq) - alturaDeAvl(avl->der)) == 2) {
    if (alturaDeAvl(avl->izq->izq) >= alturaDeAvl(avl->izq->der)) {
      avl = RSI(avl);
    } else {
      avl = RDI(avl);
    }
  }
  if ((alturaDeAvl(avl->der) - alturaDeAvl(avl->izq)) == 2) {
    if (alturaDeAvl(avl->der->der) >= alturaDeAvl(avl->der->izq)) {
      avl = RSD(avl);
    } else {
      avl = RDD(avl);
    }
  }
  return avl;
}

TAvl crearAvl() {
  return NULL;
}

bool estaVacioAvl(TAvl avl) {
  return (avl == NULL);
}

TAvl insertarEnAvl(nat elem, TAvl avl) {
  if (estaVacioAvl(avl)) {
    avl = new repAvl;
    avl->izq = avl->der = NULL;
    avl->elem = elem;
    avl->altura = 1;
    avl->cant = 1;
  }
  else {
    if (elem < avl->elem) {
      avl->izq = insertarEnAvl(elem, avl->izq);
    } else {
      avl->der = insertarEnAvl(elem, avl->der);
    }
    avl->cant = avl->cant + 1;
    avl = balanceo(avl);
    avl->altura = maximo(alturaDeAvl(avl->izq), alturaDeAvl(avl->der)) + 1;
  }
  return avl;
}

TAvl buscarEnAvl(nat elem, TAvl avl) {
  if (estaVacioAvl(avl) || (avl->elem == elem)) {
    return avl;
  } else if (avl->elem > elem) {
    return buscarEnAvl(elem,avl->izq);
  } else {
    return buscarEnAvl(elem, avl->der);
  }
}

nat raizAvl(TAvl avl) {
  assert(!estaVacioAvl(avl));
  return (avl->elem);
}

TAvl izqAvl(TAvl avl) {
  assert(!estaVacioAvl(avl));
  return avl->izq;
}

TAvl derAvl(TAvl avl) {
  assert(!estaVacioAvl(avl));
  return avl->der;
}

nat cantidadEnAvl(TAvl avl) {
  if (!estaVacioAvl(avl)) {
    return avl->cant;
  } else {
    return 0;
  }
}

nat alturaDeAvl(TAvl avl) {
  if (avl == NULL) {
    return 0;
  } else {
    return avl->altura;
  }
}

static TIterador enOrdenAvl_aux (TAvl avl, TIterador &res) {
  if (!estaVacioAvl(avl->izq)) {
    res = enOrdenAvl_aux (avl->izq, res);
  }
  res = agregarAIterador(avl->elem, res);
  if (!estaVacioAvl(avl->der)) {
    res = enOrdenAvl_aux (avl->der, res);
  }
  return res;
}

TIterador enOrdenAvl(TAvl avl) {
  TIterador res = crearIterador();
  if (!estaVacioAvl(avl)) {
    res = enOrdenAvl_aux(avl, res);
  }
  return res;
}

TAvl arregloAAvl(nat *elems, nat n) {
  assert(n>0);
  TAvl res = crearAvl();
  for (nat i = 0; i < n; i = i +1) {
    res = insertarEnAvl(elems[i], res);
  }
  return res;
}

static nat cantNodos(nat h) {
  if (h == 1) {
    return 1;
  } else if (h == 2) {
    return 2;
  } else {
    nat res = cantNodos(h-1) + cantNodos(h-2) + 1;
    return res;
  }
}

static TAvl avlMin_aux(int h, int &ua) {
  TAvl aux = crearAvl();
  if (h > 0) {
    aux = new repAvl;
    aux->izq = avlMin_aux(h-1, ua);
    //ua = ua + 1;
    aux->elem = ++ua;
    //aux->cant = cantidadEnAvl(aux->izq) + cantidadEnAvl(aux->der) + 1;
    //aux->altura = maximo(alturaDeAvl(aux->izq), alturaDeAvl(aux->der)) + 1;
    aux->der = avlMin_aux(h-2, ua);
  }
  return aux;
}

TAvl avlMin(nat h) {
  if (h == 0) {
    TAvl res = crearAvl();
    return res;
  } else if (h == 1) {
    TAvl res = crearAvl();
    res = insertarEnAvl(1, res);
    return res;
  } else {
    int a = h;
    int contador = 0;
    TAvl res = avlMin_aux(a, contador);
    res->cant = cantNodos(h);
    res->altura = h;
    return res;
  }
}

void imprimirAvl(TAvl avl) {
  if (avl != NULL) {
    TAvl aux;
    TPila pila = crearPila(1000);
    TColaAvls cola = crearColaAvls();

    cola = encolar(avl, cola);
    cola = encolar(NULL, cola);
    pila = apilar(0, pila);

    while (!estaVaciaColaAvls(cola)) {
      aux = frente(cola);
      cola = desencolar(cola);
      if ((aux == NULL) && (!estaVaciaColaAvls(cola))) {
        pila = apilar(0, pila);
        cola = encolar(NULL, cola);
      } else {
        if (aux != NULL) {
          pila = apilar(aux->elem, pila);
          if (aux->der != NULL) {
            cola = encolar(aux->der, cola);
          }
          if (aux->izq != NULL) {
            cola = encolar(aux->izq, cola);
          }
        }
      }
    }
    liberarColaAvls(cola);
    while (!estaVaciaPila(pila)) {
      if (cima(pila) == 0) {
        printf ("\n");
      } else {
        printf ("%u" " ", (cima(pila)));
      }
      pila = desapilar(pila);
    }
    liberarPila(pila);
  }
}

void liberarAvl(TAvl avl) {
  if (!estaVacioAvl(avl)) {
    liberarAvl(avl->izq);
    liberarAvl(avl->der);
    delete avl;
    avl = NULL;
  }
}
