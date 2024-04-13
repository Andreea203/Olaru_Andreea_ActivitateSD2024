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

typedef struct Nod Nod;
struct Nod {
	Oras oras;
	Nod* next;
};

Nod* creeazaNod(Oras oras) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->oras.denumire = (char*)malloc(strlen(oras.denumire) + 1);
	strcpy(nodNou->oras.denumire, oras.denumire);
	nodNou->oras.nrStrazi = oras.nrStrazi;
	nodNou->oras.nrLocuitori = oras.nrLocuitori;
	nodNou->next = NULL;
	return nodNou;
}

Nod* insereazaLaSfarsit(Nod* lista, Oras oras) {
	Nod* nod = creeazaNod(oras);
	if (lista == NULL) {
		return nod;
	}
	else {
		Nod* aux = lista;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nod;
		return lista;
	}
}

Nod* citesteFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	char buffer[100];
	char delimitare[] = ",\n";
	Nod* listaOrase = NULL;
	while (fgets(buffer, 100, file) != NULL) {
		char* element = strtok(buffer, delimitare);
		Oras o;
		o.denumire = malloc(strlen(element) + 1);
		strcpy(o.denumire, element);
		element = strtok(NULL, delimitare);
		o.nrStrazi = atoi(element);
		element = strtok(NULL, delimitare);
		o.nrLocuitori = atoi(element);
		listaOrase = insereazaLaSfarsit(listaOrase, o);
	}
	fclose(file);
	return listaOrase;
}

void afisareLista(Nod* lista) {
	while (lista != NULL) {
		printf("Orasul %s are %d strazi si %d mii locuitori.\n", lista->oras.denumire, lista->oras.nrStrazi, lista->oras.nrLocuitori);
		lista = lista->next;
	}
}

//functie care sterge un nod de pe o pozitie data
void stergeNod(Nod** lista, int pozitie) {
	if (*lista == NULL) {
		printf("Lista este goala.\n");
		return;
	}
	Nod* nodCurent = *lista;
	Nod* nodPrecedent = NULL;
	int index = 0;
	while (nodCurent != NULL && index < pozitie) {
		nodPrecedent = nodCurent;
		nodCurent = nodCurent->next;
		index++;
	}
	if (nodCurent == NULL) {
		printf("Lista are mai putine noduri decat index-ul dat. Stergerea nu se realizeaza.\n");
		return;
	}
	if (nodPrecedent == NULL) {
		*lista = nodCurent->next;
	}
	else {
		nodPrecedent->next = nodCurent->next;
	}
	free(nodCurent->oras.denumire);
	free(nodCurent);
}

//functie care sorteaza lista curenta
void sortareLista(Nod** lista) {
	if (*lista == NULL || (*lista)->next == NULL) {
		return;
	}
	Nod* listaSortata = NULL;
	Nod* nodCurent = *lista;
	while (nodCurent != NULL) {
		Nod* urmator = nodCurent->next;
		if (listaSortata == NULL || listaSortata->oras.nrLocuitori >= nodCurent->oras.nrLocuitori) {
			nodCurent->next = listaSortata;
			listaSortata = nodCurent;
		}
		else {
			Nod* aux = listaSortata;
			while (aux->next != NULL && aux->next->oras.nrLocuitori < nodCurent->oras.nrLocuitori) {
				aux = aux->next;
			}
			nodCurent->next = aux->next;
			aux->next = nodCurent;
		}
		nodCurent = urmator;
	}
	*lista = listaSortata;
}

//functie care sa insereze elemente in lista
void insereazaElement(Nod** lista, Oras oras) {
	Nod* nodNou = creeazaNod(oras);
	if (*lista == NULL || oras.nrLocuitori <= (*lista)->oras.nrLocuitori) {
		nodNou->next = *lista;
		*lista = nodNou;
		return;
	}
	Nod* aux = *lista;
	while (aux->next != NULL && aux->next->oras.nrLocuitori < oras.nrLocuitori) {
		aux = aux->next;
	}
	nodNou->next = aux->next;
	aux->next = nodNou;
}

void insereazaElementSortat(Nod** lista, Oras oras) {
	sortareLista(lista);
	insereazaElement(lista, oras);
}

//functie care salveaza in vector
Oras* salveazaInVector(Nod* lista, int* dimensiuneVector, int numarMinimLocuitori) {
	*dimensiuneVector = 0;
	int numarElemente = 0;
	Nod* nodCurent = lista;
	while (nodCurent != NULL) {
		if (nodCurent->oras.nrLocuitori >= numarMinimLocuitori) {
			numarElemente++;
		}
		nodCurent = nodCurent->next;
	}
	Oras* vectorOrase = (Oras*)malloc(numarElemente * sizeof(Oras));
	nodCurent = lista;
	int index = 0;
	while (nodCurent != NULL) {
		if (nodCurent->oras.nrLocuitori >= numarMinimLocuitori) {
			vectorOrase[index].denumire = (char*)malloc(strlen(nodCurent->oras.denumire) + 1);
			strcpy(vectorOrase[index].denumire, nodCurent->oras.denumire);
			vectorOrase[index].nrStrazi = nodCurent->oras.nrStrazi;
			vectorOrase[index].nrLocuitori = nodCurent->oras.nrLocuitori;
			index++;
		}
		nodCurent = nodCurent->next;
	}
	*dimensiuneVector = numarElemente;
	return vectorOrase;
}

//functie care interschimba elemente
void interschimbareElemente(Nod** lista, int pozitie1, int pozitie2) {
	Nod* nod1 = *lista;
	Nod* nodPrecedent1 = NULL;
	int index1 = 0;
	while (nod1 != NULL && index1 < pozitie1) {
		nodPrecedent1 = nod1;
		nod1 = nod1->next;
		index1++;
	}
	Nod* nod2 = *lista;
	Nod* nodPrecedent2 = NULL;
	int index2 = 0;
	while (nod2 != NULL && index2 < pozitie2) {
		nodPrecedent2 = nod2;
		nod2 = nod2->next;
		index2++;
	}
	if (nodPrecedent1 != NULL) {
		nodPrecedent1->next = nod2;
	}
	else {
		*lista = nod2;
	}
	if (nodPrecedent2 != NULL) {
		nodPrecedent2->next = nod1;
	}
	else {
		*lista = nod1;
	}
	Nod* aux = nod2->next;
	nod2->next = nod1->next;
	nod1->next = aux;
}

void stergereLista(Nod** lista) {
	while ((*lista) != NULL) {
		free((*lista)->oras.denumire);
		Nod* aux;
		aux = (*lista)->next;
		free((*lista));
		(*lista) = aux;
	}
	(*lista) = NULL;
}

int main() {
	Nod* listaOrase = citesteFisier("Orase.txt");
	printf("Lista orase citite din fisier:\n\n");
	afisareLista(listaOrase);
	printf("\n\n");

	int pozitieDeSters = 2;
	stergeNod(&listaOrase, pozitieDeSters);
	printf("Lista orase dupa stergere:\n\n");
	afisareLista(listaOrase);
	printf("\n\n");

	Oras orasNou = { "Noul Oras",500,100 };
	insereazaElementSortat(&listaOrase, orasNou);
	printf("Lista orase dupa sortare si inserare:\n\n");
	afisareLista(listaOrase);
	printf("\n\n");

	int dimensiuneVector;
	int numarMinimLocuitori = 100;
	Oras* vectorOrase = salveazaInVector(listaOrase, &dimensiuneVector, numarMinimLocuitori);
	printf("Vectorul de orase cu cel putin %d mii locuitori:\n\n", numarMinimLocuitori);
	for (int i = 0; i < dimensiuneVector; i++) {
		printf("Numele orasului: %s; Numar strazi: %d; Numar locuitori: %d mii\n", vectorOrase[i].denumire, vectorOrase[i].nrStrazi, vectorOrase[i].nrLocuitori);
	}
	for (int i = 0; i < dimensiuneVector; i++) {
		free(vectorOrase[i].denumire);
	}
	free(vectorOrase);
	printf("\n\n");

	afisareLista(listaOrase);
	printf("\n\n");

	int pozitie1 = 1;
	int pozitie2 = 3;
	printf("Lista orase dupa interschimbare elemente de pe pozitiile %d si %d:\n\n", pozitie1, pozitie2);
	interschimbareElemente(&listaOrase, pozitie1, pozitie2);
	afisareLista(listaOrase);

	stergereLista(&listaOrase);
	return 0;
}