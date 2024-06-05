%{
#include <stdio.h>
#include <string.h>
int vowelCount = 0, wordCount = 0;
%}

%option noyywrap

%%
[a-zA-Z]+   {
                wordCount++;
                if (strchr("AEIOUaeiou", yytext[0])) {
                    vowelCount++;
                    printf("%s%d ", yytext, vowelCount);
                } else {
                    printf("%s ", yytext);
                }
            }
.           { printf("%s", yytext); }
%%

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("Error opening input file");
        return 1;
    }

    FILE *outputFile = fopen(argv[2], "w");
    if (!outputFile) {
        perror("Error opening output file");
        fclose(inputFile);
        return 1;
    }

    yyin = inputFile;
    yyout = outputFile;

    yylex();

    fprintf(outputFile, "\n\nTotal Words Read: %d\n", wordCount);
    fprintf(outputFile, "Words Starting with a Vowel: %d\n", vowelCount);

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
