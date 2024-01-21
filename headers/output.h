/*Code for the output*/

#include <stdio.h>

#define OUTPUT_FILE ".\.\_DEBUG\output.txt"

int refresh_output() {

}

int output_to_console() {
    FILE *file;

    file = fopen(OUTPUT_FILE, "r");
    char fileContent[10000];

    fgets(fileContent, 10000, file);

    // stuff after file is read
    // file should be read line to line
    // then output

    fclose(file);
}