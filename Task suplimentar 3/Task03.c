// Olaru Andreea - Articolul Oras
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct Oras Oras;
struct Oras {
	char* denumire;
	int nrStrazi;
	int nrLocuitori;
};


Oras* adaugareInVector(Oras* orase, Oras o, int* nrOrase) {
	Oras* aux = (Oras*)malloc(sizeof(Oras) * ((*nrOrase) + 1));
	for (int i = 0; i < *nrOrase; i++) {
		aux[i] = orase[i];
	}
	aux[*nrOrase] = o;
	(*nrOrase)++;
	if (orase != NULL) {
		free(orase);
	}
	return aux;
}

Oras* citireFisier(const char* numeFisier, int* nrOrase) {
	FILE* file = fopen(numeFisier, "r");
	char buffer[100];
	char delimitare[] = ",\n";
	Oras* orase = NULL;
	(*nrOrase) = 0;
	while (fgets(buffer, 100, file) != NULL) {
		char* element = strtok(buffer, delimitare);
		Oras o;
		o.denumire = malloc(strlen(element) + 1);
		strcpy(o.denumire, element);
		element = strtok(NULL, delimitare);
		o.nrStrazi = atoi(element);
		element = strtok(NULL, delimitare);
		o.nrLocuitori = atoi(element);
		orase = adaugareInVector(orase, o, nrOrase);
	}
	fclose(file);
	return orase;
}

void salavareInFisier(const Oras* o, const char* numeFisier) {
	FILE* file = fopen(numeFisier, "w");
	fprintf(file, "Orasul %s are %d strazi si %d mii locuitori\n", o->denumire, o->nrStrazi, o->nrLocuitori);
	fclose(file);
}

void salvareVectorInFisier(const Oras* vectorOrase, int nrOrase, const char* numeFisier) {
	FILE* file = fopen(numeFisier, "a");
	for (int i = 0; i < nrOrase; i++) {
		fprintf(file, "Orasul %s are %d strazi si %d mii locuitori. \n", vectorOrase[i].denumire, vectorOrase[i].nrStrazi, vectorOrase[i].nrLocuitori);
	}
	fclose(file);
}

void main() {
	Oras* orase = NULL;
	int nrOrase = 0;
	orase = citireFisier("Orase.txt", &nrOrase);
	for (int i = 0; i < nrOrase; i++) {
		printf("Orasul %s \n", orase[i].denumire);
		printf("Numarul de strazi: %d \n", orase[i].nrStrazi);
		printf("Numarul de locuitori: %d mii locuitori. \n", orase[i].nrLocuitori);
		printf("\n");
	}
	free(orase);

	Oras o;
	o.denumire = "Bucuresti";
	o.nrStrazi = 100;
	o.nrLocuitori = 400;
	salavareInFisier(&o, "OraseCitite.txt");

	Oras vectorOrase[3];
	vectorOrase[0].denumire = "Constanta";
	vectorOrase[0].nrStrazi = 90;
	vectorOrase[0].nrLocuitori = 250;

	vectorOrase[1].denumire = "Timisoara";
	vectorOrase[1].nrStrazi = 50;
	vectorOrase[1].nrLocuitori = 200;

	vectorOrase[2].denumire = "Cluj-Napoca";
	vectorOrase[2].nrStrazi = 80;
	vectorOrase[2].nrLocuitori = 300;

	salvareVectorInFisier(vectorOrase, 3, "OraseCitite.txt");
}