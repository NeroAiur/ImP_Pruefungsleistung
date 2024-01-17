/*Code for package operations*/
#include <stdio.h>

int input_package(int package_size, int station_status) {

    // Checks if there is an error regarding the opening of the file
    if (0 <= package_size >= 6) {
        printf("ERROR: package_size is not in range 1-5. package_size: %s", package_size);
    }

    // Checks if there are free slots for every size of pocket
    int free_xs = 0;
    for (int i = 0; i < station_status.xs; i++) {
        if (station_status.xs == 0) {
            free_s += 1;
            break;
        }
    }

    int free_s = 0;
    for (int i = 0; i < station_status.s; i++) {
        if (station_status.s == 0) {
            free_s += 1;
            break;
        }
    }

    int free_s = 0;
    for (int i = 0; i < station_status.s; i++) {
        if (station_status.s == 0) {
            free_s += 1;
            break;
        }
    }
    
    int free_m = 0;
    for (int i = 0; i < station_status.m; i++) {
        if (station_status.m == 0) {
            free_m += 1;
            break;
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
            break;
        }
    }
    
    // Deciding which slot size will be taken:
    // The program will check, starting with its coresponding size, if there are slots empty
    // if there isn't it will go to the next size.
    // if there is no empty slot, it will return a value of 10, which will be used in further procesing
    int use_slot_size;
    switch (package_size) {
        case 1:
            if (free_xs != 0) {
                use_slot_size = 1;
            }

        case 2:
            if (free_s != 0) {
                use_slot_size = 2;
            }

        case 3:
            if (free_m != 0) {
                use_slot_size = 3;
            }
        
        case 4:
            if (free_l != 0) {
                use_slot_size = 4;
            }

        case 5:
            if (free_xl != 0) {
                use_slot_size = 5;
            } else {
                use_slot_size = 10;
            }
    }
}