/*
  Módulo de definición de 'TColaDePrioridad'.

  Los elementos de tipo 'TColaDePrioridad' son colas de prioridad cuyos
  elementos son de tipo 'nat' entre 1 y N, siendo N un parámetro pasado al
  crear la cola de prioridad.
  No hay elementos repetidos.
  La prioridad asociada al elemento es de tipo double y la determina un valor
  estalecido al insertar el elemento. Ese valor puede ser modificado.
  Un elemento es prioritario ante otro si su valor asociado es menor.
  Si hay más de un elemento con mínimo valor asociado cualquiera de ellos es
  el prioritario.


  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _CP_H
#define _CP_H

#include "utils.h"

// Representación de 'TColaDePrioridad'
// Se debe definir en colaDePrioridad.cpp
// struct repCP;
// Declaración del tipo 'TColaDePrioridad'
typedef struct repCP *TColaDePrioridad;

/*
  Devuelve una 'TColaDePrioridad' vacía (sin elementos). Podrá contener
  elementos entre 1 y N.
  El tiempo de ejecución en el peor caso es O(N).
 */
TColaDePrioridad crearCP(nat N);

/*
  Devuelve el valor máximo que puede tener un elemento de 'cp', que es el
  parámetro de crearCP.
  El tiempo de ejecución en el peor caso es O(1).
 */
nat rangoCP(TColaDePrioridad cp);

/*
  Inserta 'elem' en 'cp'. La prioridad asociada a 'elem' es 'valor'.
  Precondición 1 <= elem <= rangoCP(cp).
  Precondición: !estaEnCp(elem, cp).
  Devuelve 'cp'.
  El tiempo de ejecución en el peor caso es O(log N), siendo 'N' el parámetro
  pasado en crearCP.
 */
TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp);

/*
  Devuelve 'true' si y solo si en 'cp' no hay elementos.
  El tiempo de ejecución en el peor casos es O(1).
 */
bool estaVaciaCP(TColaDePrioridad cp);

/*
  Devuelve el elemento prioritario de 'cp'.
  Precondición: !estaVacioCP(cp).
  El tiempo de ejecución en el peor casos es O(1).
 */
nat prioritario(TColaDePrioridad cp);

/*
  Elimina de 'cp' el elemento prioritario.
  Precondición: !estaVacioCP(cp).
  Devuelve 'cp'.
  El tiempo de ejecución en el peor caso es O(log N), siendo 'N' el parámetro
  pasado en crearCP.
 */
TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp);

/*
  Devuelve 'true' si y solo si 'elem' es un elemento de 'cp'.
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaEnCP(nat elem, TColaDePrioridad cp);

/*
  Devuelve el valor de prioridad asociado a 'elem'.
  Precondición: estaEnCp(elem, cp).
  El tiempo de ejecución en el peor caso es O(1).
 */
double prioridad(nat elem, TColaDePrioridad cp);

/*
  Modifica el valor de la propiedad asociada a 'elem'; pasa a ser 'valor'.
  Precondición: estaEnCp(elem, cp).
  Devuelve 'cp'.
  El tiempo de ejecución en el peor caso es O(log N), siendo 'N' el parámetro
  pasado en crearCP.
 */
TColaDePrioridad actualizarEnCP(nat elem, double valor, TColaDePrioridad cp);

/*
  Libera la menoria asignada a 'cp'.
  El tiempo de ejecución en el peor caso es O(N), siendo 'N' el parámetro
  pasado en crearCP.
 */
void liberarCP(TColaDePrioridad cp);

#endif
