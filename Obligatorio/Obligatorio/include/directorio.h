/*
  Módulo de definición de 'Directorio'.
  En esta primer tarea solo se considera un unico directorio llamado RAIZ
  Laboratorio de Tecnologo informatico turno nocturno 2023.
  UTU-LATU
*/

#ifndef _DIRECTORIO_H
#define _DIRECTORIO_H

#include "../include/archivo.h"
#include "../include/linea.h"
#include "../include/fila.h"


// Representación de 'TDirectorio'.
// Se debe definir en 'directorio.cpp'.
// struct _rep_directorio;
// Declaración del tipo 'TDirectorio'

typedef struct _rep_directorio *TDirectorio;

//Crea el directorio de nombre Raíz del filesystem 
TDirectorio createRootDirectory();

//retorna true si el directorio "directorio" no tiene archivos
bool isEmptyDirectory(TDirectorio directorio);

//retorna true si el archivo de nombre "nombreArchivo existe en el directorio "directorio"
bool existFileDirectory(TDirectorio directorio, Cadena nombreArchivo);

//pre-condicion existe el archivo de nombre nombreArchivo en el directorio "directorio"
//pos-condicion: retorna un puntero al archivo de nombre "nombreArchivo"
TArchivo getFileDirectory(TDirectorio directorio, Cadena nombreArchivo);

//pre-condicion: No existe en directorio un archivo de nombre "nombreArchivo"
//crea un archivo vacio con nombre nombreArchivo y permiso de lectura/escritura
void createFileInDirectory(TDirectorio& directorio, Cadena nombreArchivo);

//pre condicion: el archivo nombreArchivo existe en directorio
//pos-condicion: inserta una nueva fila al comienzo del archivo nombreArchivo conteniendo los chars texto
void insertTextFile(TDirectorio& directorio, Cadena nombreArchivo, Cadena texto);

//pre condicion: el archivo nombreArchivo existe en directorio
//pos-condicion: agrega al comienzo de la primera fila del archivo de nombre nombreArchivo los caracteres de texto
//desplazando los caracteres existentes hacia la derecha
void insertCharsFileFirstLine(TDirectorio& directorio, Cadena nombreArchivo, Cadena texto);

//pre-condicion: existe el archivo de nombre "nombreArchivo" en el directorio "directorio"
//pos-condicion: elimina el archivo del directorio "directorio" y toda la memoria utilizada por este.
void deleteFileDirectory(TDirectorio& directorio, Cadena nombreArchivo);

//pre-condicion: existe el archivo de nombre "nombreArchivo" en el directorio "directorio"
//pos-condicion: elimina los "cantidad" caracteres iniciales del archivo nombreArchivo
void deleteCharsFile(TDirectorio& directorio, Cadena nombreArchivo, int cantidad);

//pre-condicion: existe el archivo de nombre "nombreArchivo" en el directorio "directorio"
//pos-condicion: le setea el permiso de escritura al archivo de nombre nombreArchivo
void setFilePermission(TDirectorio& directorio, Cadena nombreArchivo, bool permisoEscritura);

//pre-condicion: existe el archivo de nombre "nombreArchivo" en el directorio "directorio"
//pos-condicion: imprime el contenido del archivo "nombreArchivo"
void printFile(TDirectorio& directorio, Cadena nombreArchivo);

//pos-condicion destruye toda la memoria de directorio
void destroyDirectory (TDirectorio& directorio);

//******************************Nuevas funciones **************************************

//retorna true si el directorio de nombre nombreDierctorioHijo es hijo del directorio "directorio"
bool existChildrenDirectory(TDirectorio directorio, Cadena nombreDirectorioHijo);

//pre-condición el directorio de nombre nombreDirectorioHijo es hijo del directorio Directorio
//pos-condición retorna un puntero al directorio de nombre nombreDirectorioHijo
TDirectorio moveChildrenDirectory (TDirectorio& directorio, Cadena nombreDirectorioHijo);

//retorna un puntero de TDirectorio al padre del directorio directorio
TDirectorio moveFatherDirectory (TDirectorio& directorio);

//retorna un puntero de TDirectorio al directorio ROOT
TDirectorio moveRootDirectory (TDirectorio& directorio);

//retorna true si el directorio directorio es root
bool isRootDirectory (TDirectorio directorio);

//Pre-Condición del directorio de nombre nombreDirectorio no es hijo del directorio "directorio"
//pos-condición crea un directorio vacío, de nombre nombreDirectorio, hijo del directorio "directorio"
void createChildrenDirectory (TDirectorio& directorio, Cadena nombreDirectorio);

//pre-condición el directorio de nombre nombreDirectorio es hijo del directorio directorio
//pos-condición elimina el directorio de nombre nombreDirectorio que es hijo del directorio directorio
//eliminando toda su memoria
void removeChildrenDirectory (TDirectorio& directorio, Cadena nombreDirectorio);

//pre-condición el directorio origen es sub-directorio del directorio "directorio"
//pos-condición mueve el directorio origen y todo su contenido al directorio destino
void moveSubDirectory (TDirectorio& directorio, TDirectorio origen, TDirectorio& destino);

//pre-condición el archivo origen es sub archivo del directorio directorio
//pos-condición se mueve el archivo TArchivo como hijo del directorio destino
void moveSubArchive (TDirectorio& directorio, TArchivo origen, TDirectorio destino);

//pre-condición: directorio no es el directorio ROOT
//pos-condición: retorna un puntero al primer hermano del diretorio "directorio"
TDirectorio firstBrotherDirectory(TDirectorio directorio);

//pos-condición: retorna un puntero al primer hijo del directorio "directorio"
TDirectorio firstChildrenDirectory(TDirectorio directorio);

//Retorna true si el directorio subdir es sub-directorio del directorio "directorio" en cualquier nivel.
bool isSubDirectoryRoot (TDirectorio directorio, Cadena ruta);

//pos-condición imprime el directorio ejecuando DIR
void printDirectoryDir (TDirectorio directorio);

//pos-condición imprime el directorio ejecutando DIR /S
void printDirectoryDirS (TDirectorio directorio);

TDirectorio findDirectoryByPath(TDirectorio root, Cadena ruta);

void changeChildrenPath (TDirectorio sistema);

#endif
