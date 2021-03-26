#include "../include/colaDePrioridad.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>

struct nodoCP {
  nat elem;
  double prio;
};

struct repCP {
  nodoCP* array;
  nat* index;
  nat tope;
  nat max;
};

static void swap (nodoCP &a, nodoCP &b, TColaDePrioridad cp) {
  nat index_padre = cp->index[a.elem];
  nat index_hijo = cp->index[b.elem];

  // actualización de index
  cp->index[a.elem] = index_hijo;
  cp->index[b.elem] = index_padre;

  // actualización de nodos
  nodoCP aux = a;
  a = b;
  b = aux;
}

TColaDePrioridad crearCP(nat N) {
  TColaDePrioridad res = new repCP;
  res->tope = 0;
  res->array = new nodoCP [N+1];
  res->max = N;
  res->index = new nat [N+1];
  for (nat i = 0; i <= N; i = i+1) {
    res->index[i] = 0;
  }
  return res;
}

nat rangoCP(TColaDePrioridad cp) {
  return (cp->max);
}

TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp) {
  assert((1 <= elem) && (elem <= rangoCP(cp)));
  assert(!estaEnCP(elem, cp));
  cp->tope = cp->tope + 1;
  cp->array[cp->tope].elem = elem;
  cp->array[cp->tope].prio = valor;
  cp->index[elem] = cp->tope;
  nat i = cp->tope;
  while ((i != 1) && (cp->array[i].prio < cp->array[i/2].prio)) {
    swap(cp->array[i], cp->array[i/2], cp);
    //cp->index[elem] = i/2;
    //cp->index[cp->array[i/2].elem] = i;
    i = i/2;
  }
  return cp;
}

bool estaVaciaCP(TColaDePrioridad cp) {
  return (cp->tope == 0);
}

nat prioritario(TColaDePrioridad cp) {
  assert(!estaVaciaCP(cp));
  return (cp->array[1].elem);
}

TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp) {
  assert(!estaVaciaCP(cp));
  cp->index[cp->array[1].elem] = 0;
  if (cp->tope == 1) {
    cp->tope = 0;
  } else if (cp->tope == 2) {
    swap(cp->array[1], cp->array[2], cp);
    cp->tope = 1;
  } else {
    // se define la posición objetivo del swap
    nat i;
    if (cp->array[2].prio < cp->array[3].prio) {
      i = 2;
    } else {
      i = 3;
    }
    swap(cp->array[1], cp->array[i], cp); // intercambio con nuevo prioritario
    swap(cp->array[i], cp->array[cp->tope], cp);
    cp->tope = cp->tope - 1; // antiguo prio queda fuera del heap
    // filtrado descendente para nueva ubicación de i
    while (2*i <= cp->tope) {
      nat hijo = 2*i;
      if ((hijo + 1 <= cp->tope) && (cp->array[hijo].prio > cp->array[hijo+1].prio)) {
        hijo = hijo + 1;
      }
      if (cp->array[hijo].prio < cp->array[i].prio) {
        swap(cp->array[hijo], cp->array[i], cp);
      }
      i = hijo;
    }
  }
  return cp;
}



bool estaEnCP(nat elem, TColaDePrioridad cp) {
  //return (cp->index[elem] != 0);
  nat i = 1;
  if (cp->tope != 0) {
    while ((i <= cp->tope) && (elem != cp->array[i].elem)) {
      i = i + 1;
    }
  }
  return (i <= cp->tope);
}

double prioridad(nat elem, TColaDePrioridad cp) {
  /*nat i = cp->index[elem]; // ubicación de elem en el array
  return (cp->array[i].prio);*/
  nat i = 1;
  if (cp->tope != 0) {
    while ((i <= cp->tope) && (elem != cp->array[i].elem)) {
      i = i + 1;
    }
  }
  return cp->array[i].prio;
}

TColaDePrioridad actualizarEnCP(nat elem, double valor, TColaDePrioridad cp) {
  assert(estaEnCP(elem, cp));
  //nat i = cp->index[elem]; // se guarda en i ubicación de elem en array
  nat i = 1;
  if (cp->tope != 0) {
    while ((i <= cp->tope) && (elem != cp->array[i].elem)) {
      i = i + 1;
    }
  }
  cp->array[i].prio = valor; // se actualiza con el nuevo valor de prioridad
  if ((cp->tope) >= 2) {
    if ((i != 1) && (cp->array[i].prio < cp->array[i/2].prio)) { //filtrado ascendente
      while ((i != 1) && (cp->array[i].prio < cp->array[i/2].prio)) {
        swap(cp->array[i], cp->array[i/2], cp);
        i = i/2;
      }
    } else { // filtrado descendente
      while (2*i <= cp->tope) {
        nat hijo = 2*i;
        if ((hijo + 1 <= cp->tope) && (cp->array[hijo].prio > cp->array[hijo+1].prio)) {
          hijo = hijo + 1;
        }
        if (cp->array[hijo].prio < cp->array[i].prio) {
          swap(cp->array[hijo], cp->array[i], cp);
        }
        i = hijo;
      }
    }
  }
  return cp;
}

void liberarCP(TColaDePrioridad cp) {
  delete [] cp->array;
  delete [] cp->index;
  delete cp;
}
