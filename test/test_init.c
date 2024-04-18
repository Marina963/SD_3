#include <stdio.h>
#include "../claves_client.h"
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

char *abs_path;

int print_files(char *abs_path){
    //Imprime por pantalla los archivos que hay en el directorio tuplas
    DIR *dir = opendir(abs_path);
    struct dirent *tuplas;
    printf("En el directorio tuplas hay los siguientes archivos: ");
    while ((tuplas = readdir(dir)) != NULL){
        printf("%s ",tuplas->d_name);
    }
    printf("\n");
    return 0;
}

void test_1() {
	/*Test 1: No hay ningún archivo en la carpeta tuplas donde se enciantran las keys*/
	printf("======Test 1: No hay ningún archivo en la carpeta tuplas======\n");

	//Declaración de variables
    int in;

    //Se borran los archivos y comprueba si los a borrado
    in = init();
    printf("Resultado prueba 1: %d\n", in);
    if (in == 0 ){
        print_files(abs_path);
    }

}

void test_2() {
	/*Test 2: borra todos los arhivos de la carpeta tuplas sabiendo que exite uno */
    printf("\n======Test 2: Existe un archivo en la carpeta======\n");

	//Declaración de variables
    int in;
    int n = 32;
    double vector[n];


    //Se crea una clave en el directorio tuplas
    for (int i = 0; i < n; i++) {vector[i] = (double)i;}
    set_value(10, "prueba_2", n, vector);

    //Imprime los archivos que hay en el directorio tuplas
    print_files(abs_path);

    //Borrado con algún archivo en la carpeta de tuplas
    in = init();
    printf("Resultado prueba 2: %d\n", in);
    print_files(abs_path);
}

int main() {

    //Se obtine la path del diretorio tuplas donde estan almacanadas las key y se abre el directorio
    const char *rel_path = "./tuplas";
    abs_path = realpath(rel_path, NULL);

    test_1();
    test_2();
    printf("\n");
    return 0;
}
