#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 10

typedef struct osoba* pozicija;
typedef struct osoba {
	char ime[MAX_CHAR];
	char prezime[MAX_CHAR];
	int godina;
	pozicija next;
}osoba;

int dodavanje(pozicija, char* ime, char* prezime, int godina);
int ispis(pozicija);
int kraj(pozicija, char* ime, char* prezime, int godina);
int nadiprezime(pozicija, char* prezime);
int brisanje(pozicija, char* prezime);

int main() {
	osoba head;
	strcpy(head.ime, ""); strcpy(head.prezime, ""); head.godina = 0; head.next = NULL;

	dodavanje(&head, "Ante", "Pirija", 2004);
	ispis(head.next);
	kraj(&head, "Bruno", "Kosta", 2005);
	ispis(head.next);
	nadiprezime(&head, "Pirija");

	brisanje(&head, "Pirija");
	ispis(head.next);
	return 0;
}

int dodavanje(pozicija p, char* ime, char* prezime, int godina) {
	pozicija q;
	q = (pozicija)malloc(sizeof(osoba));
	if (!q) {
		printf("Greska pri alokaciji");
		return -1;
	}
	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	q->godina = godina;
	q->next = p->next;
	p->next = q;
	return 0;
}

int ispis(pozicija p) {
	if (p == NULL)
		printf("Lista je prazna");
	while (p != NULL) {
		printf("%s %s %d \n", p->ime, p->prezime, p->godina);
		p = p->next;
	}
	printf("\n");
	return 0;
}

int kraj(pozicija p, char* ime, char* prezime, int godina) {
	pozicija q;
	q = (pozicija)malloc(sizeof(osoba));
	if (!q) {
		printf("Greska pri alokaciji");
		return -1;
	}
	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	q->godina = godina;

	while (p->next != NULL) {
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	return 0;
}
int nadiprezime(pozicija p, char* prezime) {
	p = p->next;
	while (p != NULL) {
		if (strcmp(p->prezime, prezime) == 0) {
			printf("Pronadena je osoba %s \n", p->prezime);
			return 0;
		}
		p = p->next;
	}
	if (p == NULL)
		printf("Osoba nije pronadena\n");
	return 0;
}

int brisanje(pozicija p, char* prezime) {
	pozicija temp = p->next;
	while (temp != NULL) {
		if (strcmp(p->prezime, prezime) == 0) {
			p->next = temp->next;
			printf("Osoba je izbrisana\n");
			free(temp);
			return 0;
		}
		temp = temp->next;
		p = p->next;
	}
	return 0;

}

