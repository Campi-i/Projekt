#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include "Header.h"
#include "Strukture.h"

int main(void) {

	int odgovor = 1;


	char* datotekaLijekovi = "lijekovi.bin";
	char* datotekaRacun = "racun.txt";

	kreiranjeDatoteke(datotekaLijekovi);
	kreiranjeDatoteke(datotekaRacun);

	while (odgovor) {
		odgovor = izbornik(datotekaLijekovi, datotekaRacun);
	}

	printf("\nKraj programa");

	return 0;
}
