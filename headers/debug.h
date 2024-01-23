/* DEBUG-Code */
#include <stdio.h>
#define DEBUG_FILE ".\.\_DEBUG/DEBUG_output.txt"

int debug_output(char *calc_time, char *disp_time, char *packages,
                 char *customers, char *worker_status) {
    /* NEEDS OVERHAUL */
    
    /* opening the DEBUG-output file */
    FILE *f = fopen(DEBUG_FILE, "w");
    if (f == NULL) {
        printf("ERROR: File %s could not be opened", DEBUG_FILE);
        return -91;
    }

    /* write to file */

    /* internal calculation time */
    char *d_ct;
    if (calc_time != "") {
        d_ct = calc_time;
    } else {
        d_ct = "No internal calculation time found.";
    }
    fprintf(f, "Internal Calculation Time: %s\n", d_ct);

    /* internal display time */
    char *d_dt;
    if (disp_time != "") {
        d_dt = disp_time;
    } else {
        d_dt = "No display time found.";
    }
    fprintf(f, "Display Time: %s\n", d_dt);
    
    /* packages */
    char *d_pk;
    if (packages != "") {
        d_pk = packages;
    } else {
        d_pk = "No packages found.";
    }
    fprintf(f, "Packages: %s\n", d_dt);

    /* customers */
    char *d_cs;
    if (customers != "") {
        d_cs = customers;
    } else {
        d_cs = "No customers found.";
    }
    fprintf(f, "Customers: %s\n", d_dt);

    /* worker status */
    char *d_ws;
    if (worker_status != "") {
        d_ws = worker_status;
    } else {
        d_ws = "No worker found.";
    }
    fprintf(f, "Worker: %s\n", d_dt);
}