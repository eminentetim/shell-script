#include <stdio.h>

int main(int argc, char *argv[]) {
    int i;

    // Print command-line arguments
    for (i = 1; argv[i] != NULL; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }

    return 0;
}

