#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

int filtro(const struct dirent * carpeta){
    if ((strcmp(carpeta->d_name,".") == 0 ) || (strcmp(carpeta->d_name,"..") == 0 ) ) return 0; 
    // retornamos 0 para que no se agregue a los resultados.
    return 1;  // retornamos 1 para que se agregue
}


/* Función que revisa si a algún jugador le queda una carta, o si ganó el juego. 
Retorna 1 si le queda 1 carta, 2 si ganó el juego o 0 en caso contrario. 
*/
int revisar_ultima_carta(char carpeta[]){
     /* ver todos los archivos de la carpeta origen*/
    struct dirent **resultados = NULL;
    int numeroResultados;
    numeroResultados = scandir (carpeta, &resultados, (*filtro), NULL); // se guardan en el arreglo resultados
    int i;
    for (i=0; i<numeroResultados; i++){  //se libera la memoria usada en el arreglo resultados
        free (resultados[i]);
        resultados[i] = NULL;
    }
    free(resultados);  // se libera el puntero al arreglo
    resultados = NULL;

    if (numeroResultados == 1) return 1;
    else if (numeroResultados == 0) return 2;
    return 0;
}

/* Función que borra la carta de la carpeta ultimaCarta, dejándola vacía. 
*/
void borrar_ultimaCarta(){
    /* ver todos los archivos de la carpeta origen*/
    struct dirent **resultados = NULL;
    int numeroResultados;
    numeroResultados = scandir ("ultimaCarta", &resultados, (*filtro), NULL); // se guardan en el arreglo resultados
    char nombre_archivo[40];
    sprintf(nombre_archivo,"%s",resultados[0]->d_name); // se guarda el nombre del archivo buscado aleatoriamente
    
    int i;
    for (i=0; i<numeroResultados; i++){  //se libera la memoria usada en el arreglo resultados
        free (resultados[i]);
        resultados[i] = NULL;
    }
    free(resultados);  // se libera el puntero al arreglo
    resultados = NULL;

    char borrar[40];
    sprintf(borrar,"%s/%s","ultimaCarta",nombre_archivo);    // se borra el archivo de la carpeta de origen
    remove(borrar); 
}

int main(){
    borrar_ultimaCarta();
    return 0;
}
