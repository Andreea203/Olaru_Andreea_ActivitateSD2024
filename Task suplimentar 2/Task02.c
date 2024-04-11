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
	scanf("%39s", o.denumire);
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
			printf("Strada %d are lungimea: %.2f\n", i+1, o1.lungimeStrazi[i]);
		}
	}
	printf("\n");
}

void stergereOras(struct Oras o) {
	free(o.denumire);
	free(o.lungimeStrazi);
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

//Functie pentru a filtra orasele dupa o lungime minima data

float lungimeMinima(struct Oras o2);

struct Oras* filtruLungimeMinima(struct Oras* vectorOrase, int nrOrase, float lungimeMinimaData, int* nrOraseFiltrate) {
	struct Oras* vectorOraseFiltrate = (struct Oras*)malloc(nrOrase * sizeof(struct Oras));
	int index = 0;
	for (int i = 0; i < nrOrase; i++) {
		if (lungimeMinima(vectorOrase[i]) >= lungimeMinimaData) {
			vectorOraseFiltrate[index++] = vectorOrase[i];
		}
	}
	*nrOraseFiltrate = index;
	return vectorOraseFiltrate;
}


struct Oras* filtruNumarStrazi(struct Oras* vectorOrase, int nrOrase, int numarMinimStrazi, int* nrOraseFiltrate) {
	struct Oras* vectorOraseFiltrate = (struct Oras*)malloc(nrOrase * sizeof(struct Oras));
	int index = 0;
	for (int i = 0; i < nrOrase; i++) {
		if (vectorOrase[i].nrStrazi >= numarMinimStrazi) {
			vectorOraseFiltrate[index++] = vectorOrase[i];
		}
	}
	*nrOraseFiltrate = index;
	vectorOraseFiltrate = (struct Oras*)realloc(vectorOraseFiltrate, index * sizeof(struct Oras));
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

void afisareVectorOrase(struct Oras* vector, int dimensiune) {
	printf("Vectorul de orase:\n");
	for (int i = 0; i < dimensiune; i++) {
		printf("Oras %d\n", i + 1);
		afisareOras(vector[i]);
	}
}

void main() {
	//struct Oras oras1 = citireOras();

	//printf("%.2f\n", lungimeMinima(oras1));
	//modificaStrazi(&oras1, 1);
	//printf("%d\n", oras1.nrStrazi);
	//afisareOras(oras1);

	//free(oras1.denumire);
	//free(oras1.lungimeStrazi);

	//int nrOrase = 5;
	//struct Oras* vectorOrase = (struct Oras*)malloc(nrOrase * sizeof(struct Oras));
	//for (int i = 0; i < nrOrase; i++) {
	//	//printf("Date despre orasul %d:\n", i + 1);
	//	vectorOrase[i] = citireOras();
	//}

	////printf("Orasele initiale:\n");
	//for (int i = 0; i < nrOrase; i++) {
	//	//afisareOras(vectorOrase[i]);
	//}

	//float lungimeMinimaData = 50.0f;
	//int nrOraseFiltrate = 0;
	//struct Oras* vectorOraseFiltrate = filtruLungimeMinima(vectorOrase, nrOrase, lungimeMinimaData, &nrOraseFiltrate);
	////printf("Orasele filtrate dupa lungimea minima de %.2f:\n", lungimeMinimaData);
	//for (int i = 0; i < nrOraseFiltrate; i++) {
	//	//afisareOras(vectorOraseFiltrate[i]);
	//}

	//for (int i = 0; i < nrOraseFiltrate; i++) {
	//	stergereOras(vectorOraseFiltrate[i]);
	//}
	//free(vectorOraseFiltrate);

	//int nrMinimStrazi = 1;
	//int nrOraseFiltrateNrStrazi = 0;
	//struct Oras* vectorOraseFiltrateNrStrazi = filtruNumarStrazi(vectorOrase, nrOrase, nrMinimStrazi, &nrOraseFiltrateNrStrazi);
	//printf("Orasele filtrate dupa minimul de %d strazi:\n", nrMinimStrazi);
	//for (int i = 0; i < nrOraseFiltrateNrStrazi; i++) {
	//	afisareOras(vectorOraseFiltrateNrStrazi[i]);
	//}

	//
	//for (int i = 0; i < nrOraseFiltrateNrStrazi; i++) {
	//	stergereOras(vectorOraseFiltrateNrStrazi[i]);
	//}
	//free(vectorOraseFiltrateNrStrazi);


	//for (int i = 0; i < nrOrase; i++) {
	//	stergereOras(vectorOrase[i]);
	//}
	//free(vectorOrase);

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

	struct Oras vectorOrase[] = {
		{"Oras A",3,(float[]) { 10.5,20.4,30.6 }},
		{"Oras B",2,(float[]) { 15.4,29.5 }}
	};
	int dimensiune = sizeof(vectorOrase) / sizeof(struct Oras);
	afisareVectorOrase(vectorOrase, dimensiune);
}