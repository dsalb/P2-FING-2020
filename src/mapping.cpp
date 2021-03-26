#include "../include/mapping.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>

struct nodoMap {
  nodoMap* sig;
  nat clave;
  double valor;
};

struct repMap {
  nodoMap** hash;
  nat cont;
  nat max;
};

static nat f_hash (nat clave, nat base) {
  nat res = (clave*clave)%base;
  return res;
}

TMapping crearMap(nat M) {
  TMapping res = new repMap;
  res->hash = new nodoMap* [M];
  res->max = M-1;
  res->cont = 0;
  for (nat i = 0; i < M; i = i +1) {
    res->hash[i] = NULL;
  }
  return res;
}

TMapping asociarEnMap(nat clave, double valor, TMapping map) {
  assert(!estaLlenoMap(map));
  assert(!existeAsociacionEnMap(clave, map));
  nat base = map->max + 1;
  nat i = f_hash(clave, base);
  nodoMap* aux = new nodoMap;
  map->cont = map->cont + 1;
  aux->clave = clave;
  aux->valor = valor;
  aux->sig = map->hash[i];
  map->hash[i] = aux;
  return map;
}

TMapping desasociarEnMap(nat clave, TMapping map) {
  assert(existeAsociacionEnMap(clave, map));
  nat base = map->max + 1;
  nat i = f_hash(clave, base);
  nodoMap* aux = map->hash[i];
  if (aux->clave == clave) {
    map->hash[i] = aux->sig;
    delete aux;
  } else {
    while (aux->sig->clave != clave) {
      aux = aux->sig;
    }
    nodoMap* p = aux->sig;
    aux->sig = p->sig;
    delete p;
  }
  map->cont = map->cont - 1;
  return map;
}

bool existeAsociacionEnMap(nat clave, TMapping map) {
  bool res = false;
  nat base = map->max + 1;
  nat i = f_hash(clave, base);
  if (map->hash[i] != NULL) {
    nodoMap* aux = map->hash[i];
    while ((aux->sig != NULL) && (aux->clave != clave)) {
      aux = aux->sig;
    }
    res = (aux->clave == clave);
  }
  return res;
}

double valorEnMap(nat clave, TMapping map) {
  assert(existeAsociacionEnMap(clave, map));
  nat base = map->max + 1;
  nat i = f_hash(clave, base);
  nodoMap* aux = map->hash[i];
  while (aux->clave != clave)  {
    aux = aux->sig;
  }
  return aux->valor;
}

bool estaLlenoMap(TMapping map) {
  return (map->cont == map->max + 1);
}

void liberarMap(TMapping map) {
  for (nat i = 0; i <= map->max; i = i+1) {
    while (map->hash[i] != NULL) {
      nodoMap* aux = map->hash[i];
      map->hash[i] = aux->sig;
      delete aux;
    }
  }
  delete [] map->hash;
  delete map;
}
