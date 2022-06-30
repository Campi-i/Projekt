#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include "Header.h"

static int brojLijekova = 0;

void kreiranjeDatoteke(const char* const dat) {

	FILE* fp = fopen(dat, "rb");

	// ako ne postoji stvaramo novu datoteku sa wb, ako postoji samo zatvaramo
	if (fp == NULL) {

		fp = fopen(dat, "wb");

		if (strcmp(dat, "lijekovi.bin") == 0) {
			fwrite(&brojLijekova, sizeof(int), 1, fp);
		}

		fclose(fp);
	}
	else {
		fclose(fp);
	}
}

void dodajLijek(const char* const dat) {

	system("CLS");

	//otvaramo datoteku, dajemo joj rb+ permisiju
	FILE* fp = fopen(dat, "rb+");

	if (fp == NULL) {
		perror("Dodavanje lijeka");
		exit(EXIT_FAILURE);
	}

	fread(&brojLijekova, sizeof(int), 1, fp);

	printf("Broj lijekova: %d\n\n", brojLijekova);

	//upis lijeka u datoteku

	LIJEK pom = { 0 };

	pom.id = brojLijekova + 1;
	getchar();

	printf("Unesite ime Lijeka: ");
	scanf("%29[^\n]", pom.naziv);
	getchar();

	printf("Unesite vrstu lijeka (Bolovi, zivci, temperatura, vitamini, itd.): ");
	scanf("%29[^\n]", pom.tip);
	getchar();

	printf("Unesite kolicinu koja je zaprimljena: ");
	scanf("%d", &pom.kolicina_stanje);
	getchar();

	printf("Unesite cijenu lijeka: ");
	scanf("%f", &pom.cijena);

	//postavljanje pokazivaca

	fseek(fp, sizeof(LIJEK) * brojLijekova , SEEK_CUR);
	fwrite(&pom, sizeof(LIJEK), 1, fp);

	printf("Novi lijek dodan\n");

	rewind(fp);
	brojLijekova++;

	fwrite(&brojLijekova, sizeof(int), 1, fp);

	fclose(fp);
}

void* ucitajLijekove(const char* const dat) {

	//otvaranje datoteke

	FILE* fp = fopen(dat, "rb");

	if (fp == NULL) {
		perror("Ucitavanje");
		return NULL;
		exit(EXIT_FAILURE);
	}
	
	//ocitavanje broja lijekova

	fread(&brojLijekova, sizeof(int), 1, fp);

	LIJEK* poljeLijekova = (LIJEK*)calloc(brojLijekova, sizeof(LIJEK));

	if (poljeLijekova == NULL) {
		printf("Zauzimanje memorije");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(poljeLijekova, sizeof(LIJEK), brojLijekova, fp);

	//vracanje poljaLijekova

	return poljeLijekova;
}

void stanjeLijekova(const LIJEK* const poljeLijekova) {
	system("CLS");

	//provjeravanje poljaLijekova

	if (brojLijekova == NULL) {
		printf("Polje lijekova je prazno");
		return ;
	}

	//ispis lijekova iz niza brojLijekova

	for (int i = 0; i < brojLijekova; i++) {
		printf("ID: %d  Naziv: %s  Tip: %s  Kolicina na stanju: %d  Cijena: %.2f \n\n",
			(poljeLijekova + i)->id,
			(poljeLijekova + i)->naziv,
			(poljeLijekova + i)->tip,
			(poljeLijekova + i)->kolicina_stanje,
			(poljeLijekova + i)->cijena);
	}
}

void* pretrazivnajeLijeka(LIJEK* const poljeLijekova) {

	system("CLS");
	//provjera polja
	
	if (poljeLijekova == NULL) {
		printf("Polje lijekova prazno\n");
		return NULL;
	}

	int trazeniLijek = 0;
	int temp = 0;

	printf("Unesite ID lijeka: ");
	scanf("%d", &trazeniLijek);

	//petlja kojom idemo kroz polje, usporedjujemo trazeni id, s id-evima u polju

	for (int i = 0; i < brojLijekova; i++) {

		if (trazeniLijek == (poljeLijekova + i)->id) {

			printf("ID: %d  Naziv: %s  Tip: %s  Kolicina na stanju: %d.  Cijena: %f\n\n",
				(poljeLijekova + i)->id,
				(poljeLijekova + i)->naziv,
				(poljeLijekova + i)->tip,
				(poljeLijekova + i)->kolicina_stanje,
				(poljeLijekova + i)->cijena);

			temp++;
		}

	}

	for (int i = 0; i < brojLijekova; i++) {

		if (trazeniLijek == (poljeLijekova + i)->id) {
			printf("Clan pronaden\n");

			return (poljeLijekova + i);
		}
	}

	if (temp == 0) {
		printf("Nema lijeka pod tim imenom\n");
		return;
	}

	return NULL;
}

void pretrazivnajeLijekaIme(LIJEK* const poljeLijekova) {

	system("CLS");

	//provjera polja lijekova
	if (brojLijekova == 0) {
		printf("Polje lijekova prazno\n");
		return;
	}

	char trazeniLijek[25];
	int temp = 0;

	printf("Unesite ime lijeka: ");
	getchar();
	scanf("%29[^\n]", trazeniLijek);


	//petlja kojom prolazimo kroz polje i usporedujemo trazeno ime

	for (int i = 0; i < brojLijekova; i++) {

		if (strcmp(trazeniLijek, (poljeLijekova + i)->naziv) == 0) {

			printf("ID: %d  Naziv: %s  Tip: %s  Kolicina na stanju: %d.  Cijena: %f\n\n",
				(poljeLijekova + i)->id,
				(poljeLijekova + i)->naziv,
				(poljeLijekova + i)->tip,
				(poljeLijekova + i)->kolicina_stanje,
				(poljeLijekova + i)->cijena);

			temp++;
		}

	}

	if (temp == 0) {
		printf("Nema lijeka pod tim imenom\n");
		return;
	}
}

void zamjena(LIJEK* const high, LIJEK* const low) {
	LIJEK temp = { 0 };

	temp = *low;
	*low = *high;
	*high = temp;

}

void sortiranjeLijekova(const LIJEK* poljeLijekova) {
	
	system("CLS");

	int min = -1;

	for (int i = 0; i < brojLijekova - 1; i++)
	{
		min = i;

		for (int j = i + 1; j < brojLijekova; j++)
		{
			if ((poljeLijekova + j)->cijena < (poljeLijekova + min)->cijena) {
				min = j;
			}
		}
		zamjena((poljeLijekova + i), (poljeLijekova + min));
	}

	stanjeLijekova(poljeLijekova);
}

void azuriranjeLijeka(LIJEK* poljeLijekova, const char* const dat) {

	system("CLS");

	//provjera poljaLijkeova

	if (poljeLijekova == NULL) {
		printf("Polje prazno\n");
		return;
	}

	FILE* fp = fopen(dat, "rb+");

	//provjera datoteke

	if (fp == NULL) {
		printf("Azuriranje korisnika");
		return 1;
	}

	int trazeniId;

	printf("Unesite ID lijeka kojeg zelite azurirati: ");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 1 || trazeniId > brojLijekova) {
			printf("Lijek s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojLijekova);


	//Azuriranje datoteke

	LIJEK temp = { 0 };

	temp.id = trazeniId;

	getchar();

	printf("Unesite novi naziv lijeka (trenutno: %s): ", (poljeLijekova + trazeniId - 1)->naziv);
	scanf("%24[^\n]", temp.naziv);
	getchar();

	printf("Unesite novi tip lijeka (trenutno %s): ", (poljeLijekova + trazeniId - 1)->tip);
	scanf("%24[^\n]", temp.tip);
	getchar();

	printf("Unesite novu kolicinu lijeka (trenutno %d): ", (poljeLijekova + trazeniId - 1)->kolicina_stanje);
	scanf("%d", &temp.kolicina_stanje);


	printf("Unesite novu cijenu lijeka (trenutno %f): ", (poljeLijekova + trazeniId - 1)->cijena);
	scanf("%f", &temp.cijena);


	fseek(fp, sizeof(int), SEEK_SET);
	fseek(fp, sizeof(LIJEK) * (trazeniId - 1), SEEK_CUR);
	fwrite(&temp, sizeof(LIJEK), 1, fp);

	printf("Lijek uspjesno azuriran\n");

	fclose(fp);

}

void brisanjeLijeka(LIJEK* const poljeLijekova, const char* const dat) {
	
	system("CLS");

	//provjera polja

	if (poljeLijekova == NULL) {
		printf("Polje je prazno\n");
		return;
	}

	FILE* fp = fopen(dat, "rb+");

	//provjera datoteke

	if (fp == NULL) {
		printf("Brisanje lijeka");
		exit(EXIT_FAILURE);
	}

	fseek(fp, sizeof(int), SEEK_CUR);

	int trazeniId;

	printf("Unesite ID lijeka kojeg zelite obrisati: ");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 1 || trazeniId > brojLijekova) {
			printf("Lijek s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojLijekova);

	int counter = 0;

	//petlja kojom prolazimo kroz polje te brisemo zeljeni lijek

	for (int i = 0; i < brojLijekova; i++) {

		if (trazeniId != (poljeLijekova + i)->id) {
			
			fwrite((poljeLijekova + i), sizeof(LIJEK), 1, fp);
			counter++;
		}
	}

	rewind(fp);

	fwrite(&counter, sizeof(int), 1, fp);

	fclose(fp);

	printf("Lijek je uspjesno obrisan\n");

}

void narudzba(LIJEK* poljeLijekova, const char* const dat, const char* const datRacun) {

	system("CLS");

	srand((unsigned)time(NULL));

	//provjera poljaLijekova

	if (poljeLijekova == NULL) {
		printf("Polje korisnika prazno\n");
		return;
	}

	//provjera datoteke

	FILE* fp = fopen(dat, "rb+");

	if (fp == NULL) {
		printf("Ucitavanje korisnika");
		return;
	}

	//provjera datoteke, racun

	FILE* fprac = fopen(datRacun, "w");

	if (fprac == NULL) {
		printf("Pogreska pri stvaranju racuna");
		return;
	}

	stanjeLijekova(poljeLijekova);

	

	int ID_kupnje = 0;

	printf("Unesite ID lijeka kojeg zelite kupiti: ");

	do {
		scanf("%d", &ID_kupnje);

		if (ID_kupnje < 1 || ID_kupnje > brojLijekova) {
			printf("Lijek s unesenim ID-om ne postoji, unesite ispravan ID: ");
			stanjeLijekova(poljeLijekova);
		}
	} while (ID_kupnje < 1 || ID_kupnje > brojLijekova);


	int kolicina = 0;

	printf("Unesite zeljenu kolicinu koju zelite kupiti ");

	do {
		scanf("%d", &kolicina);

		if (kolicina < 1 || kolicina >((poljeLijekova + ID_kupnje - 1)->kolicina_stanje)) {
			printf("Unesena kolicina nije dozvoljena \n");
		}
	} while (kolicina < 1 || kolicina >((poljeLijekova + ID_kupnje - 1)->kolicina_stanje));
	
	//smanjenje kolicine lijeka unutar binarne datotoeke

	LIJEK temp = { 0 };
	temp.id = ((poljeLijekova + ID_kupnje - 1)->id);

	strcpy(temp.naziv, (poljeLijekova + ID_kupnje - 1)->naziv);
	strcpy(temp.tip, (poljeLijekova + ID_kupnje - 1)->tip);

	temp.kolicina_stanje = ((poljeLijekova + ID_kupnje - 1)->kolicina_stanje) - kolicina;

	temp.cijena = ((poljeLijekova + ID_kupnje - 1)->cijena);


	fseek(fp, sizeof(int), SEEK_SET);
	fseek(fp, sizeof(LIJEK) * (ID_kupnje - 1), SEEK_CUR);
	fwrite(&temp, sizeof(LIJEK), 1, fp);
	
	fclose(fp);
	
	
	
	
	
	int brojRacuna = 0 + (float)rand() / RAND_MAX * (99999 - 0);
	
	float pom = kolicina * (poljeLijekova + ID_kupnje - 1)->cijena;

	time_t s, val = 1;
	struct tm* curr_time;
	s = time(NULL); //Spremamamo vrijeme u sekundama
	curr_time = localtime(&s); //dohvacamo vrijeme koristeci localtime() funkciju

		
	//ispis racuna u .txt datoteku

	fprintf(fprac, "===================================================\n\n");
	fprintf(fprac, "\t	    LJEKARNA                        \n\n");
	fprintf(fprac, "===================================================\n\n");
	fprintf(fprac, "Adresa: Trg Ante Starcevica 7, 31000, Osijek\n");
	fprintf(fprac, "Vrijeme: %02d:%02d:%02d\n", curr_time->tm_hour, curr_time->tm_min,curr_time->tm_sec);
	fprintf(fprac, "Racun broj: %d\n\n", brojRacuna);
	fprintf(fprac, "===================================================\n\n");
	fprintf(fprac, "Ime lijeka: %s\n", (poljeLijekova + ID_kupnje - 1)->naziv);
	fprintf(fprac, "Namjena : %s\n", (poljeLijekova + ID_kupnje - 1)->tip);
	fprintf(fprac, "Cijena po komadu : %.2f \n", (poljeLijekova + ID_kupnje - 1)->cijena);
	fprintf(fprac, "Kolicina : %d\n\n", kolicina);
	fprintf(fprac, "===================================================\n\n");
	fprintf(fprac, "Ukupna cijena za platit : %.2f HRK\n\n", pom);
	fprintf(fprac, "===================================================\n\n");
	
	printf("HVALA NA KUPNJI.\n");

	fclose(fprac);
}
