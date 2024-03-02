// Olaru Andreea - Articolul Oras
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

struct Oras {
	char* denumire;
	int nrStrazi;
	float* lungimeStrazi;
};

struct Oras citireOras() {
	struct Oras o;
	o.denumire = (char*)malloc(40 * sizeof(char));
	printf("Denumire oras:\n");
	scanf("%s", o.denumire);
	printf("Numarul de strazi ale orasului: \n");
	scanf("%d", &o.nrStrazi);
	printf("Lungimea strazilor: \n");
	o.lungimeStrazi = (float*)malloc(o.nrStrazi * sizeof(float));
	for (int i = 0; i < o.nrStrazi; i++) {
		scanf("%f", &o.lungimeStrazi[i]);
	}
	return o;
}

void afisareOras(struct Oras o1) {
	if (o1.denumire != NULL) {
		printf("Denumirea orasului: %s\n", o1.denumire);
	}
	printf("Numarul de strazi ale orasului: %d\n", o1.nrStrazi);
	if (o1.lungimeStrazi != NULL) {
		printf("Lungimile strazilor: \n");
		for (int i = 0; i < o1.nrStrazi; i++) {
			printf("Strada %d are lungimea: %.2f\n", i,  o1.lungimeStrazi[i]);
		}
	}
	printf("\n");
}

float lungimeMinima(struct Oras o2) {
	float minim = o2.lungimeStrazi[0];
	for (int i = 1; i < o2.nrStrazi; i++) {
		if (o2.lungimeStrazi[i] < minim) {
			minim = o2.lungimeStrazi[i];
		}
	}
	return minim;
}

void modificaStrazi(struct Oras* o3, int nrStraziModificate) {
	o3->nrStrazi = nrStraziModificate;
}


void main() {
	struct Oras oras1 = citireOras();

	printf("%.2f\n", lungimeMinima(oras1));
	modificaStrazi(&oras1, 1);
	printf("%d\n", oras1.nrStrazi);
	afisareOras(oras1);
	
	free(oras1.denumire);
	free(oras1.lungimeStrazi);
}