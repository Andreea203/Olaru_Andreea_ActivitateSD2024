#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Autobuz Autobuz;
struct Autobuz {
	int linie;            //unic
	char* capatLinie;
};

typedef struct NodSecundar NodSecundar;

typedef struct NodPrincipal NodPrincipal;
struct NodPrincipal {
	Autobuz info;
	NodPrincipal* next;
	NodSecundar* vecini;
};

struct NodSecundar {
	NodPrincipal* nod;
	NodSecundar* next;
};

Autobuz initializareAutobuz(int linie, const char* capat) {
	Autobuz a;
	a.linie = linie;
	a.capatLinie = (char*)malloc(sizeof(char) * (strlen(capat) + 1));
	strcpy(a.capatLinie, capat);
	return a;
}

//functie de inserare la sfarsit in lista principala
void inserarePrincipala(NodPrincipal** graf, Autobuz a) {
	NodPrincipal* nod = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nod->info = a;  //shallow copy
	nod->next = NULL;
	nod->vecini = NULL;

	if ((*graf) != NULL) {
		NodPrincipal* aux = *graf;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nod;
	}
	else {
		*graf = nod;
	}
}


//functie de cautare dupa linie
NodPrincipal* cautaLinie(NodPrincipal* graf, int linie) {
	while (graf && graf->info.linie != linie) {
		graf = graf->next;
	}
	return graf;
}


//functie de inserare in lista secundara
NodSecundar* inserareSecundara(NodSecundar* cap, NodPrincipal* info) {
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->next = NULL;
	nou->nod = info;
	if (cap) {
		NodSecundar* p = cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
		return cap;
	}
	else {
		return nou;
	}
}


//functie de inserare muchie (va insera adresa lui 2 in 1 si vice versa)
void inserareMuchie(NodPrincipal* graf, int linieStart, int linieStop) {
	NodPrincipal* nodStart = cautaLinie(graf, linieStart);
	NodPrincipal* nodStop = cautaLinie(graf, linieStop);
	nodStart->vecini = inserareSecundara(nodStart->vecini, nodStop);
	nodStop->vecini = inserareSecundara(nodStop->vecini, nodStart);
}




void main() {
	NodPrincipal* graf = NULL;

	inserarePrincipala(&graf, initializareAutobuz(0, "Romana"));
	inserarePrincipala(&graf, initializareAutobuz(1, "Universitate"));
	inserarePrincipala(&graf, initializareAutobuz(2, "Unirii"));
	inserarePrincipala(&graf, initializareAutobuz(3, "Victoriei"));
	inserarePrincipala(&graf, initializareAutobuz(4, "Militari"));

	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 0, 4);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 2, 4);
	inserareMuchie(graf, 3, 4);
}
