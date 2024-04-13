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
	Nod* prev;
	Nod* next;
	Oras info;
};

typedef struct ListaDubla ListaDubla;
struct ListaDubla {
	Nod* prim;
	Nod* ultim;
};

typedef struct ListaSimpla ListaSimpla;
struct ListaSimpla {
	Nod* prim;
};

void afiseazaLista(ListaDubla* lista) {
	if (lista == NULL || lista->prim == NULL) {
		printf("Lista este goala.\n");
		return;
	}
	Nod* nodCurent = lista->prim;
	while (nodCurent != NULL) {
		printf("Orasul %s are %d strazi si %d mii locuitori.\n", nodCurent->info.denumire, nodCurent->info.nrStrazi, nodCurent->info.nrLocuitori);
		nodCurent = nodCurent->next;
	}
}


ListaDubla* citesteFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	ListaDubla* lista = (ListaDubla*)malloc(sizeof(ListaDubla));
	lista->prim = NULL;
	lista->ultim = NULL;

	char buffer[100];
	char delimitare[] = ",\n";
	while (fgets(buffer, 100, file) != NULL) {
		char* element = strtok(buffer, delimitare);
		Oras o;
		o.denumire = malloc(strlen(element) + 1);
		strcpy(o.denumire, element);
		element = strtok(NULL, delimitare);
		o.nrStrazi = atoi(element);
		element = strtok(NULL, delimitare);
		o.nrLocuitori = atoi(element);
		Nod* nodNou = (Nod*)malloc(sizeof(Nod));
		nodNou->info = o;
		nodNou->prev = lista->ultim;
		nodNou->next = NULL;
		if (lista->prim == NULL) {
			lista->prim = nodNou;
		}
		else {
			lista->ultim->next = nodNou;
		}
		lista->ultim = nodNou;
	}
	fclose(file);
	return lista;
}


//functie care sterge un nod de pe o pozitie data
void stergeNod(ListaDubla* lista, int pozitie) {
	if (lista == NULL || lista->prim == NULL) {
		printf("Lista este goala.\n");
		return;
	}
	Nod* nodCurent = lista->prim;
	int index = 0;
	while (nodCurent != NULL && index < pozitie) {
		nodCurent = nodCurent->next;
		index++;
	}
	if (nodCurent == NULL) {
		printf("Lista are mai putine noduri decat index-ul dat. Stergerea nu se realizeaza.\n");
		return;
	}
	if (nodCurent->prev == NULL) {
		lista->prim = nodCurent->next;
		if (lista->prim != NULL) {
			lista->prim->prev = NULL;
		}
		else {
			lista->ultim = NULL;
		}
	}
	else {
		nodCurent->prev->next = nodCurent->next;
	}
	if (nodCurent->next == NULL) {
		lista->ultim = nodCurent->prev;
	}
	else {
		nodCurent->next->prev = nodCurent->prev;
	}
	free(nodCurent->info.denumire);
	free(nodCurent);
}

//sortare crescatoare
void sortareLista(ListaDubla* lista) {
	if (lista == NULL || lista->prim == NULL) {
		return;
	}
	int schimbat;
	do {
		schimbat = 0;
		Nod* nodCurent = lista->prim;
		while (nodCurent->next != NULL) {
			if (nodCurent->info.nrLocuitori > nodCurent->next->info.nrLocuitori) {
				Oras aux = nodCurent->info;
				nodCurent->info = nodCurent->next->info;
				nodCurent->next->info = aux;
				schimbat = 1;
			}
			nodCurent = nodCurent->next;
		}
	} while (schimbat);
}

//sortare descrescatoare
void sortareListaDescrescator(ListaDubla* lista) {
	if (lista == NULL || lista->prim == NULL) {
		return;
	}
	int schimbat;
	do {
		schimbat = 0;
		Nod* nodCurent = lista->prim;
		while (nodCurent->next != NULL) {
			if (nodCurent->info.nrLocuitori < nodCurent->next->info.nrLocuitori) {
				Oras aux = nodCurent->info;
				nodCurent->info = nodCurent->next->info;
				nodCurent->next->info = aux;
				schimbat = 1;
			}
			nodCurent = nodCurent->next;
		}
	} while (schimbat);
}

//functie care sa insereze elementele in cadrul listei dublu inlantuite astfel incat acestea a fie sortate crescator 
void inserareElement(ListaDubla* lista, Oras oras) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = oras;
	nodNou->prev = NULL;
	nodNou->next = NULL;
	if (lista == NULL || lista->prim == NULL) {
		lista->prim = nodNou;
		lista->ultim = nodNou;
		return;
	}
	if (oras.nrLocuitori < lista->prim->info.nrLocuitori) {
		nodNou->next = lista->prim;
		lista->prim->prev = nodNou;
		lista->prim = nodNou;
		return;
	}
	Nod* nodCurent = lista->prim;
	while (nodCurent->next != NULL && nodCurent->next->info.nrLocuitori < oras.nrLocuitori) {
		nodCurent = nodCurent->next;
	}
	if (nodCurent->next == NULL) {
		nodNou->prev = lista->ultim;
		lista->ultim->next = nodNou;
		lista->ultim = nodNou;
	}
	else {
		nodNou->next = nodCurent->next;
		nodNou->prev = nodCurent;
		nodCurent->next->prev = nodNou;
		nodCurent->next = nodNou;
	}
}

//4
ListaSimpla* creareListaSimpla() {
	ListaSimpla* lista = (ListaSimpla*)malloc(sizeof(ListaSimpla));
	lista->prim = NULL;
	return lista;
}

void adaugaElementInListaSimpla(ListaSimpla* lista, Oras oras) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info.denumire = (char*)malloc(strlen(oras.denumire) + 1);
	strcpy(nodNou->info.denumire, oras.denumire);
	nodNou->info.nrStrazi = oras.nrStrazi;
	nodNou->info.nrLocuitori = oras.nrLocuitori;
	nodNou->next = lista->prim;
	lista->prim = nodNou;
}

void afiseazaListaSimpla(ListaSimpla* lista) {
	if (lista == NULL || lista->prim == NULL) {
		printf("Lista este goala.\n");
		return;
	}
	Nod* nodCurent = lista->prim;
	while (nodCurent != NULL) {
		printf("Numele orasului: %s; Numarul strazilor: %d; Numarul de locuitori: %d mii locuitori;\n", nodCurent->info.denumire, nodCurent->info.nrStrazi, nodCurent->info.nrLocuitori);
		nodCurent = nodCurent->next;
	}
}

void stergeListaSimpla(ListaSimpla* lista) {
	if (lista == NULL) {
		return;
	}
	Nod* nodCurent = lista->prim;
	while (nodCurent != NULL) {
		Nod* aux = nodCurent;
		nodCurent = nodCurent->next;
		free(aux->info.denumire);
		free(aux);
	}
	lista->prim = NULL;
	free(lista);
}

void salvareOraseCuNrMareLocuitori(ListaDubla* listaDubla, int limitaLocuitori) {
	ListaSimpla* listaSimpla = creareListaSimpla();
	if (listaDubla == NULL || listaDubla->prim == NULL) {
		printf("Lista dublu inlantuita este goala.\n");
		return;
	}
	Nod* nodCurent = listaDubla->prim;
	while (nodCurent != NULL) {
		if (nodCurent->info.nrLocuitori > limitaLocuitori) {
			adaugaElementInListaSimpla(listaSimpla, nodCurent->info);
		}
		nodCurent = nodCurent->next;
	}
	printf("Orasele cu numarul de locuitori mai mare de %d mii sunt:\n\n", limitaLocuitori);
	afiseazaListaSimpla(listaSimpla);
	stergeListaSimpla(listaSimpla);
}

//5
void interschimbarePozitii(ListaDubla* lista, int pozitie1, int pozitie2) {
	if (lista == NULL || lista->prim == NULL) {
		printf("Lista este goala sau invalida.\n");
		return;
	}
	Nod* nod1 = NULL;
	Nod* nod2 = NULL;
	Nod* nodCurent = lista->prim;
	int index = 0;
	while (nodCurent != NULL) {
		if (index == pozitie1) {
			nod1 = nodCurent;
		}
		if (index == pozitie2) {
			nod2 = nodCurent;
		}
		nodCurent = nodCurent->next;
		index++;
	}
	Oras aux = nod1->info;
	nod1->info = nod2->info;
	nod2->info = aux;
}

void stergeLista(ListaDubla* lista) {
	if (lista == NULL) {
		printf("Lista este deja goala.\n");
		return;
	}
	Nod* nodCurent = lista->prim;
	while (nodCurent != NULL) {
		Nod* aux = nodCurent;
		nodCurent = nodCurent->next;
		free(aux->info.denumire);
		free(aux);
	}
	free(lista);
}


int main() {
	ListaDubla* listaOrase = citesteFisier("Orase.txt");
	printf("Lista orase citite din fisier:\n\n");
	afiseazaLista(listaOrase);
	printf("\n\n");

	stergeNod(listaOrase, 3);
	printf("Lista orase dupa stergere:\n\n");
	afiseazaLista(listaOrase);
	printf("\n\n");

	sortareLista(listaOrase);
	printf("Lista sortata crescator dupa numarul de locuitori:\n\n");
	afiseazaLista(listaOrase);
	printf("\n\n");

	Oras orasNou = { "Noul Oras",500,100 };
	inserareElement(listaOrase, orasNou);
	printf("Lista orase dupa inserare:\n\n");
	afiseazaLista(listaOrase);
	printf("\n\n");

	printf("Lista sortata descrescator dupa numarul de locuitori:\n\n");
	sortareListaDescrescator(listaOrase);
	afiseazaLista(listaOrase);
	printf("\n\n");

	int pozitie1 = 0;
	int pozitie2 = 1;
	printf("Lista orase dupa interschimbare elemente de pe pozitiile %d si %d:\n\n", pozitie1, pozitie2);
	interschimbarePozitii(listaOrase, pozitie1, pozitie2);
	afiseazaLista(listaOrase);
	printf("\n\n");


	salvareOraseCuNrMareLocuitori(listaOrase, 100);
	printf("\n\n");

	//stergeLista(listaOrase);
	return 0;
}
