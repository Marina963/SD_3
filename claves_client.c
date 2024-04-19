#include "claves_client.h"
#include "claves.h"
#include <stdio.h>
#include <string.h>

int init(){
    CLIENT *clnt;

    enum clnt_stat retval_init;
    int result_init;
    char *host;

    host = getenv("IP_TUPLAS");
    if(host == NULL){
        printf("Error: host null\n");
        return -1;
    }

    clnt = clnt_create (host, CLAVES, CLAVESVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        return -1;
    }
    
    retval_init = init_x_1(&result_init, clnt);
    if (retval_init != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }

    clnt_destroy (clnt);
    return result_init;
}

int set_value(int key, char *value1, int N_value2, double *V_value2){
    CLIENT *clnt;

    enum clnt_stat retval_set_value;
    int result_set_value;
    struct arg set_value_arg;
    char *host;

    if (N_value2 > 32 || N_value2 < 1) {
        printf("Error: N_value2 fuera de rango \n");
        return -1;
    }

    host = getenv("IP_TUPLAS");
    if(host == NULL){
        printf("Error \n");
        return -1;
    }

    clnt = clnt_create (host, CLAVES, CLAVESVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror (host);
        return -1;
    }
    
    // Guarda los argumentos
    set_value_arg.key = key;
    strcpy(set_value_arg.value1, value1);
    set_value_arg.N_value2 = N_value2;
    for (int i = 0; i < N_value2; i++){
        set_value_arg.V_value2[i] = V_value2[i];
    }
    
    retval_set_value = set_value_x_1(set_value_arg, &result_set_value, clnt);
    if (retval_set_value != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }

    clnt_destroy (clnt);
    return result_set_value;
}

int get_value(int key, char *value1,  int *N_value2, double * V_value2) {
    CLIENT *clnt;
    
    int result_get_value;
    enum clnt_stat retval_get_value;
    struct res get_value_res;
    char *host;

    host = getenv("IP_TUPLAS");
    if (NULL == host) {
        printf("Error\n");
        return -1;
    }

    clnt = clnt_create(host, CLAVES, CLAVESVER, "tcp");
    if (clnt == NULL){
        clnt_pcreateerror (host);
        return -1;
    }

    retval_get_value = get_value_x_1(key, &get_value_res, clnt);
    if (retval_get_value != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }

    strcpy(value1, get_value_res.value1);
    *N_value2 = get_value_res.N_value2;

    for (int i = 0; i < *N_value2; i++) {
        V_value2[i] = get_value_res.V_value2[i];
    }

    clnt_destroy (clnt);
    return get_value_res.error_code;
}

int modify_value(int key, char *value1, int N_value2, double *V_value2) {
    CLIENT *clnt;

    enum clnt_stat retval_modify_value;
    int result_modify_value;
    struct arg modify_value_arg;
    char *host;

    if (N_value2 > 32 || N_value2 <= 0) {
        printf("Error: N_value2 fuera de rango \n");
        return -1;
    }

    host = getenv("IP_TUPLAS");
    if(host == NULL){
        printf("Error \n");
        return -1;
    }

    clnt = clnt_create (host, CLAVES, CLAVESVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror (host);
        return -1;
    }

    modify_value_arg.key = key;
    strcpy(modify_value_arg.value1, value1);
    modify_value_arg.N_value2 = N_value2;
    for (int i = 0; i < N_value2; i++){
        modify_value_arg.V_value2[i] = V_value2[i];
    }


    retval_modify_value = modify_value_x_1(modify_value_arg, &result_modify_value, clnt);
    if (retval_modify_value != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }
    
    clnt_destroy (clnt);
    return  result_modify_value;
}

int delete_key(int key) {
    CLIENT *clnt;

    enum clnt_stat retval_delete_key;
    int result_delete_key;

    char *host;

    host = getenv("IP_TUPLAS");
    if(host == NULL){
        printf("Error \n");
        return -1;
    }

    clnt = clnt_create (host, CLAVES, CLAVESVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror (host);
        return -1;
    }

    retval_delete_key = delete_key_x_1(key, &result_delete_key, clnt);
    if (retval_delete_key != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }

    clnt_destroy (clnt);
    return result_delete_key;
}

int exist(int key) {
	CLIENT *clnt;

	enum clnt_stat retval_exist;
	int result_exist;
    char *host;

    host = getenv("IP_TUPLAS");
    if(host == NULL){
        printf("Error \n");
        return -1;
    }

    clnt = clnt_create (host, CLAVES, CLAVESVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror (host);
        return -1;
    }


	retval_exist = exist_x_1(key, &result_exist, clnt);
	if (retval_exist != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}

	clnt_destroy (clnt);
    return result_exist;

}
