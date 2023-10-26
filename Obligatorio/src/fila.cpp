/* 5059724 */ 

#include "../include/fila.h"
#include "../include/linea.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

struct _rep_fila {
    TLinea lin;
    TFila sig;
};

typedef struct _rep_fila* TFila;

//Pos-condición crea una fila vacía.
TFila createRow(){
    return NULL;
}

//Pos-Condición retorna true si la fila es vacía.
bool isEmptyRow(TFila fila){
    return (fila==NULL);
}

//Pos-Condición Inserta una nueva fila al principio de "fila"
 void insertRow (TFila &fila, TLinea linea){
    TFila nodo = new _rep_fila;
    nodo->sig = fila;
    nodo->lin = linea;
    fila = nodo;
 }
 
 
//Pos-Condición modifica el primer elemento de la fila "fila" agregando los caracteres  
//al inicio del primer elemento "linea" de la fila.
void modifyRow (TFila &fila, Cadena caracteres){
    int length = strlen(caracteres);    
    for (int i = length - 1; i >= 1; i--) {
        insertCharLine(caracteres[i], fila->lin);
    }
};
 
//pre-condicion: fila !=NULL
//pos-condicion: retorna un puntero al primer nodo de la linea "linea"
TLinea headRow(TFila fila){
    return fila->lin;
}

//pre-condicion: fila !=NULL
//pos-condicion: Retorna un puntero al siguente elemento de la fila "fila"
TFila nextRow (TFila fila){
    return fila->sig;
}
 
//pre-condicion: fila != NULL
//elimina el ultimo nodo de la fila "fila"
void deleteFirstRow (TFila &fila){
    TFila actual = fila;
    TFila anterior = NULL;
    // Si hay más de un elemento en la lista, avanzar hasta el último nodo
    while(actual->sig != NULL){
        //anterior es uno menos que actual
        anterior = actual;
        actual = actual->sig;
    };// ir al final
    destroyLine(actual->lin);
    // Actualizar el puntero siguiente del nodo anterior para saltar el último nodo
    anterior->sig = NULL;
    // Borrar la memoria del último nodo usando delete
    delete actual; 
    
}
 
//Elimina toda la memoria de la fila "fila"
void deleteRows (TFila& fila){
    TFila aux = fila;
    while(!isEmptyRow(fila)){
        destroyLine(fila->lin);
        fila = fila->sig;      // Avanzar al siguiente nodo antes de eliminar el actual
        delete aux;            // Liberar la memoria del nodo actual
        aux = fila;            // Actualizar aux para apuntar al siguiente nodo
    }
    fila = NULL; 
    aux = NULL;
}