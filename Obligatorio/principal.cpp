/*
Módulo principal de la tarea 1.FILE SYSTEM

Intérprete de comandos para probar los módulos.

  Laboratorio de EDA 2023
  UTU - LATU - Turno Nocturno 
  Profesor Ferando Arrieta
*/

#include "include/directorio.h"
#include "include/archivo.h"
#include "include/linea.h"
#include "include/fila.h"
#include "include/utils.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstddef>
#define MAX_PALABRA 64
#define MAX_LINEA 256
#define MAX_RUTA 256
#define MAX_PARAMETRO 10
#define MAX_PARAMETRODIR 1
#define MAX_COMANDO 10
#define MAX_NOMBRE 15
#define MAX_EXTENSION 3
#define TEXTO_MAX 22

enum _retorno {OK, ERROR, NO_IMPLEMENTADA};
typedef enum _retorno TipoRet;
typedef char* Cadena;

  
TipoRet CREARSISTEMA(TDirectorio &s);
TipoRet CREATE (TDirectorio &sistema, char *nombreArchivo);
TipoRet DELETE (TDirectorio &sistema, char *nombreArchivo);
TipoRet ATTRIB (TDirectorio &sistema, char *nombreArchivo, char* parametro);
TipoRet IF (TDirectorio &sistema, char *nombreArchivo, char* texto);
TipoRet IN (TDirectorio &sistema, char *nombreArchivo, char* texto);
TipoRet DF (TDirectorio &sistema, char *nombreArchivo, char* cantidad);
TipoRet TYPE (TDirectorio &sistema, char *nombreArchivo);
TipoRet DESTRUIRSISTEMA (TDirectorio &sistema);
bool sistemaInicializado=false;


// programa principal
int main() {
    char restoLinea[MAX_LINEA + 1];
    char comando[MAX_PALABRA];
    char parametro[MAX_PALABRA];
    char texto[MAX_PALABRA];
    char nombrearchivo[MAX_NOMBRE];
    char cantidad [MAX_PALABRA];
    //char parametro;
    TDirectorio sistema;
    
    bool salir = false;
    while (!salir) {
        
        printf("#");	
        // leer el comando
        leerChars(comando);
        
        if (!strcmp(comando,"ATTRIB")){
            leerChars(nombrearchivo);
            leerChars(parametro);
        }
        else if (!strcmp(comando,"CREATEFILE"))
            leerChars(nombrearchivo);
        
        else if (!strcmp(comando,"DELETE"))
                leerChars(nombrearchivo);
        
        else if (!strcmp(comando,"IF")){
                leerChars(nombrearchivo);
                leerRestoLinea(texto);
        }
        else if (!strcmp(comando,"IN")){
                leerChars(nombrearchivo);
                leerRestoLinea(texto);
        }
        else if (!strcmp(comando,"DF")){
                leerChars(nombrearchivo);
                leerChars(cantidad);
        }        
        else if (!strcmp(comando,"TYPE"))
                leerChars(nombrearchivo);
                
        
        // *********************** Procesamiento de comandos ***********************************
        
        
        if (0 == strcmp(comando, "CREARSISTEMA")) {
            if (!sistemaInicializado){
                TipoRet salida=CREARSISTEMA(sistema);
                if (salida == OK){
                    sistemaInicializado=true;
                    printf("  OK\n");
                }
            }   
            else 
                 printf("  EL SISTEMA YA FUE INICIALIZADO\n");

        }else if (0 == strcmp(comando, "CREATEFILE")) {   
                TipoRet salida = CREATE(sistema, nombrearchivo);
                if (salida == OK)
                        printf("  OK\n");
                else if (salida == ERROR )
                                printf("  ERROR\n"); 

        } else if (0 == strcmp(comando, "DELETE")) {
                TipoRet salida=DELETE(sistema,nombrearchivo);
                if (salida == OK)
                        printf("  OK\n");
                else if (salida == ERROR )
                                printf("  ERROR\n");

        } else if (0 == strcmp(comando, "ATTRIB")) {
                TipoRet salida=ATTRIB(sistema, nombrearchivo,parametro);
                if (salida == OK)
                        printf("  OK\n");
                else if (salida == ERROR )
                                printf("  ERROR\n");
                
        } else if (0 == strcmp(comando, "IF")) {
                TipoRet salida=IF(sistema, nombrearchivo,texto);
                if (salida == OK)
                        printf("  OK\n");
                else if (salida == ERROR)
                                printf("  ERROR\n");
                
        } else if (0 == strcmp(comando, "IN")) {
                TipoRet salida=IN(sistema, nombrearchivo,texto);
                if (salida == OK)
                        printf("  OK\n");
                else if (salida == ERROR )
                                printf("  ERROR\n");
                
        } else if (0 == strcmp(comando, "DF")) {
                TipoRet salida=DF(sistema, nombrearchivo, cantidad);
                if (salida == OK)
                        printf("  OK\n");
                else if (salida == ERROR )
                                printf("  ERROR\n");
                
        } else if (0 == strcmp(comando, "TYPE")) {
                TipoRet salida=TYPE(sistema, nombrearchivo);
                if (salida == OK)
                        printf("  OK\n");
                else if (salida == ERROR )
                                printf("  ERROR\n");
                
        } else if (0 == strcmp(comando, "DESTRUIRSISTEMA")) {
                TipoRet salida=DESTRUIRSISTEMA(sistema);
                if (salida == OK)
                        printf("  OK\n");
                else if (salida == ERROR )
                                printf("  ERROR\n");
        }else
            printf("  Comando no reconocido.\n");

        fgets(restoLinea, MAX_LINEA + 1, stdin);
    } // while
    return 0;
} // main


//****************************** Funciones a implementar ************************************

TipoRet CREARSISTEMA (TDirectorio &sistema){
    sistema = createRootDirectory();
    return OK;
}  

TipoRet CREATE (TDirectorio &sistema, Cadena nombreArchivo){
    if(sistemaInicializado){
        if(!existFileDirectory(sistema, nombreArchivo)){
            createFileInDirectory(sistema, nombreArchivo);
            return OK;
        }else {
            printf("  - Archivo existente -\n");
            return ERROR;
        }
    }else {
        printf("  - Sistema no inicializado -\n");
        return ERROR;
    }
}

TipoRet DELETE (TDirectorio &sistema, Cadena nombreArchivo){
    if(sistemaInicializado){
        if(existFileDirectory(sistema, nombreArchivo)){
            TArchivo archivo = getFileDirectory(sistema, nombreArchivo);
            if (haveWritePermission(archivo)){
                deleteFileDirectory(sistema, nombreArchivo);
                return OK;
            }else{
                printf("  - Archivo no tiene permiso -\n");
                return ERROR;
            }  
        }else {
            printf("  - Archivo no existente -\n");
            return ERROR;
        }
    }else {
        printf("  - Sistema no inicializado -\n");
        return ERROR;
    }  
}

TipoRet ATTRIB (TDirectorio &sistema, Cadena nombreArchivo, Cadena nombrearchivo){
    if(sistemaInicializado){
        if(existFileDirectory(sistema, nombreArchivo)){
            bool permiso;
            if (0 == strcmp(nombrearchivo, "+W")){
                permiso = true;
                setFilePermission(sistema, nombreArchivo, permiso);
                printf("  - Permiso de escritura agregado -\n");
                return OK;
            }else if (0 == strcmp(nombrearchivo, "-W")){
                permiso = false;
                setFilePermission(sistema, nombreArchivo, permiso);
                printf("  - Permiso de escritura eliminado -\n");
                return OK;
            }else{
                printf("  - No existe el parametro -");
                return ERROR;
            }
        }else {
            printf("  - Archivo no existente -\n");
            return ERROR;
        }
    }else {
        printf("  - Sistema no inicializado -\n");
        return ERROR;
    }
}

TipoRet IF (TDirectorio &sistema, Cadena nombreArchivo, Cadena texto){   
    if(sistemaInicializado){
        if(existFileDirectory(sistema, nombreArchivo)){
            TArchivo archivo = getFileDirectory(sistema, nombreArchivo);
            if (haveWritePermission(archivo)){
                insertCharsFileFirstLine(sistema, nombreArchivo, texto);
                int caracteresTotales = getCountChars(archivo);

                if(caracteresTotales > TEXTO_MAX){
                    // Calcular la cantidad de caracteres que deben eliminarse del nuevo texto
                    int caracteresAEliminar = caracteresTotales - TEXTO_MAX;

                    if (caracteresAEliminar > 0) {
                        // Eliminar caracteres excedentes del archivo
                        deleteCharsFile(sistema, nombreArchivo, caracteresAEliminar);
                    }
                }
                return OK;
            }else{
                printf("  - No tiene permisos -\n");
                return ERROR;
            }
        }else {
            printf("  - Archivo no existente -\n");
            return ERROR;
        }
    }else {
        printf("  - Sistema no inicializado -\n");
        return ERROR;
    }
}

TipoRet IN (TDirectorio &sistema, Cadena nombreArchivo, Cadena texto){
    if(sistemaInicializado){
        if(existFileDirectory(sistema, nombreArchivo)){
            TArchivo archivo = getFileDirectory(sistema, nombreArchivo); 
            if (haveWritePermission(archivo)){
                insertTextFile(sistema, nombreArchivo, texto);

                int caracteresTotales = getCountChars(archivo);
                if(caracteresTotales > TEXTO_MAX){
                    // Calcular la cantidad de caracteres que deben eliminarse del nuevo texto
                    int caracteresAEliminar = caracteresTotales - TEXTO_MAX;
                    if (caracteresAEliminar > 0) {
                        deleteCharsFile(sistema, nombreArchivo, caracteresAEliminar);
                    }
                }
                return OK;
            }else{
                printf("  - No tiene permisos -\n");
                return ERROR;
            }
        }else {
            printf("  - Archivo no existente -\n");
            return ERROR;
        }
    }else {
        printf("  - Sistema no inicializado -\n");
        return ERROR;
    }
}

TipoRet DF (TDirectorio &sistema, Cadena nombreArchivo, Cadena cantidad){
    if(sistemaInicializado){
        if(existFileDirectory(sistema, nombreArchivo)){
            TArchivo archivo = getFileDirectory(sistema, nombreArchivo);
            if (haveWritePermission(archivo)){
                deleteCharsFile(sistema, nombreArchivo, atoi(cantidad));
                return OK;
            }else{
                printf("  - Archivo no tiene permiso -\n");
                return ERROR;
            }
        }else {
            printf("  - Archivo no existente -\n");
            return ERROR;
        }
    }else {
        printf("  - Sistema no inicializado\n -");
        return ERROR;
    }
}

TipoRet TYPE (TDirectorio &sistema, Cadena nombreArchivo){
    if(sistemaInicializado){
        if(existFileDirectory(sistema, nombreArchivo)){
            printFile(sistema, nombreArchivo);
            return OK;
        }else {
            printf("  - Archivo no existente -\n");
            return ERROR;
        }
    }else {
        printf("  - Sistema no inicializado -\n");
        return ERROR;
    }  
}

TipoRet DESTRUIRSISTEMA (TDirectorio &sistema){
    if(sistemaInicializado){
        destroyDirectory(sistema);
        sistemaInicializado=false;
        return OK;
    }else {
        printf("  - Sistema no inicializado -\n");
        return ERROR;
    }
}