/**
*   Express is a step-by-step mathematical expression solver
*   Copyright (C) 2006 Simone Pernice <pernice@libero.it>
*
*   This file is part of Express.
*
*   Express is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   Express is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with Express.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXLUNG 160

char testo [MAXLUNG], vecchiotesto [MAXLUNG];
struct razionale {long int num; long int den; long int nesp; long int desp;};
typedef struct razionale raz;

void caricatesto (void);
int ripulisci (void);
int trovasottoespr (int *relativaposizione);
void opera (int lasottostringaallaposizione);
int correggi (void);
void stampa (void);
void schermatainiziale (void);

raz numero (int *);
int piusignificativo (int); /*ritorna 0 se non ce ne piu' */
char operatore (int *);
raz eseguiloperazione (raz, raz, char);
void sostituisci (raz, int, int);
void eliminaparentesi (int);
void stampa (void);
void stampafrazione (char r[4][MAXLUNG/2], int *, int *, int);

long mcd (long, long);
long mcm (long, long);
void assomiglia (raz *, raz *);
void semplifica (raz *);
void espandi (raz *);
