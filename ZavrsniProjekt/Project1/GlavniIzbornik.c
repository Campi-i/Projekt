#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<math.h>
#include "Strukture.h"
#include "Header.h"

int izbornik(const char* const lijekoviDat, const char* const racuniDat) {

	static LIJEK* poljeLijekova = NULL;
	static LIJEK* pronadjeniLijek = NULL;

	int odabir = 0;



	printf("***************************************\n");
	printf("          ~ LJEKARNA ~          \n");
	printf("***************************************\n");
	printf("1 - Unos novog lijeka             \n");
	printf("---------------------------------------\n");
	printf("2 - Stanje svih lijekova u ljekarni  \n");
	printf("---------------------------------------\n");
	printf("3 - Pretrazivanje lijeka po imenu       \n");
	printf("---------------------------------------\n");
	printf("4 - Pretrazivanje lijeka po ID-u	       \n");
	printf("---------------------------------------\n");
	printf("5 - Sortiranje lijekova po cijeni	       \n");
	printf("---------------------------------------\n");
	printf("6 - Azuriranje lijeka           \n");
	printf("---------------------------------------\n");
	printf("7 - Brisanje lijeka iz ljekarne	       \n");
	printf("---------------------------------------\n");
	printf("8 - Kupnja lijeka	       \n");
	printf("---------------------------------------\n");
	printf("10 - Izlaz iz programa         \n");
	printf("***************************************\n");

	scanf("%d", &odabir);

	switch (odabir) {

	case 1:
		dodajLijek(lijekoviDat);
		break;

	case 2:

		if (poljeLijekova != NULL) {
			free(poljeLijekova);
			poljeLijekova = NULL;
		}

		poljeLijekova = (LIJEK*)ucitajLijekove(lijekoviDat);

		stanjeLijekova(poljeLijekova);

		break;

	case 3:

		if (poljeLijekova != NULL) {
			free(poljeLijekova);
			poljeLijekova = NULL;
		}

		poljeLijekova = (LIJEK*)ucitajLijekove(lijekoviDat);

		pretrazivnajeLijekaIme(poljeLijekova);
		break;


	case 4:

		if (poljeLijekova != NULL) {
			free(poljeLijekova);
			poljeLijekova = NULL;
		}

		poljeLijekova = (LIJEK*)ucitajLijekove(lijekoviDat);

		pretrazivnajeLijeka(poljeLijekova);

		break;

	case 5:

		if (poljeLijekova != NULL) {
			free(poljeLijekova);
			poljeLijekova = NULL;
		}

		poljeLijekova = (LIJEK*)ucitajLijekove(lijekoviDat);

		sortiranjeLijekova(poljeLijekova);


		break;

	case 6:
		if (poljeLijekova != NULL) {
			free(poljeLijekova);
			poljeLijekova = NULL;
		}

		poljeLijekova = (LIJEK*)ucitajLijekove(lijekoviDat);

		azuriranjeLijeka(poljeLijekova, lijekoviDat);

		break;

	case 7:

		if (poljeLijekova != NULL) {
			free(poljeLijekova);
			poljeLijekova = NULL;
		}

		poljeLijekova = (LIJEK*)ucitajLijekove(lijekoviDat);

		brisanjeLijeka(poljeLijekova, lijekoviDat);

		break;


	case 8:

		if (poljeLijekova != NULL) {
			free(poljeLijekova);
			poljeLijekova = NULL;
		}

		poljeLijekova = (LIJEK*)ucitajLijekove(lijekoviDat);

		narudzba(poljeLijekova, lijekoviDat, racuniDat);

		break;

	default:
		odabir = 0;
	}

	return odabir;
}
