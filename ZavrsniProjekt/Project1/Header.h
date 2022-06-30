#define _CRT_SECURE_NO_WARNINGS
#ifndef HEADER_H
#define HEADER_H
#include "Strukture.h"

void kreiranjeDatoteke(const char* const);
void dodajLijek(const char* const);
void* ucitajLijekove(const char* const);
void stanjeLijekova(const LIJEK* const);
void* pretrazivnajeLijeka(LIJEK* const);
void pretrazivnajeLijekaIme(LIJEK* const);
void zamjena(LIJEK* const, LIJEK* const);
void sortiranjeLijekova(const LIJEK*);
void azuriranjeLijeka(LIJEK* , const char* const );
void brisanjeLijeka(LIJEK* const , const char* const);
void narudzba(LIJEK* , const char* const, const char* const);



#endif // HEADER_H

#pragma once
