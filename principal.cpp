/*
  Módulo principal de la tarea 5.

Intérprete de comandos para probar los módulos.

Están creados una TCadena 'cad', un TLocalizador 'loc',  un TBinario 'b',
un TIterador 'it', una TPila 'p', una TColaAvls cavl, un TAvl 'avl', un
TConjunto 'conj', una TColaDePrioridad 'cp', un TMapping 'map',  y un TGrafo
'g'..

Cada comando tiene un nombre y una secuencia (posiblemente vacía) de parámetros.
Se asume que los comandos están bien formados. Esto implica que:
- el nombre es uno de los descritos más abajo;
- la cantidad y tipo de los parámetros cumplen con lo requerido.

Si un parámetro debe ser de tipo TInfo su formato cumple con lo descrito en
'infoATexto' del módulo 'info''.


El comando
Fin
termina el programa

El comando
# comentario
imprime comentario.

El comando
reiniciar
libera la memoria asignada a 'cad', 'b', 'it', 'p', 'cavl', 'avl', 'conj', 'cp',
'map' y 'g' y
los vuelve a crear.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#include "include/avl.h"
#include "include/binario.h"
#include "include/cadena.h"
#include "include/colaAvls.h"
#include "include/colaDePrioridad.h"
#include "include/conjunto.h"
#include "include/grafo.h"
#include "include/info.h"
#include "include/iterador.h"
#include "include/mapping.h"
#include "include/pila.h"
#include "include/usoTads.h"
#include "include/utils.h"

#include <assert.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h> // para srand, rand
#include <string.h>
#include <time.h>

#define MAX_PALABRA 32
#define MAX_LINEA 256

#define MAX_PILA 10
#define MAX_CP 10
#define MAX_MAP 10
#define MAX_N 10
#define MAX_M 30

/*
  Lee y devuelve un TInfo desde la entrada estándar.
  Se asume que la antrada cumple con el formato descrito en 'infoATexto' del
  módulo 'info''.
 */
TInfo leerInfo() {
  char simbolo = leerChar();
  assert(simbolo == '(');
  nat natural = leerNat();
  simbolo = leerChar();
  assert(simbolo == ',');
  double real = leerDouble();
  simbolo = leerChar();
  assert(simbolo == ')');
  (void)simbolo;
  return crearInfo(natural, real);
} // leerInfo

/*
  Lee y devuelve una TCadena desde la entrada estándar.
  Se asume que en la entrada hay un espacio en blanco después de cada elemento.
 */
TCadena leerCadena() {
  nat n = leerNat();
  TCadena res = crearCadena();
  for (nat i = 1; i <= n; i++) {
    TInfo info = leerInfo();
    res = insertarAlFinal(info, res);
  }
  return res;
} // leerCadena

struct tArregloTope {
  ArregloNats datos;
  nat tope;
};
typedef struct tArregloTope TArregloTope;

/*
  Lee una secuencia de nat desde la entrada estándar y las devuelve en un
  arreglo con tope.
  Primero lee la cantidad de elemntos.
  Después de cada elemento hay un espacio en blanco.
  La secuencia está ordenada de manera creciente estricta según los campos
  naturales.
 */
TArregloTope leerArregloOrdenado() {
  nat n = leerNat();
  TArregloTope res;
  res.tope = n;
  if (n == 0) {
    res.datos = NULL;
  } else {
    res.datos = new nat[n];
    for (nat i = 0; i < n; i++) {
      res.datos[i] = leerNat();
    }
  }

  bool estaOrdenado = true;
  nat pos = 0;
  while (estaOrdenado && pos + 1 < res.tope) {
    if (res.datos[pos] < res.datos[pos + 1])
      pos++;
    else
      estaOrdenado = false;
  }
  if (!estaOrdenado) {
    printf("Secuencia no ordenada. \n");
    delete[] res.datos;
    res.tope = 0;
  }
  return res;
} // leerArregloOrdenado

/* Inserta subárboles. */
TBinario insSubArbol(nat dato, nat inc, TBinario a) {
  a = insertarEnBinario(crearInfo(dato, (double)dato), a);
  if (inc > 1) {
    inc >>= 1;
    a = insSubArbol(dato - inc, inc, a);
    a = insSubArbol(dato + inc, inc, a);
  }
  return a;
} // insSubArbol

// Libera la memoria de 'cavl' y de sus binarios. //
void destruirColaAvls(TColaAvls cavl) {
  while (!estaVaciaColaAvls(cavl)) {
    TAvl f = frente(cavl);
    desencolar(cavl);
    liberarAvl(f);
  }
  liberarColaAvls(cavl);
} // destruirColaAvls

// programa principal
int main() {

  TGrafo g = crearGrafo(MAX_N, MAX_M);
  TColaDePrioridad cp = crearCP(MAX_CP);
  TMapping map = crearMap(MAX_MAP);
  TAvl avl = crearAvl();
  TConjunto conj = crearConjunto();
  TColaAvls cavl = crearColaAvls();
  TPila p = crearPila(MAX_PILA);
  TIterador it = crearIterador();
  TBinario b = crearBinario();
  TCadena cad = crearCadena();
  TLocalizador loc = inicioCadena(cad); // no válido porque cad es vacía

  char restoLinea[MAX_LINEA];
  char nom_comando[MAX_PALABRA];

  int cont_comandos = 0;
  bool salir = false;
  while (!salir) {
    // mostrar el prompt
    cont_comandos++;
    printf("%u>", cont_comandos);

    // leer el comando
    leerChars(nom_comando);

    // procesar el comando
    if (!strcmp(nom_comando, "Fin")) {
      salir = true;
      printf("Fin.\n");
      // comentario
    } else if (!strcmp(nom_comando, "#")) {
      leerRestoLinea(restoLinea);
      printf("# %s.\n", restoLinea);

      // operaciones de grafo
    } else if (!strcmp(nom_comando, "cantidadVertices")) {
      printf("%d.\n", cantidadVertices(g));

    } else if (!strcmp(nom_comando, "hayMParejas")) {
      printf("%s.\n", hayMParejas(g) ? "Hay M parejas" : "NO hay M parejas");

    } else if (!strcmp(nom_comando, "hacerVecinos")) {
      nat v1 = leerNat(), v2 = leerNat();
      assert((1 <= v1) && (v1 <= cantidadVertices(g)));
      assert((1 <= v2) && (v2 <= cantidadVertices(g)));
      assert(v1 != v2);
      assert(!sonVecinos(v1, v2, g));
      assert(!hayMParejas(g));
      double d = leerDouble();
      assert(d >= 0);
      g = hacerVecinos(v1, v2, d, g);
      printf("Nuevos vecinos: %d %d %4.2f.\n", v1, v2, d);

    } else if (!strcmp(nom_comando, "sonVecinos")) {
      nat v1 = leerNat(), v2 = leerNat();
      assert((1 <= v1) && (v1 <= cantidadVertices(g)));
      assert((1 <= v2) && (v2 <= cantidadVertices(g)));
      printf("%s vecinos.\n", sonVecinos(v1, v2, g) ? "Son" : "NO son");

    } else if (!strcmp(nom_comando, "distancia")) {
      nat v1 = leerNat(), v2 = leerNat();
      assert((1 <= v1) && (v1 <= cantidadVertices(g)));
      assert((1 <= v2) && (v2 <= cantidadVertices(g)));
      assert(sonVecinos(v1, v2, g));
      printf("%.2lf\n", distancia(v1, v2, g));

    } else if (!strcmp(nom_comando, "vecinos")) {
      nat v = leerNat();
      assert((1 <= v) && (v <= cantidadVertices(g)));
      TIterador vs = vecinos(v, g);
      vs = reiniciarIterador(vs);
      while (estaDefinidaActual(vs)) {
        printf("%d ", actualEnIterador(vs));
        vs = avanzarIterador(vs);
      }
      printf("\n");
      liberarIterador(vs);

      // operaciones de pila

    } else if (!strcmp(nom_comando, "apilar")) {
      if (estaLlenaPila(p))
        printf("p está llena.\n");
      else {
        nat num = leerNat();
        p = apilar(num, p);
        printf("Apilado.\n");
      }

    } else if (!strcmp(nom_comando, "cima")) {
      assert(!estaVaciaPila(p));
      printf("%d.\n", cima(p));

    } else if (!strcmp(nom_comando, "desapilar")) {
      if (estaVaciaPila(p))
        printf("p está vacía.\n");
      else {
        p = desapilar(p);
        printf("Desapilado.\n");
      }

    } else if (!strcmp(nom_comando, "estaVaciaPila")) {
      printf("p %s vacia.\n", estaVaciaPila(p) ? "está" : "NO está");

    } else if (!strcmp(nom_comando, "estaLlenaPila")) {
      printf("p %s llena.\n", estaLlenaPila(p) ? "está" : "NO está");

      // operaciones de cola_avl

    } else if (!strcmp(nom_comando, "encolar")) {
      TAvl nuevo = crearAvl();
      nat elem = leerNat();
      while (elem != 0) {
        nuevo = insertarEnAvl(elem, nuevo);
        elem = leerNat();
      }
      cavl = encolar(nuevo, cavl);
      printf("Encolado.\n");

    } else if (!strcmp(nom_comando, "frente")) {
      assert(!estaVaciaColaAvls(cavl));
      TAvl f = frente(cavl);
      if (estaVacioAvl(f))
        printf("Avl vacío.\n");
      else
        printf("%d\n", raizAvl(f));

    } else if (!strcmp(nom_comando, "desencolar")) {
      if (estaVaciaColaAvls(cavl))
        printf("cb está vacía.\n");
      else {
        TAvl f = frente(cavl);
        cavl = desencolar(cavl);
        liberarAvl(f);
        printf("Desencolado.\n");
      }

    } else if (!strcmp(nom_comando, "estaVaciaColaAvls")) {
      printf("cavl %s vacia.\n", estaVaciaColaAvls(cavl) ? "está" : "NO está");

      // operaciones de avl
    } else if (!strcmp(nom_comando, "estaVacioAvl")) {
      printf("%s.\n", estaVacioAvl(avl) ? "Vacio" : "No vacío");

    } else if (!strcmp(nom_comando, "insertarEnAvl")) {
      nat elem = leerNat();
      assert(estaVacioAvl(buscarEnAvl(elem, avl)));
      avl = insertarEnAvl(elem, avl);
      printf("Insertado.\n");

    } else if (!strcmp(nom_comando, "buscarEnAvl")) {
      nat elem = leerNat();
      TAvl sub = buscarEnAvl(elem, avl);
      if (estaVacioAvl(sub))
        printf("sub es vacío.\n");
      else {
        printf("%d\n", raizAvl(sub));
        TAvl hijo;
        hijo = izqAvl(sub);
        if (estaVacioAvl(hijo))
          printf(" | ");
        else
          printf("%d", raizAvl(hijo));
        printf(" - ");
        hijo = derAvl(sub);
        if (estaVacioAvl(hijo))
          printf(" | ");
        else {
          printf("%d", raizAvl(hijo));
        }
        printf("\n");
      }

    } else if (!strcmp(nom_comando, "raizAvl")) {
      assert(!estaVacioAvl(avl));
      printf("%d\n", raizAvl(avl));

    } else if (!strcmp(nom_comando, "izqAvl")) {
      assert(!estaVacioAvl(avl));
      TAvl subIzq = izqAvl(avl);
      if (estaVacioAvl(subIzq))
        printf("Izquierdo es vacío\n");
      else {
        printf("%d\n", raizAvl(subIzq));
      }

    } else if (!strcmp(nom_comando, "derAvl")) {
      assert(!estaVacioAvl(avl));
      TAvl subDer = derAvl(avl);
      if (estaVacioAvl(subDer))
        printf("Derecho es vacío\n");
      else {
        printf("%d\n", raizAvl(subDer));
      }

    } else if (!strcmp(nom_comando, "cantidadEnAvl")) {
      printf("Cantidad en avl: %d.\n", cantidadEnAvl(avl));

    } else if (!strcmp(nom_comando, "alturaDeAvl")) {
      printf("Altura de avl: %d.\n", alturaDeAvl(avl));

    } else if (!strcmp(nom_comando, "enOrdenAvl")) {
      TIterador itAvl = enOrdenAvl(avl);
      itAvl = reiniciarIterador(itAvl);
      if (!estaDefinidaActual(itAvl)) {
        printf("No hay elementos en el avl.\n");
      } else {
        do {
          printf("%d ", actualEnIterador(itAvl));
          itAvl = avanzarIterador(itAvl);
        } while (estaDefinidaActual(itAvl));
        printf("\n");
      }
      liberarIterador(itAvl);

    } else if (!strcmp(nom_comando, "arregloAAvl")) {
      TArregloTope elems = leerArregloOrdenado();
      liberarAvl(avl);
      if (elems.tope == 0)
        avl = crearAvl();
      else {
        avl = arregloAAvl(elems.datos, elems.tope);
        delete[] elems.datos;
      }
      printf("\n");

    } else if (!strcmp(nom_comando, "avlMin")) {
      nat h = leerNat();
      TAvl min = avlMin(h);
      printf("\n");
      imprimirAvl(min);
      printf("Cantidad: %d.\n", cantidadEnAvl(min));
      liberarAvl(min);

    } else if (!strcmp(nom_comando, "imprimirAvl")) {
      printf("\n");
      imprimirAvl(avl);

      // operaciones de conjunto

    } else if (!strcmp(nom_comando, "estaVacioConjunto")) {
      printf("%s.\n", estaVacioConjunto(conj) ? "Vacio" : "No vacío");

    } else if (!strcmp(nom_comando, "cardinalidad")) {
      printf("%d.\n", cardinalidad(conj));

    } else if (!strcmp(nom_comando, "perteneceAConjunto")) {
      nat elem = leerNat();
      printf("%s.\n",
             perteneceAConjunto(elem, conj) ? "Pertenece" : "No pertenece");

    } else if (!strcmp(nom_comando, "singleton")) {
      nat elem = leerNat();
      liberarConjunto(conj);
      conj = singleton(elem);
      printf("Creado el singleton.\n");

    } else if (!strcmp(nom_comando, "arregloAConjunto")) {
      TArregloTope elems = leerArregloOrdenado();
      liberarConjunto(conj);
      if (elems.tope == 0)
        conj = crearConjunto();
      else {
        conj = arregloAConjunto(elems.datos, elems.tope);
        delete[] elems.datos;
      }
      printf("Arreglo a conjunto con %d elementos.\n", elems.tope);

    } else if (!strcmp(nom_comando, "unionDeConjuntos")) {
      TArregloTope elems = leerArregloOrdenado();
      TConjunto a;
      if (elems.tope == 0)
        a = crearConjunto();
      else {
        a = arregloAConjunto(elems.datos, elems.tope);
        delete[] elems.datos;
      }
      TConjunto alias = conj;
      conj = unionDeConjuntos(alias, a);
      liberarConjunto(alias);
      liberarConjunto(a);
      printf("Union.\n");

    } else if (!strcmp(nom_comando, "diferenciaDeConjuntos")) {
      TArregloTope elems = leerArregloOrdenado();
      TConjunto a;
      if (elems.tope == 0)
        a = crearConjunto();
      else {
        a = arregloAConjunto(elems.datos, elems.tope);
        delete[] elems.datos;
      }
      TConjunto alias = conj;
      conj = diferenciaDeConjuntos(alias, a);
      liberarConjunto(alias);
      liberarConjunto(a);
      printf("Diferencia.\n");

    } else if (!strcmp(nom_comando, "iteradorDeConjunto")) {
      TIterador itC = iteradorDeConjunto(conj);
      itC = reiniciarIterador(itC);
      if (!estaDefinidaActual(itC)) {
        printf("No hay elementos en el conjunto.\n");
      } else {
        do {
          printf("%d ", actualEnIterador(itC));
          itC = avanzarIterador(itC);
        } while (estaDefinidaActual(itC));
        printf("\n");
      }
      liberarIterador(itC);

      // operaciones de map
    } else if (!strcmp(nom_comando, "asociarEnMap")) {
      assert(!estaLlenoMap(map));
      nat clave = leerNat();
      double valor = leerDouble();
      assert(!existeAsociacionEnMap(clave, map));
      map = asociarEnMap(clave, valor, map);
      printf("Establecida la asociación.\n");

    } else if (!strcmp(nom_comando, "desasociarEnMap")) {
      nat clave = leerNat();
      assert(existeAsociacionEnMap(clave, map));
      map = desasociarEnMap(clave, map);
      printf("Eliminada la asociación.\n");

    } else if (!strcmp(nom_comando, "existeAsociacionEnMap")) {
      nat clave = leerNat();
      printf("%s.\n", existeAsociacionEnMap(clave, map)
                          ? "Existe asociacion"
                          : "No existe asociacion");

    } else if (!strcmp(nom_comando, "valorEnMap")) {
      nat clave = leerNat();
      assert(existeAsociacionEnMap(clave, map));
      printf("%.2lf\n", valorEnMap(clave, map));

    } else if (!strcmp(nom_comando, "estaLlenoMap")) {
      printf("%s.\n", estaLlenoMap(map) ? "LLeno" : "No lleno");

      // operaciones de cp

    } else if (!strcmp(nom_comando, "insertarEnCP")) {
      nat elem = leerNat();
      double valor = leerDouble();
      assert((1 <= elem) && (elem <= rangoCP(cp)));
      assert(!estaEnCP(elem, cp));
      cp = insertarEnCP(elem, valor, cp);
      printf("Se insertó el elemento.\n");

    } else if (!strcmp(nom_comando, "actualizarEnCP")) {
      nat elem = leerNat();
      double valor = leerDouble();
      assert(estaEnCP(elem, cp));
      cp = actualizarEnCP(elem, valor, cp);
      printf("Se actualizó el valor.\n");

    } else if (!strcmp(nom_comando, "eliminarPrioritario")) {
      assert(!estaVaciaCP(cp));
      cp = eliminarPrioritario(cp);
      printf("Eliminado.\n");

    } else if (!strcmp(nom_comando, "prioritario")) {
      assert(!estaVaciaCP(cp));
      printf("%d\n", prioritario(cp));

    } else if (!strcmp(nom_comando, "estaVaciaCP")) {
      printf("%s.\n", estaVaciaCP(cp) ? "Vacia" : "No vacía");

    } else if (!strcmp(nom_comando, "rangoCP")) {
      printf("%d.\n", rangoCP(cp));

    } else if (!strcmp(nom_comando, "estaEnCP")) {
      nat elem = leerNat();
      printf("%s.\n", estaEnCP(elem, cp) ? "Está" : "No está");

    } else if (!strcmp(nom_comando, "prioridad")) {
      nat elem = leerNat();
      assert(estaEnCP(elem, cp));
      printf("%.2lf.\n", prioridad(elem, cp));

      // operaciones de iterador

    } else if (!strcmp(nom_comando, "agregarAIterador")) {
      nat elem = leerNat();
      it = agregarAIterador(elem, it);
      printf("Agregando.\n");

    } else if (!strcmp(nom_comando, "reiniciarIterador")) {
      it = reiniciarIterador(it);
      printf("Reiniciado.\n");

    } else if (!strcmp(nom_comando, "avanzarIterador")) {
      it = avanzarIterador(it);
      printf("Avanzando.\n");

    } else if (!strcmp(nom_comando, "actualEnIterador")) {
      assert(estaDefinidaActual(it));
      printf("%d\n", actualEnIterador(it));

    } else if (!strcmp(nom_comando, "estaDefinidaActual")) {
      printf("Actual de it %s definida.\n",
             estaDefinidaActual(it) ? "está" : "NO está");

      // operaciones de binario

    } else if (!strcmp(nom_comando, "insertarEnBinario")) {
      TInfo info = leerInfo();
      assert(esVacioBinario(buscarSubarbol(natInfo(info), b)));
      b = insertarEnBinario(info, b);
      printf("Insertado.\n");

    } else if (!strcmp(nom_comando, "mayor")) {
      assert(!esVacioBinario(b));
      ArregloChars txtInfo = infoATexto(mayor(b));
      printf("%s\n", txtInfo);
      delete[] txtInfo;

    } else if (!strcmp(nom_comando, "removerMayor")) {
      assert(!esVacioBinario(b));
      TInfo info = mayor(b);
      b = removerMayor(b);
      liberarInfo(info);
      printf("Removido el mayor.\n");

    } else if (!strcmp(nom_comando, "removerDeBinario")) {
      nat elem = leerNat();
      assert(!esVacioBinario(buscarSubarbol(elem, b)));
      b = removerDeBinario(elem, b);
      printf("Removido.\n");

    } else if (!strcmp(nom_comando, "esVacioBinario")) {
      printf("%s.\n", esVacioBinario(b) ? "Vacio" : "No vacío");

    } else if (!strcmp(nom_comando, "esAvl")) {
      printf("%s.\n", esAvl(b) ? "AVL" : "No AVL");

    } else if (!strcmp(nom_comando, "raiz")) {
      assert(!esVacioBinario(b));
      TInfo info = raiz(b);
      ArregloChars txtInfo = infoATexto(info);
      printf("%s\n", txtInfo);
      delete[] txtInfo;

    } else if (!strcmp(nom_comando, "izquierdo")) {
      assert(!esVacioBinario(b));
      if (esVacioBinario(izquierdo(b)))
        printf("izquierdo de b es vacío.\n");
      else {
        TInfo info = raiz(izquierdo(b));
        ArregloChars txtInfo = infoATexto(info);
        printf("%s\n", txtInfo);
        delete[] txtInfo;
      }

    } else if (!strcmp(nom_comando, "derecho")) {
      assert(!esVacioBinario(b));
      if (esVacioBinario(derecho(b)))
        printf("derecho de b es vacío.\n");
      else {
        TInfo info = raiz(derecho(b));
        ArregloChars txtInfo = infoATexto(info);
        printf("%s\n", txtInfo);
        delete[] txtInfo;
      }

    } else if (!strcmp(nom_comando, "buscarSubarbol")) {
      nat elem = leerNat();
      TBinario sub = buscarSubarbol(elem, b);
      if (esVacioBinario(sub))
        printf("sub es vacío.\n");
      else {
        ArregloChars txtInfo = infoATexto(raiz(sub));
        printf("%s\n", txtInfo);
        delete[] txtInfo;
      }

    } else if (!strcmp(nom_comando, "alturaBinario")) {
      printf("%d.\n", alturaBinario(b));

    } else if (!strcmp(nom_comando, "cantidadBinario")) {
      printf("%d.\n", cantidadBinario(b));

    } else if (!strcmp(nom_comando, "sumaUltimosPositivos")) {
      nat ult = leerNat();
      printf("%4.2lf\n", sumaUltimosPositivos(ult, b));

    } else if (!strcmp(nom_comando, "linealizacion")) {
      TCadena lineal = linealizacion(b);
      imprimirCadena(lineal);
      liberarCadena(lineal);

    } else if (!strcmp(nom_comando, "menores")) {
      nat clave = leerNat();
      TBinario filtro = menores(clave, b);
      imprimirBinario(filtro);
      liberarBinario(filtro);

    } else if (!strcmp(nom_comando, "imprimirBinario")) {
      imprimirBinario(b);

      // operaciones de cadena

    } else if (!strcmp(nom_comando, "esLocalizador")) {
      printf("loc%s válido.\n", esLocalizador(loc) ? "" : " no");

    } else if (!strcmp(nom_comando, "esVaciaCadena")) {
      printf("cad%s.\n", esVaciaCadena(cad) ? " vacia" : " no vacia");

    } else if (!strcmp(nom_comando, "inicioCadena")) {
      loc = inicioCadena(cad);
      printf("loc al inicio.\n");

    } else if (!strcmp(nom_comando, "finalCadena")) {
      loc = finalCadena(cad);
      printf("loc al final.\n");

    } else if (!strcmp(nom_comando, "infoCadena")) {
      assert(localizadorEnCadena(loc, cad));
      ArregloChars txtInfo = infoATexto(infoCadena(loc, cad));
      printf("%s\n", txtInfo);
      delete[] txtInfo;

    } else if (!strcmp(nom_comando, "esFinalCadena")) {
      printf("loc%s es final de cad.\n", esFinalCadena(loc, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "esInicioCadena")) {
      printf("loc%s es incio de cad.\n", esInicioCadena(loc, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "siguiente")) {
      assert(localizadorEnCadena(loc, cad));
      loc = siguiente(loc, cad);
      printf("loc al siguiente.\n");

    } else if (!strcmp(nom_comando, "anterior")) {
      assert(localizadorEnCadena(loc, cad));
      loc = anterior(loc, cad);
      printf("loc al anterior.\n");

    } else if (!strcmp(nom_comando, "insertarAlFinal")) {
      cad = insertarAlFinal(leerInfo(), cad);
      printf("Insertado al final.\n");

    } else if (!strcmp(nom_comando, "insertarAntes")) {
      assert(localizadorEnCadena(loc, cad));
      cad = insertarAntes(leerInfo(), loc, cad);
      printf("Insertado antes de loc.\n");

    } else if (!strcmp(nom_comando, "removerDeCadena")) {
      assert(localizadorEnCadena(loc, cad));
      cad = removerDeCadena(loc, cad);
      printf("Removido.\n");

    } else if (!strcmp(nom_comando, "imprimirCadena")) {
      imprimirCadena(cad);

    } else if (!strcmp(nom_comando, "kesimo")) {
      nat k = leerNat();
      loc = kesimo(k, cad);
      if (esLocalizador(loc))
        printf("loc en la posición %d.\n", k);
      else
        printf("loc quedó no válido.\n");

    } else if (!strcmp(nom_comando, "localizadorEnCadena")) {
      printf("loc%s pertenece a cad.\n",
             localizadorEnCadena(loc, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "precedeEnCadena")) {
      printf("loc1%s precede a loc.\n",
             precedeEnCadena(kesimo(leerNat(), cad), loc, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "insertarSegmentoDespues")) {
      assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
      cad = insertarSegmentoDespues(leerCadena(), loc, cad);
      printf("Segmento insertado después de loc.\n");

    } else if (!strcmp(nom_comando, "copiarSegmento")) {
      nat k1 = leerNat(), k2 = leerNat();
      assert((1 <= k1) && (k1 <= k2));
      TLocalizador desde = kesimo(k1, cad), hasta = kesimo(k2, cad);
      assert(esVaciaCadena(cad) || precedeEnCadena(desde, hasta, cad));
      TCadena sgm = copiarSegmento(desde, hasta, cad);
      imprimirCadena(sgm);
      liberarCadena(sgm);

    } else if (!strcmp(nom_comando, "borrarSegmento")) {
      nat k1 = leerNat(), k2 = leerNat();
      assert((1 <= k1) && (k1 <= k2));
      TLocalizador desde = kesimo(k1, cad), hasta = kesimo(k2, cad);
      assert(esVaciaCadena(cad) || precedeEnCadena(desde, hasta, cad));
      cad = borrarSegmento(desde, hasta, cad);
      printf("Segmento borrado.\n");

    } else if (!strcmp(nom_comando, "cambiarEnCadena")) {
      assert(localizadorEnCadena(loc, cad));
      TInfo anteriorInfo = infoCadena(loc, cad);
      cad = cambiarEnCadena(leerInfo(), loc, cad);
      liberarInfo(anteriorInfo);
      printf("Cambio.\n");

    } else if (!strcmp(nom_comando, "intercambiar")) {
      nat k1 = leerNat(), k2 = leerNat();
      assert((1 <= k1) && (1 <= k2));
      TLocalizador loc1 = kesimo(k1, cad), loc2 = kesimo(k2, cad);
      assert(localizadorEnCadena(loc1, cad) && localizadorEnCadena(loc2, cad));
      cad = intercambiar(loc1, loc2, cad);
      printf("Intercambio.\n");

    } else if (!strcmp(nom_comando, "siguienteClave")) {
      assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
      int clave = leerNat();
      loc = siguienteClave(clave, loc, cad);
      if (esLocalizador(loc))
        printf("loc avanzó buscando %d.\n", clave);
      else
        printf("loc quedó no válido.\n");

    } else if (!strcmp(nom_comando, "anteriorClave")) {
      assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
      int clave = leerNat();
      loc = anteriorClave(clave, loc, cad);
      if (esLocalizador(loc))
        printf("loc retrocedió buscando %d.\n", clave);
      else
        printf("loc quedó no válido.\n");

    } else if (!strcmp(nom_comando, "menorEnCadena")) {
      assert(localizadorEnCadena(loc, cad));
      loc = menorEnCadena(loc, cad);
      printf("El menor es %d.\n", natInfo(infoCadena(loc, cad)));

      // operaciones de usoTads

      // nueva
    } else if (!strcmp(nom_comando, "accesibles")) {
      nat v = leerNat();
      assert((1 <= v) && (v <= cantidadVertices(g)));
      ArregloBools acs = accesibles(v, g);
      for (nat i = 1; i <= cantidadVertices(g); i++)
        printf("%d ", (acs[i] ? 1 : 0));
      printf("\n");
      delete[] acs;

      // nueva
    } else if (!strcmp(nom_comando, "longitudesCaminosMasCortos")) {
      nat v = leerNat();
      assert((1 <= v) && (v <= cantidadVertices(g)));
      ArregloDoubles ds = longitudesCaminosMasCortos(v, g);
      for (nat i = 1; i <= cantidadVertices(g); i++)
        if (ds[i] == DBL_MAX)
          printf("INF ");
        else
          printf("%.2lf ", ds[i]);
      printf("\n");
      delete[] ds;

    } else if (!strcmp(nom_comando, "interseccionDeConjuntos")) {
      TArregloTope elems = leerArregloOrdenado();
      TConjunto a;
      if (elems.tope == 0)
        a = crearConjunto();
      else {
        a = arregloAConjunto(elems.datos, elems.tope);
        delete[] elems.datos;
      }
      TConjunto alias = conj;
      conj = interseccionDeConjuntos(alias, a);
      liberarConjunto(alias);
      liberarConjunto(a);
      printf("Intersección.\n");

    } else if (!strcmp(nom_comando, "esCamino")) {
      TCadena camino = leerCadena();
      printf("%s camino.\n", esCamino(camino, b) ? "Es" : "NO es");
      liberarCadena(camino);

    } else if (!strcmp(nom_comando, "nivelEnBinario")) {
      nat l = leerNat();
      if (l == 0) {
        printf("l = 0.\n");
      } else {
        TCadena nivel = nivelEnBinario(l, b);
        imprimirCadena(nivel);
        liberarCadena(nivel);
      }

    } else if (!strcmp(nom_comando, "pertenece")) {
      int i = leerNat();
      printf("%d%s pertenece a cad.\n", i, pertenece(i, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "longitud")) {
      printf("Longitud: %u\n", longitud(cad));

    } else if (!strcmp(nom_comando, "estaOrdenadaPorNaturales")) {
      printf("cad%s.\n",
             estaOrdenadaPorNaturales(cad) ? " ordenada" : " no ordenada");

    } else if (!strcmp(nom_comando, "hayNatsRepetidos")) {
      printf("En cad%s.\n", hayNatsRepetidos(cad)
                                ? " hay naturales repetidos"
                                : " no hay naturales repetidos");

    } else if (!strcmp(nom_comando, "sonIgualesCadena")) {
      TCadena otra = leerCadena();
      printf("%s.\n",
             sonIgualesCadena(cad, otra) ? "Son iguales" : "No son iguales");
      liberarCadena(otra);

    } else if (!strcmp(nom_comando, "concatenar")) {
      TCadena otra = leerCadena();
      TCadena conc = concatenar(cad, otra);
      imprimirCadena(conc);
      liberarCadena(conc);
      liberarCadena(otra);

    } else if (!strcmp(nom_comando, "ordenar")) {
      assert(!hayNatsRepetidos(cad));
      cad = ordenar(cad);
      printf("Quedó ordenada.\n");

    } else if (!strcmp(nom_comando, "cambiarTodos")) {
      nat original = leerNat(), nuevo = leerNat();
      cad = cambiarTodos(original, nuevo, cad);
      printf("Cambiados.\n");

    } else if (!strcmp(nom_comando, "subCadena")) {
      assert(estaOrdenadaPorNaturales(cad));
      nat menor = leerNat(), mayor = leerNat();
      assert(menor <= mayor);
      assert(pertenece(menor, cad) && pertenece(mayor, cad));
      TCadena sub = subCadena(menor, mayor, cad);
      imprimirCadena(sub);
      liberarCadena(sub);

      // test de tiempo
    } else if (!strcmp(nom_comando, "tiempo_grafo")) {
      nat tamanio = leerNat();
      TGrafo gt = crearGrafo(tamanio, 2 * tamanio);
      nat v = tamanio / 2;
      for (nat i = 1; i < v; i++)
        hacerVecinos(i, v, 10, gt);
      for (nat i = tamanio; i > v; i--)
        hacerVecinos(i, v, 10, gt);
      liberarGrafo(gt);
      printf("\n");

    } else if (!strcmp(nom_comando, "tiempo_map")) {
      nat tamanio = leerNat();
      const nat MODULO = 1000000;
      srand(1);
      TMapping a = crearMap(tamanio);
      printf("prueba asociar, desasociar, existeAsociacion. \n");
      for (nat j = 1; j < tamanio; j++) {
        nat rnd = rand() % MODULO;
        if (existeAsociacionEnMap(rnd, a))
          a = desasociarEnMap(rnd, a);
        a = asociarEnMap(rnd, (double)rnd, a);
      }
      printf("prueba existeAsociacion, valorEnMap. \n");
      for (nat j = 0; j < MODULO; j++) {
        nat rnd = rand() % MODULO;
        if (existeAsociacionEnMap(rnd, a))
          valorEnMap(rnd, a);
      }
      liberarMap(a);

    } else if (!strcmp(nom_comando, "tiempo_cp")) {
      nat N = leerNat();
      printf("\n prueba 1. \n");
      TColaDePrioridad a = crearCP(N);
      for (nat i = N; i >= 1; i--) {
        insertarEnCP(i, (double)i, a);
      }
      for (nat i = 1; i <= N; i++)
        eliminarPrioritario(a);
      liberarCP(a);

      printf(" prueba 2. \n");
      a = crearCP(N);
      for (nat i = 1; i <= N; i++) {
        insertarEnCP(i, (double)i, a);
      }
      for (nat i = 1; i <= N; i++)
        eliminarPrioritario(a);
      liberarCP(a);

      printf(" prueba 3. \n");
      a = crearCP(N);
      insertarEnCP(N, (double)N, a);
      for (nat i = 1; i <= N; i++) {
        insertarEnCP(1, 1.0, a);
        eliminarPrioritario(a);
        prioritario(a);
      }
      liberarCP(a);

      printf(" prueba 4. \n");
      a = crearCP(N);
      insertarEnCP(1, 1.0, a);
      insertarEnCP(N, (double)N, a);
      for (nat i = 1; i <= N; i++) {
        estaEnCP(1, a);
        estaEnCP(N / 2, a);
        estaEnCP(N, a);
      }
      liberarCP(a);

    } else if (!strcmp(nom_comando, "tiempo_sumaUltimosPositivos")) {
      nat min = leerNat(), max = leerNat(), iter = leerNat(),
          timeout = leerNat();
      printf("\n Construyendo el árbol. \n");
      TBinario a = crearBinario();
      for (nat i = max; i > min; i--)
        a = insertarEnBinario(crearInfo(i, (double)i), a);
      printf(" Obteniendo suma ultimos positivos. \n");

      clock_t tm = clock();
      for (nat i = 0; i < iter; i++)
        sumaUltimosPositivos(i, a);
      tm = clock() - tm;
      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);

      printf(" Liberando binario. \n");
      liberarBinario(a);

    } else if (!strcmp(nom_comando, "tiempo_esAvl")) {
      nat raiz = leerNat(), dosH = leerNat(), iter = leerNat(),
          timeout = leerNat();
      printf("\n Construyendo el árbol. \n");
      TBinario a = crearBinario();
      a = insSubArbol(raiz, dosH, a);
      printf(" Evaluando si es AVL. \n");

      clock_t tm = clock();
      for (nat i = 0; i < iter; i++)
        esAvl(a);
      tm = clock() - tm;
      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido: %.1f > %d \n", tiempo, timeout);

      printf(" Liberando binario. \n");
      liberarBinario(a);

    } else if (!strcmp(nom_comando, "reiniciar")) {
      liberarCadena(cad);
      cad = crearCadena();
      loc = inicioCadena(cad);
      liberarBinario(b);
      b = crearBinario();
      liberarPila(p);
      p = crearPila(MAX_PILA);
      liberarAvl(avl);
      avl = crearAvl();
      destruirColaAvls(cavl);
      cavl = crearColaAvls();
      liberarIterador(it);
      it = crearIterador();
      liberarConjunto(conj);
      conj = crearConjunto();
      liberarCP(cp);
      cp = crearCP(MAX_CP);
      liberarMap(map);
      map = crearMap(MAX_MAP);
      liberarGrafo(g);
      g = crearGrafo(MAX_N, MAX_M);
      printf("Estructuras reiniciadas.\n");

    } else {
      printf("Comando no reconocido.\n");
    } // if
    fgets(restoLinea, MAX_LINEA + 1, stdin);
  } // while

  liberarCadena(cad);
  liberarBinario(b);
  liberarIterador(it);
  liberarPila(p);
  liberarAvl(avl);
  destruirColaAvls(cavl);
  liberarConjunto(conj);
  liberarCP(cp);
  liberarMap(map);
  liberarGrafo(g);
  return 0;
} // main
