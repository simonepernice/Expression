# Expression
Step by step expression solver with fraction and power management
Copyright by Simone Pernice
First release on 8/11/1996 with Borland C
Under GNU GPL 3.0 licenceQuesto 

Programma (ideato e realizzato da Simone Pernice) 
Risolve espressioni algebriche con frazioni ed elevazioni a potenza.
I simboli da sostituire a quelli tradizionalmente usati sono:

* ELEVAZIONI A POTENZA : ^  ES:(2^3 = 2 alla terza)
* MOLTIPLICAZIONE      : *  ES:(2*3 = 2 per 3)
* DIVISIONE            : /  ES:(2/3 = 2 diviso 3)
* ADDIZIONE            : + 
* SOTTRAZIONE          : -

Inoltre per velocizzare la computazione si usino le seguenti espressioni, si noti che non sono operazioni percio' (2+3)f7 o (2+3)e7 sono errori:

* FRAZIONI             : f  ES:(2f3 = 2 fratto 3)
* POTENZE              : e  ES:(2e3 = 2 elevato a 3

Le operazioni indicate sono in ordine di priorita', ovvero prima verranno eseguite le elevazioni a potenza, quindi le moltiplicazioni, le divisioni, le addizioni e le sottrazioni.

I rapporti non semplificabili con denominatore diverso da 1 sono sostituiti con frazioni ( es: 2/3=2f3 ). 

Nota, pero', la differenza tra 2/3/4=1f6 e 2/3f4=8f3.

E' possibile inserire le operazioni con numeri negativi sia separando i numeri con parentesi che non (es: 2*-3=2*(-3) ).

Il programma corregge automaticamente gli errori di digitazione piu' grossalani:
Inserisce eventuali parentesi mancanti, qualora tra un numero e una parentesi mancasse un simbolo di operazione, verra' inserito un `*`,
qualsiasi carattere che non sia un numero, una `e` o `f`, viene scartato.
Tutte le parentesi vengono sostituite con quelle tonde ed eseguite in ordine dalla piu' interna alla piu' esterna.

SI CONSIGLIA DI USARE IL PROGRAMMA COME VERIFICA DEI CALCOLI SVOLTI.

In fine desidero ringraziare Stefania Giaconia, a cui dedico questo\n"programma, che oltre ad avere realizzato questa guida e' stata\n"una compagna insostituibile per le sue geniali idee e nella fase di debugging.
