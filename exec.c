#include "header.h"
void execute_batch_file(char* fileName) {
    int status = system(fileName);
    if (status == -1) {
        printf("Error executing system command\n");
    } else if (WIFEXITED(status)) {
        if (WEXITSTATUS(status) == 127) {
            printf("Error: batch file not found\n");
        }
    }
}
