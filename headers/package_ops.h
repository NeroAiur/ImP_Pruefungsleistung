/*Code for package operations*/
#include <stdio.h>
#include ".\structs.h"

#define xs_locker_amount 4
#define s_locker_amount 5
#define m_locker_amount 21
#define l_locker_amount 10
#define xl_locker_amount 2

<<<<<<< HEAD
#define TRUE 1
#define FALSE 0


=======
>>>>>>> 4dde38a8363b0cd4078fcdf0f28c306d2fb6c2ba
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
                if (postOfficeBox.XS_locker[i].isEmpty == TRUE) {
                    postOfficeBox.XS_locker[i].locker_content = package;
                    postOfficeBox.XS_locker[i].isEmpty = FALSE;
                    postOfficeBox.XS_locker[i].locker_age = 0;
                    break;
                }
            }

        case 2:
            for (int i = 0; i < s_locker_amount; i++) {
                if (postOfficeBox.S_locker[i].isEmpty == TRUE) {
                    postOfficeBox.S_locker[i].locker_content = package;
                    postOfficeBox.S_locker[i].isEmpty = FALSE;
                    postOfficeBox.S_locker[i].locker_age = 0;
                    break;
                }
            }

        case 3:
            for (int i = 0; i < m_locker_amount; i++) {
                if (postOfficeBox.M_locker[i].isEmpty == TRUE) {
                    postOfficeBox.M_locker[i].locker_content = package;
                    postOfficeBox.M_locker[i].isEmpty = FALSE;
                    postOfficeBox.M_locker[i].locker_age = 0;
                    break;
                }
            }
        
        case 4:
            for (int i = 0; i < l_locker_amount; i++) {
                if (postOfficeBox.L_locker[i].isEmpty == TRUE) {
                    postOfficeBox.L_locker[i].locker_content = package;
                    postOfficeBox.L_locker[i].isEmpty = FALSE;
                    postOfficeBox.L_locker[i].locker_age = 0;
                    break;
                }
            }

        case 5:
            for (int i = 0; i < xl_locker_amount; i++) {
                if (postOfficeBox.XL_locker[i].isEmpty == TRUE) {
                    postOfficeBox.XL_locker[i].locker_content = package;
                    postOfficeBox.XL_locker[i].isEmpty = FALSE;
                    postOfficeBox.XL_locker[i].locker_age = 0;
                    break;
                }
            }
        /*
        ***********************************
        CODE MISSING FOR THE CASE WHERE THERE IS NO OCCUPIABLE SLOT
        NEEDS CLEARANCE
        ***********************************
        */

    }

        return postOfficeBox;
}

struct postOfficeBox output_package(struct postOfficeBox postOfficeBox, int recipientID) {
    /*
    Goes through every single locker size and checks every non-empty locker.
    If the locker's content's recipient_id is equal to that customer's/worker's ID, set the locker status to empty and void the package
    */
    for (int i = 0; i < xs_locker_amount; i++) {
        if (postOfficeBox.XS_locker[i].isEmpty == FALSE) {
            if (recipientID == 300) {
                if (postOfficeBox.XS_locker[i].locker_age >= 4) {
                    postOfficeBox.XS_locker[i].isEmpty = TRUE;
                    postOfficeBox.XS_locker[i].locker_content = NULL;
                    continue;
                } else if (postOfficeBox.XS_locker[i].locker_content.package_recipient_id != 300) {
                    postOfficeBox.XS_locker[i].locker_content.package_isInternal_pickUpReady = TRUE;
                    continue;
                }
            }
            if (postOfficeBox.XS_locker[i].locker_content.package_recipient_id == recipientID) {
                postOfficeBox.XS_locker[i].isEmpty = TRUE;
                postOfficeBox.XS_locker[i].locker_content = NULL;
                continue;
            }
<<<<<<< HEAD
            if (recipientID == 300 && postOfficeBox.XS_locker[i].locker_age >= 4) {
                postOfficeBox.XS_locker[i].isEmpty = TRUE;
                postOfficeBox.XS_locker[i].locker_content* = NULL;
            }
=======
>>>>>>> 4dde38a8363b0cd4078fcdf0f28c306d2fb6c2ba
        }
    }

    for (int i = 0; i < s_locker_amount; i++) {
        if (postOfficeBox.S_locker[i].isEmpty == FALSE) {
            if (recipientID == 300) {
                if (postOfficeBox.S_locker[i].locker_age >= 4) {
                    postOfficeBox.S_locker[i].isEmpty = TRUE;
                    postOfficeBox.S_locker[i].locker_content = NULL;
                    continue;
                } else if (postOfficeBox.S_locker[i].locker_content.package_recipient_id != 300) {
                    postOfficeBox.S_locker[i].locker_content.package_isInternal_pickUpReady = TRUE;
                    continue;
                }
            }
            if (postOfficeBox.S_locker[i].locker_content.package_recipient_id == recipientID) {
                postOfficeBox.S_locker[i].isEmpty = TRUE;
                postOfficeBox.S_locker[i].locker_content = NULL;
                continue;
            }
        }
    }

    for (int i = 0; i < m_locker_amount; i++) {
        if (postOfficeBox.M_locker[i].isEmpty == FALSE) {
            if (recipientID == 300) {
                if (postOfficeBox.M_locker[i].locker_age >= 4) {
                    postOfficeBox.M_locker[i].isEmpty = TRUE;
                    postOfficeBox.M_locker[i].locker_content = NULL;
                    continue;
                } else if (postOfficeBox.M_locker[i].locker_content.package_recipient_id != 300) {
                    postOfficeBox.M_locker[i].locker_content.package_isInternal_pickUpReady = TRUE;
                    continue;
                }
            }
            if (postOfficeBox.M_locker[i].locker_content.package_recipient_id == recipientID) {
                postOfficeBox.M_locker[i].isEmpty = TRUE;
                postOfficeBox.M_locker[i].locker_content = NULL;
                continue;
            }
        }
    }

    for (int i = 0; i < l_locker_amount; i++) {
        if (postOfficeBox.L_locker[i].isEmpty == FALSE) {
            if (recipientID == 300) {
                if (postOfficeBox.L_locker[i].locker_age >= 4) {
                    postOfficeBox.L_locker[i].isEmpty = TRUE;
                    postOfficeBox.L_locker[i].locker_content = NULL;
                    continue;
                } else if (postOfficeBox.L_locker[i].locker_content.package_recipient_id != 300) {
                    postOfficeBox.L_locker[i].locker_content.package_isInternal_pickUpReady = TRUE;
                    continue;
                }
            }
            if (postOfficeBox.L_locker[i].locker_content.package_recipient_id == recipientID) {
                postOfficeBox.L_locker[i].isEmpty = TRUE;
                postOfficeBox.L_locker[i].locker_content = NULL;
                continue;
            }
        }
    }

    for (int i = 0; i < xl_locker_amount; i++) {
        if (postOfficeBox.XL_locker[i].isEmpty == FALSE) {
            if (recipientID == 300) {
                if (postOfficeBox.XL_locker[i].locker_age >= 4) {
                    postOfficeBox.XL_locker[i].isEmpty = TRUE;
                    postOfficeBox.XL_locker[i].locker_content = NULL;
                    continue;
                } else if (postOfficeBox.XL_locker[i].locker_content.package_recipient_id != 300) {
                    postOfficeBox.XL_locker[i].locker_content.package_isInternal_pickUpReady = TRUE;
                    continue;
                }
            }
            if (postOfficeBox.XL_locker[i].locker_content.package_recipient_id == recipientID) {
                postOfficeBox.XL_locker[i].isEmpty = TRUE;
                postOfficeBox.XL_locker[i].locker_content = NULL;
                continue;
            }
        }
    }

    return postOfficeBox;

}

struct postOfficeBox age_packages(struct postOfficeBox postOfficeBox) {
    for (int i = 0; i < xs_locker_amount; i++) {
        if (postOfficeBox.XS_locker[i].isEmpty == FALSE) {
            postOfficeBox.XS_locker[i].locker_age += 1;
        }
    }

    for (int i = 0; i < s_locker_amount; i++) {
        if (postOfficeBox.S_locker[i].isEmpty == FALSE) {
            postOfficeBox.S_locker[i].locker_age += 1;
        }
    }

    for (int i = 0; i < m_locker_amount; i++) {
        if (postOfficeBox.M_locker[i].isEmpty == FALSE) {
            postOfficeBox.M_locker[i].locker_age += 1;
        }
    }

    for (int i = 0; i < l_locker_amount; i++) {
        if (postOfficeBox.L_locker[i].isEmpty == FALSE) {
            postOfficeBox.L_locker[i].locker_age += 1;
        }
    }

    for (int i = 0; i < xl_locker_amount; i++) {
        if (postOfficeBox.XL_locker[i].isEmpty == FALSE) {
            postOfficeBox.XL_locker[i].locker_age += 1;
        }
    }

    return postOfficeBox;
};
