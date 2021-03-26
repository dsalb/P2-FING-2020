/*
  Módulo de definición de 'usoTads'.

  Se definen funciones sobre tads.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _USOTADS_H
#define _USOTADS_H

#include "binario.h"
#include "cadena.h"
#include "conjunto.h"
#include "grafo.h"
#include "utils.h"

// nueva
/*
  Devuelve un arreglo que indica a cuales vértices se puede llegar desde 'v'.
  El arreglo devuelto tiene tamaño N+1. La coordenada 0 no se tiene en cuenta.
  La coordenada 'i' (1 <= i <= N) es 'true' si y solo si el vértice 'i' es
  accesible desde 'v'.
  Precondición: 1 <= v <= N.

  Seudocódigo:
   - Inicializar cada coordenada del arreglo a devolver con 'false'
     (se considera cada vértice no accesible).
   - Pasar 'v' como parámetro a una función auxiliar. Esta función
     -- marca el parámetro como accesible desde 'v'.
     -- para cada vécino de su parámetro que todavía sea no accesible
        desde 'v' hace una llamada recursiva.
   - Devolver el arreglo.
 */
ArregloBools accesibles(nat v, TGrafo g);

// nueva

/*
  Devuelve un arreglo con las longitudes de los caminos más cortos desde 'v'
  hasta cada vértice del grafo.
  El arreglo devuelto tiene tamaño N+1. La coordenada 0 no se tiene en cuenta.
  En la coordenada 'i' (1 <= i <= N) se devuelve la longitud del camino más
  corto desde 'v' hasta 'i'. Si 'i' no es accesible desde 'v' el valor de esa
  coordenada es DBL_MAX (definido en float.h)
  Precondición: 1 <= v <= N.

  Seudocódigo:
   - Crear colecciones 'C' y 'S', inicialmente vacías, de pares (u,du)
     donde 'u' representa un vértice y 'du' es la longitud del camino más
     corto desde 'v' hasta 'u'. El valor de 'du' en 'C' es provisorio
     mientras que en 'S' es definitivo.
   - Insertar (v,0) en 'C'.
   . Mientras 'C' no es vacía:
     -- se obtiene y remueve de 'C' el par (u, du) tal que 'du' es mínimo
        entre todos los pares de 'C'.
     -- se inserta ese par en 'S'.
     -- para cada vecino 'w' de 'u' que no está en S sea dw' = du + d(u,w),
        donde d(u,v) es la distancia entre 'u' y 'w'.
        Si 'w' no está en 'C' se inserta (w,dw') en 'C'.
        Si 'w' está en 'C' en el par (w,dw) y dw' < dw entoces se actualiza
        'C' con el par con (w,dw') en lugar de (w,dw).
   - Para cada vétice 'u' que no pertenece a 'S' se inserta en 'S' el par
     (u, infinito).
   - Devolver 'S'.

 */
ArregloDoubles longitudesCaminosMasCortos(nat v, TGrafo g);

/*
  Devuelve un 'TConjunto' con los elementos que pertenecen a 'c1' y 'c2'.
  El 'TConjunto' resultado no comparte memoria ni con 'c1' no con 'c2'.
  El tiempo de ejecucion en el peor caso es O(n1 + n2 + n.log n),
  siendo 'n1' y 'n2' la cantidad de elementos de 'c1' y 'c2' respectivamente y
  'n' la del 'TConjunto' resultado.
 */
TConjunto interseccionDeConjuntos(TConjunto c1, TConjunto c2);

/*
  Devuelve una 'TCadena' con los elementos del nivel 'l' de 'b'.
  La raíz es el nivel 1.
  La 'TCadena' resultado debe estar ordenada de manera creciente según los
  componentes naturales de sus elementos.
  Precondición: l > 0.
  La 'TCadena' devuelta no comparte memoria con 'b'.
 */
TCadena nivelEnBinario(nat l, TBinario b);

/*
  Devuelve 'true' si y solo si en 'b' hay un camino desde la raiz hasta una
  hoja que sea compatible con 'c'.
  Decimos que una cadena y un camino son compatibles si tienen la misma
  longitud y al recorrer la cadena desde el inicio hasta el final y el camino
  desde la raíz hasta la hoja los componentes naturales de los respectivos
  elementos son iguales.
  Ver ejemplos en la letra.
  Si 'b' y 'c' son vacíos devuelve 'true'.
  El tiempo de ejecución es O(log n) en promedio, siendo 'n' es la cantidad de
  elementos de 'b'.
 */
bool esCamino(TCadena c, TBinario b);

/*
  Devuelve 'true' si y solo si en 'cad' hay un elemento cuyo campo natural es
  'elem'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
bool pertenece(nat elem, TCadena cad);

/*
  Devuelve la cantidad de elementos de 'cad'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
nat longitud(TCadena cad);

/*
  Devuelve 'true' si y solo si 'cad' está ordenada de forma no dereciente
  (creciente de manera no estricta) según las campos naturales de sus elementos.
  Si esVaciaVadena(cad) devuelve 'true'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
bool estaOrdenadaPorNaturales(TCadena cad);

/*
  Devuelve 'true' si y solo si los componentes naturales de algún par de
  elementos de 'cad' son iguales.
  El tiempo de ejecución en el peor caso es O(n^2), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
bool hayNatsRepetidos(TCadena cad);

/*
  Devuelve 'true' si y solo si 'c1' y 'c2' son iguales (es decir, si los
  elementos son iguales y en el mismo orden).
  Si esVaciaCadena(c1) y esVaciaCadena(c2) devuelve 'true'.
  El tiempo de ejecución en el peor caso es O(n1 + n2), siendo 'n1' u 'n2' la
  cantidad de elementos de 'c1' y 'c2' respectivamente.
 */
bool sonIgualesCadena(TCadena c1, TCadena c2);

/*
  Devuelve el resultado de concatenar 'c2' después de 'c1'.
  La 'TCadena' resultado no comparte memoria ni con 'c1' ni con 'c2'.
  El tiempo de ejecución en el peor caso es O(n1 + n2), siendo 'n1' u 'n2' la
  cantidad de elementos de 'c1' y 'c2' respectivamente.
 */
TCadena concatenar(TCadena c1, TCadena c2);

/*
  Se ordena 'cad' de manera creciente según los componentes naturales de sus
  elementos.
  Devuelve 'cad'
  Precondición: ! hayNatsRepetidos(cad)
  No se debe obtener ni devolver memoria de manera dinámica.
  Se debe mantener las relaciones de precedencia entre localizadores.
  Si esVaciaCadena(cad) no hace nada.
  El tiempo de ejecución en el peor caso es O(n^2), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCadena ordenar(TCadena cad);

/*
  Cambia todas las ocurrencias de 'original' por 'nuevo' en los elementos
  de 'cad'.
  Devuelve 'cad'
  No debe quedar memoria inaccesible.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCadena cambiarTodos(nat original, nat nuevo, TCadena cad);

/*
  Devuelve la 'TCadena' de elementos de 'cad' que cumplen
  "menor <= natInfo (elemento) <= mayor".
  El orden relativo de los elementos en la 'TCadena' resultado debe ser el mismo
  que en 'cad'.
  Precondición: estaOrdenadaPorNaturales (cad), 'menor' <= 'mayor',
  pertenece (menor, cad), pertenece (mayor, cad).
  La 'TCadena' resultado no comparte memoria con 'cad'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCadena subCadena(nat menor, nat mayor, TCadena cad);

#endif
