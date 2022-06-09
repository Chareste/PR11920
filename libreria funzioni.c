//correttezza dell'intero
int read_int(int d){
	while(scanf("%d", &d) != 1){
		puts("Inserisci un intero.");
		scanf("%*[^\n]%*c");
	}
	return d;
}

//correttezza dell'intero positivo
int read_int_pos(int dpos){
	while(scanf("%d", &dpos) != 1 || dpos <= 0){
		puts("Inserisci un intero positivo.");
		scanf("%*[^\n]%*c");
	}
	return dpos;
}


//lettura array di n interi
void readArray(int a[], int size){ 
	int i;
	for(i = 0; i < size; i++){
		scanf("%d", &a[i]);
	}
}

//stampa di array
void printArray(int a[], int size){ 
    int i; 
    for (i = 0; i < size; i++){ 
        printf("%d ", a[i]); 
	}
    puts(""); //newline
} 	



/*ordinamento di array (quicksort)*/
int partition(int a[], int lo, int hi){ 
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
void quickSort(int a[], int lo, int hi){ 
    if (lo < hi){
        int q = partition(a,lo,hi); 
  
        quickSort(a, lo, q-1); 
        quickSort(a, q+1, hi); 
    } 
} 
void swap(int* a, int* b){ 
    int t = *a; 
    *a=*b; 
    *b=t; 
} 

/*struttura lista di base*/
typedef struct list{
	int data; //cosa contiene
	struct list *next;
}Node;
typedef Node *NodePtr;

/*LISTE*/


//inserimento in lista in cima
void insert(NodePtr* head, int n){
	
	NodePtr currPtr = *head;
	
	NodePtr newPtr = malloc(sizeof(Node));
	newPtr->data = n;
	
    newPtr->next = currPtr;
    *head = newPtr; 
}


//inserisce il nodo in coda (un solo puntatore)
void insertLast(NodePtr *head, int n){   
	
		
	NodePtr newPtr = malloc(sizeof(Node));
	newPtr->next = NULL; 
	newPtr->data = n;
	
	if(*head == NULL){  //la lista è vuota
		*head = newPtr;
		return;
	}
	
	NodePtr currPtr = *head;
	
	while(currPtr->next != NULL){ currPtr = currPtr->next; }
	
	currPtr->next = newPtr;
}



//inserimento in lista ordinato
void insertOrd(NodePtr* head,int n){
	
	NodePtr prevPtr = NULL;
	NodePtr currPtr = *head;
	
	NodePtr newPtr = malloc(sizeof(Node));
	newPtr->data = n;
	
	while(currPtr != NULL && currPtr->data < n){
		prevPtr = currPtr;
		currPtr = currPtr->next;
	}
	//if (currPtr != NULL && currPtr->data == n) {return;} //se uguale non inserisce
	
	
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

//unisce due liste ordinate in modo ricorsivo
void sorted_merge(NodePtr a, NodePtr b){
	
	//casi base: una lista è vuota
	if(a == NULL){return b;}
	if(b == NULL){return a;}
	
	NodePtr res = NULL;
	
	if(a->data <= b->data){
		res = a;
		res ->next = sorted_merge(a->next, b);
	}
	else{
		res = b;
		res ->next = sorted_merge(a, b->next);
	}
	
	return res;
}


//stampa lista
void printList(NodePtr head){
	NodePtr ptr = head;
	while(ptr){
		printf("%d\n", ptr->data);
		ptr = ptr->next;
	}

//	printf("NULL\n");
}


//unisce due liste (prima la 1 poi la 2)
NodePtr listUnion(NodePtr h1, NodePtr h2){
	
    NodePtr l = NULL;
	
    while(h1 != NULL && h2 != NULL){
		
        if(h1 != NULL){ insert(&temp, h1->val); }
		
        if(h2 != NULL){ insert(&temp, h2->val); }
		
        h1 = h1->next;
        h2 = h2->next;
    }
    return l;
}



//cancellazione della memoria iterativa (Riceve pointer)
void freeSet(NodePtr *head){ 
	
	while(*head != NULL){ (*head) = (*head)->next; }
}

/*STACK*/
//inserisce il nodo in cima allo stack
void push(NodePtr *head, int n){
	
	NodePtr newPtr = malloc(sizeof(Node));
	newPtr->data = n;
	newPtr->next = *head;
	*head = newPtr;
	
}

//preleva e restituisce il valore in cima allo stack
//va bene anche come delete function
int pop(NodePtr *head){ 
	
	if(*head == NULL) return;
	
	NodePtr current = *head;
	int pop_val = (*head)->data;
	*head = (*head)->next;
	current->next = NULL; //sost con free current ma controlla se segfaulta
	
	return pop_val;
}


/*QUEUE*/
//inserimento in coda
void insertQueue(NodePtr *head, NodePtr *tail, int n){  
	
		
	NodePtr newPtr = malloc(sizeof(Node));
	newPtr->next = NULL; 
	newPtr->data = n;
	
	if(*head == NULL){ *head = newPtr; } //la lista è vuota
	else{ (*tail)->next = newPtr; }  //inserisce il nodo in coda
	
	*tail = newPtr;

}


//Scorre la lista fino a trovare corrispondenza, poi stampa il valore
void print_if_found(NodePtr current, int c){
	while (current != NULL){ 
		if (current->data == c){
			printf("%d ", c); 
			break;
		}
		current = current->next; 
	} 
}


	
