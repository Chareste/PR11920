
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct per memorizzare lo studente

typedef struct s{
    int matricola;
    float voto;
} Studente;



//**********************************FUNZIONI A DISPOSIZIONE*********
void stampa(Studente* l, int count);

int partition(Studente* a, int lo, int hi);
void quickSort(Studente* a, int lo, int hi);
void swap(Studente* a, Studente* b);

//**********************************FUNZIONI DA IMPLEMENTARE********
void leggiStudenti(Studente* studenti, int count);

void calcolaMedie(Studente* studenti, int count, float* mediaA, float* mediaB);

void stampaSopraLaMedia(Studente* studenti, int count, float mediaA, float mediaB);


//**********************************FUNZIONE MAIN******************

int main(){
	
    
    //variabili per memorizzare le medie e il numero di studenti
    int count;
    float mediaA, mediaB;

    //leggo numero di studenti
    scanf("%d",&count);

    //array per memorizzare gli studenti
    Studente lista[count];

    //leggo gli studenti
    leggiStudenti(lista, count);

    //stampo la lista
    printf("Lista iniziale di studenti:\n");
    stampa(lista, count);
    
    //calcolo medie
    calcolaMedie(lista, count,&mediaA,&mediaB);
	
    //stampo gli studenti sopra la media
    printf("Lista filtrata in ordine inverso:\n");
    stampaSopraLaMedia(lista,count,mediaA,mediaB);
}



//*********************IMPLEMENTAZIONE FUNZIONI A DISPOSIZIONE*********

void stampa(Studente* l, int c){
	if (c>0){
		printf("%d:%.1f\n",l[0].matricola,l[0].voto);
		stampa(l+1,c-1);
	}
}

//*********************TODO: IMPLEMENTAZIONE FUNZIONI RICHIESTE*********

void leggiStudenti(Studente* studenti, int count){
	
	//Studente pari[count];
	Studente dispari[count];
	
	Studente temp;
	
	int i=0, j=0, k;
	
	
	while(scanf("%d %f", &temp.matricola, &temp.voto) == 1 && temp.matricola != 0){
		if(temp.matricola % 2 == 0){
			studenti[i].matricola = temp.matricola;
			studenti[i].voto = temp.voto;
			i++;
		}
		else{
			dispari[j].matricola = temp.matricola;
			dispari[j].voto = temp.voto;
			j++;
		}
	}
	quickSort(&studenti, 0, i-1);
	quickSort(&dispari, 0, j-1);
	
	for(k = 0;k < j; k++){
		studenti[i].matricola = dispari[k].matricola;
		studenti[i].voto = dispari[k].voto;
		i++;
	}	
	
}


/*ordinamento di array (quickSort)*/
int partition(Studente* a, int lo, int hi){ 
    int p = a[hi];    
    int i = (lo-1);
  
    for (int j = lo; j <= hi-1; j++){ 
        if (a[j] < p){ //elemento minore di pivot
            i++;    
            swap(&a[i],&a[j]); 
        } 
    } 
    swap(&a[i+1], &a[hi]); 
    return (i+1); 
} 
void quickSort(Studente* a, int lo, int hi){ 
    if (lo < hi){
        int q = partition(a,lo,hi); 
  
        quickSort(a, lo, q-1); 
        quickSort(a, q+1, hi); 
    } 
} 
void swap(Studente* a, Studente* b){ 
    int t = *a; 
    *a=*b; 
    *b=t; 
} 




void calcolaMedie(Studente* studenti, int count, float* mediaA, float* mediaB){
	
	*mediaA = 0;
	*mediaB = 0;
	
	int counterA = 0, counterB = 0, i = 0;
	
	
	while(matricola % 2 == 0){
		counterA++;
		*mediaA += studenti[i].matricola;
		
		i++
	}
	while(i < count){
		counterB++;
		*mediaB += studenti[i].matricola;
		
		i++
	}
	
	*mediaA /= counterA;
	*mediaB /= counterB;	
	
}	
	
void stampaSopraLaMedia(Studente* studenti, int count, float mediaA, float mediaB){
	
	if(count <= 0) return;
	
	else{
		if(l->matricola % 2 == 0){
			if(studenti[count - 1].voto >= mediaA)
				printf("%d:%.2f", studenti[count - 1].matricola, studenti[count - 1].voto);
		}
		else{
			if(studenti[count - 1] >= mediaB)
				printf("%d:%.2f", studenti[count - 1].matricola, studenti[count - 1].voto);
		}
		stampaStudenti(&studenti, count-- , mediaA, mediaB);
	}
}