#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "ObslugaPlikow.h"
#include "Macierz.h"
#include "Solver.h"
#include "Blad.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

class Koordynator
{
	string macierze[4];
	string rownania[9];
	string rownaniaPro[2];
	std::ifstream plik;
	char typ;
	int rodzajPliku;
	int nrPliku;
	Macierz<float, float>* macierzF;
	Macierz<double, double>* macierzD;
	//Macierz<int, double>* macierzI;
	vector<char> zmienne;
	void wyznaczZmienne();
	void zaladujNazwy();
	void operator=(const Koordynator& other_) = delete;
	Koordynator(const Koordynator& other_) = delete;
public:
	Koordynator();
	~Koordynator();
	void wyswietlPliki() const;
	void wczytajMacierz(int ktora);
	void wczytajRownanie(int ktore);
	void wczytajRownaniePro(int ktore);
	void rozwiazMacierz() const;
	void rozwiazRownanie() const;
	void prezentacja();
};

