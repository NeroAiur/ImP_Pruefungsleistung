/*Code for package operations*/
#include <stdio.h>

int input_package(int package_size, int station_status) {
    // station_status is a struct
    // station_status.<SIZE> are arrays. each array has either 0 or 1 on their positions. 1 means "occupied" 0 means "free"

    // Checks if there is an error regarding the opening of the file
    if (0 <= package_size >= 6) {
        printf("ERROR: package_size is not in range 1-5. package_size: %s", package_size);
    }

    // Checks if there are free slots for each slot size
    int free_xs = 0;
    for (int i = 0; i < station_status.xs; i++) {
        if (station_status.xs[i] == 0) {
            free_s += 1;
            break;
        }
    }

    int free_s = 0;
    for (int i = 0; i < station_status.s; i++) {
        if (station_status.s[i] == 0) {
            free_s += 1;
            break;
        }
    }

    int free_s = 0;
    for (int i = 0; i < station_status.s; i++) {
        if (station_status.s[i] == 0) {
            free_s += 1;
            break;
        }
    }
    
    int free_m = 0;
    for (int i = 0; i < station_status.m; i++) {
        if (station_status.m[i] == 0) {
            free_m += 1;
            break;
        }
    }
    
    int free_l = 0;
    for (int i = 0; i < station_status.l; i++) {
        if (station_status.l[i] == 0) {
            free_l += 1;
        }
    }
    
    int free_xl = 0;
    for (int i = 0; i < station_status.xl; i++) {
        if (station_status.xl[i] == 0) {
            free_xl += 1;
            break;
        }
    }
    
    // Packages can only be put into slots of their coresponding size, or larger.
    // The following switch-statement will start at the packages coresponding size and check if the sizes "free" value is true ("1").
    // If thats the case, it will go through the station_status.<SIZE> array and change the first unoccupied slot (the first "0") and occupy it (change the value to "1").
    // If there is no unoccupied slot in that size, it will look for the next larger size, repeating until an unoccupied slot.
    // This means there could be a package of size xs (package_size = 1) that will be put into a slot of size xl (most fitting for package_size 5).
    // If there no occupiable slot, the package will be stored by the worker or taken home by a customer.
    switch (package_size) {
        case 1:
            if (free_xs != 0) {
                for (int i = 0, i < station_status.xs; i++) {
                    if (station_status.xs[i] == 0) {
                        station_status.xs[i] = 1;
                        break;
                    }
                }
            }

        case 2:
            if (free_s != 0) {
                for (int i = 0, i < station_status.s; i++) {
                    if (station_status.s[i] == 0) {
                        station_status.s[i] = 1;
                        break;
                    }
                }
            }

        case 3:
            if (free_m != 0) {
                for (int i = 0, i < station_status.m; i++) {
                    if (station_status.m[i] == 0) {
                        station_status.m[i] = 1;
                        break;
                    }
                }
            }
        
        case 4:
            if (free_l != 0) {
                for (int i = 0, i < station_status.l; i++) {
                    if (station_status.l[i] == 0) {
                        station_status.l[i] = 1;
                        break;
                    }
                }
            }

        case 5:
            if (free_xl != 0) {
                for (int i = 0, i < station_status.xl; i++) {
                    if (station_status.xl[i] == 0) {
                        station_status.xl[i] = 1;
                        break;
                    }
                }
            } else {
                // ***********************************
                // CODE MISSING FOR THE CASE WHERE THERE IS NO OCCUPIABLE SLOT
                // ***********************************
                break;
            }
    }

    return station_status;
}