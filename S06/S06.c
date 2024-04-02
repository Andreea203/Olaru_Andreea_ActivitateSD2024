#include <stdio.h>
#include <malloc.h>

typedef struct Santier Santier;
typedef struct NodLdi NodLdi;
typedef struct ListaDubla ListaDubla;

struct Santier {
	char* numeProiect;
	int nrMuncitori;
	float suprafata;
};

struct NodLdi {
	NodLdi* prev;
	NodLdi* next;
	Santier info;
};

struct ListaDubla {
	NodLdi* prim;
	NodLdi* ultim;
};



void inserareInceput(ListaDubla* lista, Santier s) {
	NodLdi* aux = malloc(sizeof(NodLdi));
	aux->info = s;
	aux->next = lista->prim;
	aux->prev = NULL;
	if (lista->prim != NULL) {
		lista->prim->prev = aux;
	}
	else {
		lista->ultim = aux;
	}
	lista->prim = aux;
}


float densitateSantier(Santier santier) {
	if (santier.suprafata > 0) {
		return santier.nrMuncitori / santier.suprafata;
	}
	else return 0;
}

void stergereSantierDupaNume(ListaDubla* lista, const char* numeSantier) {
	NodLdi* nod = lista->prim;
	while (nod != NULL) {
		if (strcmp(nod->info.numeProiect, numeSantier) == 0) {
			if (nod->prev == NULL) {  //adica daca este primul nod
				if (nod->next == NULL) {
					lista->prim = NULL;
					lista->ultim = NULL;
				}
				else {
					nod->next->prev = NULL;
					lista->prim = nod->next;
				}
			}
			else {
				if (nod->next == NULL) {
					nod->prev->next = NULL;
					lista->ultim = nod->prev;
				}
				else {
					nod->prev->next = nod->next;
					nod->next->prev = nod->prev;
				}
			}

			free(nod->info.numeProiect);
			free(nod);
			nod = NULL;
		}
		else {
			nod = nod->next;
		}
	}
}

Santier initSantier(const char* numeProiect, int nrMuncitori, float suprafata) {
	Santier santier;
	santier.numeProiect = (char*)malloc(strlen(numeProiect) + 1);
	strcpy(santier.numeProiect, numeProiect);
	santier.nrMuncitori = nrMuncitori;
	santier.suprafata = suprafata;
	return santier;
}

void afisareSantier(Santier santier) {
	printf("Santierul %s are %d muncitori si o suprafata de %5.2f m2 \n", santier.numeProiect, santier.nrMuncitori, santier.suprafata);
	//printf("\n");
}

void afisareLdiDeLaInceput(ListaDubla lista) {
	for (NodLdi* nod = lista.prim; nod != NULL; nod = nod->next) {
		afisareSantier(nod->info);
	}
	printf("\n\n");
}

void stergereCompleta(ListaDubla* lista) {
	if (lista != NULL) {
		NodLdi* aux = lista->prim;
		while (aux != NULL) {
			free(aux->info.numeProiect);
			NodLdi* temporar = aux->next;
			free(aux);
			aux = temporar;
		}
		lista->prim = NULL;
		lista->ultim = NULL;
	}
}

int calculNrTotalMuncitori(ListaDubla lista) {
	int suma = 0;
	for (NodLdi* i = lista.prim; i != NULL; i = i->next) {
		suma += i->info.nrMuncitori''
	}
	return suma;
}

int calculNrMuncitoriSuprafata(ListaDubla lista, float suprafataMax) {
	int suma = 0;
	for (NodLdi* i = lista.prim; i != NULL; i = i->next) {
		if (i->info.suprafata < suprafataMax) {
			suma += i->info.nrMuncitori;
		}
	}
	return suma;
}

int main() {
	Santier s1 = initSantier("Santier 1", 10, 300);
	Santier s2 = initSantier("Santier 2", 20, 500);
	Santier s3 = initSantier("Santier 3", 50, 800);

	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	inserareInceput(&lista, s1);
	inserareInceput(&lista, s2);
	inserareInceput(&lista, s3);

	//afisareLdiDeLaInceput(lista);

	/*stergereSantierDupaNume(&lista, "Santier 2");
	afisareLdiDeLaInceput(lista);
	stergereSantierDupaNume(&lista, "Santier 1");
	afisareLdiDeLaInceput(lista);
	stergereSantierDupaNume(&lista, "Santier 3");
	afisareLdiDeLaInceput(lista);*/

	int nrMuncitori = calculNrTotalMuncitori(lista);
	printf("Numarul total de muncitori: %d\n", nrMuncitori);

	int nrMuncitori2 = calculNrMuncitoriSuprafata(lista, 350);
	printf("Numarul de muncitori: %d\n", nrMuncitori2);

	stergereCompleta(&lista);
	afisareLdiDeLaInceput(lista);
}