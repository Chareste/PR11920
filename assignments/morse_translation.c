#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


//lista di memorizzazione con inserimento in coda
typedef struct morseQueue{
	char letter; //lettera/cifra
	char *morse; //traduzione in morse
	struct morseNode *nextPtr;
}Morse;
typedef Morse *NodePtr;

//prototipi
void insert(NodePtr *head, NodePtr *tail, char *row);  
void free_list(Morse *lPtr);
int prep_string(char *line_i);
void print_morse(NodePtr head, char line_i[]);
int isEmpty(NodePtr headPtr);
void print_if_found(NodePtr current, char character);


int main(){
	
	NodePtr headPtr = NULL; //inizializzazione coda
	NodePtr tailPtr = NULL;
	
	
	char *row = malloc(50 * sizeof(char)); //stringa temporanea di assunzione input
	row[0] = '\0';
	scanf("%[^\n]%*c", row);
	
	while (row[0] != '*') { //input terminerà con ****
		insert(&headPtr,&tailPtr, row);
		row[0] = '\0'; //reset stringa
		scanf("%[^\n]%*c", row); //nuova lettura
	} //fine acquisizione dati
	free(row); //libero memoria temporanea
	
	//ottenimento linea da tradurre	
	char line[150];
	fgets(line, 150, stdin);
	strtok(line, "\n"); //cambio newline con /0
	for(;;){
		
		//se non sono presenti punteggiature stampa la traduzione
		if(prep_string(line) == 0){print_morse(headPtr, line);} 
		else{puts("Errore nell'input");}
	
		if(fgets(line, 150, stdin) == NULL){break;} //condizione di terminazione end of file
		strtok(line, "\n");
	
	}

	free_list(headPtr); //libera lo spazio occupato dalla coda
}


/*inserisce il nodo in coda*/
void insert(NodePtr *head, NodePtr *tail, char *row){  
	
	//divisione stringa in token
	char new_letter; 
	sscanf(strtok(row, ":"), "%c", &new_letter);
	char* new_morse = strtok(NULL, "\0");
	
	
	NodePtr newPtr = malloc(sizeof(Morse));
	newPtr->nextPtr = NULL; 
	
	//trasferimento assegnazione token a pointer
	newPtr->letter = new_letter;  
	newPtr->morse = malloc(strlen(new_morse) + 1);
	strcpy(newPtr->morse, new_morse);
	
	if(isEmpty(*head)){ *head = newPtr; } //la lista è vuota
	else{ (*tail)->nextPtr = newPtr; }  //inserisce il nodo in coda
	
	*tail = newPtr;

}


/*libera la lista*/
void free_list(Morse *lPtr){
	
	Morse *tmp;
	
	while(lPtr != NULL){
		tmp = lPtr;
		lPtr = lPtr->nextPtr;
		free(tmp->morse);
		free(tmp);
	}
}


/*trasforma le maiuscole in minuscole e restituisce 1 se presente punteggiatura.*/
int prep_string(char *line_i){
	int i = 0;
	while(line_i[i] != '\0'){
		if(ispunct(line_i[i]) != 0){return 1;}
		line_i[i] = tolower(line_i[i]);
		i++;
	}
	return 0;
}

//stampa la traduzione in morse della riga
void print_morse(NodePtr head, char line_i[]){  
	int i = 0;
	
	//ripete il processo per ogni carattere della stringa
	while(line_i[i] != '\0'){ 
		if(isblank(line_i[i]) != 0){ //stampa 7 spazi se presente spazio
			printf("       ");
		}
		else{ print_if_found(head, line_i[i]); } //stampa la traduzione del carattere
		i++;
	}
	puts("");
}

//controlla se la lista è vuota	
int isEmpty(NodePtr headPtr){return headPtr == NULL;}

/*Scorre la lista fino a trovare corrispondenza del carattere,
 poi stampa la traduzione in morse*/
void print_if_found(NodePtr current, char character){
	while (current != NULL){ 
		if (current->letter == character){
			printf("%s   ", current->morse); 
			break;
		}
		current = current->nextPtr; 
	} 
}
	
	
