#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* Struktura èvora binarnog stabla pretraživanja */
typedef struct CvorStabla {
    int vrijednost;
    struct CvorStabla* lijevoDijete;
    struct CvorStabla* desnoDijete;
} CvorStabla;

/* Funkcija za stvaranje novog èvora */
CvorStabla* stvoriNoviCvor(int novaVrijednost) {
    CvorStabla* noviCvor = (CvorStabla*)malloc(sizeof(CvorStabla));
    if (noviCvor == NULL) {
        printf("Greška pri alokaciji memorije!\n");
        return NULL;
    }
    noviCvor->vrijednost = novaVrijednost;
    noviCvor->lijevoDijete = NULL;
    noviCvor->desnoDijete = NULL;
    return noviCvor;
}

/* Funkcija za umetanje elementa u stablo */
CvorStabla* umetniElement(CvorStabla* korijen, int novaVrijednost) {
    if (korijen == NULL) {
        return stvoriNoviCvor(novaVrijednost);
    }

    if (novaVrijednost < korijen->vrijednost) {
        korijen->lijevoDijete = umetniElement(korijen->lijevoDijete, novaVrijednost);
    }
    else if (novaVrijednost > korijen->vrijednost) {
        korijen->desnoDijete = umetniElement(korijen->desnoDijete, novaVrijednost);
    }

    return korijen;
}

/* Inorder ispis */
int inorderIspis(CvorStabla* korijen) {
    if (korijen == NULL) {
        return 0;
    }
    inorderIspis(korijen->lijevoDijete);
    printf("%d ", korijen->vrijednost);
    inorderIspis(korijen->desnoDijete);
    return 1;
}

/* Preorder ispis */
int preorderIspis(CvorStabla* korijen) {
    if (korijen == NULL) {
        return 0;
    }
    printf("%d ", korijen->vrijednost);
    preorderIspis(korijen->lijevoDijete);
    preorderIspis(korijen->desnoDijete);
    return 1;
}

/* Postorder ispis */
int postorderIspis(CvorStabla* korijen) {
    if (korijen == NULL) {
        return 0;
    }
    postorderIspis(korijen->lijevoDijete);
    postorderIspis(korijen->desnoDijete);
    printf("%d ", korijen->vrijednost);
    return 1;
}

/* Pronalaženje najmanje vrijednosti */
CvorStabla* pronadiNajmanjiCvor(CvorStabla* korijen) {
    while (korijen != NULL && korijen->lijevoDijete != NULL) {
        korijen = korijen->lijevoDijete;
    }
    return korijen;
}

/* Brisanje elementa iz stabla */
CvorStabla* obrisiElement(CvorStabla* korijen, int trazenaVrijednost) {
    if (korijen == NULL) {
        return NULL;
    }

    if (trazenaVrijednost < korijen->vrijednost) {
        korijen->lijevoDijete = obrisiElement(korijen->lijevoDijete, trazenaVrijednost);
    }
    else if (trazenaVrijednost > korijen->vrijednost) {
        korijen->desnoDijete = obrisiElement(korijen->desnoDijete, trazenaVrijednost);
    }
    else {
        if (korijen->lijevoDijete == NULL) {
            CvorStabla* privremeniCvor = korijen->desnoDijete;
            free(korijen);
            return privremeniCvor;
        }
        else if (korijen->desnoDijete == NULL) {
            CvorStabla* privremeniCvor = korijen->lijevoDijete;
            free(korijen);
            return privremeniCvor;
        }

        CvorStabla* najmanjiDesni = pronadiNajmanjiCvor(korijen->desnoDijete);
        korijen->vrijednost = najmanjiDesni->vrijednost;
        korijen->desnoDijete = obrisiElement(korijen->desnoDijete, najmanjiDesni->vrijednost);
    }
    return korijen;
}

/* Pretraživanje elementa */
int pronadiElement(CvorStabla* korijen, int trazenaVrijednost) {
    if (korijen == NULL) {
        return 0;
    }
    if (korijen->vrijednost == trazenaVrijednost) {
        return 1;
    }
    if (trazenaVrijednost < korijen->vrijednost) {
        return pronadiElement(korijen->lijevoDijete, trazenaVrijednost);
    }
    return pronadiElement(korijen->desnoDijete, trazenaVrijednost);
}

/* Level order ispis (koristi jednostavno polje kao red) */
int levelOrderIspis(CvorStabla* korijen) {
    if (korijen == NULL) {
        return 0;
    }

    CvorStabla* red[100];
    int pocetak = 0, kraj = 0;

    red[kraj++] = korijen;

    while (pocetak < kraj) {
        CvorStabla* trenutni = red[pocetak++];
        printf("%d ", trenutni->vrijednost);

        if (trenutni->lijevoDijete != NULL) {
            red[kraj++] = trenutni->lijevoDijete;
        }
        if (trenutni->desnoDijete != NULL) {
            red[kraj++] = trenutni->desnoDijete;
        }
    }
    return 1;
}

int main() {
    CvorStabla* korijen = NULL;
    int izbor = 0;
    int vrijednost = 0;
    int n = 0;

    do {
        printf("\n--- BINARNO STABLO PRETRAŽIVANJA ---\n");
        printf("1. Unos novog elementa\n");
        printf("2. Inorder ispis\n");
        printf("3. Preorder ispis\n");
        printf("4. Postorder ispis\n");
        printf("5. Level order ispis\n");
        printf("6. Pronalazenje elementa\n");
        printf("7. Brisanje elementa\n");
        printf("8. Izlaz\n");
        printf("Odabir: ");
        scanf("%d", &izbor);

        switch (izbor) {
        case 1:
            printf("Koliko vrijednosti mislite unijeti?\n->", n);
            scanf("%d", &n);
            {
                for (int i = 0; i < n; i++) {
                    printf("Unesi vrijednost", i + 1);
                    scanf("%d", &vrijednost);
                    korijen = umetniElement(korijen, vrijednost);
                }
            }
            break;
            /*scanf("%d", &vrijednost);
            korijen = umetniElement(korijen, vrijednost);
            break;*/
        case 2:
            printf("Inorder: ");
            inorderIspis(korijen);
            printf("\n");
            break;
        case 3:
            printf("Preorder: ");
            preorderIspis(korijen);
            printf("\n");
            break;
        case 4:
            printf("Postorder: ");
            postorderIspis(korijen);
            printf("\n");
            break;
        case 5:
            printf("Level order: ");
            levelOrderIspis(korijen);
            printf("\n");
            break;
        case 6:
            printf("Unesite vrijednost za pretraživanje: ");
            scanf("%d", &vrijednost);
            if (pronadiElement(korijen, vrijednost)) {
                printf("Element postoji u stablu.\n");
            }
            else {
                printf("Element ne postoji u stablu.\n");
            }
            break;
        case 7:
            printf("Unesite vrijednost za brisanje: ");
            scanf("%d", &vrijednost);
            korijen = obrisiElement(korijen, vrijednost);
            break;
        case 8:
            printf("Izlaz iz programa.\n");
            break;
        default:
            printf("Neispravan odabir!\n");
        }

    } while (izbor != 8);

    return 0;
}
