//arbori binari de cautare
//info din rad (5) trebuie sa fie mai mare decat info din nodul din stanga (3)
//info din rad (5) trebuie sa fie mai mica decat info din nodul din dreapta (8)
//ce e in stanga este mai mic, ce este in dreapta este mai mare

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Rezervare Rezervare;
struct Rezervare {
	int id;
	char* numeClient;
	int nrPersoane;
};

typedef struct Nod Nod;
struct Nod {
	Nod* stanga;
	Nod* dreapta;
	Rezervare info;
};

Rezervare citireRezervare(FILE* f) {
	Rezervare r;
	char aux[30];
	fscanf(f, "%d", &r.id);
	fscanf(f, "%s", &aux);
	r.numeClient = malloc(strlen(aux) + 1);
	strcpy(r.numeClient, aux);
	fscanf(f, "%d", &r.nrPersoane);
	return r;
}

Nod* inserareInArbore(Nod* arbore, Rezervare rez) {
	if (arbore != NULL) {
		if (arbore->info.id < rez.id) {
			arbore->dreapta = inserareInArbore(arbore->dreapta, rez);
		}
		else {
			arbore->stanga = inserareInArbore(arbore->stanga, rez);
		}
	}
	else {
		Nod* temp = (Nod*)malloc(sizeof(Nod));
		temp->info = rez; //shallow copy
		temp->dreapta = NULL;
		temp->stanga = NULL; 
		arbore = temp;
	}
	return arbore;
}

void citireFisier(char* numeFisier, Nod** radacina) {
	FILE* f = fopen(numeFisier, "r");
	int nrRezervari;
	fscanf(f, "%d", &nrRezervari);
	for (int i = 0; i < nrRezervari; i++) {
		Rezervare rez = citireRezervare(f);
		*radacina = inserareInArbore(*radacina, rez);
	}
}

//moduri de citire:
//preordine: R-S-D
//postordine: S-D-R
//inordine: S-R-D

void afisareRezervare(Rezervare r) {
	printf("Rezervarea cu ID-ul %d a fost facuta de %s pentru %d persoane.\n", r.id, r.numeClient, r.nrPersoane);
}

void afisareArborePreordine(Nod* arbore) {
	if (arbore != NULL) {
		afisareRezervare(arbore->info);
		afisareArborePreordine(arbore->stanga);
		afisareArborePreordine(arbore->dreapta);
	}
}

void afisareArboreInOrdine(Nod* arbore) {
	if (arbore != NULL) {
		afisareArboreInOrdine(arbore->stanga);
		afisareRezervare(arbore->info);
		afisareArboreInOrdine(arbore->dreapta);
	}
}

void afisareArborePostordine(Nod* arbore) {
	if (arbore != NULL) {
		afisareArborePostordine(arbore->stanga);
		afisareArborePostordine(arbore->dreapta);
		afisareRezervare(arbore->info);
	}
}

Rezervare cautareRezervareDupaId(Nod* radacina, int id) {
	if (radacina != NULL) {
		if (radacina->info.id < id) {
			return cautareRezervareDupaId(radacina->dreapta, id);
		}
		else {
			if (radacina->info.id > id) {
				return cautareRezervareDupaId(radacina->stanga, id);
			}
			else {
				return radacina->info;
			}
		}
	}
	else {
		Rezervare r;
		r.id = -1;
		r.numeClient = NULL;
		r.nrPersoane = -1;
		return r;
	}
}

int calculNrTotalPersoane(Nod* radacina) {
	if (radacina != NULL) {
		int rPersoane = radacina->info.nrPersoane;
		int sPersoane = calculNrTotalPersoane(radacina->stanga);
		int dPersoane = calculNrTotalPersoane(radacina->dreapta);
		int suma = rPersoane + sPersoane + dPersoane;
		return suma;
	}
	else {
		return 0;
	}
}

void main() {
	Nod* radacina = NULL;
	citireFisier("Rezervari.txt", &radacina);
	printf("Preordine:\n");
	afisareArborePreordine(radacina);
	printf("\nIn ordine:\n");
	afisareArboreInOrdine(radacina);
	printf("\nPostordine:\n");
	afisareArborePostordine(radacina);

	printf("\n\n");
	afisareRezervare(cautareRezervareDupaId(radacina, 10));

	printf("\n\n");
	printf("Numar total persoane: %d\n", calculNrTotalPersoane(radacina));
}