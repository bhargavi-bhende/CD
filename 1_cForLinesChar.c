#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    FILE *file;
    char filename[100];
    char ch;
    int lines = 0, tabs = 0, spaces = 0, words = 0, characters = 0;
    int in_word = 0;

    // Get the file name from the user
    printf("Enter the filename: ");
    scanf("%s", filename);

    // Open the file
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    // Read the file character by character
    while ((ch = fgetc(file)) != EOF) {
        characters++;

        // Count lines
        if (ch == '\n') {
            lines++;
        }
        // Count tabs
        if (ch == '\t') {
            tabs++;
        }
        // Count spaces
        if (ch == ' ') {
            spaces++;
        }
        // Count words
        if (isspace(ch) || ispunct(ch)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            words++;
        }
    }

    // If the last character was not a newline, increment lines
    if (ch != '\n') {
        lines++;
    }

    // Close the file
    fclose(file);

    // Print the results
    printf("Lines: %d\n", lines);
    printf("Tabs: %d\n", tabs);
    printf("Spaces: %d\n", spaces);
    printf("Words: %d\n", words);
    printf("Characters: %d\n", characters);

    return 0;
}