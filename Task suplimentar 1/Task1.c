// Olaru Andreea - Articolul Oras
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

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
	scanf("%s", o.denumire);
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

float medieLocuitori(const Oras* oras) {
	return (float)oras->nrLocuitori / oras->nrStrazi;
}

void modificaStrazi(struct Oras* o3, int nrStraziModificate) {
	o3->nrStrazi = nrStraziModificate;
}


void main() {
	Oras oras1 = citireOras();
	Oras oras2;
	oras2.nrStrazi = 10;
	oras2.nrLocuitori = 500;
	float medie = medieLocuitori(&oras2);
	printf("Media numarul de locuitori din oras: %.2f\n", medie);
	modificaStrazi(&oras2, 5);
	printf("%d\n", oras1.nrStrazi);
	afisareOras(oras1);
	
	free(oras1.denumire);
}