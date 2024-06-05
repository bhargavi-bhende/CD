#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_IDENTIFIER_LENGTH 100
#define BUFFER_SIZE 256

// Function to check if a character is a delimiter
bool isDelimiter(char ch) {
    return isspace(ch) || ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
           ch == ',' || ch == ';' || ch == '>' || ch == '<' || ch == '=' ||
           ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' ||
           ch == '}';
}

// Function to check if a character is a part of an operator
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
           ch == '>' || ch == '<' || ch == '=';
}

// Function to check if the string is a valid identifier
bool isValidIdentifier(char* str) {
    if (!isalpha(str[0]) || strlen(str) > MAX_IDENTIFIER_LENGTH) {
        return false;
    }
    for (int i = 1; i < strlen(str); i++) {
        if (!isalnum(str[i])) {
            return false;
        }
    }
    return true;
}

// Function to skip comments and whitespace
void skipWhitespaceAndComments(FILE *fp) {
    char ch, ch_next;
    while ((ch = fgetc(fp)) != EOF) {
        if (isspace(ch)) {
            continue;
        } else if (ch == '/') {
            ch_next = fgetc(fp);
            if (ch_next == '/') {
                // Single-line comment
                while ((ch = fgetc(fp)) != '\n' && ch != EOF);
            } else if (ch_next == '*') {
                // Multi-line comment
                while ((ch = fgetc(fp)) != '*' || (ch_next = fgetc(fp)) != '/') {
                    if (ch == EOF) break;
                }
            } else {
                // It was just a division operator
                ungetc(ch_next, fp);
                return;
            }
        } else {
            ungetc(ch, fp);
            return;
        }
    }
}

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "inline", "int",
    "long", "register", "restrict", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while", "_Alignas", "_Alignof",
    "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary", "_Noreturn",
    "_Static_assert", "_Thread_local"
};
const int numKeywords = sizeof(keywords) / sizeof(char*);

// Function to check if a string is a keyword
bool isKeyword(const char *str) {
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Main function to implement the lexical analyzer
int main() {
    FILE *fp;
    char ch, buffer[BUFFER_SIZE];
    int i;

    fp = fopen("2_input.c", "r");
    if (fp == NULL) {
        printf("Error while opening the file.\n");
        return 0;
    }

    while ((ch = fgetc(fp)) != EOF) {
        skipWhitespaceAndComments(fp);

        if (ch == '#') {
            // Read the directive
            i = 0;
            buffer[i++] = ch;
            while (!isspace(ch = fgetc(fp))) {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            if (strcmp(buffer, "#include") == 0) {
                // Handle the include directive
                printf("Directive: %s\n", buffer);
                while ((ch = fgetc(fp)) != '<'); // Skip until the opening angle bracket
                i = 0;
                buffer[i++] = ch;
                while ((ch = fgetc(fp)) != '>') {
                    buffer[i++] = ch;
                }
                buffer[i++] = ch; // Include the closing '>'
                buffer[i] = '\0';
                printf("Header File: %s\n", buffer);
            } else {
                printf("Preprocessor Directive: %s\n", buffer);
            }
        } else if (isDelimiter(ch)) {
            if (ch != ' ' && ch != '\t' && ch != '\n') {
                printf("Symbol: %c\n", ch);
            }
            continue;
        } else if (isOperator(ch)) {
            printf("Operator: %c\n", ch);
            continue;
        } else if (isdigit(ch)) {
            buffer[0] = ch;
            i = 1;
            while (isdigit(ch = fgetc(fp))) {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            ungetc(ch, fp); // Roll back the extra read
            printf("Number: %s\n", buffer);
        } else if (isalpha(ch)) {
            buffer[0] = ch;
            i = 1;
            while (isalnum(ch = fgetc(fp)) || ch == '_') {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            ungetc(ch, fp); // Roll back the extra read

            if (isKeyword(buffer)) {
                printf("Keyword: %s\n", buffer);
            } else if (isValidIdentifier(buffer)) {
                printf("Identifier: %s\n", buffer);
            } else {
                printf("Invalid Identifier: %s\n", buffer);
            }
        } else if (ch == '\"') {
            // Handle string literals
            i = 0;
            buffer[i++] = ch;
            while ((ch = fgetc(fp)) != '\"') {
                buffer[i++] = ch;
            }
            buffer[i++] = ch; // Include the closing quote
            buffer[i] = '\0';
            printf("String: %s\n", buffer);
        }
    }

    fclose(fp);
    return 0;
}
