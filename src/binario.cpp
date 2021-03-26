#include "../include/binario.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct repBinario {
	TInfo dato;
	TBinario izq;
	TBinario der;
	nat altura;
};

TBinario crearBinario () {
  return NULL;
}

static int maximo (int a, int b) {
  if (a>b) {
    return a;
  } else {
    return b;
  }
}

TBinario insertarEnBinario(TInfo i, TBinario b) {
  assert(esVacioBinario(buscarSubarbol(natInfo(i), b)));
  if (b == NULL) {
    b = new repBinario;
    b->dato = i;
    b->izq = b->der = NULL;
		b->altura = 1;
  } else if (natInfo(i)<natInfo(b->dato)) {
    b->izq = insertarEnBinario(i, b->izq);
		//b->altura = b->altura + 1;
		b->altura = maximo(alturaBinario(b->izq), alturaBinario(b->der)) + 1;
  } else if (natInfo(i)>natInfo(b->dato)) {
    b->der = insertarEnBinario(i, b->der);
		//b->altura = b->altura + 1;
		b->altura = maximo(alturaBinario(b->izq), alturaBinario(b->der)) + 1;
  }
  return b;
}

TInfo mayor(TBinario b) {
  assert(!esVacioBinario(b));
  TInfo res;
  if (b->der == NULL) {
    res = b->dato;
  } else {
    res = mayor(b->der);
  }
  return res;
}

TBinario removerMayor(TBinario b) {
  assert(!esVacioBinario(b));
	if (derecho(b) == NULL) {
		TBinario aux = b;
		b = izquierdo(b);
		delete aux;
		return b;
	} else {
		b->der = removerMayor(derecho(b));
		b->altura = maximo(alturaBinario(b->izq), alturaBinario(b->der)) + 1;
		return b;
	}
}

TBinario removerDeBinario(nat elem, TBinario b){
	assert(!esVacioBinario(buscarSubarbol(elem, b)));
	TBinario aux;
	if (natInfo(b->dato) == elem) {
		if (izquierdo(b) == NULL) {
			aux = b;
			b = derecho(b);
			liberarInfo(aux->dato);
			delete aux;
			return b;
		} else if (derecho(b) == NULL) {
			aux = b;
			b = izquierdo(b);
			liberarInfo(aux->dato);
			delete aux;
			return b;
		} else {
			liberarInfo(b->dato);
			b->dato = copiaInfo(mayor(izquierdo(b)));
			b->izq = removerDeBinario(natInfo(mayor(izquierdo(b))), izquierdo(b));
			return b;
		}
	} else if (natInfo(b->dato) > elem) {
		b->izq = removerDeBinario(elem, izquierdo(b));
		b->altura = maximo(alturaBinario(b->izq), alturaBinario(b->der)) + 1;
		return b;
	} else {
		b->der = removerDeBinario(elem, derecho(b));
		b->altura = maximo(alturaBinario(b->izq), alturaBinario(b->der)) + 1;
		return b;
	}
}

void liberarBinario(TBinario b) {
	if (b != NULL) {
		liberarBinario(izquierdo(b));
		liberarBinario(derecho(b));
		liberarInfo(b->dato);
		delete b;
		b = NULL;
	}
}

bool esVacioBinario(TBinario b) {
  return (b == NULL);
}

bool esAvl(TBinario b) {
	bool res;
	int alt_izq = 0;
	int alt_der = 0;
	if (b != NULL) {
		if (b->der != NULL) {
			alt_der = b->der->altura;
		}
		if (b->izq != NULL) {
			alt_izq = b->izq->altura;
		}
		if ((abs(alt_der - alt_izq) <= 1) && esAvl(izquierdo(b)) && esAvl(derecho(b))) {
			res = true;
		} else {
			res = false;
		}
	} else {
		res = true;
	}
	return res;
}

TInfo raiz(TBinario b) {
  assert(!esVacioBinario(b));
  return (b->dato);
}

TBinario izquierdo(TBinario b) {
  TBinario res = b->izq;
  return res;
}

TBinario derecho(TBinario b) {
  TBinario res = b->der;
  return res;
}

TBinario buscarSubarbol(nat elem, TBinario b) {
	TBinario res;
	if (esVacioBinario(b) || (natInfo(b->dato) == elem)) {
		res = b;
	} else {
		if (natInfo(b->dato) > elem) {
			return buscarSubarbol(elem, izquierdo(b));
		} else {
			return buscarSubarbol(elem, derecho(b));
		}
	}
	return res;
}

nat alturaBinario(TBinario b) {
	if (b == NULL) {
		return 0;
	} else {
		return b->altura;
	}
 	/*nat res;
  if (b == NULL) {
    res = 0;
  } else {
    nat alt_izq = alturaBinario(b->izq);
    nat alt_der = alturaBinario(b->der);
    if (alt_izq > alt_der) {
      res = alt_izq + 1;
    } else {
      res = alt_der + 1;
    }
  }
  return res;*/
}

nat cantidadBinario(TBinario b) {
  nat res;
  if (b == NULL) {
    res = 0;
  } else {
    res = cantidadBinario(b->der) + cantidadBinario(b->izq) + 1;
  }
  return res;
}

static double sumaaux(nat i, double res, nat &contador, TBinario b) {
	if (b == NULL) {
		return res;
	} else {
		if (derecho(b) != NULL) {
				res = sumaaux(i, res, contador, derecho(b));
		}
		if ((realInfo(b->dato) > 0) && (contador < i)) {
			res = res + realInfo(b->dato);
			contador = contador + 1;
		}
		if (izquierdo(b) != NULL) {
			res = sumaaux(i, res, contador, izquierdo(b));
		}
		return res;
	}
}


double sumaUltimosPositivos(nat i, TBinario b) {
	double res;
	nat contador = 0;
	res = sumaaux(i, 0.0, contador, b);
	return res;
}

static TCadena lineaaux (TCadena res, TBinario b) {
	if ((b->izq == NULL) && (b->der == NULL)) {
		res = insertarAlFinal(copiaInfo(b->dato), res);
	} else {
		if (izquierdo(b) != NULL) {
			lineaaux(res, izquierdo(b));
		}
		res = insertarAlFinal(copiaInfo(b->dato), res);
		if (derecho(b) != NULL) {
			lineaaux(res, derecho(b));
		}
	}
	return res;
}

TCadena linealizacion(TBinario b) {
	TCadena res = crearCadena();
	return lineaaux (res, b);
}

TBinario menores(double cota, TBinario b) {
	TBinario res;
	if (b == NULL) {
		res = NULL;
	} else {
		TBinario men_izq = menores(cota, b->izq);
		TBinario men_der = menores(cota, b->der);

		if (realInfo(b->dato) < cota) {
			res = new repBinario;
			res->dato = copiaInfo(b->dato);
			res->izq = men_izq;
			res->der = men_der;
		} else if (men_izq == NULL) {
			res = men_der;
		} else if (men_der == NULL) {
			res = men_izq;
		} else {
			res = new repBinario;
			res->dato = copiaInfo(mayor(men_izq));
			men_izq = removerDeBinario(natInfo(mayor(men_izq)), men_izq);
			res->izq = men_izq;
			res->der = men_der;
		}
	}
	return res;
}

/*
Función auxiliar a imprimirBinario.
Imprime un nodo en el formato (X,Y.Y), con X natural e Y.Y real.
*/
static void imprimirAuxiliar(TBinario b, int aux) {
	if (!esVacioBinario(b->der)) {
		imprimirAuxiliar(b->der, aux+1);
	}
	TInfo info = raiz(b);
	ArregloChars text = infoATexto(info);
	for (int i=1; i <= aux; i = i + 1) {
		printf("%s", "-");
	}
	printf ("%s", text);
	printf ("\n");
	delete[] text;
	if (!esVacioBinario(b->izq)) {
		imprimirAuxiliar(b->izq, aux + 1);
	}
}

void imprimirBinario(TBinario b) {
	printf ("\n");
	if (!esVacioBinario(b)) {
		imprimirAuxiliar(b, 0);
	}
}
