#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Cvor {
    int vrijednost;
    struct Cvor* lijevo;
    struct Cvor* desno;
} Cvor;

Cvor* noviCvor(int vrijednost) {
    Cvor* cvor = (Cvor*)malloc(sizeof(Cvor));
    if (cvor == NULL) {
        return NULL;
    }
    cvor->vrijednost = vrijednost;
    cvor->lijevo = NULL;
    cvor->desno = NULL;
    return cvor;
}

Cvor* umetniRazina(Cvor* korijen, int vrijednost) {
    if (korijen == NULL) {
        return noviCvor(vrijednost);
    }

    Cvor* red[100];
    int p = 0, k = 0;
    red[k++] = korijen;

    while (p < k) {
        Cvor* tren = red[p++];

        if (tren->lijevo == NULL) {
            tren->lijevo = noviCvor(vrijednost);
            return korijen;
        }
        else {
            red[k++] = tren->lijevo;
        }

        if (tren->desno == NULL) {
            tren->desno = noviCvor(vrijednost);
            return korijen;
        }
        else {
            red[k++] = tren->desno;
        }
    }
    return korijen;
}

int inorderDat(Cvor* korijen, FILE* dat) {
    if (korijen == NULL) {
        return 0;
    }
    inorderDat(korijen->lijevo, dat);
    fprintf(dat, "%d ", korijen->vrijednost);
    inorderDat(korijen->desno, dat);
    return 1;
}

int replaceSuma(Cvor* korijen) {
    if (korijen == NULL) {
        return 0;
    }

    int sumaL = replaceSuma(korijen->lijevo);
    int sumaD = replaceSuma(korijen->desno);

    int stara = korijen->vrijednost;
    korijen->vrijednost = sumaL + sumaD;

    return korijen->vrijednost + stara;
}

int obrisiStablo(Cvor* korijen) {
    if (korijen == NULL) {
        return 0;
    }
    obrisiStablo(korijen->lijevo);
    obrisiStablo(korijen->desno);
    free(korijen);
    return 1;
}

int main() {
    srand((unsigned int)time(NULL));

    Cvor* korijen = NULL;
    FILE* dat = fopen("inorder_ispis.txt", "w");

    if (dat == NULL) {
        printf("Greska pri otvaranju datoteke.\n");
        return 1;
    }

    int n = 9;
    for (int i = 0; i < n; i++) {
        int rnd = rand() % 80 + 10;
        korijen = umetniRazina(korijen, rnd);
    }

    fprintf(dat, "Inorder prije replace:");
        printf("Inorder prije replace:");
            inorderDat(korijen, dat);
    inorderDat(korijen, stdout);

    replaceSuma(korijen);

    fprintf(dat, "Inorder nakon replace :");
        printf("Inorder nakon replace :");
            inorderDat(korijen, dat);
    inorderDat(korijen, stdout);

    fclose(dat);
    obrisiStablo(korijen);

    printf("Program uspjesno zavrsen.\n");
    return 0;
}
