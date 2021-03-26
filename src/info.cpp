/*
  Módulo de implementación de `TInfo'.

  Se implementa struct rep_info como un registro con dos campos, uno natural y
  otro double.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/info.h"
#include "../include/utils.h"

#include <stdio.h> // sprintf
#include <stdlib.h>
#include <string.h> // strcpy, strcat

struct repInfo {
  nat n;
  double r;
};

TInfo crearInfo(nat natural, double real) {
  TInfo nueva = new repInfo;
  nueva->n = natural;
  nueva->r = real;
  return nueva;
}

TInfo copiaInfo(TInfo info) {
  TInfo copia = new repInfo;
  *copia = *info;
  return copia;
}

void liberarInfo(TInfo info) { delete info; };

nat natInfo(TInfo info) { return info->n; }

double realInfo(TInfo info) { return info->r; }

bool sonIgualesInfo(TInfo i1, TInfo i2) {
  return (i1->n == i2->n) && (i1->r == i2->r);
}

ArregloChars infoATexto(TInfo info) {
  char copia_nat[11];
  sprintf(copia_nat, "%d", info->n);
  char copia_real[10];
  sprintf(copia_real, "%4.2lf", info->r);

  ArregloChars texto = new char[strlen(copia_nat) + strlen(copia_real) + 5];
  strcpy(texto, "(");
  strcat(texto, copia_nat);
  strcat(texto, ",");
  strcat(texto, copia_real);
  strcat(texto, ")");
  return texto;
}
