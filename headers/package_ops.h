/*Code for package operations*/
#include <stdio.h>
#include ".\structs.h"

#define xs_locker_amount 4
#define s_locker_amount 5
#define m_locker_amount 21
#define l_locker_amount 10
#define xl_locker_amount 2

struct postOfficeBox input_package(struct package package, struct postOfficeBox postOfficeBox) {
    /*Checks if there is an error regarding the opening of the file*/
    if (0 <= package.package_size >= 6) {
        printf("ERROR: package.package_size is not in range 1-5. package.package_size: %s", package.package_size);
    }
    
    /*
    Packages can only be put into slots of their coresponding size, or larger.
    The following switch-statement will start at the packages coresponding locker size.
    If there is an empty locker, it will be put into that locker.
    If there is no empty locker, it will go to the next larger size and search for an empty locker, repeating until there is one.
    This means there could be a package of size xs (package.package_size = 1) that will be put into a slot of size xl (most fitting for package.package_size 5).
    If there no occupiable slot, the package will be stored by the worker or taken home by a customer.
    If the package is inserted, the locker_age (days a package has been in a locker) will be set to 0.
    */
    switch (package.package_size) {
        case 1:
            for (int i = 0; i < xs_locker_amount; i++) {
                if (postOfficeBox.XS_locker[i].isEmpty == 1) {
                    postOfficeBox.XS_locker[i].locker_content = package;
                    postOfficeBox.XS_locker[i].isEmpty = 0;
                    postOfficeBox.XS_locker[i].locker_age = 0;
                    break;
                }
            }

        case 2:
            for (int i = 0; i < s_locker_amount; i++) {
                if (postOfficeBox.S_locker[i].isEmpty == 1) {
                    postOfficeBox.S_locker[i].locker_content = package;
                    postOfficeBox.S_locker[i].isEmpty = 0;
                    postOfficeBox.S_locker[i].locker_age = 0;
                    break;
                }
            }

        case 3:
            for (int i = 0; i < m_locker_amount; i++) {
                if (postOfficeBox.M_locker[i].isEmpty == 1) {
                    postOfficeBox.M_locker[i].locker_content = package;
                    postOfficeBox.M_locker[i].isEmpty = 0;
                    postOfficeBox.M_locker[i].locker_age = 0;
                    break;
                }
            }
        
        case 4:
            for (int i = 0; i < l_locker_amount; i++) {
                if (postOfficeBox.L_locker[i].isEmpty == 1) {
                    postOfficeBox.L_locker[i].locker_content = package;
                    postOfficeBox.L_locker[i].isEmpty = 0;
                    postOfficeBox.L_locker[i].locker_age = 0;
                    break;
                }
            }

        case 5:
            for (int i = 0; i < xl_locker_amount; i++) {
                if (postOfficeBox.XL_locker[i].isEmpty == 1) {
                    postOfficeBox.XL_locker[i].locker_content = package;
                    postOfficeBox.XL_locker[i].isEmpty = 0;
                    postOfficeBox.XL_locker[i].locker_age = 0;
                    break;
                }
            }
        /* *********************************** */
        /* CODE MISSING FOR THE CASE WHERE THERE IS NO OCCUPIABLE SLOT */
        /* *********************************** */

    }

        return postOfficeBox;
}

struct postOfficeBox age_package(struct package package, struct postOfficeBox postOfficeBox) {
    for (int i = 0; i < xs_locker_amount; i++) {
        if (postOfficeBox.XS_locker[i].isEmpty == 0) {
            postOfficeBox.XL_locker[i].locker_age += 1;
        }
    }

    for (int i = 0; i < s_locker_amount; i++) {
        if (postOfficeBox.S_locker[i].isEmpty == 0) {
            postOfficeBox.S_locker[i].locker_age += 1;
        }
    }

    for (int i = 0; i < m_locker_amount; i++) {
        if (postOfficeBox.M_locker[i].isEmpty == 0) {
            postOfficeBox.M_locker[i].locker_age += 1;
        }
    }

    for (int i = 0; i < l_locker_amount; i++) {
        if (postOfficeBox.L_locker[i].isEmpty == 0) {
            postOfficeBox.L_locker[i].locker_age += 1;
        }
    }

    for (int i = 0; i < xl_locker_amount; i++) {
        if (postOfficeBox.XL_locker[i].isEmpty == 0) {
            postOfficeBox.XL_locker[i].locker_age += 1;
        }
    }
};
