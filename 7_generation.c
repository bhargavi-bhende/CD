#include <stdio.h>
#include <conio.h>
#include <string.h>

char op[2], arg1[5], arg2[5], result[5];
int addRegister = 0, subRegister = 1, mulRegister = 2, divRegister = 3, assignRegister = 4;

void main() {
    FILE *fp1, *fp2;
    fp1 = fopen("7_input.txt", "r");
    fp2 = fopen("7_output.txt", "w");

    while (!feof(fp1)) {
        fscanf(fp1, "%s%s%s%s", op, arg1, arg2, result);
        
        if (strcmp(op, "+") == 0) {
            fprintf(fp2, "\nMOV R%d,%s", addRegister, arg1);
            fprintf(fp2, "\nADD R%d,%s", addRegister, arg2);
            fprintf(fp2, "\nMOV %s,R%d", result, addRegister);
        }
        else if (strcmp(op, "*") == 0) {
            fprintf(fp2, "\nMOV R%d,%s", mulRegister, arg1);
            fprintf(fp2, "\nMUL R%d,%s", mulRegister, arg2);
            fprintf(fp2, "\nMOV %s,R%d", result, mulRegister);
        }
        else if (strcmp(op, "-") == 0) {
            fprintf(fp2, "\nMOV R%d,%s", subRegister, arg1);
            fprintf(fp2, "\nSUB R%d,%s", subRegister, arg2);
            fprintf(fp2, "\nMOV %s,R%d", result, subRegister);
        }
        else if (strcmp(op, "/") == 0) {
            fprintf(fp2, "\nMOV R%d,%s", divRegister, arg1);
            fprintf(fp2, "\nDIV R%d,%s", divRegister, arg2);
            fprintf(fp2, "\nMOV %s,R%d", result, divRegister);
        }
        else if (strcmp(op, "=") == 0) {
            fprintf(fp2, "\nMOV R%d,%s", assignRegister, arg1);
            fprintf(fp2, "\nMOV %s,R%d", result, assignRegister);
        }
    }

    fclose(fp1);
    fclose(fp2);
    getch();
}
