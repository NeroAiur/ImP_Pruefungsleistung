/*Code for package operations*/
#include <stdio.h>
#include ".\structs.h"

#define xs_locker_amount 4
#define s_locker_amount 5
#define m_locker_amount 21
#define l_locker_amount 10
#define xl_locker_amount 2

struct postOfficeBox input_package(struct package package, struct postOfficeBox postOfficeBox) {
    int free_xs = 0;
    int free_s = 0;
    int free_m = 0;
    int free_l = 0;
    int free_xl = 0;

    // postOfficeBox is a struct
    // postOfficeBox.<SIZE> are arrays. each array has either 0 or 1 on their positions. 1 means "occupied" 0 means "free"

    // Checks if there is an error regarding the opening of the file
    if (0 <= package.package_size >= 6) {
        printf("ERROR: package.package_size is not in range 1-5. package.package_size: %s", package.package_size);
    }

    // Checks if there are free slots for each slot size
    for (int i = 0; i < xs_locker_amount; i++) { // 4 is the amount of XS-lockers at the station
        if (postOfficeBox.XS_locker[i].isEmpty == 1) {
            free_xs += 1;
            break;
        }
    }

    for (int i = 0; i < s_locker_amount; i++) { // 5 is the amount of S-lockers at the station
        if (postOfficeBox.S_locker[i].isEmpty == 1) {
            free_s += 1;
            break;
        }
    }
    
    for (int i = 0; i < m_locker_amount; i++) { // 21 is the amount of M-lockers at the station
        if (postOfficeBox.M_locker[i].isEmpty == 1) {
            free_m += 1;
            break;
        }
    }
    
    for (int i = 0; i < l_locker_amount; i++) {
        if (postOfficeBox.L_locker[i].isEmpty == 1) {
            free_l += 1;
        }
    }
    
    for (int i = 0; i < xl_locker_amount; i++) {
        if (postOfficeBox.XL_locker[i].isEmpty == 1) {
            free_xl += 1;
            break;
        }
    }
    
    // Packages can only be put into slots of their coresponding size, or larger.
    // The following switch-statement will start at the packages coresponding size and check if the sizes "free" value is true ("1").
    // If thats the case, it will go through the postOfficeBox.<SIZE> array and change the first unoccupied slot (the first "0") and occupy it (change the value to "1").
    // If there is no unoccupied slot in that size, it will look for the next larger size, repeating until an unoccupied slot.
    // This means there could be a package of size xs (package.package_size = 1) that will be put into a slot of size xl (most fitting for package.package_size 5).
    // If there no occupiable slot, the package will be stored by the worker or taken home by a customer.
    switch (package.package_size) {
        case 1:
            if (free_xs != 0) {
                for (int i = 0; i < xs_locker_amount; i++) {
                    if (postOfficeBox.XS_locker[i].isEmpty == 1) {
                        postOfficeBox.XS_locker[i].locker_content = package;
                        postOfficeBox.XS_locker[i].isEmpty = 0;
                        break;
                    }
                }
            }

        case 2:
            if (free_s != 0) {
                for (int i = 0; i < s_locker_amount; i++) {
                    if (postOfficeBox.S_locker[i].isEmpty == 1) {
                        postOfficeBox.S_locker[i].locker_content = package;
                        postOfficeBox.S_locker[i].isEmpty = 0;
                        break;
                    }
                }
            }

        case 3:
            if (free_m != 0) {
                for (int i = 0; i < m_locker_amount; i++) {
                    if (postOfficeBox.M_locker[i].isEmpty == 1) {
                        postOfficeBox.M_locker[i].locker_content = package;
                        postOfficeBox.M_locker[i].isEmpty = 0;
                        break;
                    }
                }
            }
        
        case 4:
            if (free_l != 0) {
                for (int i = 0; i < l_locker_amount; i++) {
                    if (postOfficeBox.L_locker[i].isEmpty == 1) {
                        postOfficeBox.L_locker[i].locker_content = package;
                        postOfficeBox.L_locker[i].isEmpty = 0;
                        break;
                    }
                }
            }

        case 5:
            if (free_xl != 0) {
                for (int i = 0; i < xl_locker_amount; i++) {
                    if (postOfficeBox.XL_locker[i].isEmpty == 1) {
                        postOfficeBox.XL_locker[i].locker_content = package;
                        postOfficeBox.XL_locker[i].isEmpty = 0;
                        break;
                    }
                }
            } else {
                /* *********************************** */
                /* CODE MISSING FOR THE CASE WHERE THERE IS NO OCCUPIABLE SLOT */
                /* *********************************** */
                break;
            }
    }

    return postOfficeBox;
}