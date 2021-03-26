/*
  Módulo de definición de 'TCadena'.

  Los elementos de tipo 'TCadena' son lista doblemente enlazada de elementos
  de tipo 'Tinfo', con cabezal con punteros al inicio y al final.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _CADENA_H
#define _CADENA_H

#include "info.h"

/*
  Las variables de tipo 'TLocalizador' permiten acceder a los elementos en las
  estructuras que los contienen. En el caso de una cadena enlazada esas
  variables son punteros a los nodos.
 */
// Rrepresentación de 'TLocalizador'.
// Se debe definir en 'cadena.cpp'.
// struct nodo;
// Declaración del tipo 'TLocalizador'
typedef struct nodo *TLocalizador;

// Representación de 'TCadena'.
// Se debe definir en 'cadena.cpp'.
// struct repCadena;
// Declaración del tipo 'TCadena'
typedef struct repCadena *TCadena;

/*
  Devuelve 'true' si y solo si 'loc' es un 'TLocalizador' válido.
  En cadenas enlazadas un 'TLocalizador' es válido si y solo si no es 'NULL'.
  El tiempo de ejecución en el peor caso es O(1).
 */
bool esLocalizador(TLocalizador loc);

/*
  Devuelve la 'TCadena' vacía (sin elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
TCadena crearCadena();

/*
  Libera la memoria asignada a 'cad' y la de todos sus elementos.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
 */
void liberarCadena(TCadena cad);

/*
  Devuelve 'true' si y solo si 'cad' es vacía (no tiene elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
bool esVaciaCadena(TCadena cad);

/*
  Devuelve el 'TLocalizador' con el que se accede al inicio de 'cad'.
  Si esVaciaCadena(cad) devuelve un 'TLocalizador' no válido.
  El tiempo de ejecución en el peor caso es O(1).
 */
TLocalizador inicioCadena(TCadena cad);

/*
  Devuelve el 'TLocalizador' con el que se accede al final de 'cad'.
  Si es_vacia_cadena(cad) devuelve un 'TLocalizador' no válido.
  El tiempo de ejecución en el peor caso es O(1).
 */
TLocalizador finalCadena(TCadena cad);

/*
  Devuelve el elemento de 'cad' al que se accede con 'loc'.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
 */
TInfo infoCadena(TLocalizador loc, TCadena cad);

/*
  Devuelve el 'TLocalizador' con el que se accede al elemento de 'cad'
  inmediatamente siguiente a 'loc'.
  Si esFinalCadena(loc, cad) devuelve un 'TLocalizador' no válido.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
 */
TLocalizador siguiente(TLocalizador loc, TCadena cad);

/*
  Devuelve el 'TLocalizador' con el que se accede al elemento de 'cad'
  inmediatamente anterior a 'loc'.
  Si esInicioCadena(loc, cad) devuelve un 'TLocalizador' no válido.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
 */
TLocalizador anterior(TLocalizador loc, TCadena cad);

/*
  Devuelve 'true' si y solo si con 'loc' se accede al último elemento de 'cad'.
  Si esVaciaCadena (cad) devuelve 'false'.
  El tiempo de ejecución en el peor caso es O(1).
 */
bool esFinalCadena(TLocalizador loc, TCadena cad);

/*
  Devuelve 'true' si y solo si con 'loc' se accede al primer elemento de 'cad'.
  Si esVaciaCadena (cad) devuelve 'false'.
  El tiempo de ejecución en el peor caso es O(1).
 */
bool esInicioCadena(TLocalizador loc, TCadena cad);

/*
  Se inserta 'i' como último elemento de 'cad'.
  Devuelve 'cad'.
  Si esVaciaVadena (cad) 'i' se inserta como único elemento de 'cad'.
  El tiempo de ejecución en el peor caso es O(1).
 */
TCadena insertarAlFinal(TInfo i, TCadena cad);

/*
  Se inserta 'i' como un nuevo elemento inmediatamente antes de 'loc'.
  Devuelve 'cad'.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
 */
TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad);

/*
  Se remueve el elemento al que se accede desde 'loc' y se libera la memoria
  asignada al mismo y al nodo apuntado por el localizador.
  Devuelve 'cad'.
  El valor de 'loc' queda indeterminado.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
 */
TCadena removerDeCadena(TLocalizador loc, TCadena cad);

/*
  Imprime los elementos de 'cad' de la siguiente forma:
  (n de pos1,r de pos1)(n de pos2,r de pos2) ...
  donce 'n` es el componente natural y 'r' es el componente real.
  Antes de terminar, se debe imprimir un fin de linea.
  Si esVaciaCadena(cad) sólo se imprime el fin de línea.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
 */
void imprimirCadena(TCadena cad);

/*
  Devuelve el 'TLocalizador' con el que se accede al k-esimo elemento de 'cad'.
  Si 'k' es 0 o mayor a la cantidad de elementos de 'cad' devuelve un
  localizdor  no válido.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
 */
TLocalizador kesimo(nat k, TCadena cad);

/*
  Devuelve 'true' si y solo si con 'loc' se accede a un elemento de 'cad',
  (o sea, si apunta a un nodo de 'cad').
  Si esVaciaCadena (cad) devuelve 'false'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
 */
bool localizadorEnCadena(TLocalizador loc, TCadena cad);

/*
  Devuelve 'true' si y solo si 'loc1' es igual o precede a 'loc2' en 'cad'.
  Si esVaciaCadena (cad) devuelve 'false'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
 */
bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad);

/*
  Se inserta en 'cad' la 'TCadena' 'sgm' inmediatamente después de 'loc',
  manteniendo los elementos originales y el orden relativo entre ellos.
  Devuelve 'cad'.
  No se debe obtener memoria (los nodos de 'sgm' pasan a ser parte de 'cad').
  Se libera la memoria asignada al resto de las estructuras de 'sgm'.
  El valor de 'sgm' queda indeterminado.
  Si esVaciaCadena(cad) 'loc' es ignorado y el segmento queda insertado.
  Precondición: esVaciaCadena(cad) o localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
 */
TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad);

/*
  Devuelve una 'TCadena' con los elementos de 'cad' que se encuentran entre
  'desde' y 'hasta', incluidos.
  La 'TCadena' resultado no comparte memoria con 'cad'.
  Si esVaciaCadena(cad) devuelve la 'TCadena' vacia.
  Precondición: esVaciaCadena(cad) o precedeEnCadena(desde, hasta, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en la cadena resultado.
 */
TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad);

/*
  Remueve de 'cad' los elementos que se encuentran  entre 'desde' y 'hasta',
  incluidos y libera la memoria que tenían asignada y la de sus nodos.
  Devuelve 'cad'.
  Si esVaciaCadena(cad) devuelve la 'TCadena' vacía.
  Precondición: esVaciaCadena(cad) o precedeEnCadena(desde, hasta, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en la cadena resultado.
 */
TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad);

/*
  Sustituye con 'i' el elemento de 'cad' al que se accede con 'loc'.
  Devuelve 'cad'.
  No destruye el elemento al que antes se accedía con 'loc'.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
 */
TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad);

/*
  Intercambia los elementos a los que se accede con 'loc1' y 'loc2'.
  'loc1' y 'loc2' mantienen su relación de precedencia.
  Devuelve 'cad'.
  Precondición:
    localizadorEnCadena (loc1, cad)
  y localizadorEnCadena (loc2, cad).
  El tiempo de ejecución en el peor caso es O(1).
 */
TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad);

/*
  Devuelve el primer 'TLocalizador' con el que se accede a un elemento cuyo
  componente natural es igual a 'clave', buscando desde 'loc' (inclusive) hacia
  el final de 'cad'. Si no se encuentra o 'cad' es vacía devuelve un
  'TLocalizador' no válido.
  Precondición: esVaciaCadena(cad) o localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
 */
TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad);

/*
  Devuelve el primer 'TLocalizador' con el que se accede a un elemento cuyo
  componente natural es igual a 'clave', buscando desde 'loc' (inclusive) hacia
  el inicio de 'cad'. Si no se encuentra o 'cad' es vacía devuelve un
  'TLocalizador' no válido.
  Precondición: esVaciaCadena(cad) o localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
 */
TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad);

/*
  Devuelve el 'TLocalizador' con el que se accede al elemento cuyo componente
  natural es el menor en el segmento que va desde 'loc' hasta finalCadena(cad).
  Si hay más de un elemento cuyo valor es el menor el resultado accede al que
  precede a los otros.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
 */
TLocalizador menorEnCadena(TLocalizador loc, TCadena cad);

#endif
