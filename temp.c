#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int i;

    for (i = 0; i < 5; i++) {
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {
            // Child process, execute the command
            printf("Child %d executing\n", i + 1);
            execlp("ls", "ls", "-l", "/tmp", NULL);

            // If exec fails, print an error
            perror("execlp");
            exit(EXIT_FAILURE);
        } else {
            // Parent process, wait for the child to exit
            wait(NULL);
        }
    }

    return 0;
}

