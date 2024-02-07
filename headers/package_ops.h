/*Code for package operations*/
#include <stdio.h>
#include ".\structs.h"

#define start_id_xs 0
#define start_id_s 4
#define start_id_m 9
#define start_id_l 30
#define start_id_xl 40
#define eol 42

#define TRUE 1
#define FALSE 0


struct postOfficeBox input_package(struct package package, struct postOfficeBox postOfficeBox) {
    /*Checks if there is an error regarding the opening of the file*/
    if (0 <= package.size >= 6) {
        printf("ERROR: package.package_size is not in range 1-5. package.package_size: %s", package.size);
    }
    
    /*
    Packages can only be put into slots of their coresponding size, or larger.
    The following switch-statement will start at the packages coresponding locker size.
    If there is an empty locker, it will be put into that locker.
    If there is no empty locker, it will go to the next larger size and search for an empty locker, repeating until there is one.
    This means there could be a package of size xs (package.package_size = 1) that will be put into a slot of size xl (most fitting for package.package_size 5).
    If there no occupiable slot, the package will be stored by the worker or taken home by a customer.
    If the package is inserted, the fuse_time (days a package has been in a locker) will be set to 0.
    */
    switch (package.size) {
        case 1:
            for (int i = start_id_xs; i < start_id_s; i++) {
                if (postOfficeBox.lockers[i].isEmpty == TRUE) {
                    postOfficeBox.lockers[i].content = package;
                    postOfficeBox.lockers[i].isEmpty = FALSE;
                    postOfficeBox.lockers[i].fuse_time = 0;
                }
            }

        case 2:
            for (int i = start_id_s; i < start_id_m; i++) {
                if (postOfficeBox.lockers[i].isEmpty == TRUE) {
                    postOfficeBox.lockers[i].content = package;
                    postOfficeBox.lockers[i].isEmpty = FALSE;
                    postOfficeBox.lockers[i].fuse_time = 0;
                }
            }

        case 3:
            for (int i = start_id_m; i < start_id_l; i++) {
                if (postOfficeBox.lockers[i].isEmpty == TRUE) {
                    postOfficeBox.lockers[i].content = package;
                    postOfficeBox.lockers[i].isEmpty = FALSE;
                    postOfficeBox.lockers[i].fuse_time = 0;
                }
            }
        
        case 4:
            for (int i = start_id_l; i < start_id_xl; i++) {
                if (postOfficeBox.lockers[i].isEmpty == TRUE) {
                    postOfficeBox.lockers[i].content = package;
                    postOfficeBox.lockers[i].isEmpty = FALSE;
                    postOfficeBox.lockers[i].fuse_time = 0;
                }
            }

        case 5:
            for (int i = start_id_xl; i < eol; i++) {
                if (postOfficeBox.lockers[i].isEmpty == TRUE) {
                    postOfficeBox.lockers[i].content = package;
                    postOfficeBox.lockers[i].isEmpty = FALSE;
                    postOfficeBox.lockers[i].fuse_time = 0;
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
    for (int i = 0; i < eol; i++) {
        if (postOfficeBox.lockers[i].isEmpty == FALSE) {
            if (recipientID == 300) {
                if (postOfficeBox.lockers[i].fuse_time >= 4) {
                    postOfficeBox.lockers[i].isEmpty = TRUE;
                    postOfficeBox.lockers[i].content = NULL;
                    continue;
                } else if (postOfficeBox.lockers[i].content.recipient_id != 300) {
                    postOfficeBox.lockers[i].content.isInternal_pickUpReady = TRUE;
                    continue;
                } else if (postOfficeBox.lockers[i].content.recipient_id == recipientID) {
                    postOfficeBox.lockers[i].isEmpty = TRUE;
                    postOfficeBox.lockers[i].content = NULL;
                    continue;
                }
            } else if (postOfficeBox.lockers[i].content.recipient_id == recipientID) {
                postOfficeBox.lockers[i].isEmpty = TRUE;
                postOfficeBox.lockers[i].content = NULL;
                continue;
            }
        }
    }

    return postOfficeBox;
}

struct postOfficeBox age_packages(struct postOfficeBox postOfficeBox) {
    for (int i = 0; i < eol; i++) {
        if (postOfficeBox.lockers[i].isEmpty == FALSE) {
            postOfficeBox.lockers[i].fuse_time += 1;
        }
    }
    
    return postOfficeBox;
};
