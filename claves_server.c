#include "claves.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

pthread_mutex_t mutex;

void get_tuple_abs_path(char * tuple_name, int key) {
    //Función auxiliar que obtiene el path absoluto de una tupla
    strcpy(tuple_name, abs_path);
    strcat(tuple_name, "/");
    char key_str[32];
    sprintf(key_str, "%d", key);
    strcat(tuple_name, key_str);
}

int init_x_1_svc(int *result, struct svc_req *rqstp) {

    pthread_mutex_lock(&mutex);

    // Declaración de variables necesarias para el init
    DIR *dir = opendir(abs_path);
    struct dirent* tuplas;
    char* file_name;
    char res[4] = "0";
    *result = 0;

    // Mientras haya tuplas en el fichero de tuplas
    while ((tuplas = readdir(dir)) != NULL) {

        // Si el objeto no es un directorio
        if (strcmp(tuplas->d_name, ".") != 0 && strcmp(tuplas->d_name, "..") != 0) {

            // Se reserva espacio para el nombre del fichero y se obtiene su path absoluto
            file_name = calloc(PATH_MAX, sizeof(char));
            strcpy(file_name, abs_path);
            strcat(file_name, "/");
            strcat(file_name, tuplas->d_name);

            // Se borra el fichero, si hay algún error, se escribe y la respuesta devolverá -1
            if (remove(file_name) == -1) {
                perror("");
                *result = -1;
                return 0;
            }

            // Se libera el espacio dinámico
            free(file_name);
        }
    }

    pthread_mutex_unlock(&mutex);


    return 1;
}

int set_value_x_1_svc(struct arg arg1, int *result,  struct svc_req *rqstp) {

    pthread_mutex_lock(&mutex);

    *result = 0;

    // Se obtiene el nombre absoluto del fichero
    char *tuple_name = calloc(PATH_MAX, sizeof(char));
    get_tuple_abs_path(tuple_name, key);

    // Se mira si existe
    if (access(tuple_name, F_OK) == 0) {
        printf("Error: Archivo existe\n");
        *result = -;
        return 0;
    }
    // Crea el fichero
    FILE * tuple;
    tuple = fopen(tuple_name, "w+");
    if (tuple == NULL) {
        perror("");
        *result = -;
        return 0;
    }

    if (fprintf(tuple, "%d\n", arg1.key) < 0) {*result = -1;}
    if (fprintf(tuple, "%s\n", arg1.value1) < 0) {*result = -1;}
    if (fprintf(tuple, "%d\n", *arg1.N_value2) < 0) {*result = -1;}
    for (int i = 0; i < *arg1.N_value2; i++) {
        if (fprintf(tuple, "%lf", arg1.V_value2[i]) < 0) {*result = -1;}
        if (i < *arg1.N_value2 -1) {fprintf(tuple, ", ");}
    }

    // Cierra la tupla
    fclose(tuple);

    pthread_mutex_unlock(&mutex);
	return 1;
}

int get_value_x_1_svc(struct arg arg1, int *result,  struct svc_req *rqstp)
{
    pthread_mutex_lock(&mutex);

    *result = 0;

    // Se consigue el path de la tupla
    char *tuple_name = calloc(PATH_MAX, sizeof(char));
    get_tuple_abs_path(tuple_name, key);

    // Se mira si existe
    if (access(tuple_name, F_OK) == -1) {
        printf("Error: Archivo no existe\n");
        *result = -1;
        return 0;
    }

    // Abre el archivo
    FILE * tuple;
    tuple = fopen(tuple_name, "r");
    if (tuple == NULL) {
        perror("");
        *result = -1;
        return 0;
    }


    // Lee los datos
    int key;

    // Ley la key
    if (fscanf(tuple, "%d\n", &key) < 1) {*result = -1;}

    // Lee value1 y lo manda por el socket
    if (fscanf(tuple, "%[^\n]s\n", arg1.value1) < 1) {
        printf("Error: lectura de value1 de get_value\n");
        *result = -1;
        return 0;
    }

    // Lee N_value2 y lo manda por el socket
    if (fscanf(tuple, "%d\n", arg1.N_value2) < 1) {
        printf("Error: lectura de N_value2 de get_value\n");
        *result = -1;
        return 0;
    }

    else if (*arg1.N_value2 > 32 || *arg1.N_value2 <= 0){
        printf("Error: N_value2 fuera de rango\n");
        *result = -1;
        return 0;
    }


    // Lee V_value2 y lo manda por el socket
    for (int i = 0; i < *arg1.N_value2; i++) {
        if (fscanf(tuple, "%lf", &arg1.V_value2[i]) < 1) {*result = -1;}
        if (i < *arg1.N_value2 -1) { fscanf(tuple, ", ");}
    }

    // Cierra la tupla
    fclose(tuple);

    pthread_mutex_unlock(&mutex);

	return 1;
}

int modify_value_x_1_svc(struct arg arg1, int *result,  struct svc_req *rqstp) {

    pthread_mutex_lock(&mutex);

    *result = 0;

    // Se obtiene el nombre absoluto del fichero
    char *tuple_name = calloc(PATH_MAX, sizeof(char));
    get_tuple_abs_path(tuple_name, key);

    // Se mira si existe
    if (access(tuple_name, F_OK) == 0) {
        printf("Error: Archivo existe\n");
        *result = -;
        return 0;
    }
    // Crea el fichero
    FILE * tuple;
    tuple = fopen(tuple_name, "w+");
    if (tuple == NULL) {
        perror("");
        *result = -;
        return 0;
    }

    if (fprintf(tuple, "%d\n", arg1.key) < 0) {*result = -1;}
    if (fprintf(tuple, "%s\n", arg1.value1) < 0) {*result = -1;}
    if (fprintf(tuple, "%d\n", *arg1.N_value2) < 0) {*result = -1;}
    for (int i = 0; i < *arg1.N_value2; i++) {
        if (fprintf(tuple, "%lf", arg1.V_value2[i]) < 0) {*result = -1;}
        if (i < *arg1.N_value2 -1) {fprintf(tuple, ", ");}
    }

    // Cierra la tupla
    fclose(tuple);

    pthread_mutex_unlock(&mutex);

	return 1;
}

int delete_key_x_1_svc(int key, int *result,  struct svc_req *rqstp) {
    pthread_mutex_lock(&mutex);

    // Declaración de variables necesarias para el delete key
    DIR *dir = opendir(abs_path);
    struct dirent* tuplas;
    char* file_name;
    char key_str[32];
    sprintf(key_str, "%d", key);
    char *tuple_name = (char *)calloc(PATH_MAX, sizeof(char));
    get_tuple_abs_path(tuple_name, key);

    *result = 0;

    // Si el fichero existe se busca
    if (access(tuple_name, F_OK) == 0) {
        // Mientras haya tuplas en el fichero de tuplas
        while ((tuplas = readdir(dir)) != NULL) {
            // Si el objeto no es un directorio
            if (strcmp(tuplas->d_name, key_str) == 0) {
                // Se reserva espacio para el nombre del fichero y se obtiene su path absoluto
                file_name = calloc(PATH_MAX, sizeof(char));
                strcpy(file_name, abs_path);
                strcat(file_name, "/");
                strcat(file_name, tuplas->d_name);

                // Se borra el fichero, si hay algún error, se escribe y la respuesta devolverá -1
                if (remove(file_name) == -1) {
                    perror("");
                    *result = -1;
                    return 0;
                }
                // Se libera el espacio dinámico
                free(file_name);
            }
        }
    }
    else {
        printf("Error: el fichero no existe\n");
        *result = -1;
        return  0;
    }

    pthread_mutex_unlock(&mutex);
	return 1;
}

int exist_x_1_svc(int key, int *result,  struct svc_req *rqstp) {
    pthread_mutex_lock(&mutex);
    *result = 0;

    // Datos para el fichero
    char *tuple_name = calloc(PATH_MAX, sizeof(char));
    get_tuple_abs_path(tuple_name, key);

    // Se mira si existe
    res = access(tuple_name, F_OK);
    if (access(tuple_name, F_OK ) == 0) {
        *result = 1;
    } else {
        if (errno == ENOENT) {
            *result = 0;
        } else {
            *result = -1;
            return 0;
        }
    }
    pthread_mutex_unlock(&mutex);
	return 1;
}

int claves_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	xdr_free (xdr_result, result);

	/*
	 * Insert additional freeing code here, if needed
	 */

	return 1;
}
