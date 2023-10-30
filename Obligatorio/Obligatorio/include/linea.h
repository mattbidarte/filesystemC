/*
 * TAD linea de char, estructura que modela una lista de char.
 */

/* 
 * File:   linea.h
 * Author: farrieta
 *
 * Created on 29 de agosto de 2023, 17:17
 */

#ifndef LINEA_H
#define LINEA_H

typedef struct _rep_linea *TLinea;
typedef char* Cadena;

//Pos-condicion: Crea una linea vacía
TLinea createLine ();

//pos-condicion: Retorna true si la linea "linea" es vacia
bool isEmptyLine (TLinea linea);

//pre-condicion: linea != NULL
//Inserta el caracter letra al inicio de la linea.
void insertCharLine(char letra, TLinea& linea);

//pre-condición linea != NULL
//Retorna el primer caracter de la linea "linea"
char firstCharLine(TLinea linea);

//pre-condicion linea !=NULL
//Retorna un puntero a al siguiente nodo de "linea"
TLinea nextLine(TLinea linea);

//Retorna la cantidad de elementos que tiene la linea "linea"
int countNodesLine(TLinea linea);

//pre-condicion: linea != NULL
//pos-condicion: Elimina el primer nodo de la linea "linea"
void deleteFirstChar(TLinea& linea);

//pre-condicion: linea != NULL
//pos-condicion: Elimina el ultimo nodo de la linea "linea"
void deleteLastChar(TLinea& linea);

//Pos-condicion: Destruye toda la memoria utilizada por linea
void destroyLine(TLinea& linea);
    

#endif /* LINEA_H */

