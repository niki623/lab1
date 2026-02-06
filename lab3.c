#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *array[5] = {NULL};
    int index = 0;
    int count = 0;

    while (1) {
        char *line = NULL;
        size_t len = 0;
        printf("Enter input: ");
        fflush(stdout);

        ssize_t nread = getline(&line, &len, stdin);
        if (nread == -1) {
            free(line);
            break;
        }
        line[strcspn(line, "\n")] = '\0';

        free(array[index]);
        array[index] = strdup(line);

        // Wrap index manually instead of using modulo
        index++;
        if (index == 5)
            index = 0;

        if (count < 5)
            count++;

        if (strcmp(line, "print") == 0) {
            int start = index - count;
            if (start < 0)
                start += 5;  // wrap around for start
            for (int i = 0; i < count; i++) {
                int pos = start + i;
                if (pos >= 5)
                    pos -= 5;  // wrap around for printing
                printf("%s\n", array[pos]);
            }
        }

        free(line);
    }

    for (int i = 0; i < 5; i++)
        free(array[i]);

    return 0;
}

