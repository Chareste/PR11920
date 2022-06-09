
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*la funzione riceve la dimensione di un array e successivamente la lista di interi contenuta.
	Restituisce l'array senza gli elementi minori o uguali alla media*/

//**********************************FUNZIONI A DISPOSIZIONE*********


//funzione di stampa di un array
void printArray(int array[], int size);


//**********************************FUNZIONI DA IMPLEMENTARE********

//lettura di un array di interi - riceve come parametero l'array vuoto e la sua dimensione gia' inizializzata
void readIntegers(int array[], int size);

//rimozione di elementi minori o uguali alla media, in place. 
void removeSmaller(int array[], int* size);



void mergeSort(int a[], int min, int max);
void merge(int a[], int min, int q, int max);

//**********************************FUNZIONE MAIN******************

int main(){
	int n;

	//leggo la dimensione e dichiare l'array
	scanf("%d",&n);
	int numbers[n];
	
	//leggo i numeri
	readIntegers(numbers, n);

	//stampo l'array
	printf("Array iniziale:\n");
	printArray(numbers,n);
	
	//rimuovo i numeri minori o uguali alla media
	removeSmaller(numbers,&n);

	//stampo l'array
	printf("Array finale:\n");
	printArray(numbers,n);
}



//*********************IMPLEMENTAZIONE FUNZIONI A DISPOSIZIONE*********

void printArray(int a[], int n){
	int i;
	for (i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
}

//*********************TODO: IMPLEMENTAZIONE FUNZIONI RICHIESTE*********

/* Legge da standard input gli elementi dell'
array, con controllo dell’input: tutti gli interi devono essere maggiori o uguali a 0. Se
si riscontra un input che non soddisfa la condizione, il programma stampa il messaggio
Errore in input e esce. La funzione memorizza gli elementi nell’array ricevuto come
parametro in ordine crescente */

void readIntegers(int array[], int size){
	if(size == 0){return;} //array vuoto
	int i;
	int verifyinput = 0;
	for(i = 0; i < size; i++){
		//incrementa contatore verifica in caso di input non conforme
		if(scanf("%d", &array[i]) != 1 || array[i] < 0){verifyinput++;}
	}
	if(verifyinput != 0){ //
		puts("Errore di input");
		exit(EXIT_SUCCESS);
	}
	else {mergeSort(array, 0, size - 1);} //effettua il sorting 
}
	
	
	
	



/* la funzione prende come parametro un’array e la sua dimensione, e modifica l’array
rimuovendo gli elementi minori o uguali alla media dei suoi elementi iniziali.
La dimensione dell’array viene aggiornata. */

void removeSmaller(int array[], int* size){
	if(*size == 0){return;} //array vuoto
	int mid = 0;
	int i, j;
	int tmp = *size;
	
	for(i = 0; i < *size; i++){ //ricava la media sommando tutto e dividendo per size
		mid = mid + array[i];
	}
	mid /= *size;
	
	if(mid == array[*size]){return;} //l'array ha i numeri tutti uguali
	
	for(i = 0; array[i] <= mid; i++){
		array[i] = 0;
		*size = *size - 1;
	}
	int a[*size];
	for(j = 0; j < *size; j++){
		a[j] = array[i];
		i++;
	}
	
	for(i = 0; i < *size; i++){
		array[i] = a[i];
	}
	array[i] = '\0';
}
		







 //ordinamento mergesort
void mergeSort(int a[], int min, int max) {
  int q;
  if (min < max) {
    q = (min+max)/2;
    mergeSort(a, min, q);
    mergeSort(a, q+1, max);
    merge(a, min, q, max);
  }
  return;
}
	
void merge(int a[], int min, int q, int max) {
  int i, j, k = 0, b[max+1];
  i = min;
  j = q+1;

  while (i<=q && j<=max) {
    if (a[i]<a[j]) {
      b[k] = a[i];
      i++;
    } else {
      b[k] = a[j];
      j++;
    }
    k++;
  }
  while (i <= q) {
    b[k] = a[i];
    i++;
    k++;
  }
  while (j <= max) {
    b[k] = a[j];
    j++;
    k++;
  }
  for (k=min; k<=max; k++){
    a[k] = b[k-min];
  }
}	
