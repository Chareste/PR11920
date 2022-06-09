
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct per la lista

typedef struct n{
    int matricola;
    float voto;
    struct n* next;
} Nodo;
typedef Nodo * Lista;


//**********************************FUNZIONI A DISPOSIZIONE*********
void stampaLista(Lista l);

void insertOrd(Lista* head,int m, int v);
void concat(Lista *list1, Lista *list2);
void insertLast(Lista *head, int m, int v);
void freeSet(Lista *head);

//**********************************FUNZIONI DA IMPLEMENTARE********
Lista leggiStudenti();
void calcolaMedie(Lista l, float* mediaA, float* mediaB);
void stampaStudenti(Lista l, float mediaA, float mediaB);


//**********************************FUNZIONE MAIN******************

int main(){
    
    //lista per memorizzare gli studenti
    Lista l=NULL;
    
    //variabili per memorizzare le medie
    float mediaA, mediaB;
    
    //leggo gli studenti
    l=leggiStudenti();
    
    //stampo la lista
    printf("Lista iniziale:\n");
    stampaLista(l);
    
    //calcolo medie
    calcolaMedie(l,&mediaA,&mediaB);
    
    
    //stampo gli studenti sopra la media
    printf("Lista filtrata in ordine inverso:\n");
    stampaStudenti(l,mediaA,mediaB);
}



//*********************IMPLEMENTAZIONE FUNZIONI A DISPOSIZIONE*********

void stampaLista(Lista l){
    if (l!=NULL){
        printf("%d:%.1f\n",l->matricola,l->voto);
        stampaLista(l->next);
    }
}

//*********************TODO: IMPLEMENTAZIONE FUNZIONI RICHIESTE*********

Lista leggiStudenti(){
	
	Lista pari = NULL;
	Lista dispari = NULL;
	
	int matr, voto;
	
	scanf("%d %d", &matr, &voto);
	
	while(matr != 0){
		if(matr % 2 == 0) 
			insertOrd(&pari, matr, voto);
		else 
			insertOrd(&dispari, matr, voto);
		
		scanf("%d %d", &matr, &voto);
	}
	
	concat(&pari, &dispari);
	
	return pari;
	
}

void calcolaMedie(Lista l, float* mediaA, float* mediaB){
	
	*mediaA = 0;
	*mediaB = 0;
	
	int counterA = 0, counterB = 0;
	
	
	while(l->matricola % 2 == 0){
		counterA++;
		*mediaA += l->matricola;
		
		l = l->next;
	}
	while(l =! NULL){
		counterB++;
		*mediaB += l->matricola;
		
		l = l->next;
	}
	
	*mediaA /= counterA;
	*mediaB /= counterB;	
}

void stampaStudenti(Lista l, float mediaA, float mediaB){
	
	if(l == NULL) return;
	
	else{
		stampaStudenti(l->next, mediaA, mediaB);
	
		if(l->matricola % 2 == 0){
			if(l->voto >= mediaA)
				printf("%d:%d.00", l->matricola, l->voto);
		}
		else{
			if(l->voto >= mediaB)
				printf("%d:%d.00", l->matricola, l->voto);
		}
	}
}




void insertOrd(Lista* head,int m, int v){
	
	Lista prevPtr = NULL;
	Lista currPtr = *head;
	
	Lista newPtr = malloc(sizeof(Nodo));
	newPtr->matricola = m;
	newPtr->voto = v;
	newPtr->next = NULL;
	
	
	while(currPtr != NULL && currPtr->matricola < m){
		prevPtr = currPtr;
		currPtr = currPtr->next;
	}
	
	//inserimento in cima alla lista
    if(prevPtr == NULL){
        newPtr->next = currPtr;
        *head = newPtr;
    }
    //inserisce il nuovo nodo tra previousPtr e currentPtr
    else{
        prevPtr->next = newPtr;
        newPtr->next = currPtr;
    }
}
//inserisce il nodo in coda (un solo puntatore)
void insertLast(Lista *head, int m, int v){   
	
		
	Lista newPtr = malloc(sizeof(Nodo));
	newPtr->next = NULL; 
	newPtr->matricola = m;
	newPtr->voto = v;
	
	if(*head == NULL){  //la lista è vuota
		*head = newPtr;
		return;
	}
	
	Lista currPtr = *head;
	
	/*loopa qui perché è stronzo*/
	while(currPtr->next != NULL){ currPtr = currPtr->next; }
	
	currPtr->next = newPtr;
}

void concat(Lista *list1, Lista *list2){
	
	Lista ptr = *list2;
	int m, v;
	
	while(ptr != NULL){
		m = ptr->matricola;
		v = ptr->voto;
		
		insertLast(&list1, m, v);
		ptr = ptr->next;
	}
	
	freeSet(&list2);
	
}	
//cancellazione della memoria iterativa (Riceve pointer)
void freeSet(Lista *head){ 
	
	while(*head != NULL){ (*head) = (*head)->next; }
}	
