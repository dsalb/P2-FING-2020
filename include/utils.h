/*
  Módulo de definición de 'utils'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _UTILS_H
#define _UTILS_H

/*
  #include <float.h>  // DBL_MAX
  #include <limits.h> // UINT_MAX
  #include <stdio.h>  // printf, scanf, sprintf
  #include <stdlib.h> // NULL
*/

// tipo para los enteros no negativos
typedef unsigned int nat;

// tipos para arreglos
typedef nat *ArregloNats;       // arreglo de nat
typedef char *ArregloChars;     // arreglo de char
typedef bool *ArregloBools;     // arreglo de bool
typedef double *ArregloDoubles; // arreglo de double

// leen desde la entrada estándar y devuelven el elemento leído
nat leerNat();
char leerChar();
double leerDouble();

/*
  Lee en 'cs' desde la entreada estándar.
 */
void leerChars(ArregloChars cs);

/*
  Lee en 'cs' el resto de la línea de la entrada estandar sin consumir
  el cambi de línea.
 */
void leerRestoLinea(ArregloChars cs);

#endif
