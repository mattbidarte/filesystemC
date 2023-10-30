/* 5059724 */ 
/*
 Modulo que implemente el archivo linea.h
*/

#include "../include/linea.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

struct _rep_linea {
    char valor;
    TLinea sig   ;
};

typedef struct _rep_linea *TLinea;

//Pos-condicion: Crea una linea vacía
TLinea createLine (){
    return NULL;
};

//pos-condicion: Retorna true si la linea "linea" es vacia
bool isEmptyLine (TLinea linea){
    return (linea==NULL);
};

//Inserta el caracter letra al inicio de la linea.
void insertCharLine(char letra, TLinea& linea){
    TLinea nodo = new _rep_linea;
    nodo->valor = letra;
    nodo->sig = linea;
    linea = nodo;                 
};

//pre-condición linea != NULL
//Retorna el primer caracter de la linea "linea"
char firstCharLine(TLinea linea) {
    return linea->valor;
};

//pre-condicion linea !=NULL
//Retorna un puntero a al siguiente nodo de "linea"
TLinea nextLine(TLinea linea){
    return linea->sig;
};

//Retorna la cantidad de elementos que tiene la linea "linea"
int countNodesLine(TLinea linea){
    int cont = 0;
    while (!isEmptyLine(linea)){
        cont++;
        linea = nextLine(linea);
    }
    return cont;
};

//pre-condicion: linea != NULL
//pos-condicion: Elimina el primer nodo de la linea "linea"
void deleteFirstChar(TLinea& linea){
    TLinea nodoBorrar = linea;      //auxiliar igualado a puntero linea
    linea = linea->sig;             //primer nodo ahora va a ser el segundo
    delete nodoBorrar;              //borrado primer nodo
};

//pre-condicion: linea != NULL
//pos-condicion: Elimina el ultimo nodo de la linea "linea"
void deleteLastChar(TLinea& linea){   
    //actual es = linea y anterior va a ser uno menos que actual
    TLinea actual = linea;
    TLinea anterior = NULL;
    
    if(linea->sig==NULL){
        delete actual;
        linea = NULL;
    }else {
        // Si hay más de un elemento en la lista, avanzar hasta el último nodo
        while(actual->sig != NULL){
            //anterior es uno menos que actual
            anterior = actual;
            actual = actual->sig;
        };
        // Actualizar el puntero siguiente del nodo anterior para saltar el último nodo
        anterior->sig = NULL;
        // Borrar la memoria del último nodo usando delete
        delete actual; 
    }
};

//Pos-condicion: Destruye toda la memoria utilizada por linea
void destroyLine(TLinea& linea){
    TLinea aux = linea;
    while(!isEmptyLine(linea)){
        linea = linea->sig;     // Avanzar al siguiente nodo antes de eliminar el actual
        delete aux;             // Liberar la memoria del nodo actual
        aux = linea;            // Actualizar aux para apuntar al siguiente nodo
    }
    
    linea = NULL;               
};
