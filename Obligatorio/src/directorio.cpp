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
    TDirectorio root;
    TDirectorio padre;
    TDirectorio primerHijo;
    TDirectorio primerHermano;
    Cadena ruta;
};

//Crea el directorio de nombre Raíz del filesystem 
TDirectorio createRootDirectory(){
    TDirectorio nodo = new _rep_directorio;
       
    nodo->nombreDir = new char[5];
    strcpy(nodo->nombreDir, "RAIZ");
    nodo->archivo = NULL;
    nodo->padre = NULL;
    nodo->primerHermano = NULL;
    nodo->primerHijo = NULL;
    nodo->root = nodo;
    nodo->ruta = new char[5];
    strcpy(nodo->ruta, "RAIZ");
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
    
     // Recorrer y destruir los directorios hijos del directorio
    TDirectorio hijo = directorio->primerHijo;
    while (hijo != NULL) {
        TDirectorio siguienteHijo = hijo->primerHermano;
        destroyDirectory(hijo);
        hijo = siguienteHijo;
    }
    
    // Borrar la memoria usada por el nombre del directorio
    delete[] directorio->nombreDir;
    
    // Borrar la memoria usada por la ruta del directorio
    delete[] directorio->ruta;
    
    // Eliminar el directorio
    delete directorio;
 
    directorio = NULL;
};

//******************************Nuevas funciones ***************************************

//retorna true si el directorio de nombre nombreDierctorioHijo es hijo del directorio "directorio"
bool existChildrenDirectory(TDirectorio directorio, Cadena nombreDirectorioHijo){
    // Caso base: si el directorio no tiene hijos, devuelve falso
    if (directorio->primerHijo == NULL) {
        return false;
    }

    // Recorre todos los hijos del directorio
    TDirectorio primerHijo = directorio->primerHijo;
    // Comprueba si el nombre del directorio actual coincide con el nombre buscado
    if (strcmp(primerHijo->nombreDir, nombreDirectorioHijo) == 0) {
        return true;
    } else {
        // Llamada recursiva para comprobar en los hermanos del directorio actual
        if (primerHijo->primerHermano != NULL) {
            return existChildrenDirectory(primerHijo->primerHermano, nombreDirectorioHijo);
        } else {
            return false;
        }
    }
};

//pre-condición el directorio de nombre nombreDirectorioHijo es hijo del directorio Directorio
//pos-condición retorna un puntero al directorio de nombre nombreDirectorioHijo
TDirectorio moveChildrenDirectory (TDirectorio& directorio, Cadena nombreDirectorioHijo){
    TDirectorio directorioHijo = directorio->primerHijo;
    
    while (directorioHijo != NULL) {
        if (strcmp(directorioHijo->nombreDir, nombreDirectorioHijo) == 0) {
            return directorioHijo;
        }else
            directorioHijo = directorioHijo->primerHermano;
    }
    
    return NULL; // Si no se encuentra el directorio hijo
};

//retorna un puntero de TDirectorio al padre del directorio directorio
TDirectorio moveFatherDirectory (TDirectorio& directorio){
    return directorio->padre;
};

//retorna un puntero de TDirectorio al directorio ROOT
TDirectorio moveRootDirectory (TDirectorio& directorio){
    return directorio->root;
};

//retorna true si el directorio directorio es root
bool isRootDirectory (TDirectorio directorio){
    return (directorio == directorio->root);
};

//Pre-Condición del directorio de nombre nombreDirectorio no es hijo del directorio "directorio"
//pos-condición crea un directorio vacío, de nombre nombreDirectorio, hijo del directorio "directorio"
void createChildrenDirectory (TDirectorio& directorio, Cadena nombreDirectorio){
    TDirectorio nuevoDir = new _rep_directorio; 
    nuevoDir->nombreDir = new char[strlen(nombreDirectorio) + 1];
    strcpy(nuevoDir->nombreDir, nombreDirectorio);
    nuevoDir->archivo = NULL;
    nuevoDir->padre = directorio;
    nuevoDir->primerHermano = NULL;
    nuevoDir->primerHijo = NULL;
    
    nuevoDir->ruta = new char[strlen(nombreDirectorio) + strlen(directorio->ruta) + 2];
    strcpy(nuevoDir->ruta, directorio->ruta);
    strcat(nuevoDir->ruta, "/");
    strcat(nuevoDir->ruta, nombreDirectorio);
    
    if(directorio->padre == NULL)
        nuevoDir->root = directorio;
    else
        nuevoDir->root = directorio->root;
    
    // Agregar el nuevo directorio como el primer hijo
    if (directorio->primerHijo == NULL) {
        directorio->primerHijo = nuevoDir;
    } else {
        // Agregar el nuevo directorio de manera alfabeticamente
        TDirectorio actual = directorio->primerHijo;
        TDirectorio anterior = NULL;

        while (actual != NULL && strcmp(nombreDirectorio, actual->nombreDir) > 0) {
            anterior = actual;
            actual = actual->primerHermano;
        }

        if (anterior == NULL) {
            // Agregar el nuevo directorio al principio
            nuevoDir->primerHermano = directorio->primerHijo;
            directorio->primerHijo = nuevoDir;
        } else {
            // Agregar el nuevo directorio después de "anterior"
            nuevoDir->primerHermano = anterior->primerHermano;
            anterior->primerHermano = nuevoDir;
        }
    }
};

//pre-condición el directorio de nombre nombreDirectorio es hijo del directorio directorio
//pos-condición elimina el directorio de nombre nombreDirectorio que es hijo del directorio directorio
//eliminando toda su memoria
void removeChildrenDirectory (TDirectorio& directorio, Cadena nombreDirectorio){
    TDirectorio aBorrar = moveChildrenDirectory(directorio, nombreDirectorio);
    
    if (directorio->primerHijo == aBorrar) {
        directorio->primerHijo = aBorrar->primerHermano;
    } else {
        TDirectorio hermano = directorio->primerHijo;
        while (hermano != NULL) {
            if (hermano->primerHermano == aBorrar) {
                hermano->primerHermano = aBorrar->primerHermano;
                break;
            }else
                hermano = hermano->primerHermano;
        }
    }

    destroyDirectory(aBorrar);
};

//pre-condición el directorio origen es sub-directorio del directorio "directorio"
//pos-condición mueve el directorio origen y todo su contenido al directorio destino
void moveSubDirectory (TDirectorio& directorio, TDirectorio origen, TDirectorio& destino);

//pre-condición el archivo origen es sub archivo del directorio directorio
//pos-condición se mueve el archivo TArchivo como hijo del directorio destino
void moveSubArchive (TDirectorio& directorio, TArchivo origen, TDirectorio destino);

//pre-condición: directorio no es el directorio ROOT
//pos-condición: retorna un puntero al primer hermano del diretorio "directorio"
TDirectorio firstBrotherDirectory(TDirectorio directorio){
    return directorio->primerHermano;
};

//pos-condición: retorna un puntero al primer hijo del directorio "directorio"
TDirectorio firstChildrenDirectory(TDirectorio directorio){
    return directorio->primerHijo;
};

//Retorna true si el directorio subdir es sub-directorio del directorio "directorio" en cualquier nivel.
bool isSubDirectoryRoot (TDirectorio directorio, Cadena ruta);

//pos-condición imprime el directorio ejecuando DIR
void printDirectoryDir (TDirectorio directorio){
    ListaArchivo actualArchivo = directorio->archivo;
    TDirectorio primerHijo = directorio->primerHijo;
    
    printf("%s\n", directorio->ruta);
    
    while (actualArchivo != NULL) {
        TArchivo actual = actualArchivo->elemento;
        if (haveWritePermission(actual)) {
            printf("%s        Lectura/Escritura\n", getFileName(actual));
        } else{
            printf("%s        Lectura\n", getFileName(actual));
        }
        actualArchivo = actualArchivo->sig;
    }

    while (primerHijo != NULL) {
        printf("%s\n", primerHijo->nombreDir);
        primerHijo = primerHijo->primerHermano;
    }
};

//pos-condición imprime el directorio ejecutando DIR /S
void printDirectoryDirS (TDirectorio directorio);