#include "../include/colaDePrioridad.h"
#include "../include/usoTads.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/binario.h"

#include <assert.h>
#include <stdlib.h>
#include <float.h>


ArregloBools accesibles_aux(nat v, TGrafo g, ArregloBools &res) {
	res[v] = true;
	TIterador iter = vecinos(v, g);
	iter = reiniciarIterador(iter);
	while (estaDefinidaActual(iter)) {
		if (res[actualEnIterador(iter)] == false) {
			res = accesibles_aux(actualEnIterador(iter), g, res);
		}
		iter = avanzarIterador(iter);
	}
	liberarIterador(iter);
	return res;
}

ArregloBools accesibles(nat v, TGrafo g) {
	nat n = cantidadVertices(g);
	ArregloBools res = new bool [n + 1];
	for (nat i = 0; i <= n; i = i + 1) {
		res[i] = false;
	}
	res = accesibles_aux(v, g, res);
	return res;
}

/*ArregloDoubles longitudesCaminosMasCortos(nat v, TGrafo g) {
	assert(1 <= v);
	assert(v <= cantidadVertices(g));
	nat n = cantidadVertices(g);
	double ceninela = 0.333333222221111;
	ArregloDoubles S = new double [n + 1];
	for (nat j = 0; j <= n; j = j + 1) {
		S[j] = ceninela;
	}
	ArregloDoubles C = new double [n + 1];
	for (nat k = 0; k <= n; k = k + 1) {
		C[k] = ceninela;
	}
	C[v] = 0.0;
	nat C_cant = 1;

	while (C_cant != 0) {
		nat p = 0;
		nat ver;
		double ar = 0.00;
		while (p <= n) {
			if ((C[p] != ceninela) && (C[p] <= ar)) {
				ar = C[p];
				ver = p;
			}
			p = p + 1;
		}
		C[ver] = ceninela;
		C_cant = C_cant - 1;
		S[ver] = ar;
		TIterador iter = vecinos(ver, g);
		iter = reiniciarIterador(iter);
		while (estaDefinidaActual(iter)) {
			if (S[actualEnIterador(iter)] == ceninela) {
				double ar_n = ar + distancia(ver, actualEnIterador(iter), g);
				if (C[actualEnIterador(iter)] == ceninela) {
					C[actualEnIterador(iter)] = ar_n;
				} else {
					if (ar_n < ar) {
						C[actualEnIterador(iter)] = ar_n;
					}
				}
			}
			iter = avanzarIterador(iter);
		}
		liberarIterador(iter);
		nat contador = 0;
		for (nat g = 0; g <= n; g++) {
			if (C[g] != ceninela) {
				contador = contador + 1;
			}
		}
		C_cant = contador;
	}
	delete [] C;
	S[0] = DBL_MAX;
	for (nat i = 0; i <= n; i = i + 1) {
		if (S[i] == ceninela) {
			S[i] = DBL_MAX;
		}
	}
	return S;
}*/

ArregloDoubles longitudesCaminosMasCortos(nat v, TGrafo g) {
	assert(1 <= v);
	assert(v <= cantidadVertices(g));
	nat n = cantidadVertices(g);
	double ceninela = 0.333333222221111;
	ArregloDoubles S = new double [n + 1];
	for (nat j = 0; j <= n; j = j + 1) {
		S[j] = ceninela;
	}
	TColaDePrioridad C = crearCP(n);
	C = insertarEnCP(v, 0.0, C);

	while (!estaVaciaCP(C)) {
		nat ver = prioritario(C);
		double ar = prioridad(prioritario(C), C);
		C = eliminarPrioritario(C);
		S[ver] = ar;
		TIterador iter = vecinos(ver, g);
		iter = reiniciarIterador(iter);
		while (estaDefinidaActual(iter)) {
			if (S[actualEnIterador(iter)] == ceninela) {
				double ar_n = ar + distancia(ver, actualEnIterador(iter), g);
				if (!estaEnCP(actualEnIterador(iter), C)) {
					C = insertarEnCP(actualEnIterador(iter), ar_n, C);
				} else {
					if (ar_n < prioridad(actualEnIterador(iter), C)) {
						C = actualizarEnCP(actualEnIterador(iter), ar_n, C);
					}
				}
			}
			iter = avanzarIterador(iter);
		}
		liberarIterador(iter);
	}
	liberarCP(C);
	S[0] = DBL_MAX;
	for (nat i = 0; i <= n; i = i + 1) {
		if (S[i] == ceninela) {
			S[i] = DBL_MAX;
		}
	}
	return S;
}

/*ArregloDoubles longitudesCaminosMasCortos(nat v, TGrafo g) {
	assert(1 <= v);
	assert(v <= cantidadVertices(g));
	nat n = cantidadVertices(g);
	ArregloDoubles res = new double [n + 1];
	TColaDePrioridad C = crearCP(n);
	TColaDePrioridad S = crearCP(n);
	C = insertarEnCP(v, 0.0, C);

	while (!estaVaciaCP(C)) {
		nat ver = prioritario(C);
		double ar = prioridad(prioritario(C), C);
		C = eliminarPrioritario(C);
		S = insertarEnCP(ver, ar, S);
		TIterador iter = vecinos(ver, g);
		iter = reiniciarIterador(iter);
		while (estaDefinidaActual(iter)) {
			if (!estaEnCP(actualEnIterador(iter), S)) {
				double ar_n = ar + distancia(ver, actualEnIterador(iter), g);
				if (!estaEnCP(actualEnIterador(iter), C)) {
					C = insertarEnCP(actualEnIterador(iter), ar_n, C);
				} else {
					if (ar_n < ar) {
						C = actualizarEnCP(actualEnIterador(iter), ar_n, C);
					}
				}
			}
			iter = avanzarIterador(iter);
		}
		liberarIterador(iter);
	}
	liberarCP(C);
	res[0] = DBL_MAX;
	for (nat i = 0; i<= n; i = i + 1) {
		if (estaEnCP(i, S)) {
			res[i] = prioridad(i, S);
		} else {
			res[i] = DBL_MAX;
		}
	}
	liberarCP(S);
	return res;
}*/



TConjunto interseccionDeConjuntos(TConjunto c1, TConjunto c2) {
	TConjunto c1dc2 = diferenciaDeConjuntos(c1, c2);
	TConjunto res = diferenciaDeConjuntos(c1, c1dc2);
	liberarConjunto(c1dc2);
	return res;
}

TCadena nivelEnBinario(nat l, TBinario b) {
	assert(l > 0);
	TCadena res = crearCadena();
	if ((l == 1) && (!esVacioBinario(b))) {
		res = insertarAlFinal(copiaInfo(raiz(b)), res);
	} else {
		TCadena aux_izq;
		TCadena aux_der;
		if (!esVacioBinario(b)) {
			aux_izq = nivelEnBinario(l-1, izquierdo(b));
			aux_der = nivelEnBinario(l-1, derecho(b));
			res = insertarSegmentoDespues(aux_der, inicioCadena(res), res);
			res = insertarSegmentoDespues(aux_izq, inicioCadena(res), res);
		}
	}
	res = ordenar(res);
	return res;
}

static bool hoja (TBinario b) {
	if ((izquierdo(b) == NULL) && (derecho(b) == NULL)) {
		return true;
	} else {
		return false;
	}
}

bool esCamino(TCadena c, TBinario b) {
	TLocalizador actual = inicioCadena(c);
	while (((actual != NULL) && (!esVacioBinario(b))) && (natInfo(raiz(b)) == natInfo(infoCadena(actual, c)))) {
		actual = siguiente(actual, c);
		if ((actual != NULL) && (!hoja(b))) {
			if ((natInfo(infoCadena(actual, c))) > (natInfo(raiz(b)))) {
				b = derecho(b);
			} else {
				b = izquierdo(b);
			}
		}
	}
	if (actual == NULL) {
		return (hoja(b));
	} else {
		return false;
	}
}

bool pertenece(nat elem, TCadena cad) {
	bool res;
	TLocalizador aux = inicioCadena(cad);
	while ((aux != NULL) && (natInfo(infoCadena(aux, cad)) != elem)) {
		aux = siguiente(aux,cad);
	}
	res = (aux != NULL);
	return res;
}

nat longitud(TCadena cad) {
	nat res = 0;
	TLocalizador aux = inicioCadena(cad);
	while (aux != NULL) {
		aux = siguiente(aux,cad);
		res = res+1;
	}
	return res;
}

bool estaOrdenadaPorNaturales(TCadena cad) {
	bool res;
	TLocalizador aux = inicioCadena(cad);
	if (esVaciaCadena(cad) || (longitud(cad) == 1)) {
		res = true;
	} else {
		while ((!esFinalCadena(aux, cad)) && ((natInfo(infoCadena(aux, cad)) <= (natInfo(infoCadena(siguiente(aux,cad), cad)))))) {
			aux = siguiente(aux,cad);
		}
		res = esFinalCadena(aux,cad);
	}
	return res;
}

bool hayNatsRepetidos(TCadena cad) {
	bool res;
	if (esVaciaCadena(cad) || (longitud(cad) == 1)) {
		res = false;
	} else {
		TLocalizador aux = inicioCadena(cad);
		while ((aux != (finalCadena(cad))) && (aux == anteriorClave(natInfo(infoCadena(aux,cad)), finalCadena(cad), cad))) {
			aux = siguiente(aux,cad);
		}
		res = (aux != (finalCadena(cad)));
	}
	return res;
}

bool sonIgualesCadena(TCadena c1, TCadena c2) {
	bool res;
	if (longitud(c1) != longitud(c2)) {
		res = false;
	} else {
			if (esVaciaCadena(c1) && esVaciaCadena(c2)) {
				res = true;
			} else {
				TLocalizador aux1 = inicioCadena(c1);
				TLocalizador aux2 = inicioCadena(c2);
				while ((aux1 != NULL) && (sonIgualesInfo(infoCadena(aux1, c1),infoCadena(aux2, c2)))) {
					aux1 = siguiente(aux1,c1);
					aux2 = siguiente(aux2,c2);
				}
				res = aux1 == NULL;
			}
	}
	return res;
}

TCadena concatenar(TCadena c1, TCadena c2) {
	TCadena res = copiarSegmento(inicioCadena(c1), finalCadena(c1), c1);
	TCadena aux = copiarSegmento(inicioCadena(c2), finalCadena(c2), c2);
	res = insertarSegmentoDespues(aux, finalCadena(res), res);
	return res;
}

TCadena ordenar(TCadena cad) {
	assert(!hayNatsRepetidos(cad));
	if (!esVaciaCadena(cad) || longitud(cad)>1) {
		TLocalizador aux = inicioCadena(cad);
		while ((!esFinalCadena(aux,cad)) && (!estaOrdenadaPorNaturales(cad))) {
			if (menorEnCadena(aux,cad) != aux) {
				cad = intercambiar(aux, menorEnCadena(siguiente(aux,cad), cad), cad);
			}
			aux = siguiente(aux,cad);
		}
	}
	return cad;
}

TCadena cambiarTodos(nat original, nat nuevo, TCadena cad) {
	TLocalizador aux = inicioCadena(cad);
	while (aux != NULL) {
		if (natInfo(infoCadena(aux,cad)) == original) {
			TInfo puente = crearInfo(nuevo, realInfo(infoCadena(aux,cad)));
			liberarInfo(infoCadena(aux,cad));
			cad = cambiarEnCadena(puente, aux, cad);
		}
		aux = siguiente(aux,cad);
	}
	return cad;
}

TCadena subCadena(nat menor, nat mayor, TCadena cad) {
	/*assert(estaOrdenadaPorNaturales(cad), menor <= mayor, pertenece(menor, cad), pertenece(mayor, cad));*/
	TCadena res = crearCadena();
	TLocalizador aux = inicioCadena(cad);
	while (aux != NULL) {
		if ((menor <= natInfo(infoCadena(aux,cad))) && (natInfo(infoCadena(aux,cad)) <= mayor)) {
			res = insertarAlFinal(copiaInfo(infoCadena(aux,cad)), res);
		}
		aux = siguiente(aux,cad);
	}
	return res;
}
