
/*
  Módulo de definición de 'TAvl'.

  Los elementos de tipo 'TAvl' son avls cuyos elementos son de tipo nat.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _TAvl_H
#define _TAvl_H

#include "iterador.h"
#include "utils.h"

// Representación de 'TAvl'.
// Se debe definir en avl.cpp.
// struct repAvl;
// Declaración del tipo 'TAvl'.
typedef struct repAvl *TAvl;

/*
  Devuelve un 'TAvl' vacío (sin elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
TAvl crearAvl();

/*
  Devuelve 'true' si y solo si 'avl' es vacío (no tiene elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaVacioAvl(TAvl avl);

/*
  Inserta 'elem' en 'avl' respetando la propiedad de orden definida.
  Precondición: esVacioAvl(buscarEnAvl(elem, avl).
  Devuelve 'avl'.
  El tiempo de ejecución en el peor caso es O(log n), siendo 'n' la cantidad
  de elementos de 'avl'.
*/
TAvl insertarEnAvl(nat elem, TAvl avl);

/*
  Devuelve el subárbol cuya raíz es 'elem'.
  Si ningún nodo cumple esa condición devuelve el árbol vacío.
  El 'TAvl' resultado comparte memoria con el parámetro.
  El tiempo de ejecución en el peor caso es O(log n), siendo 'n' la cantidad
  de elementos de 'avl'.
 */
TAvl buscarEnAvl(nat elem, TAvl avl);

/*
  Devuelve el elemento asociado a la raíz de 'avl'.
  Precondición: ! esVacioAvl(b).
  El tiempo de ejecución en el peor caso es O(1).
 */
nat raizAvl(TAvl avl);

/*
  Devuelve el subárbol izquierdo de 'avl'.
  Precondición: ! esVacioAvl(TAvl).
  El 'TAvl' resultado comparte memoria con el parámetro.
  El tiempo de ejecución en el peor caso es O(1).
 */
TAvl izqAvl(TAvl avl);

/*
  Devuelve el subárbol derecho de 'avl'.
  Precondición: ! esVacioAvl(TAvl).
  El 'TAvl' resultado comparte memoria con el parámetro.
  El tiempo de ejecución en el peor caso es O(1).
 */
TAvl derAvl(TAvl avl);

/*
  Devuelve la cantidad de elementos en 'avl'.
  El tiempo de ejecución en el peor caso es O(1).
 */
nat cantidadEnAvl(TAvl avl);

/*
  Devuelve la altura de 'avl'.
  La altura de un árbol vacío es 0.
  El tiempo de ejecución en el peor caso es O(1).
 */
nat alturaDeAvl(TAvl avl);

/*
  Devuelve un 'TIterador' de los elementos de 'avl'.
  En la recorrida del iterador devuelto los elementos aparecerán en orden
  creciente.
  El 'TIterador' resultado no comparte memoria con 'avl'.
  El tiempo de ejecución en el peor caso es O(n) siendo 'n' la cantidad de
  elementos de 'avl'.
 */
TIterador enOrdenAvl(TAvl avl);

/*
  Devuelve un 'TAvl' con los 'n' elementos que están en el rango [0 .. n - 1]
  del arreglo 'elems'.
  Precondiciones:
  - n > 0
  - Los elementos están ordenados de manera creciente estricto
  (creciente y sin  repetidos).
  En cada nodo del árbol resultado la cantidad de elementos de su subárbol
  izquierdo es igual a, o 1 menos que, la cantidad de elementos de su subárbol
  derecho.
  El tiempo de ejecución en el peor caso es O(n).
 */
TAvl arregloAAvl(nat *elems, nat n);

/*
  Devuelve un 'TAvl' de altura 'h' con 'n' nodos, siendo 'n' la mínima cantidad
  de elementos que puede tener un 'TAvl' de altura 'h'.
  Los elementos van desde 1 hasta 'n'.
  En ningún nodo puede ocurrir que el subárbol derecho tenga más nodos que el
  subárbol izquierdo.
  La altura de un árbol vacío es 0.
  El tiempo de ejecución en el peor caso es O(n).
  Ver ejemplos en la letra.
 */
TAvl avlMin(nat h);

/*
  Imprime los elementos de cada nivel de 'avl'.
  Imprime una línea por nivel, primero el más profundo y al final el que
  corresponde a la raíz.
  Cada nivel se imprime en orden creciente. Se debe dejar un espacio en
  blanco después de cada número.
  Se puede asumir que 0 no es ningún elemento.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'TAvl'.
  Ver ejemplos en la letra.
 */
void imprimirAvl(TAvl avl);

/*
  Libera la memoria asignada a 'TAvl'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'TAvl'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad
  de elementos de 'avl'.
 */
void liberarAvl(TAvl avl);

#endif
