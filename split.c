#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** split_string(const char* str, const char* delimiter, size_t* num_words) {
    if (str == NULL || delimiter == NULL || num_words == NULL) {
        return NULL;
    }

    // Create a copy of the original string to avoid modifying it
    char* str_copy = strdup(str);
    if (str_copy == NULL) {
        return NULL;  // Error handling
    }

    // Allocate memory for the result array
    size_t max_words = 10;  // Initial capacity
    char** words = malloc(max_words * sizeof(char*));
    if (words == NULL) {
        free(str_copy);
        return NULL;  // Error handling
    }

    // Tokenize the string using the delimiter
    char* token = strtok(str_copy, delimiter);
    size_t count = 0;

    while (token != NULL) {
        // If the result array is full, reallocate with a larger capacity
        if (count >= max_words) {
            max_words += 10;
            char** new_words = realloc(words, max_words * sizeof(char*));
            if (new_words == NULL) {
                // Cleanup before returning in case of error
                for (size_t i = 0; i < count; i++) {
                    free(words[i]);
                }
                free(words);
                free(str_copy);
                return NULL;  // Error handling
            }
            words = new_words;
        }

        // Allocate memory for each word and copy it
        words[count] = strdup(token);
        if (words[count] == NULL) {
            // Cleanup before returning in case of error
            for (size_t i = 0; i < count; i++) {
                free(words[i]);
            }
            free(words);
            free(str_copy);
            return NULL;  // Error handling
        }

        count++;

        // Move to the next token
        token = strtok(NULL, delimiter);
    }

    // Free the copy of the string
    free(str_copy);

    // Update the number of words
    *num_words = count;

    return words;
}

int main() {
    const char* input = "Hello, world! This is a test.";

    size_t num_words;
    char** words = split_string(input, " ", &num_words);

    if (words != NULL) {
        for (size_t i = 0; i < num_words; i++) {
            printf("Word %zu: %s\n", i, words[i]);
        }

        // Don't forget to free the allocated memory
        for (size_t i = 0; i < num_words; i++) {
            free(words[i]);
        }
        free(words);
    }

    return 0;
}

