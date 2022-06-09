#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//lista libreria
typedef struct library{ 
	int isbn;
	char *author;
	char *title;
	int act; //libri attualmente presenti
	int tot; //totale inseriti
	struct library *nextPtr;
}Lib;
typedef Lib *NodePtr;


/*prototipi*/
//funzioni del menu
void print_lib(NodePtr cPtr); 
void search(NodePtr cPtr);
void loan(NodePtr cPtr);
void ret_book(NodePtr cPtr);

short read_choice(short c); 
void insert(NodePtr *head, char *line); 
void free_list(Lib *lPtr); 
int compare(NodePtr lib1, NodePtr lib2);


int main(){
	
	NodePtr lPtr = NULL; //inizializzazione lista
	
	char *tmpbook = malloc(250 * sizeof(char)); //stringa temporanea di assunzione input
	tmpbook[0] = '\0';
	scanf("%[^\n]%*c", tmpbook);
	
	while (tmpbook[0] != '0') { //input terminerà con isbn 0
		insert(&lPtr, tmpbook);
		tmpbook[0] = '\0'; //reset stringa
		scanf("%[^\n]%*c", tmpbook); //nuova lettura
	} //fine acquisizione catalogo
	
	free(tmpbook); //libero memoria temporanea
		
	
	//stampa menu
	puts("Scegli un opzione:");
	printf("1) Stampa catalogo.\n2) Cerca.\n3) Prestito.\n"
			"4) Restituzione.\n5) Esci.\nScelta: ");
	short choice; //valore scelta inserito da user
	choice = read_choice(choice); //controllo input
	
	while(choice != 5){ //termina il programma con input = 5
		switch(choice){ //opzioni menu
			case 1:
				print_lib(lPtr); //stampa libreria
				break;
			case 2:
				search(lPtr); //ricerca nella libreria
				break;
			case 3:
				loan(lPtr); //prestito di un libro
				break;
			case 4:
				ret_book(lPtr); //restituzione
				break;
		}
		//loop di lettura scelta
		puts("Scegli un opzione:");
		printf("1) Stampa catalogo.\n2) Cerca.\n3) Prestito.\n"
			"4) Restituzione.\n5) Esci.\nScelta: ");
		choice = read_choice(choice);
	}
	free_list(lPtr); //libera memoria della libreria
	puts("Bye"); //termina programma
}


/*opz. 1: stampa catalogo di libri inseriti e rispettiva quantità */
void print_lib(NodePtr cPtr){
	while (cPtr != NULL) { //stampa in ordine alfabetico finché non arriva alla fine della lista
		printf("%d - %s - %s (%d/%d)\n", cPtr->isbn, cPtr->author, cPtr->title, cPtr->act, cPtr->tot);
		cPtr = cPtr->nextPtr;
	}
}

/*opz. 2: Cerca un libro tramite nome autore e titolo */
void search(NodePtr cPtr){
	char tmp;
	while((tmp = getchar()) != '\n' && tmp != EOF){} //pulizia buffer
	char author_t[50];
	char title_t[100];
	
	//inserimento da user di autore e titolo cercati
	printf("Inserire nome autore: "); 
	fgets(author_t, 50, stdin);
	strtok(author_t, "\n"); //cambia newline in /0
	
	printf("Inserire titolo: ");
	fgets(title_t, 100, stdin);
	strtok(title_t, "\n");
	
	while (cPtr != NULL) { //ricerca in lista
		if(strcmp(author_t, cPtr->author) == 0 && strcmp(title_t, cPtr->title) == 0){ //corrispondenza del libro trovata
			if(cPtr->act == 0){ //copie attuali in memoria -> 0
				puts("Non ci sono copie disponibili del libro richiesto.");
				return;
			}
			printf("%d copie disponibili.\n", cPtr->act); //stampa quante copie ci sono
			return;
		}
		cPtr = cPtr->nextPtr;
	}
	puts("Libro non trovato."); //Libro non presente in lista
}

/*opz. 3: Prestito di un libro tramite ISBN */
void loan(NodePtr cPtr){
	unsigned int tmp;
	printf("ISBN: ");
	scanf("%u", &tmp); //inserimento ISBN cercato
	while (cPtr != NULL){
		if(tmp == cPtr->isbn){ //ricerca in lista
			if(cPtr->act == 0){ //copie attuali in memoria -> 0
				puts("Non ci sono copie disponibili del libro richiesto.");
			}
			else{
				cPtr->act -= 1; //decremento copie in memoria
				puts("Operazione completata.");
			}
			return;
		}
		cPtr = cPtr->nextPtr;
	}
	puts("Non risultano copie in prestito."); //Libro non presente in lista
}

/*opz. 4: Restituzione libro tramite ISBN */ //(simmetrica a loan ma con incremento)
void ret_book(NodePtr cPtr){
	unsigned int tmp;
	printf("ISBN: ");
	scanf("%u", &tmp); //inserimento ISBN cercato
	while (cPtr != NULL){
		if(tmp == cPtr->isbn){ //ricerca in lista
			if(cPtr->act == cPtr->tot){ //non sono state prestate copie
				puts("Non risultano copie in prestito.");
				return;
			}
			cPtr->act += 1; //incremento copie in memoria
			puts("Operazione completata.");
			return;
		}
		cPtr = cPtr->nextPtr;
	}
	puts("Non risultano copie in prestito."); //Libro non presente in lista
}

/*controllo della scelta dell'input del menu*/
short read_choice(short c){
	while(scanf("%hi", &c) != 1 || c <= 0 || c > 5){ //input non compreso tra 1 e 5
		puts("Errore. Scelta non valida.");
		scanf("%*[^\n]%*c");
	}
	return c;
}

/*inserimento in lista*/
void insert(NodePtr *head, char *line){  
	
	//divisione della linea in token
	int new_isbn; 
	sscanf(strtok(line, ","), "%d", &new_isbn);
	char* new_title = strtok(NULL, ",");
	char* new_author = strtok(NULL, "\0");
	
	NodePtr prevPtr = NULL;
	NodePtr currPtr = *head;
	
	NodePtr newPtr = malloc(sizeof(Lib));
	//trasferimento lettura scanf in nodo
		newPtr->isbn = new_isbn;  
		newPtr->author = malloc(strlen(new_author) + 1);
		strcpy(newPtr->author, new_author);
		newPtr->title = malloc(strlen(new_title) + 1);
		strcpy(newPtr->title, new_title);
	newPtr->act = 1; //inizializzazione nuovo libro a 1
	newPtr->tot = 1;
	
	newPtr->nextPtr = NULL; 
	
	//scorri finché il nuovo libro è alfabeticamente successivo al corrente
	while(currPtr != NULL && compare(newPtr, currPtr) > 0){ 
		prevPtr = currPtr;
		currPtr = currPtr->nextPtr;
	}
	if (currPtr == NULL || currPtr->isbn != new_isbn) {	
	
		//inserimento nuovo nodo nella lista
        if(prevPtr == NULL){
            newPtr->nextPtr = currPtr;
            *head = newPtr;
        }
        //inserisce il nuovo nodo tra previousPtr e currentPtr
        else {
            prevPtr->nextPtr = newPtr;
            newPtr->nextPtr = currPtr;
        }
	}
	else { //libro già presente, incremento valore
		(currPtr->act)++;
		(currPtr->tot)++;
	}	
}
	
/*libera la lista*/
void free_list(Lib *lPtr){
	
	Lib *tmp;
	
	while(lPtr != NULL){
		tmp = lPtr;
		lPtr = lPtr->nextPtr;
		free(tmp->author);
		free(tmp->title);
		free(tmp);
	}
}

/*confronta il libro in insert con il nodo esaminato*/
int compare(NodePtr lib1, NodePtr lib2){
	
    int author_compare = strcmp(lib1->author, lib2->author);
	if (author_compare != 0){return author_compare;} //se l'autore è diverso si ferma
	
	int title_compare = strcmp(lib1->title, lib2->title);
	return title_compare; //restituisce il valore di confronto dei titoli
	}
