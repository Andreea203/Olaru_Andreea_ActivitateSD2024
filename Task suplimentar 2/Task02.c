// Olaru Andreea - Articolul Oras
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct Oras Oras;
struct Oras {
	char* denumire;
	int nrStrazi;
	int nrLocuitori;
};

Oras citireOras() {
	Oras o;
	o.denumire = (char*)malloc(40 * sizeof(char));
	printf("Denumire oras:\n");
	scanf("%39s", o.denumire);
	printf("Numarul de strazi ale orasului: \n");
	scanf("%d", &o.nrStrazi);
	printf("Numarul de locuitori: \n");
	scanf("%d", &o.nrLocuitori);
	return o;
}

void afisareOras(Oras o1) {
	if (o1.denumire != NULL) {
		printf("Denumirea orasului: %s\n", o1.denumire);
	}
	printf("Numarul de strazi ale orasului: %d\n", o1.nrStrazi);
	printf("Numarul de locuitori ai orasului: %d mii locuitori\n", o1.nrLocuitori);
	printf("\n");
}

void stergereOras(struct Oras o) {
	free(o.denumire);
}

float medieLocuitori(const Oras* oras) {
	return (float)oras->nrLocuitori / oras->nrStrazi;
}

void modificaStrazi(struct Oras* o3, int nrStraziModificate) {
	o3->nrStrazi = nrStraziModificate;
}

//Functie pentru a filtra orasele dupa un numar minim de locuitori dat

Oras* filtruNumarLocuitoriMinim(Oras* vectorOrase, int nrOrase, int numarMinimLocuitori, int* nrOraseFiltrate) {
	Oras* vectorOraseFiltrate = (Oras*)malloc(nrOrase * sizeof(Oras));
	int index = 0;
	for (int i = 0; i < nrOrase; i++) {
		if (vectorOrase[i].nrLocuitori >= numarMinimLocuitori) {
			vectorOraseFiltrate[index++] = vectorOrase[i];
		}
	}
	*nrOraseFiltrate = index;
	return vectorOraseFiltrate;
}


int* concatenareVectori(int* vector1, int dimensiune1, int* vector2, int dimensiune2) {
	int* vectorNou = (int*)malloc((dimensiune1 + dimensiune2) * sizeof(int));
	for (int i = 0; i < dimensiune1; i++) {
		vectorNou[i] = vector1[i];
	}
	for (int i = 0; i < dimensiune2; i++) {
		vectorNou[dimensiune1 + i] = vector2[i];
	}
	return vectorNou;
}

void afisareVector(int* vector, int dimensiune) {
	for (int i = 0; i < dimensiune; i++) {
		printf("%d ", vector[i]);
	}
	printf("\n");
}

void afisareVectorOrase(Oras* vector, int dimensiune) {
	printf("Vectorul de orase:\n");
	for (int i = 0; i < dimensiune; i++) {
		printf("Oras %d\n", i + 1);
		afisareOras(vector[i]);
	}
}

void main() {
	int vector1[] = { 1,2,3 };
	int dimensiune1 = sizeof(vector1) / sizeof(int);
	int vector2[] = { 4,5,6 };
	int dimensiune2 = sizeof(vector2) / sizeof(int);

	printf("Vectorul 1: ");
	afisareVector(vector1, dimensiune1);
	printf("Vectorul 2: ");
	afisareVector(vector2, dimensiune2);

	int* vectorConcatenat = concatenareVectori(vector1, dimensiune1, vector2, dimensiune2);
	printf("Vectorul concatenat: ");
	afisareVector(vectorConcatenat, dimensiune1 + dimensiune2);
	free(vectorConcatenat);

	printf("\n");

	Oras vectorOrase[5];
	vectorOrase[0].denumire = "Constanta";
	vectorOrase[0].nrStrazi = 90;
	vectorOrase[0].nrLocuitori = 250;

	vectorOrase[1].denumire = "Timisoara";
	vectorOrase[1].nrStrazi = 50;
	vectorOrase[1].nrLocuitori = 200;

	vectorOrase[2].denumire = "Cluj-Napoca";
	vectorOrase[2].nrStrazi = 80;
	vectorOrase[2].nrLocuitori = 300;

	vectorOrase[3].denumire = "Buzau";
	vectorOrase[3].nrStrazi = 40;
	vectorOrase[3].nrLocuitori = 100;

	vectorOrase[4].denumire = "Bucuresti";
	vectorOrase[4].nrStrazi = 100;
	vectorOrase[4].nrLocuitori = 400;

	int nrOraseFiltrate = 0;
	int numarMinimLocuitori = 250;
	Oras* vectorOraseFiltrate = filtruNumarLocuitoriMinim(vectorOrase, sizeof(vectorOrase) / sizeof(vectorOrase[0]), numarMinimLocuitori, &nrOraseFiltrate);
	if (nrOraseFiltrate > 0) {
		printf("Orasele cu cel putin %d locuitori sunt:\n", numarMinimLocuitori);
		for (int i = 0; i < nrOraseFiltrate; i++) {
			printf("%s\n", vectorOraseFiltrate[i].denumire);
		}
		free(vectorOraseFiltrate);
	}
	else {
		printf("Nu exista orase care sa indeplineasca criteriul de filtrare.\n");
	}
	
}