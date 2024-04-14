struct arg {
        int key;
        string value1<256>;
        int *N_value2;
        double V_value2[32];
} ;

program CLAVES{
    version CLAVESVER {
        int init_x(void) = 1;
        int set_value_x(struct arg) = 2;
        int get_value_x(struct arg) = 3;
        int modify_value_x(struct arg) = 4;
        int delete_key_x(int key) = 5;
        int exist_x(int key) = 6;
    } = 1;
} = 99;