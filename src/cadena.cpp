#include "../include/info.h"
#include "../include/utils.h"
#include "../include/cadena.h"
#include "../include/usoTads.h"


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct nodo {
	TInfo dato;
	TLocalizador anterior;
	TLocalizador siguiente;
};

struct repCadena {
	TLocalizador inicio;
	TLocalizador final;
};

bool esLocalizador(TLocalizador loc) {
	return (loc != NULL);
}

TCadena crearCadena() {
	TCadena res = new repCadena;
	res->inicio = res->final = NULL;
	return res;
}

void liberarCadena(TCadena cad) {
	TLocalizador a_borrar;
	while (cad->inicio != NULL) {
		a_borrar = cad->inicio;
		cad->inicio = cad->inicio->siguiente;
		liberarInfo(a_borrar->dato);
		delete a_borrar;
	}
	delete cad;
}

bool esVaciaCadena(TCadena cad) {
	assert(((cad->inicio == NULL) && (cad->final == NULL)) || ((cad->inicio != NULL) && (cad->final != NULL)));

	return ((cad->inicio == NULL) && (cad->final == NULL));
}

TLocalizador inicioCadena(TCadena cad) {
	TLocalizador res;
	if (esVaciaCadena(cad)) {
		res = NULL;
	} else {
		res = cad->inicio;
	}
	return res;
}

TLocalizador finalCadena(TCadena cad) {
	TLocalizador res;
	if (esVaciaCadena(cad)) {
		res = NULL;
	} else {
		res = cad->final;
	}
	return res;
}

TInfo infoCadena(TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	TInfo res;
	res = loc->dato;
	return res;
}

TLocalizador siguiente(TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	TLocalizador res;
	if (esFinalCadena(loc, cad)) {
		res = NULL;
	} else {
		res = loc->siguiente;
	}
	return res;
}

TLocalizador anterior(TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	TLocalizador res;
	if (esInicioCadena(loc, cad)) {
		res = NULL;
	} else {
		res = loc->anterior;
	}
	return res;
}

bool esFinalCadena(TLocalizador loc, TCadena cad) {
	bool res;
	if ((cad->final == loc) && (!esVaciaCadena(cad))) {
		res = true;
	} else {
		res = false;
	}
	return res;
}

bool esInicioCadena(TLocalizador loc, TCadena cad) {
	bool res;
	if ((cad->inicio == loc) && (!esVaciaCadena(cad))) {
		res = true;
	} else {
		res = false;
	}
	return res;
}

TCadena insertarAlFinal(TInfo i, TCadena cad) {
	TLocalizador aux = new nodo;
	aux->dato = i;
	if (esVaciaCadena(cad)) {
		cad->inicio = cad->final = aux;
		aux->anterior = aux->siguiente = NULL;
	} else {
		cad->final->siguiente = aux;
		aux->anterior = cad->final;
		cad->final = aux;
		aux->siguiente = NULL;
	}
	return cad;
}

TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	TLocalizador aux = new nodo;
	aux->dato = i;
	if (esInicioCadena(loc,cad)) {
		aux->anterior = NULL;
		aux->siguiente = cad->inicio;
		cad->inicio->anterior = aux;
		cad->inicio = aux;
	} else {
		aux->anterior = anterior(loc,cad);
		loc->anterior->siguiente = aux;
		aux->siguiente = loc;
		loc->anterior = aux;
	}
	return cad;
}

TCadena removerDeCadena(TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	if (longitud(cad) == 1) {
		cad->inicio = cad->final = NULL;
		liberarInfo(loc->dato);
	} else if (esInicioCadena(loc,cad)) {
		cad->inicio = loc->siguiente;
		cad->inicio->anterior = NULL;
		liberarInfo(loc->dato);
	} else if (esFinalCadena (loc,cad)) {
		cad->final = loc->anterior;
		cad->final->siguiente = NULL;
		liberarInfo(loc->dato);
	} else {
		loc->anterior->siguiente = loc->siguiente;
		loc->siguiente->anterior = loc->anterior;
		liberarInfo(loc->dato);
		}
	delete loc;
	loc = NULL;
	return cad;
}

void imprimirCadena(TCadena cad) {
	if (!esVaciaCadena(cad)) {
		TLocalizador aux;
		aux = cad->inicio;
		while (aux != NULL) {
			ArregloChars text = infoATexto(aux->dato);
			printf ("%s", text);
			delete[] text;
			aux = aux->siguiente;
		}
	}
	printf ("\n");
}

TLocalizador kesimo(nat k, TCadena cad) {
	TLocalizador res;
	if (k > longitud(cad) || (k == 0)) {
		res = NULL;
	} else {
		nat i = 1;
		res = inicioCadena(cad);
		while (i != k) {
			i = i+1;
			res = res->siguiente;
		}
	}
	return res;
}


bool localizadorEnCadena(TLocalizador loc, TCadena cad) {
	TLocalizador cursor = inicioCadena(cad);
	while (esLocalizador(cursor) && (cursor != loc)) {
		cursor = siguiente(cursor, cad);
	}
	return esLocalizador(cursor);
}

bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
	bool res;
	res = localizadorEnCadena(loc1, cad);
	if (res) {
		TLocalizador cursor = loc1;
		while (esLocalizador(cursor) && (cursor != loc2))
			cursor = siguiente(cursor, cad);
		res = esLocalizador(cursor);
		assert(!res || localizadorEnCadena(loc2, cad));
	}
	return res;
}

TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad) || esVaciaCadena(cad));
	if (esVaciaCadena(sgm)) {
		delete sgm;
		sgm = NULL;
		return cad;
	} else {
		if (esVaciaCadena(cad)) {
			cad->inicio = inicioCadena(sgm);
			cad->final = finalCadena(sgm);
		} else if (esFinalCadena(loc, cad)) {
			loc->siguiente = inicioCadena(sgm);
			inicioCadena(sgm)->anterior = loc;
			cad->final = finalCadena(sgm);
		} else {
			inicioCadena(sgm)->anterior = loc;
			finalCadena(sgm)->siguiente = siguiente(loc,cad);
			siguiente(loc,cad)->anterior = finalCadena(sgm);
			loc->siguiente = inicioCadena(sgm);
		}
		delete sgm;
		sgm = NULL;
		return cad;
	}

}

TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
	assert(esVaciaCadena(cad) || precedeEnCadena(desde, hasta, cad));
	TCadena res = crearCadena();
	if (!esVaciaCadena(cad)) {
		while (desde != hasta->siguiente) {
			insertarAlFinal(copiaInfo(desde->dato), res);
			desde = desde->siguiente;
		}
	}
	return res;
}

TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
	assert(esVaciaCadena(cad) || precedeEnCadena(desde, hasta, cad));
	if (!esVaciaCadena(cad)) {
		while (desde != hasta) {
			TLocalizador aux = siguiente(desde,cad);
			removerDeCadena(desde, cad);
			desde = aux;
		}
		removerDeCadena(hasta,cad);
	}
	return cad;
}


TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	loc->dato = i;
	return cad;
}

TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
	assert(localizadorEnCadena (loc1, cad) && localizadorEnCadena (loc2, cad));
	TLocalizador aux = new nodo;
	aux->dato = loc1->dato;
	loc1->dato = loc2->dato;
	loc2->dato = aux->dato;
	delete aux;
	return cad;
}

TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad) {
	assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
	TLocalizador aux = loc;
	if (esVaciaCadena(cad)) {
		aux = NULL;
		return aux;
	} else {
		while ((natInfo(aux->dato) != clave) && (aux->siguiente != NULL)) {
			aux = aux->siguiente;
		}
		if ((natInfo(aux->dato)) == clave) {
			return aux;
		} else {
			return aux = NULL;
		}
	}
}

TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad) {
	assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
	TLocalizador aux = loc;
	if (esVaciaCadena(cad)) {
		aux = NULL;
		return aux;
	} else {
		while ((natInfo(aux->dato) != clave) && (aux->anterior != NULL)) {
			aux = aux->anterior;
		}
		if ((natInfo(aux->dato)) == clave) {
			return aux;
		} else {
			return aux = NULL;
		}
	}
}


TLocalizador menorEnCadena(TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	TLocalizador aux = loc;
	TLocalizador res = aux;
	while (aux != NULL) {
		nat a = natInfo(aux->dato);
		nat b = natInfo(res->dato);
		if (a<b) {
			res = aux;
		}
		aux = aux->siguiente;
	}
	return res;
}
