/*DEBUG-Code*/
#include <stdio.h>
#define DEBUG_FILE "/../_DEBUG/DEBUG_output.txt"

char *calc_time = "";
char *disp_time = "";
char packages = "";
char customers = "";
char worker_status = "";

char *calc_time 
int debug_output(calc_time, disp_time, packages, customers, worker_status) {
    // opening the DEBUG-output file
    FILE *f = fopen(DEBUG_FILE, "w");
    if (f == NULL) {
        printf("ERROR: File %s could not be opened", filename);
        return -1;
    }

    // write to file
    if (calc_time != "") {
        d_ct = calc_time;
    } else {
        d_ct = "No internal calculation time found.";
    }
    fprintf(f, "Internal Calculation Time: %s\n", d_ct);

    if (disp_time != "") {
        d_dt = disp_time;
    } else {
        d_dt = "No display time found.";
    }
    fprintf(f, "Display Time: %s\n", d_dt);
    
    if (packages != "") {
        d_pk = packages;
    } else {
        d_pk = "No packages found.";
    }
    fprintf(f, "Packages: %s\n", d_dt);

    if (customers != "") {
        d_cs = customers;
    } else {
        d_cs = "No customers found.";
    }
    fprintf(f, "Customers: %s\n", d_dt);

    if (worker_status != "") {
        d_cs = worker_status;
    } else {
        d_cs = "No worker found.";
    }
    fprintf(f, "Worker: %s\n", d_dt);
}