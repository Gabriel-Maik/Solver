#include "Blad.h"

Blad::Blad(const char* _wiadomosc)
	: std::exception(_wiadomosc)//, ktoraKolumna(0)
{
}
/*
Blad::Blad(const char* _wiadomosc, int _ktoraKolumna)
	: std::exception(_wiadomosc), ktoraKolumna(_ktoraKolumna)
{
}*/
