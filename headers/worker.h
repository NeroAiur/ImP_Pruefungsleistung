/*Code for the worker to work*/
#include <stdio.h>
#include ".\structs.h"
#include ".\package_ops.h"

struct postOfficeBox workwork(struct postOfficeBox postOfficeBox) {
    int recipientID = 300;

    output_package(postOfficeBox, recipientID);

    // für jedes Fach
    // wenn ID != 300
    // package_isInternal_pickUpReady TRUE

    // wenn locker_age >= 4
    // voide package
    return postOfficeBox;
}

