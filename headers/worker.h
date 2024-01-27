/*Code for the worker to work*/
#include <stdio.h>
#include ".\structs.h"
#include ".\package_ops.h"

struct postOfficeBox workwork(struct postOfficeBox postOfficeBox) {
    int recipientID = 300;

    output_package(postOfficeBox, recipientID);

    return postOfficeBox;
}

