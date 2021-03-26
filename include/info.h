/*
  Módulo de definición de 'TInfo'.

  Los elementos de tipo 'TInfo' son punteros a una estructura (que debe
  definirse en info.cpp) compuesta por un natural y un real.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _INFO_H
#define _INFO_H

#include "utils.h"

// Representación de 'TInfo'.
// Se debe definir en info.cpp.
// struct repInfo;
// Declaración del tipo 'TInfo'.
typedef struct repInfo *TInfo;

/* Operaciones de TInfo */

/*
  Devuelve un 'TInfo' compuesto por 'natural' y 'real'.
 */
TInfo crearInfo(nat natural, double real);

/*
  Libera la memoria reservada por 'info'.
 */
void liberarInfo(TInfo info);

/*
  Devuelve una copia de 'info'.
  El elemento devuelto no comparte memoria con 'info'.
 */
TInfo copiaInfo(TInfo info);

/*
  Devuelve el componente natural de 'info'.
 */
nat natInfo(TInfo info);

/*
  Devuelve el componente real de 'info'.
 */
double realInfo(TInfo info);

/*
  Devuelve 'true' si y solo si los componenetes naturales de 'i1' e 'i2' son
  iguales y los compoentes reales de 'i1' e 'i2' son iguales.
 */
bool sonIgualesInfo(TInfo i1, TInfo i2);

/*
  Devuelve un arreglo de caracteres formado por la concatenación del componente
  natural  de 'info', el string "," y el componente real  de 'info' encerrados
  entre parentesis.
  El elemento devuelto no comparte memoria con 'info'.
  Termina con '\0'.
   Ejemplos:
   (4,2.0)
   (9,-1.2)
   (0,0)
 */
ArregloChars infoATexto(TInfo info);

#endif
