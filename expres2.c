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

#include "expres2.h"
#define MAXLUNG 160

int main ()
{
	int pos;
	char carattere, a;

	schermatainiziale ();
	do
	{
		do
			caricatesto ();
		while (correggi());

		pos = 0;
		while (trovasottoespr (&pos))
		{
			opera (pos);
			pos = 0;
		}

		printf ("\n La soluzione e' stata trovata, vuoi calcolarne un'altra? ((S)/N)");


		carattere = getchar ();
		a = tolower(carattere);
		if (a!='\n') while (getchar()!='\n');
	}
	while (a != 'n');
	printf ("\n Arrivederci alla prossima volta e ricorda di non usare mai il cervello per\n risolvere delle espressioni, tanto lo faccio io per te...\n");
	return 0;
}

void schermatainiziale (void)
{
	char scritta[]={
	"Questo Programma (ideato e realizzato da Simone Pernice) risolve\n"
	"espressioni algebriche con frazioni ed elevazioni a potenza.\n"
	"\n"
	"I simboli da sostituire a quelli tradizionalmente usati sono:\n"
	"\n"
	"ELEVAZIONI A POTENZA : \" ^ \"  ES:(2^3 = 2 alla terza)\n"
	"MOLTIPLICAZIONE      : \" * \"  ES:(2*3 = 2 per 3)\n"
	"DIVISIONE            : \" / \"  ES:(2/3 = 2 diviso 3)\n"
	"ADDIZIONE            : \" + \"\n"
	"SOTTRAZIONE          : \" - \"\n"
	"\n"
	"Inoltre per velocizzare la computazione si usino le seguenti espressioni\n"
	"(si noti che non sono operazioni percio' (2+3)f7 o (2+3)e7 sono errori):\n"
	"FRAZIONI             : \" f \"  ES:(2f3 = 2 fratto 3)\n"
	"POTENZE              : \" e \"  ES:(2e3 = 2 elevato a 3)\n"
	"\n"
	"Le operazioni indicate sono in ordine di priorita', ovvero prima verranno\n"
	"eseguite le elevazioni a potenza, quindi le moltiplicazioni, le divisioni,\n"
	"le addizioni e le sottrazioni.\n"
	"I rapporti non semplificabili con denominatore diverso da 1 sono sostituiti\n"
	"con frazioni ( es: 2/3=2f3 ). Nota, pero', la differenza tra 2/3/4=1f6 e\n"
	"2/3f4=8f3.\n"
	"PREMERE INVIO PER CONTINUARE\n"
	"E' possibile inserire le operazioni con numeri negativi sia separando i\n"
	"numeri con parentesi che non (es: 2*-3=2*(-3) ).\n"
	"Il programma corregge automaticamente gli errori di digitazione piu'\n"
	"grossalani:\n"
	"Inserisce eventuali parentesi mancanti,\n"
	"qualora tra un numero e una parentesi mancasse un simbolo di operazione,\n"
	"verra' inserito un \" * \",\n"
	"qualsiasi carattere che non sia un numero, una \"e\" o \"f\", viene scartato.\n"
	"Tutte le parentesi vengono sostituite con quelle tonde ed eseguite in\n"
	"ordine dalla piu' interna alla piu' esterna.\n"
	"E' possibile modificare il testo inserito con i tasti:\n"
	"Ins  : inserisce un carattere nella posizione in cui si trova il cursore\n"
	"Canc : cancella il carattere indicato dal cursore\n"
	"Del  : cancella il carattere alla sinistra del cursore\n"
	"Fine : porta il cursore alla fine dell'espressione\n"
	"Home : porta il cursore all'inizio dell'espressione\n"
	"Frecce cursore:\n"
	"su               : ristampa la riga precedente\n"
	"destra e sinistra: spostano il cursore a destra e a sinistra sulla riga.\n"
	"\n"
	"SI CONSIGLIA DI USARE IL PROGRAMMA COME VERIFICA DEI CALCOLI SVOLTI.\n"
	"\n"
	"PREMERE INVIO PER CONTINUARE\n"
	"\n\n\n\n\n\n\n\n\n\n"
	"In fine desidero ringraziare Stefania Giaconia, a cui dedico questo\n"
	"programma, che oltre ad avere realizzato questa guida e' stata\n"
	"una compagna insostituibile per le sue geniali idee e nella fase di debugging.\n"
	"\n\n\n\n\n\n\n"
	"PREMERE INVIO PER CONTINUARE\n"
	};
	char c,d;
	int i=0, j=0;
	unsigned long int chksum=0;

	/* chksumtest */
	while (scritta[j])
	{
		chksum += scritta[j];
		++j;
	}
	if (chksum != 200308)
	{
		printf ("\n Il programma e' stato modificato senza l'autorizzazione dell'autore!");
		printf ("La check sum sarebbe dovuta essere %ld\n", chksum);
		exit (1);
	}

	//textbackground (BLUE);
	//textcolor (WHITE);
	system ("clear");//clrscr ();
	printf ("--------------------------------------------------------------------------------\n");
	printf ("     Benvenuti in ESPRESS, programma ideato e realizzato da SIMONE PERNICE.\n"); 
	printf ("--------------------------------------------------------------------------------\n");
	printf ("> Premi INVIO per continuare e h seguita da INVIO per l'aiuto.\n");
	d=0;
	while ((c=getchar())!='\n') d=c;
	//fflush (stdin);
	if (!d) return;
	//clrscr ();
	system ("clear");
	j=0;
	while ((c=scritta[i++])!='\0')
	{
		if (c=='\n') ++j;
		printf ("%c",c);
		if (j==23) {j=0; while(getchar()!='\n'); system ("clear");}
	}
	if (j) while (getchar()!='\n');
}

void aggiorna (int pos)
{
	//gotoxy (3, 4); 
	printf ("%s", testo);
	//putchar(' ');
	//printf("%c", ' ');
	if (pos+3<=80);  //gotoxy (pos+3,    4);
	else;		//		 gotoxy (pos+3-80, 5);
}

void caricatesto(void)
{
	int i, j;
	char c;

	system ("clear");
	printf ("--------------------------------------------------------------------------------\n");
	printf ("        Inserisci il testo dell'espressione di seguito al prompt.\n");
	printf ("--------------------------------------------------------------------------------\n");
	printf ("> ");

	fgets (testo, MAXLUNG, stdin);
	testo[ strlen (testo) - 1 ] = '\0';

	//fflush (stdin);
/*
	for (i=0; i<MAXLUNG; ++i) testo[i]='\0';
	i = 0;
	while ( (c = getch()) != '\r'&& (i<MAXLUNG-8))
	{
		switch (c)
		{
			case 'K': //sinistra
				if (i>0) --i; break;

			case 'M': //destra
				if (testo[i]) ++i; break;

			case 'H': //su
				j = strlen (vecchiotesto);
				if (i+j < MAXLUNG-8)
				{
					strncpy (testo+i, vecchiotesto, j);
					i += j;  break;
				}

			case '\b': //del
				if (i>0)
				{
					j = --i;
					do testo[j]=testo[j+1]; while(testo[j++]);
				}
				break;

			case 'O': //fine
				while(testo[i]) ++i;
				break;

			case 'S': //canc
				j=i;
				do
					testo[j]=testo[j+1];
				while (testo[++j]);
				break;

			case 'G': //home
				i=0; break;

			default: // carica il carattere in modo insert 
				if (c!='\x0')
				{
					j = i; while (testo[++j]);
					while (j>i) {testo[j]=testo[j-1]; --j;}
					testo[i] = c; ++i;
				}
		}
		if (c!='\x0') aggiorna (i);
	}
	printf ("\n");
	if (!(i<MAXLUNG-5)) printf ("L'espressione e' troppo lunga, prova a scomporla in due parti.\n");
	*/
}

int correggi (void)
{
	int i=0, fine, parentesi=0, moltiplicazioni=0;

	while (testo[i])
	{
		switch (testo[i])
		{
			case '[': testo[i] = '('; ++parentesi; break;
			case ']': testo[i] = ')'; --parentesi; break;
			case '{': testo[i] = '('; ++parentesi; break;
			case '}': testo[i] = ')'; --parentesi; break;
			case '(': ++parentesi; break;
			case ')': --parentesi; break;
		}
		++i;
	}
	fine = i;

	if (parentesi < 0)
	{
		printf("Ci sono piu' parentesi chiuse di quelle aperte, reinserire il testo.");
		return -1; /*falso per continuare*/
	}
	else if (parentesi > 0) printf ("Saranno aggiunte parentesi chiuse alla fine del testo.\n");

	/* inserimento parentesi iniziale e finale */
	for (i=fine; i >= 1; --i) testo[i] = testo [i-1];
	testo[0] = '('; testo[++fine] = ')'; ++fine;

	/* inserimento parentesi mancanti */
	for (i=fine; i< parentesi+fine; ++i) testo[i]=')';
	testo[i] = '\0';

	if (ripulisci ()) printf("Sono stati eliminati dei caratteri estranei.\n");
	if (testo[2]=='\0') printf ("E' necessario inserire un'equazione da risolvere.\n");

	/*inserimento "*" */
	i=0; while (testo[i])
	{
		char a = testo[i], b = testo[i+1];

		if ( (isdigit(a) && b=='(') || (a==')' && isdigit(b)) || (a==')' && b=='(') )
		{
			int j=i+1,k=i+1;

			moltiplicazioni = 1;
			while (testo[j++]);
			while (j>k)
			{
				testo[j]=testo[j-1];
				--j;
			}
			testo[k] = '*';
		}
		++i;
	}
	if (moltiplicazioni) printf("Sono stati aggiunti dei simboli \"*\".\n");

	/* copia ed elimina le parentesi iniziali e finali */
	strcpy (vecchiotesto, testo+1);
	i = 0; while (vecchiotesto[++i]); vecchiotesto[--i]='\0';

	stampa ();
	return 0;
}

int ripulisci (void)
{
	int i=0 , j=0;
	char c;

	do
	{
		if (isdigit(c=testo[i++])||c=='+'||c=='*'||c=='^'||c=='/'||c=='-'||
			c=='\n'||c=='\0'||c=='('||c==')'||c=='f'||c=='e')
			{ testo[j++]=c; }
	}
	while (c);
	return (i!=j);
}

void stampafrazione (char r[4][MAXLUNG/2], int *rpto, int *pto, int h)
{
	char c, p1, p2;
	int i, denominatore=0;

	for (i=0; i<=3; ++i) r[i][*rpto]=' ';
	++(*rpto);
	p1=p2=*rpto;

	c=testo[*pto];
	do
	{
		for (i=0; i<=3; ++i) r[i][p1]=' ';
		r[h][p1++]=c;
		++(*pto);
	}
	while (isdigit(c=testo[*pto]));
	if (c=='f')
	{
		denominatore=1;
		++(*pto);
		while (isdigit(c=testo[*pto]))
		{
			if (p2>=p1) for (i=0; i<=3; ++i) r[i][p2]=' ';
			r[h-1][p2]=r[h][p2];
			r[h][p2]  ='-';
			r[h+1][p2]=c;
			++p2;
			++(*pto);
		}
	}
	if ((p2<p1)&&denominatore) for (i=p2; i<=p1-1; ++i)
	{
		r[h-1][i]=r[h][i];
		r[h][i]  ='-';
		r[h+1][i]=' ';
	}
	*rpto =(p2>p1? p2: p1);
	for (i=0; i<=3; ++i) r[i][*rpto]=' '; ++(*rpto);
   --(*pto);
}

void stampa (void)
{
	//printf ("Testo da stampare: %s\n", testo);
	char r[4][MAXLUNG/2];
	int pto=0, rpto=0, i;
	char c;

	while ((c=testo[pto])!=0)
	{
		switch (c)
		{
			case '(':
						 r[0][rpto]=' ';r[1][rpto]='(';r[2][rpto]='(';r[3][rpto]='(';
						 ++rpto;
						 break;
			case ')':
						 r[0][rpto]=' ';r[1][rpto]=')';r[2][rpto]=')';r[3][rpto]=')';
						 ++rpto;
						 break;
			case '+':
			case '-':
			case '*':
			case '/':
			case '^':
						 for (i=0; i<=3; ++i) r[i][rpto]=' ';
						 switch (c)
						 {
							case '*': r[2][rpto]='x'; break;
							case '/': r[2][rpto]=':'; break;
							default : r[2][rpto]=c;	  break;
						 }
						 ++rpto;
						 break;
			case 'e':
						 ++ pto;
						 stampafrazione (r, &rpto, &pto, 1);
						 break;
			default:
						 stampafrazione (r, &rpto, &pto, 2);
						 break;
		}
		if (rpto>70)
		{
			for (i=0; i<=3; ++i)
			{
				r[i][rpto]='\0';
				printf (">> %s\n", r[i]);
			}
			rpto =0;
		}
		++pto;
	}
	for (i=0; i<=3; ++i)
	{
		r[i][rpto]='\0';
		printf (">> %s\n", r[i]);
	}
	printf ("Premi INVIO per continuare.");
	while (getchar() != '\n');
	//fflush (stdin);
}

/*--------------------------------Cuore-------------------------------------*/

void opera (int pos)
{
	raz op1, op2, soluzione;
	char op;
	int inizio, startpos = pos;

	pos = piusignificativo(startpos);
	while (pos)
	{
		inizio = pos - 1;
		op1 = numero (&pos);
		op  = operatore (&pos);
		op2 = numero (&pos);
		soluzione = eseguiloperazione (op1, op2, op);
		sostituisci (soluzione, inizio, pos);
		pos = piusignificativo(startpos);
		if (pos) stampa ();
	}
	trovasottoespr(&pos);
	if (pos==1)
	{
		op1 = numero(&pos);
		if ((float)op1.nesp/(float)op1.desp!=1)
		{
			stampa ();
			eliminaparentesi (startpos);
			espandi (&op1);
			sostituisci (op1, -1, --pos);
		}
		else eliminaparentesi (startpos);
	}
	else eliminaparentesi (startpos);
	stampa ();
}

int noncenepiu (int *inizio)
{
	int i=*inizio;
	if (testo[i] != 0)
	{
		++i;
		while ((testo[i]!='(') && (testo[i]!=')') && (testo[i]!='\0'))
			++i;
	}
	else return 0;
	++(*inizio);
	return (testo[i] != ')');
}

int trovasottoespr (int *inizio)
{
	do
		{
			while ((testo[*inizio]!='(') && (testo[*inizio]!=0))
				++(*inizio);
		}
	while (noncenepiu (inizio));

	return ((testo[*inizio] != '\n') && (testo[*inizio] != '\0'));
}

raz numero (int *posizione)
{
	raz valore = {0,1,1,1};

	valore.num = atol (&testo[*posizione]);
	while (isdigit(testo[++*posizione]));

	if (testo[*posizione] == 'e')
	{
		++*posizione;
		valore.nesp = atol (&testo[*posizione]);
		while (isdigit(testo[++*posizione]));
		if (testo[*posizione] == 'f')
		{
			++*posizione;
			valore.desp = atol (&testo[*posizione]);
			while (isdigit(testo[++*posizione]));
		}
	}
	else if (testo[*posizione] == 'f')
	{
		++*posizione;
		valore.den = atol (&testo[*posizione]);
		while (isdigit(testo[++*posizione]));
		if (testo[*posizione] == 'e')
		{
			++*posizione;
			valore.nesp = atol (&testo[*posizione]);
			while (isdigit(testo[++*posizione]));
		}
		if (testo[*posizione] == 'f')
		{
			++*posizione;
			valore.desp = atol (&testo[*posizione]);
			while (isdigit(testo[++*posizione]));
		}
	}
	return valore;
}

char operatore (int *posizione)
{
	/* per funzionare correttamente va chiamato dopo numero */
	return testo[(*posizione)++];
}

int piusignificativo (int posizione)
{
	int pos=posizione, i=0, fine;
	char c;

	struct operatore {int pos; char op;};
	typedef struct operatore oper;
	oper operatori[MAXLUNG];

	operatori[i].pos = pos;
	operatori[i].op = testo[pos-1];
	if (testo[pos] == '-' || testo[pos] == '+') ++pos;
	while ( (c=testo[pos]) != ')' && c!=0)
	{
		if (!isdigit(c) && c!='f' && c!='e' && testo[pos-1]!='e')
			{
				operatori[++i].op=c;
				operatori[i].pos=++pos;
				++pos;
			}
		else	++pos;
	}
	fine = i+1;

	i=1; while (operatori[i].op!='^' && i < fine) ++i;
	if (i<fine) return operatori[--i].pos;

	i=1; while (operatori[i].op!='*' && operatori[i].op!='/' && i < fine) ++i;
	if (i<fine) return operatori[--i].pos;

	i=1; while (operatori[i].op!='+' && (operatori[i].op!='-' ||
					testo[operatori[i].pos-2]=='e')  && i < fine) ++i;
	if (i<fine) return operatori[--i].pos;

	/* se non e' rimasto piu' nulla */
	return 0;
}

raz eseguiloperazione (raz op1, raz op2, char op)
{
	raz soluzione={0,0,1,1};
	long temp;
	int errore=0;

	switch (op)
	{
		case '^':
						semplifica (&op2);
						soluzione.num = op1.num;
						soluzione.den = op1.den;
						soluzione.nesp = op1.nesp*op2.num;
						soluzione.desp = op1.desp*op2.den;
						break;

		case '/':
						errore = (op2.num==0);
						assomiglia (&op1,&op2);
						if (op1.num==op2.num && op1.den==op2.den)
						{
							soluzione=op1;
							temp = soluzione.desp = mcd (op1.desp, op2.desp);
							soluzione.nesp = (temp / op1.desp * op1.nesp) -
												  (temp / op2.desp * op2.nesp);
						}
						else if ((float)op1.nesp/op1.desp==(float)op2.nesp/op2.desp)
						{
							soluzione.num=op1.num*op2.den;
							soluzione.den=op1.den*op2.num;
							soluzione.nesp=op1.nesp;
							soluzione.desp=op1.desp;
						}
						else
						{
							espandi (&op1);
							espandi (&op2);
							soluzione.num=op1.num*op2.den;
							soluzione.den=op1.den*op2.num;
						}
						break;
		case '*':
						assomiglia (&op1,&op2);
						if (op1.num==op2.num && op1.den==op2.den)
						{
							soluzione=op1;
							temp = soluzione.desp = mcd (op1.desp, op2.desp);
							soluzione.nesp = (temp / op1.desp * op1.nesp) +
												  (temp / op2.desp * op2.nesp);
						}
						else if ((float)op1.nesp/op1.desp==(float)op2.nesp/op2.desp)
						{
							soluzione.num=op1.num*op2.num;
							soluzione.den=op1.den*op2.den;
							soluzione.nesp=op1.nesp;
							soluzione.desp=op1.desp;
						}
						else
						{
							espandi (&op1);
							espandi (&op2);
							soluzione.num=op1.num*op2.num;
							soluzione.den=op1.den*op2.den;
						}
						break;

		case '-':
						espandi (&op1);
						espandi (&op2);
						temp = soluzione.den = mcd (op1.den, op2.den);
						soluzione.num = (temp / op1.den * op1.num) -
											 (temp / op2.den * op2.num);
						break;

		case '+':
						espandi (&op1);
						espandi (&op2);
						temp = soluzione.den = mcd (op1.den, op2.den);
						soluzione.num = (temp / op1.den * op1.num) +
											 (temp / op2.den * op2.num);
						break;

		default:
						printf ("E' stato riscontrato qualche errore, il risultato e' inattendibile.\n");
						errore = 1;
	}

	if (errore)
	{
		printf ("Si e' verificata una divisione per zero, il risultato e' inattendibile.\n");
		soluzione.num = soluzione.den = 0;
	}

	semplifica (&soluzione);
	return soluzione;
}

void espandi (raz *op)
{
	long int temp;

	if (op->nesp<0) { temp=op->num; op->num=op->den; op->den=temp; op->nesp=-op->nesp;}
	if (op->nesp==0) op->num=op->den=op->nesp=op->desp=1;
	if ((float)op->nesp/(float)op->desp==1) return;
	op->num = (long) pow (op->num, op->nesp/op->desp);
	op->den = (long) pow (op->den, op->nesp/op->desp);
	if ( (float)op->nesp/(float)op->desp!=(op->nesp/op->desp) )
	{
		printf ("Attenzione: potrebbero essere state introdotte delle approssimazioni nella\nesecuzione degli esponenziali.\n");
	}
	op->nesp=op->desp=1;
	return;
}

long mcd (long a, long b)
{
	long max,min,vmcd;

	a = labs (a);
	b = labs (b);
	if (a > b)	{max = a; min = b;}
	else 			{max = b; min = a;}
	vmcd = max;
	while ((vmcd % min) != 0 || (vmcd % max) != 0) ++vmcd;
	return vmcd;
}

long mcm (long a, long b)
{
	long max, min, vmcm;

	a = labs (a);
	b = labs (b);
	if (a > b) 	{max = a; min = b;}
	else 			{max = b; min = a;}
	vmcm = min;
	while ((min % vmcm) != 0 || (max % vmcm) != 0) --vmcm;
	return vmcm;
}

void assomiglia (raz  *a, raz *b)
{
	long int temp;

	if ((float)a->num/(float)a->den==(float)b->num/(float)b->den) return;
	if ((float)a->nesp/(float)a->desp==(float)b->nesp/(float)b->desp) return;
	if ((float)a->num/(float)a->den==(float)b->den/(float)b->num ||
		 (float)a->nesp/(float)a->desp==-(float)b->nesp/(float)b->desp)
	{
		temp=a->num;a->num=a->den;a->den=temp;
		a->nesp=-a->nesp;

	}
	semplifica (a);
}


void semplifica (raz *a)
{
	long temp;

	if (a->nesp==0)
	{
		a->num=a->den=a->nesp=a->desp=1;
		return;
	}
	if (a->num != 0)
	{
		temp = mcm (a->num, a->den);
		a->num /= temp;
		a->den /= temp;
		if ( (a->den)<0 )
		{
			a->den = -(a->den);
			a->num = -(a->num);
		}
	}
	else a->den = 1;
	if (a->nesp != 0)
	{
		temp = mcm (a->nesp, a->desp);
		a->nesp /= temp;
		a->desp /= temp;
		if ( (a->desp)<0 )
		{
			a->desp = -(a->desp);
			a->nesp = -(a->nesp);
		}
	}
	else a->desp = 1;
}
// A utility function to reverse a string
void reverse(char str[])
{
    int start = 0;
    int end = strlen (str) - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
}

/* itoa:  convert n to characters in s */
void ltoa(int n, char s[], int radix)
{
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
}

void sostituisci (raz soluzione, int inizio, int fine)
{
	char testoprov [MAXLUNG];
	char num[7], den[7], nesp[7], desp[7];

	(++fine);
	strcpy (testoprov, testo + fine - 1);
	ltoa (soluzione.num, num, 10);
	strcpy (testo+inizio+1, num);
	inizio += strlen (num);
	if (soluzione.den != 1)
	{
		ltoa (soluzione.den, den+1, 10);
		den[0] = 'f';
		strcpy (testo+inizio+1, den);
		inizio += strlen (den);
	}
	if ((float)soluzione.nesp/(float)soluzione.desp != 1)
	{
		ltoa (soluzione.nesp, nesp+1, 10);
		nesp[0] = 'e';
		strcpy (testo+inizio+1, nesp);
		inizio += strlen (nesp);
		if (soluzione.desp != 1)
		{
			ltoa (soluzione.desp, desp+1, 10);
			desp[0] = 'f';
			strcpy (testo+inizio+1, desp);
			inizio += strlen (desp);
		}
	}
	strcpy (testo+inizio+1, testoprov);
}

void eliminaparentesi (int startpos)
{
	char testoprov [MAXLUNG], a, b;
	int start=startpos;

	/* elimina le parentesi */
	testo [startpos-1] = 'a';
	while (testo[startpos++]!=')');
	testo [--startpos] = 'a';

	/* elimina i dopppi segni ++,+-,-+,-- sorti dall'eliminazione delle parentesi*/
	a=testo[start-2];
	b=testo[start];
	switch (a)
	{
		case '+':
			if (b=='-') testo[start-2] = 'a';
			if (b=='+') testo[start-2] = 'a';
			break;

		case '-':
			if (b=='+') testo[start]='a';
			if (b=='-')
			{
				testo[start]='a';
				testo[start-2]='+';
			}
	}
	ripulisci ();
}
/*----------------------------------end-Cuore-------------------------------*/

/*Simone Pernice 8/11/1996*/
/*Nuova routine di stampa realizzata 26/7/1997*/
/*Gestione degli esponenti realizzata 16/9/1997*/
/*Gestione degli esponenti frazionari realizzata 19/9/97*/
/*Ulitima revisione 21/9/97*/

