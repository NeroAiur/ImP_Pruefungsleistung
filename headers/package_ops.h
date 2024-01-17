/*Code for package operations*/
#include <stdio.h>

int package_size = 0;
int station_status;

int input_package(int package_size, int station_status) {
    if (0 <= package_size >= 6) {
        printf("ERROR: package_size is not in range 1-5. package_size: %s", package_size);
    }

    // we need to decide how the station status will stored
    // until that I'll just leave this free how to get the data and will use one possible integration

    int free_xs = 0;
    for (int i = 0; i < station_status.xs; i++) {
        if (station_status.xs == 0) {
            free_s += 1;
        }
    }

    int free_s = 0;
    for (int i = 0; i < station_status.s; i++) {
        if (station_status.s == 0) {
            free_s += 1;
        }
    }

    int free_s = 0;
    for (int i = 0; i < station_status.s; i++) {
        if (station_status.s == 0) {
            free_s += 1;
        }
    }
    
    int free_m = 0;
    for (int i = 0; i < station_status.m; i++) {
        if (station_status.m == 0) {
            free_m += 1;
        }
    }
    
    int free_l = 0;
    for (int i = 0; i < station_status.l; i++) {
        if (station_status.l == 0) {
            free_l += 1;
        }
    }
    
    int free_xl = 0;
    for (int i = 0; i < station_status.xl; i++) {
        if (station_status.xl == 0) {
            free_xl += 1;
        }
    }
    
}