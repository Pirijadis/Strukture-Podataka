#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* struktura čvora */
typedef struct Cvor {
    int vrijednost;
    struct Cvor* lijevo;
    struct Cvor* desno;
} Cvor;

/* stvaranje novog čvora */
Cvor* stvoriCvor(int vrijednost)
{
    Cvor* novi = (Cvor*)malloc(sizeof(Cvor));
    novi->vrijednost = vrijednost;
    novi->lijevo = NULL;
    novi->desno = NULL;
    return novi;
}

/* umetanje u binarno stablo pretraživanja */
Cvor* umetni(Cvor* korijen, int vrijednost)
{
    if (korijen == NULL)
        return stvoriCvor(vrijednost);

    if (vrijednost < korijen->vrijednost)
        korijen->lijevo = umetni(korijen->lijevo, vrijednost);
    else
        korijen->desno = umetni(korijen->desno, vrijednost);

    return korijen;
}

/* inorder ispis u datoteku */
void inorderIspis(Cvor* korijen, FILE* dat)
{
    if (korijen == NULL)
        return;

    inorderIspis(korijen->lijevo, dat);
    fprintf(dat, "%d ", korijen->vrijednost);
    inorderIspis(korijen->desno, dat);
}

/* zamjena vrijednosti čvora sumom njegovih potomaka */
int zamijeniSumomPotomaka(Cvor* korijen)
{
    if (korijen == NULL)
        return 0;

    int sumaLijevo = zamijeniSumomPotomaka(korijen->lijevo);
    int sumaDesno = zamijeniSumomPotomaka(korijen->desno);

    int staraVrijednost = korijen->vrijednost;
    korijen->vrijednost = sumaLijevo + sumaDesno;

    return korijen->vrijednost + staraVrijednost;
}

/* brisanje stabla */
void obrisiStablo(Cvor* korijen)
{
    if (korijen == NULL)
        return;

    obrisiStablo(korijen->lijevo);
    obrisiStablo(korijen->desno);
    free(korijen);
}

/* MAIN FUNKCIJA */
int main()
{
    Cvor* korijen = NULL;
    FILE* dat;
    int i, broj;

    srand((unsigned)time(NULL));

    /* stvaranje stabla */
    for (i = 0; i < 10; i++) {
        broj = rand() % 81 + 10;   /* 10–90 */
        korijen = umetni(korijen, broj);
    }

    dat = fopen("stablo.txt", "w");
    if (dat == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return 1;
    }

    fprintf(dat, "Inorder prije zamjene:\n");
    inorderIspis(korijen, dat);

    zamijeniSumomPotomaka(korijen);

    fprintf(dat, "\n\nInorder nakon zamjene:\n");
    inorderIspis(korijen, dat);

    fclose(dat);
    obrisiStablo(korijen);

    printf("Program zavrsio. Rezultati su u datoteci stablo.txt\n");

    return 0;
}
