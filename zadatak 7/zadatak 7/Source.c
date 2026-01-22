#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef struct Direktorij* Pozicija;

struct Direktorij {
    char naziv[MAX];
    Pozicija podDirektorij;
    Pozicija sljedeci;
    Pozicija roditelj;
};

/* Funkcije */
Pozicija stvoriDirektorij(char* naziv, Pozicija roditelj);
void napraviDirektorij(Pozicija trenutni);
void promijeniDirektorij(Pozicija* trenutni);
void vratiSeNazad(Pozicija* trenutni);
void ispisiDirektorij(Pozicija trenutni);

int main() {
    int izbor = 0;

    Pozicija root = stvoriDirektorij("root", NULL);
    Pozicija trenutni = root;

    while (1) {
        printf("\nTrenutni direktorij: %s\n", trenutni->naziv);
        printf("1 - md (napravi direktorij)\n");
        printf("2 - cd dir (udi u direktorij)\n");
        printf("3 - cd..\n");
        printf("4 - dir (ispis sadrzaja)\n");
        printf("5 - izlaz\n");
        printf("Odabir: ");
        scanf("%d", &izbor);

        switch (izbor) {
        case 1:
            napraviDirektorij(trenutni);
            break;
        case 2:
            promijeniDirektorij(&trenutni);
            break;
        case 3:
            vratiSeNazad(&trenutni);
            break;
        case 4:
            ispisiDirektorij(trenutni);
            break;
        case 5:
            return 0;
        default:
            printf("Neispravan unos!\n");
        }
    }
}

/* Kreiranje novog direktorija */
Pozicija stvoriDirektorij(char* naziv, Pozicija roditelj) {
    Pozicija novi = (Pozicija)malloc(sizeof(struct Direktorij));
    strcpy(novi->naziv, naziv);
    novi->podDirektorij = NULL;
    novi->sljedeci = NULL;
    novi->roditelj = roditelj;
    return novi;
}

/* md */
void napraviDirektorij(Pozicija trenutni) {
    char naziv[MAX];
    printf("Unesi naziv direktorija: ");
    scanf("%s", naziv);

    Pozicija novi = stvoriDirektorij(naziv, trenutni);

    if (trenutni->podDirektorij == NULL)
        trenutni->podDirektorij = novi;
    else {
        Pozicija temp = trenutni->podDirektorij;
        while (temp->sljedeci != NULL)
            temp = temp->sljedeci;
        temp->sljedeci = novi;
    }
}

/* cd dir */
void promijeniDirektorij(Pozicija* trenutni) {
    char naziv[MAX];
    printf("Unesi naziv direktorija: ");
    scanf("%s", naziv);

    Pozicija temp = (*trenutni)->podDirektorij;

    while (temp != NULL) {
        if (strcmp(temp->naziv, naziv) == 0) {
            *trenutni = temp;
            return;
        }
        temp = temp->sljedeci;
    }

    printf("Direktorij ne postoji!\n");
}

/* cd.. */
void vratiSeNazad(Pozicija* trenutni) {
    if ((*trenutni)->roditelj != NULL)
        *trenutni = (*trenutni)->roditelj;
    else
        printf("Vec si u root direktoriju!\n");
}

/* dir */
void ispisiDirektorij(Pozicija trenutni) {
    Pozicija temp = trenutni->podDirektorij;

    if (temp == NULL) {
        printf("Direktorij je prazan.\n");
        return;
    }

    printf("Sadrzaj direktorija:\n");
    while (temp != NULL) {
        printf("- %s\n", temp->naziv);
        temp = temp->sljedeci;
    }
}
