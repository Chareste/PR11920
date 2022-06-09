
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struttura di dati per memorizzare un insieme
typedef struct n{
	int v;
	struct n* next;
} Node;
typedef Node* Set;

//**********************************FUNZIONI A DISPOSIZIONE*********

//funzione di lettura di un set
Set readSet();

//funzione di stampa di un set
void printSet(Set l);


//**********************************FUNZIONI DA IMPLEMENTARE********

//inserimento ordinato di un elemento in un set (senza duplicati!)
void insert(Set* s,int n);

//intersezione di 2 insiemi, senza modificare gli insiemi di partenza
Set intersect(Set s1, Set s2);


//cancellazione della memoria
void freeSet(Set* s);

//scorre la seconda lista per cercare corrispondenza nella prima
void check_list(Set curr2, Set *s3, int val);

//**********************************FUNZIONE MAIN******************

int main(){
	Set s1, s2, s3;
	s1=readSet();
	s2=readSet();

	printf("I 2 insiemi:\n");
	printSet(s1);
	printSet(s2);

	s3=intersect(s1,s2);
	
	printf("L'intersezione dei 2 insiemi:\n");
	printSet(s3);

	freeSet(&s1);
	freeSet(&s2);
	freeSet(&s3);
}


//*********************IMPLEMENTAZIONE FUNZIONI A DISPOSIZIONE*********

//funzione di lettura di un set
//utilizza la funzione "insert" da implementare
Set readSet(){
	Set s=NULL;
	int x;
	scanf("%d",&x);
	while (x!=-1){
		insert(&s,x);
		scanf("%d",&x);
	}
	return s;
}

//funzione di stampa di un set
void printSet(Set s){
	if (s!=NULL){	
		printf("%d->",s->v);
		printSet(s->next);
	}
	else{
		printf("NULL\n");
	}
}



//*********************TODO: IMPLEMENTAZIONE FUNZIONI RICHIESTE*********


//inserimento ordinato di un elemento in un set (senza duplicati!)
void insert(Set* s,int n){
	
	Set prevPtr = NULL;
	Set currPtr = *s;
	
	Set newPtr = malloc(sizeof(Node));
	newPtr->v = n;
	
	while(currPtr != NULL && currPtr->v < n){
		prevPtr = currPtr;
		currPtr = currPtr->next;
	}
	if (currPtr != NULL && currPtr->v == n) {return;}
	
	else{
	
		//inserimento nuovo nodo nella lista
        if(prevPtr == NULL){
            newPtr->next = currPtr;
            *s = newPtr;
        }
        //inserisce il nuovo nodo tra previousPtr e currentPtr
        else {
            prevPtr->next = newPtr;
            newPtr->next = currPtr;
        }
	}
		
}
	

//intersezione di 2 insiemi, senza modificare gli insiemi di partenza
Set intersect(Set s1, Set s2){
	
	Set s3 = NULL;
	Set curr1 = s1;
	Set curr2 = s2;
	
	int tmp;
	
	while (curr1 != NULL){
		tmp = curr1->v;
	
		check_list(curr2, &s3, tmp);
		
		curr1 = curr1->next; 
	}
	
	return s3;
}



void check_list(Set curr2, Set *s3, int val){
	while (curr2 != NULL){ 
	
		if (curr2->v == val){ //il valore puntato combacia
			insert(s3, val);
			return;
		}
		curr2 = curr2->next; 
	} 
}
	



//cancellazione della memoria iterativa (Riceve pointer)
void freeSet(Set* s){ 
	
///	Set *tmp;
	
	while(*s != NULL){
///		*tmp = *s;
		(*s) = (*s)->next;
		///aggiungi free per ogni elemento della lista malloc-ed
///		free(*tmp);
	}
}