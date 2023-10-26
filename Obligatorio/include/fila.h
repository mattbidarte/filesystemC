/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Fila.h
 * Author: 9754farrieta
 *
 * Created on 1 de septiembre de 2023, 14:23
 */
#include "../include/linea.h"

#ifndef FILA_H
#define FILA_H

typedef struct _rep_fila* TFila;

//Pos-condición crea una fila vacía.
TFila createRow();

//Pos-Condición retorna true si la fila es vacía.
bool isEmptyRow(TFila fila);

//Pos-Condición modifica el primer elemento de la fila "fila" agregando los caracteres al inicio del primer elemento "linea" de la fila.
void modifyRow (TFila &fila, Cadena caracteres);

//Pos-Condición Inserta una nueva fila al principio de "fila"
 void insertRow (TFila &fila, TLinea linea);
 
//pre-condicion: fila !=NULL
//pos-condicion: retorna un puntero al primer nodo de la fila "fila"
TLinea headRow(TFila fila);

//pre-condicion: fila !=NULL
//pos-condicion: Retorna un puntero al siguente elemento de la fila "fila"
TFila nextRow (TFila fila);
 
//pre-condicion: fila != NULL
//elimina el primer nodo de la fila "fila"
void deleteFirstRow (TFila &fila);
 
//Elimina toda la memoria de la fila "fila"
void deleteRows (TFila& fila);
 

#endif /* FILA_H */
