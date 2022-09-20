#pragma once
#include <iostream>
#include <exception>

class Blad : public std::exception
{
	//const int ktoraKolumna;
public:
	Blad(const char* _wiadomosc);
	//Blad(const char* _wiadomosc, int ktoraKolumna);
	//const int getKolumna() const { return ktoraKolumna; }
};

