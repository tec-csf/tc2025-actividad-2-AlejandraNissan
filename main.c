//Alejandra Nissan
//A01024682

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Funciones para imprimir
typedef void (* impresion)(void *);

void imprimirInt(void * vecto);
void imprimirFloat(void * vector);
void imprimirLibro(void * vector);
void imprimirChar(void * vector);

//Iterador genérico
typedef void (*t_iterator)(void *, size_t, size_t, impresion, int);


void recorre(t_iterator, void *, size_t, size_t,impresion, int);

//Tipos de iteradores
void forwardIterator(void *, size_t, size_t, impresion, int);
void reverseIterator(void *, size_t, size_t, impresion, int);
void bidirectionalIterator(void *, size_t, size_t, impresion, int);

//Funciones para iteradores
void* begin(void *, size_t, size_t);
void* end(void*, size_t, size_t);
void* next(void *, void *, size_t, size_t);
void* previous(void *, void *, size_t, size_t);


typedef struct{
  char * titulo;
  int paginas;
}Libro;


int main (int argc, const char* arv[]){
    //Arreglo de enteros
    int num = 10;
    int * arregloInt = (int*)malloc(num*sizeof(int));
    int * aux = arregloInt;
    int * last = arregloInt + num;
    Libro * arregloLibro = (Libro*)malloc(num*sizeof(Libro));
    Libro * auxL = arregloLibro;
    Libro * lastL = arregloLibro + num;

    printf("Int array before iteration:\n");
    for (; aux < last; ++aux) {
        *aux = rand() % 100;
        printf(" %d ", *aux);
    }

    printf("\n Book array before iteration:\n");    
    for(; auxL < lastL; ++auxL){
        auxL->paginas = rand() %100;
        auxL->titulo = (char * ) malloc(sizeof(char) * 30);
        strcpy(auxL->titulo, "Becoming");
        printf("Title: %s, Pages: %d\n", auxL->titulo, auxL->paginas);
    }
    printf("\n");

    //Funcionalidad con arreglo de enteros
    recorre(&forwardIterator, arregloInt, num, sizeof(int), &imprimirInt, -1);
    recorre(&reverseIterator, arregloInt, num, sizeof(int), &imprimirInt, -1);
    recorre(&bidirectionalIterator, arregloInt, num, sizeof(int), &imprimirInt, 1);
    recorre(&bidirectionalIterator, arregloInt, num, sizeof(int), &imprimirInt, 0);

    free(arregloInt);

    //Funcionalidad con arreglo de libros
    recorre(&forwardIterator, arregloLibro, num, sizeof(Libro), &imprimirLibro, -1);
    recorre(&reverseIterator, arregloLibro, num, sizeof(Libro), &imprimirLibro, -1);
    recorre(&bidirectionalIterator, arregloLibro, num, sizeof(Libro), &imprimirLibro, 1);
    recorre(&bidirectionalIterator, arregloLibro, num, sizeof(Libro), &imprimirLibro, 0);

    for(int i = 0; i<num; i++){
        free((arregloLibro+i)->titulo);
    }
    free(arregloLibro);
    return 0;
}

void recorre(t_iterator algoritmo, void * vector, size_t numElementos, size_t tamano, impresion ptrImprimir, int sentido){
    (*algoritmo)(vector, numElementos, tamano, ptrImprimir, sentido);
}

void forwardIterator(void * vector, size_t numElementos, size_t tamano, impresion ptrImprimir, int sentido){
    printf("Forward iterator\n");
    for(void* aux = begin(vector, numElementos, tamano); aux<end(vector, numElementos, tamano); aux=next(vector, aux, numElementos, tamano)){
        (*ptrImprimir)(aux);
    }

}

void reverseIterator(void * vector, size_t numElementos, size_t tamano, impresion ptrImprimir, int sentido){
    printf("Reverse iterator\n");
    for(void* aux = (end(vector, numElementos, tamano)- tamano); aux>=begin(vector, numElementos, tamano); aux=previous(vector, aux, numElementos, tamano)){
        (*ptrImprimir)(aux);
    }
}

void bidirectionalIterator(void * vector, size_t numElementos, size_t tamano, impresion ptrImprimir, int sentido){
    if(sentido == 1){
        printf("Bidirectional iterator going forward\n");
        forwardIterator(vector, numElementos, tamano, ptrImprimir, sentido);
    }
    else if(sentido == 0){
        printf("Bidirectional iterator going in reverse\n");
        reverseIterator(vector, numElementos, tamano, ptrImprimir, sentido);        
    }
    else{
        printf("That is not an option, 1 goes forward and 0 goes in reverse");
    }
}

void* begin(void* vector, size_t numElementos, size_t tamano){
    return vector;
}

void* next(void* vectorInicial, void* vector, size_t numElementos, size_t tamano){
    if((vector)<= end(vectorInicial, numElementos, tamano)){
        vector+= tamano;
        return (vector);
    }
    else{
        return NULL;
    }
}

void* end(void* vector, size_t numElementos, size_t tamano){
    return (vector + ((numElementos)*tamano));
}


void* previous(void* vectorInicial, void* vector, size_t numElementos, size_t tamano){
    if((vector)> vectorInicial){
        vector-= tamano;
        return (vector);
    }
    else{
        return NULL;
    }
}


//Funciones de impresion
void imprimirInt(void * vector){
    int * vectorInt = (int*) vector; 
    printf("%d\n", *vectorInt);
}
void imprimirFloat(void * vector){
    float * vectorFloat = (float*) vector; 
    printf("%f\n", *vectorFloat);
}
void imprimirLibro(void * vector){
    Libro * vectorLibro = (Libro*) vector; 
    printf("Title: %s ", vectorLibro->titulo);
    printf("Pages: %d\n", vectorLibro->paginas);
}
void imprimirChar(void * vector){
    char * vectorChar = (char*) vector; 
    printf("%c\n", *vectorChar);
}
















