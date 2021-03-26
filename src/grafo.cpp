#include "../include/grafo.h"
#include "../include/iterador.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct nodoG {
  nat vert;
  double arist;
  nodoG* sig;
};

struct repGrafo {
  nodoG** arrayN;
  //nat* arrayV;
  nat cant_vertices;
  nat parejas;
  nat max_parejas;
};

TGrafo crearGrafo(nat N, nat M) {
  TGrafo g = new repGrafo;
  g->cant_vertices = N;
  g->parejas = 0;
  g->max_parejas = M;
  g->arrayN = new nodoG* [N + 1];
  for (nat i = 0; i <= N; i = i + 1) {
    g->arrayN[i] = NULL;
  }
  return g;
}

nat cantidadVertices(TGrafo g) {
  if (g != NULL) {
    return (g->cant_vertices);
  } else {
    return 0;
  }
}

bool hayMParejas(TGrafo g) {
  if (g != NULL) {
    return (g->parejas == g->max_parejas);
  } else {
    return false;
  }
}

TGrafo hacerVecinos(nat v1, nat v2, double d, TGrafo g) {
  assert(1 <= v1);
  assert(v2 <= g->cant_vertices);
  assert(v1 != v2);
  assert(!sonVecinos(v1, v2, g));
  assert(!hayMParejas(g));
  assert(d >= 0);

  nodoG* aux1 = new nodoG;
  aux1->vert = v2;
  aux1->arist = d;

  nodoG* aux2 = new nodoG;
  aux2->vert = v1;
  aux2->arist = d;

  if ((g->arrayN[v1] == NULL) || (g->arrayN[v1]->vert > v2)) {
    aux1->sig = g->arrayN[v1];
    g->arrayN[v1] = aux1;
  } else {
    nodoG* p = g->arrayN[v1];
    while ((p->sig != NULL) && (p->sig->vert < v2)) {
      p = p->sig;
    }
    aux1->sig = p->sig;
    p->sig = aux1;
  }
  if ((g->arrayN[v2] == NULL) || (g->arrayN[v2]->vert > v1)) {
    aux2->sig = g->arrayN[v2];
    g->arrayN[v2] = aux2;
  } else {
    nodoG* p = g->arrayN[v2];
    while ((p->sig != NULL) && (p->sig->vert < v1)) {
      p = p->sig;
    }
    aux2->sig = p->sig;
    p->sig = aux2;
  }
  g->parejas = g->parejas + 1;
  return g;
}

bool sonVecinos(nat v1, nat v2, TGrafo g) {
  assert(1 <= v1);
  assert(v2 <= g->cant_vertices);
  bool res = false;
  if (g->arrayN[v1] != NULL) {
    nodoG* p = g->arrayN[v1];
    while ((p != NULL) && (p->vert != v2)) {
      p = p->sig;
    }
    res = p != NULL;
  }
  return res;
}

double distancia(nat v1, nat v2, TGrafo g) {
  assert(sonVecinos(v1, v2, g));
  assert(1 <= v1);
  assert(v2 <= g->cant_vertices);
  double res;

  nodoG* p = g->arrayN[v1];
  while ((p != NULL) && (p->vert != v2)) {
    p = p->sig;
  }
  res = p->arist;

  return res;
}

TIterador vecinos(nat v, TGrafo g) {
  assert(1 <= v);
  assert(v <= g->cant_vertices);
  TIterador iter = crearIterador();

  nodoG* p = g->arrayN[v];
  while (p != NULL) {
    iter = agregarAIterador(p->vert, iter);
    p = p->sig;
  }
  return iter;
}

void liberarGrafo(TGrafo g) {
  for (nat i = 0; i <= g->cant_vertices; i = i + 1) {
    nodoG* p = g->arrayN[i];
    while (p != NULL) {
      nodoG* aux = p;
      p = p->sig;
      delete aux;
    }
  }
  delete [] g->arrayN;
  delete g;
}
