/* 5059724 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/linea.h"
#include "../include/fila.h"
#include "../include/directorio.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

struct _lista_archivos {
    TArchivo elemento;
    _lista_archivos* sig;
};

typedef struct _lista_archivos* ListaArchivo;

typedef struct _rep_directorio *TDirectorio;

struct _rep_directorio {
    Cadena nombreDir;
    ListaArchivo archivo;
};

//Crea el directorio de nombre Raíz del filesystem 
TDirectorio createRootDirectory(){
    TDirectorio nodo = new _rep_directorio;
       
    nodo->nombreDir = new char[5];
    strcpy(nodo->nombreDir, "RAIZ");
    nodo->archivo = NULL;
    
    return nodo;   
};

//retorna true si el directorio "directorio" no tiene archivos
bool isEmptyDirectory(TDirectorio directorio){
    return (directorio->archivo==NULL);
};

//retorna true si el archivo de nombre "nombreArchivo existe en el directorio "directorio"
bool existFileDirectory(TDirectorio directorio, Cadena nombreArchivo){ 
    ListaArchivo currentArchivo = directorio->archivo; // Recorrer la lista de archivos en el directorio
    while (currentArchivo != NULL) {
        if (strcmp(nombreArchivo, getFileName(currentArchivo->elemento)) == 0) {
            return true; // El archivo existe en el directorio
        }
        currentArchivo = currentArchivo->sig;
    }
    return false; // El archivo no se encontró en el directorio
};

//pre-condicion existe el archivo de nombre nombreArchivo en el directorio "directorio"
//pos-condicion: retorna un puntero al archivo de nombre "nombreArchivo"
TArchivo getFileDirectory(TDirectorio directorio, Cadena nombreArchivo){
    // Recorrer la lista de archivos en el directorio
    ListaArchivo currentArchivo = directorio->archivo;
    while (currentArchivo != NULL) {
        if (strcmp(nombreArchivo, getFileName(currentArchivo->elemento)) == 0) {
            return currentArchivo->elemento; //El archivo existe en el directorio
        } else {
            currentArchivo = currentArchivo->sig;
        }
    }

    // El archivo no se encontró en el directorio
    return NULL;
}

//pre-condicion: No existe en directorio un archivo de nombre "nombreArchivo"
//crea un archivo vacio con nombre nombreArchivo y permiso de lectura/escritura
void createFileInDirectory(TDirectorio& directorio, Cadena nombreArchivo){
    Cadena nom;
    Cadena ext;
    
    nom = strtok(nombreArchivo, ".");
    ext = strtok(NULL, ".");
    
    TArchivo nuevoArchivo = createEmptyFile(nom, ext);
    
    // Crear un nuevo nodo _lista_archivos
    ListaArchivo nuevoNodo = new _lista_archivos;
    nuevoNodo->elemento = nuevoArchivo;
    nuevoNodo->sig = NULL;

    // Verificar si la lista está vacía
    if (isEmptyDirectory(directorio)) {
        directorio->archivo = nuevoNodo;
    } else {
        // Encontrar el último nodo en la lista
        ListaArchivo ultimo = directorio->archivo;
        while (ultimo->sig != NULL) {
            ultimo = ultimo->sig;
        }
        // Conectar el último nodo al nuevo nodo
        ultimo->sig = nuevoNodo;
    }      
};

//pre condicion: el archivo nombreArchivo existe en directorio
//pos-condicion: inserta una nueva fila al comienzo del archivo nombreArchivo conteniendo los chars texto
void insertTextFile(TDirectorio& directorio, Cadena nombreArchivo, Cadena texto){
    TArchivo archivo = getFileDirectory(directorio, nombreArchivo);
    insertChartsNewRow(archivo, texto);
};

//pre condicion: el archivo nombreArchivo existe en directorio
//pos-condicion: agrega al comienzo de la primera fila del archivo de nombre nombreArchivo los caracteres de texto
//desplazando los caracteres existentes hacia la derecha
void insertCharsFileFirstLine(TDirectorio& directorio, Cadena nombreArchivo, Cadena texto){
    TArchivo archivo = getFileDirectory(directorio, nombreArchivo);
    if(isEmptyFile(archivo)){
        insertTextFile(directorio, nombreArchivo, texto);
    }else {
        insertChartsFirstRow(archivo, texto);
    }
    
};

//pre-condicion: existe el archivo de nombre "nombreArchivo" en el directorio "directorio"
//pos-condicion: elimina el archivo del directorio "directorio" y toda la memoria utilizada por este.
void deleteFileDirectory(TDirectorio& directorio, Cadena nombreArchivo){
    TArchivo aBorrar = getFileDirectory(directorio, nombreArchivo);
    ListaArchivo actual = directorio->archivo;
    ListaArchivo anterior = NULL;
    
    // Recorre la lista de archivos en el directorio para encontrar el archivo a eliminar
    while (actual != NULL) {
        if (actual->elemento == aBorrar) {
            // Encontrado el archivo con el nombre especificado
            if (anterior == NULL) {
                // Si es el primer archivo en la lista
                directorio->archivo = actual->sig;
            } else {
                // Si no es el primer archivo, ajustar los punteros del nodo anterior
                anterior->sig = actual->sig;
            }
            // Eliminar el archivo y liberar su memoria
            destroyFile(aBorrar);
            delete actual; // Liberar la memoria del nodo de archivo
            return; // Salir de la función después de eliminar el archivo
        } else {
            // Avanzar en la lista
            anterior = actual;
            actual = actual->sig;
        }
    }
};

//pre-condicion: existe el archivo de nombre "nombreArchivo" en el directorio "directorio"
//pos-condicion: elimina los "cantidad" caracteres finales del archivo nombreArchivo
void deleteCharsFile(TDirectorio& directorio, Cadena nombreArchivo, int cantidad){
    TArchivo archMod = getFileDirectory(directorio, nombreArchivo);
    deleteCharterFile (archMod, cantidad);
};

//pre-condicion: existe el archivo de nombre "nombreArchivo" en el directorio "directorio"
//pos-condicion: le setea el permiso de escritura al archivo de nombre nombreArchivo
void setFilePermission(TDirectorio& directorio, Cadena nombreArchivo, bool permisoEscritura){
    TArchivo archMod = getFileDirectory(directorio, nombreArchivo);
    setWritePermission(archMod, permisoEscritura);
};

//pre-condicion: existe el archivo de nombre "nombreArchivo" en el directorio "directorio"
//pos-condicion: imprime el contenido del archivo "nombreArchivo"
void printFile(TDirectorio& directorio, Cadena nombreArchivo){
    TArchivo archivo = getFileDirectory(directorio, nombreArchivo);
    int totalLineas = getCountRow(archivo);
    int caracteresTotales = getCountChars(archivo);
    if (caracteresTotales == 0)
        printf("  - Archivo vacio -\n");
    else{
        for (int numero_linea = 1; numero_linea <= totalLineas; numero_linea++) {
            //printf("  Línea %d: ", numero_linea);
            printf("  %d: ", numero_linea);
            printLineFile(archivo, numero_linea);
            printf("\n");
        }
    }
};

//pos-condicion destruye toda la memoria de directorio
void destroyDirectory (TDirectorio& directorio){
    // Verificar si el directorio está vacío
    if (!isEmptyDirectory(directorio)) {
        ListaArchivo actualArchivo = directorio->archivo;
        ListaArchivo nextArchivo;
        
        // Recorrer y destruir todos los archivos en el directorio
        while (actualArchivo != NULL) {
            nextArchivo = actualArchivo->sig; // Almacenar el siguiente archivo antes de destruir el actual
            destroyFile(actualArchivo->elemento); // Destruir el archivo actual
            actualArchivo = nextArchivo; // Avanzar al siguiente archivo
        }
    }
    
    // Borrar la memoria usada por el nombre del directorio
    delete[] directorio->nombreDir;
    
    // Eliminar el directorio
    delete directorio;
 
    directorio = NULL;
};