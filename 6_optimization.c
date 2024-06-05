#include <stdio.h>
#include <string.h>

struct op {
    char l;
    char r[20];
};

struct op op[10], pr[10];

int main() {
    int i, j, n, z = 0;
    char temp;
    char *p;

    printf("Enter number of values: ");
    scanf("%d", &n);
    getchar(); // Consume newline character after reading 'n'

    for (i = 0; i < n; i++) {
        printf("\tLeft: ");
        op[i].l = getchar();
        getchar(); // Consume newline character after reading 'l'
        printf("\tRight: ");
        scanf("%s", op[i].r);
        getchar(); // Consume newline character after reading 'r'
    }

    printf("\nIntermediate Code:\n");
    for (i = 0; i < n; i++) {
        printf("%c=%s\n", op[i].l, op[i].r);
    }

    printf("\nAfter Dead Code Elimination:\n");
    for (i = 0; i < n; i++) {
        temp = op[i].l;
        for (j = 0; j < n; j++) {
            p = strchr(op[j].r, temp);
            if (p) {
                pr[z].l = op[i].l;
                strcpy(pr[z].r, op[i].r);
                z++;
                break; // Break loop once a match is found
            }
        }
    }

    printf("\nOptimized Code:\n");
    for (i = 0; i < z; i++) {
        printf("%c=%s\n", pr[i].l, pr[i].r);
    }

    return 0;
}

/*Enter number of values: 5
        Left: a
        Right: 9
        Left: b
        Right: c+d
        Left: e
        Right: c+d
        Left: f
        Right: b+e
        Left: r
        Right: f
*/