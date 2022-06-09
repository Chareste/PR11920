#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define STATES 12
#define F (STATES - 1) //Il fail state è l'ultimo dell'array

/*prototipi*/
int isone(char d);
int iszero(char d);
void verify_language(int s);

//prototipi stati
int start(char c);
int zero(char c);
int one_1(char c);
int one_2(char c);
int one_3(char c);
int onenum_1(char c);
int onenum_2(char c);
int num_1(char c);
int num_2(char c);
int num_3(char c);
int onenum_3(char c);
int fail(char c);


 
int main(){
	//l'array di puntatori a funzioni richiesto dal testo dell'esercizio
	int (*state_switch[STATES])(char) = {start, zero, one_1, one_2, one_3, onenum_1, onenum_2, num_1, num_2, num_3, onenum_3, fail};
	int state = 0;
	int i = 0;
	
	//lettura stringa da input
	char input[20];
	fgets(input, 20, stdin);
	strtok(input, "\n"); //cambia newline con /0
	
	for(;;){
		while(input[i] != '\0'){ 
			state = (*state_switch[state])(input[i]);//esegue il passaggio di stato in base all'input
			i++;
		}
		verify_language(state); //verifica del linguaggio nello stato finale
		
		//condizione di uscita: fine file o stringa vuota
		if(fgets(input, 20, stdin) == NULL || input[0] == '\n'){break;} ; 
		strtok(input, "\n");
		state = 0; //continua il loop
	}
	
}


/*verifica lo stato e stampa se il linguaggio è verificato o no*/
void verify_language(int s){
	switch(s){
		case 4: //stati che rispettano il linguaggio
		case 5:
		case 6:
		case 9:
			puts("stringa appartenente al linguaggio");
			break;
		default: //tutti gli altri stati non rispettano il linguaggio
			puts("stringa non appartenente al linguaggio");
			break;
	}
}

/* STATI DELL'AUTOMA | regex: [A-Z]*01*[^A-Z]{3} */

int start(char c){ //state 0 (iniziale)
	if(isupper(c) != 0){return 0;} //rimane nello stato se riceve [A-Z]
	else if(iszero(c) != 0){return 1;} //richiede uno zero per avanzare
	else{return F;} //fuori alfabeto o altri caratteri
}
int zero(char c){ //state 1 = dopo inserimento di uno 0
	if(isone(c) != 0){return 2;} //riceve un uno
	else if(isdigit(c) != 0){return 7;} //riceve una cifra != 1
	else{return F;}
}
int one_1(char c){ //state 2 = un 1
	if(isone(c)!= 0){return 3;}
	else if(isdigit(c) != 0){return 10;} //il primo uno è seguito da un numero != 1
	else{return F;}
}
int one_2(char c){ //state 3 = due 1
	if(isone(c)!= 0){return 4;}
	else if(isdigit(c) != 0){return 5;}
	else{return F;}
}
int one_3(char c){ //state 4 = 3 o più 1
	if(isone(c)!= 0){return 4;} //rimane nello stato se riceve 1
	else if(isdigit(c) != 0){return 5;}
	else{return F;}
}
int onenum_1(char c){ //state 5 = un numero != 1 dopo almeno due 1
	if(isdigit(c) != 0){return 6;}
	else{return F;}
}
int onenum_2(char c){ //state 6 = due numeri != 1 dopo almeno un 1
	if(isdigit(c) != 0){return 9;}
	else{return F;}
}
int num_1(char c){ //state 7 = zero seguito da un numero != 1
	if(isdigit(c) != 0){return 8;}
	else{return F;}
}
int num_2(char c){ //state 8 = aggiunta di un numero allo stato 7
	if(isdigit(c) != 0){return 9;}
	else{return F;}
}
int num_3(char c){return F;}//state 9: inserire qualcosa porta nel failstate
int onenum_3(char c){ //state 10: simile al 5 ma non verifica il linguaggio
	if(isdigit(c) != 0){return 6;}
	else{return F;}
}
int fail(char c){return F;} //trap state 

/* UTILITIES */
int isone(char d){ //restituisce 1 se il valore è 1, 0 altrimenti
	if((int)d == 49){return 1;} 
	else{return 0;}
}
int iszero(char d){ //restituisce 1 se il valore è 0, 0 altrimenti
	if((int)d == 48){return 1;}
	else{return 0;}
}