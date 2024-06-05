%{
#include <stdio.h>
#include <string.h>
int charCount = 0, wordCount = 0, lineCount = 0;
%}

%option noyywrap

%%
[^#\n]+ {
    charCount += yyleng;
    wordCount++;
    fprintf(yyout, "%s", yytext);
}

"#"(.*) {
    fprintf(yyout, "%s", yytext); // Print the line starting with '#' as-is
}

\n {
    charCount++; // Count the newline character
    lineCount++;
    fprintf(yyout, "%s", yytext);
}

"abc" {
    charCount += 3; // Count the characters in 'abc'
    wordCount++; // Consider 'abc' as a word for word count
    fprintf(yyout, "ABC");
}
. {
    charCount++;
    fprintf(yyout, "%s", yytext);
}
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

    fprintf(outputFile, "\n\nCharacter Count: %d\n", charCount);
    fprintf(outputFile, "Word Count: %d\n", wordCount);
    fprintf(outputFile, "Line Count: %d\n", lineCount);

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
