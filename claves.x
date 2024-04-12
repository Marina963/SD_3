struct arg {
        int key;
        string value1<256>;
        int *N_value2;
        double V_value2[32];
    } ;

program CLAVES{
    version CLAVESVER {
        int init(void) = 1;
        int get_value(struct arg) = 2;
    } = 1;
} = 99;