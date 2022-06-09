#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//limiti di un intero
#define INT_MAX  2147483647
#define INT_MIN -2147483648

/*legge da input operazioni in Notazione Polacca Inversa.
Restituisce il risultato e la versione in binario. Termina con fine*/

//Struttura della pila di lavoro
typedef struct stack{
	int num;
	struct stack *nextPtr;
}Stack;
typedef Stack *NodePtr;

/*prototipi*/

void push(NodePtr *topPtr, int info);
int pop(NodePtr *topPtr);
void print_bin(NodePtr *topPtr);
int overflow_check(long c);

short overflow_index; //var. globale che indica overflow se > 0
	
int main(){
	
	NodePtr stPtr = NULL;
	char line[50];
	fgets(line, 50, stdin); //prendo da input la riga con le operazioni
	strtok(line, "\n"); //cambia newline con /0
		
	while(strcmp(line, "fine") != 0){ //condizione di terminazione del programma
		overflow_index = 0;
		
		char *tokenPtr = strtok(line, " ");
		while(tokenPtr != NULL){ //ripetizione per ogni token nella linea
			char* tmpPtr;
			long number = strtol(tokenPtr, &tmpPtr, 10); //restituisce un long se c'è un numero, 0 altrimenti
			if(overflow_check(number) != 0){break;}

			/*se è un operatore preleva due numeri per eseguire l'operazione,
			poi reinserisce il risultato nello stack*/
			if(number == 0 && strcmp(tokenPtr, "0") != 0){ //esclude valore 0
				//estrae i due numeri in cima allo stack
				int a = pop(&stPtr); 
				int b = pop(&stPtr);
		
				if(strcmp(tokenPtr, "+") == 0){ //somma i due elementi
					long sum = (long)a + (long)b;
					if(overflow_check(sum) != 0){break;} //controlla overflow del risultato
					push(&stPtr, sum); //reinserisce risultato nello stack
				}
				else if(strcmp(tokenPtr, "-") == 0){ //sottrae l'elemento più in alto a quello più basso
					long subt = (long)b - (long)a;
					if(overflow_check(subt) != 0){break;} //controlla overflow del risultato
					push(&stPtr, subt); //reinserisce risultato nello stack
				}
				else{ //moltiplicazione tra i due elementi
					long mult = (long)a * (long)b;
					if(overflow_check(mult) != 0){break;} //controlla overflow del risultato
					push(&stPtr, mult); //reinserisce risultato nello stack
				}
			}
			else{ //Il token è un numero
				push(&stPtr, number); //aggiunge il numero allo stack
			}
		if(overflow_index != 0){break;} //scarta la riga se c'è overflow
		tokenPtr = strtok(NULL, " "); //acquisizione token successivo
				}
		if(overflow_index == 0){ //non è presente overflow
			printf("%d", stPtr->num); //stampa decimale, è presente un solo elemento nello stack
			print_bin(&stPtr);	//stampa il binario
		}
		else{puts("Overflow!");} //stampa il messaggio di overflow
		
		//continua il loop di scansione
		fgets(line, 50, stdin);
		strtok(line, "\n");
	}
}

/*inserisce il nodo in cima alla pila*/
void push(NodePtr *topPtr, int info){
	
	NodePtr newPtr = malloc(sizeof(Stack));
	newPtr->num = info;
	newPtr->nextPtr = *topPtr;
	*topPtr = newPtr;
	
}


/*preleva e restituisce il valore in cima alla pila*/
int pop(NodePtr *topPtr){ 
	
	NodePtr tmpPtr = *topPtr;
	int pop_val = (*topPtr)->num;
	*topPtr = (*topPtr)->nextPtr;
	free(tmpPtr);
	
	return pop_val;
}

/* stampa il valore presente nel nodo in binario */
void print_bin(NodePtr *topPtr){
	printf(" in C2: ");
	
	int displaymask = 1 << 31;
	size_t b;
	int n = (*topPtr)->num;
	//manipola i bit per restituire il valore in binario
	for(b = 1; b <= 32; ++b){
		printf("%s", n & displaymask ? "1" : "0");
		n <<= 1;  // sposta valore a sx di 1 bit
		
		if(b % 4 == 0){ //spazio dopo 4 bit
		printf(" ");
		}
	}
	printf("\n");
}


/*se il long supera i confini di un int restituisce 1 e aumenta il contatore*/
int overflow_check(long c){ 
	if(c > INT_MAX || c < INT_MIN){
		overflow_index++;
		return 1;
		}
	return 0;
}
