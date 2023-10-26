/* 5059724 */

#include "../include/archivo.h"
#include "../include/fila.h"
#include "../include/linea.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>



struct _rep_archivo {
    Cadena nombre;
    Cadena extension;
    bool permiso;
    TFila fila;
};

typedef struct _rep_archivo *TArchivo;

//Crea un archivo vacío con nombre nombreArchivo, extensión extension y con permiso de lectura/escritura
//El archivo no contiene filas.
TArchivo createEmptyFile (Cadena nombreArchivo, Cadena extension){
    TArchivo archivo = new _rep_archivo;   
    
    archivo->nombre = new char [16];
    strcpy(archivo->nombre, nombreArchivo);
    archivo->extension = new char [4];
    strcpy(archivo->extension, extension);
    
    archivo->permiso = true;
    archivo->fila = createRow();
    
    return archivo;
}

//Retorna un puntero a un array con el nombre del archivo "archivo"
char* getFileName (TArchivo archivo){ 
    int lenNombre = strlen(archivo->nombre);
    int lenExtension = strlen(archivo->extension);
    int lenTotal = lenNombre + 1 + lenExtension + 1;
   
    Cadena nombreCompleto = new char[lenTotal];
    
    strcpy(nombreCompleto, archivo->nombre);
    strcat(nombreCompleto, ".");
    strcat(nombreCompleto, archivo->extension);
    
    return nombreCompleto;
}

//Retorna true si archivo tiene permiso de escritura
bool haveWritePermission (TArchivo archivo){
    return (archivo->permiso==true);
}

//Retorna retorna un puntero a la primer fila del archivo "archivo"
TFila firstRowFile (TArchivo archivo){
    return archivo->fila;
};


//retorna true si archivo no tiene filas;
bool isEmptyFile(TArchivo archivo){
    return (firstRowFile(archivo)==NULL);
}

//retorna true si el archivo no tiene filas, es decir el archivo es vacío.
bool isEmptyRowFile(TArchivo archivo){
    return (firstRowFile(archivo)==NULL);
};

//Retorna un puntero a la primer Fila de archivo
TLinea getFirstRow (TArchivo archivo){
     return headRow(firstRowFile(archivo));
}

//Retorna un puntero a la siguiente Fila de archivo
TLinea getNextRow (TArchivo archivo){
    return headRow(nextRow(firstRowFile(archivo)));
}

//Retorna retorna un puntero a la siguiente fila del "archivo"
TFila nextRowFile (TArchivo archivo){
    return nextRow(firstRowFile(archivo));
};

//Retorna la cantidad de Fila que tiene el archvio "archivo"
int getCountRow (TArchivo archivo){
    int cont = 0;
    TFila filaActual = archivo->fila;

    while (filaActual != NULL) {
        cont++;
        filaActual = nextRow(filaActual);
    }

    return cont;
}

//Retorna la cantidad de caracteres que tiene el archvio "archivo"
int getCountChars (TArchivo archivo){
    int cont = 0;
    TFila filaActual = archivo->fila; // Guardar una copia del puntero de fila actual

    while (!isEmptyFile(archivo)) {
        int nodosFila = countNodesLine(getFirstRow(archivo));
        cont += nodosFila;
        archivo->fila = nextRow(archivo->fila);
    }

    archivo->fila = filaActual; // Restaurar el puntero de fila original
    return cont;
}

//imprime la Linea del archivo indicada por "numero_linea"
//pre-condición el archivo tiene por lo menos numero_linea de lineas
void printLineFile(TArchivo archivo, int numero_linea){
    int total_filas = getCountRow(archivo);
    
    if(total_filas >= numero_linea){
        int cont = 1;
        TFila filaActual = archivo->fila;

        while (cont != numero_linea) {
            cont++;
            filaActual = nextRow(filaActual); // Mover la copia en lugar de la original
        } // Estamos parados en la línea número "numero_linea"

        TLinea linea = headRow(filaActual); // Obtener la primera línea de la fila actual

        while (!isEmptyLine(linea)) {
            printf("%c", firstCharLine(linea));
            linea = nextLine(linea);
        }
    } 
};
    
//Elimina los cant cantidad de caracteres finales del "archivo"
//En caso que el archivo tenga menos caracteres los elimina a todos
void deleteCharterFile (TArchivo &archivo, int cant){
   // Si cant es mayor o igual al total de caracteres, eliminar todo el archivo.
    int cantidadActual = getCountChars(archivo);
    if (cant >= cantidadActual) {
        deleteRows(archivo->fila);
        archivo->fila = createRow();
    }else {
        TFila primeraFila = archivo->fila;
   
         while (!isEmptyRow(primeraFila) && cant > 0) {    
            // Avanzar hasta la última fila
            while (!isEmptyRow(primeraFila) && !isEmptyRow(nextRow(primeraFila))) {
                primeraFila = nextRow(primeraFila);
            }//ultima fila 
            int caracteresEnFila = countNodesLine(headRow(primeraFila));
            if (caracteresEnFila > cant) {
                // Eliminar los últimos cant caracteres de esta fila
                TLinea actual = headRow(primeraFila);
                for (int i = 0; i < cant; i++) {
                    deleteLastChar(actual);
                }
                cant = 0;  // No necesitamos borrar más caracteres
            } else {
                // Eliminar toda la fila actual
                deleteFirstRow(archivo->fila);
                cant -= caracteresEnFila;
                primeraFila = archivo->fila;
            }
        }
     } 
};
    
//Cambia el nombre del archivo "archivo" por nuevoNombre
void setName(TArchivo &archivo, Cadena nuevoNombre);

//Cambia la extension del "archivo" por nuevaExtension
void setExtension(TArchivo &archivo, Cadena nuevaExtension);

//Inserta el texto "texto" como una nueva fila al comienzo del archivo 
void insertChartsNewRow(TArchivo &archivo, Cadena texto){
    TLinea nuevaLinea = createLine();
    insertRow(archivo->fila, nuevaLinea);
    modifyRow(archivo->fila, texto);
}

//pre-condicion El archivo tiene por lo menos una fila
//Inserta el texto "texto" al inicio de la primer fila del archivo
void insertChartsFirstRow(TArchivo &archivo, Cadena texto){ 
    TFila primeraFila = archivo->fila;
    modifyRow(primeraFila, texto);    
};

//si valor == true se le asigna el permiso de escritura de "archivo"
//si valor == false se le quita el permiso de escritura de "archivo"
//pre-condicion archivo !=NULL
void setWritePermission(TArchivo &archivo, bool valor){
    if(valor==true){
        archivo->permiso=true;
    }else{
        archivo->permiso=false;
    }   
}


//elimina toda la memoria utilizada por "archivo"
void destroyFile (TArchivo &archivo){
    while(!isEmptyFile(archivo)){
        deleteRows(archivo->fila);
    }
    // Liberar la memoria de las cadenas
    delete[] archivo->nombre;
    delete[] archivo->extension;

    // Eliminar el archivo
    delete archivo; 
}

