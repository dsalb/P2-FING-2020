/*
  Módulo de definición de 'TPila'.

  Los elementos de tipo 'TPila' son estructuras lineal acotadas con
  comportamiento LIFO cuyos elementos son naturales.

  La cantidad de elementos que puede mantener se establece en el parámetro
  de 'crearPila'.


  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _PILA_H
#define _PILA_H

#include "utils.h"

// Representación de 'TPila'.
// Se debe definir en pila.cpp.
// struct repPila;
// Declaración del tipo 'TPila'
typedef struct repPila *TPila;

/*
  Devuelve una 'TPila' vacía (sin elementos) que puede tener hasta 'tamanio'
  elementos.
  Precondición: tamanio > 0.
 */
TPila crearPila(nat tamanio);

/*
  Apila 'num' en 'p'.
  Devuelve 'p'.
  Si estaLenaPila(p) no hace nada.
  El tiempo de ejecución en el peor caso es O(1).
 */
TPila apilar(nat num, TPila p);

/*
  Remueve de 'p' el elemento que está en la cima.
  Devuelve 'p'.
  Si estaVaciaPila(p) no hace nada.
  El tiempo de ejecución en el peor caso es O(1).
 */
TPila desapilar(TPila p);

/*
  Libera la memoria asignada a 'p'.
 */
void liberarPila(TPila p);

/*
  Devuelve 'true' si y solo si 'p' es vacía (no tiene elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaVaciaPila(TPila p);

/*
  Devuelve 'true' si y solo si la cantidad de elementos en 'p' es 'tamanio'
  (siendo 'tamanio' el valor del parámetro con que fue creada 'p').
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaLlenaPila(TPila p);

/*
  Devuelve el elemento que está en la cima de 'p'.
  Precondición: ! estaVaciaPila(p);
  El tiempo de ejecución en el peor caso es O(1).
 */
nat cima(TPila p);

#endif
