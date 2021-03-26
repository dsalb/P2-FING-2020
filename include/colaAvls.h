/*
  Módulo de definición de TCcolaAvls'.

  Los elementos de tipo 'TColaAvls' son estructuras lineales con
  comportamiento FIFO cuyos elementos son de tipo 'avl'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _COLA_AVLS_H
#define _COLA_AVLS_H

#include "avl.h"
#include "utils.h"

// Representación de TColaAvls'.
// Se debe definir en colaAvls.cpp
// struct repColaAvls;
// Declaración del tipo 'TColaAvls'
typedef struct repColaAvls *TColaAvls;

/*
  Devuelve una 'TColaAvls' vacía (sin elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
TColaAvls crearColaAvls();

/*
  Encola 'avl' en 'c'.
  Devuelve 'c'.
  El tiempo de ejecución en el peor caso es O(1).
 */
TColaAvls encolar(TAvl avl, TColaAvls c);

/*
  Remueve de 'c' el elemento que está en el frente.
  Si estaVaciaColaAvls(c) no hace nada.
  Devuelve 'c'.
  NO libera la memoria del elemento removido.
  El tiempo de ejecución en el peor caso es O(1).
 */
TColaAvls desencolar(TColaAvls c);

/*
  Libera la memoria asignada a 'c', pero NO la de sus elementos.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad
  de elementos de 'c'.
 */
void liberarColaAvls(TColaAvls c);

/*
  Devuelve 'true' si y solo si 'c' es vacía (no tiene elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaVaciaColaAvls(TColaAvls c);

/*
  Devuelve el elemento que está en el frente de 'c'.
  Precondición: ! estaVaciaColaAvls(c);
  El tiempo de ejecución en el peor caso es O(1).
 */
TAvl frente(TColaAvls c);

#endif
