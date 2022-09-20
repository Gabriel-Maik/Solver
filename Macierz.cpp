/*#include <iomanip>
#include <iostream>

#include "Macierz.h"

Macierz<T1, T2>::Macierz(const int iloscRownan) : ile_wierszy(iloscRownan), dlugosc_wiersza(iloscRownan + 1) {
	alokuj();
	zeruj();
}

Macierz::~Macierz()
{
	delete[] wiersze;
	delete[] dane;
}

void Macierz::alokuj()
{
	dane = new double[ile_wierszy*dlugosc_wiersza];
	wiersze = new double*[ile_wierszy];
	for (int i = 0; i < ile_wierszy; ++i) {
		wiersze[i] = dane + i * dlugosc_wiersza;
	}
}

void Macierz::zeruj() {
	for (int i = 0; i < ile_wierszy*dlugosc_wiersza; ++i) {
		dane[i] = 0;
	}
}

void Macierz::pokaz() const {
	using std::cout;
	using std::endl;
	using std::setw;
	using std::fixed;
	using std::setprecision;
	for (int i = 0; i < ile_wierszy; ++i) {
		for (int j = 0; j < dlugosc_wiersza - 1; ++j) {
			cout << setw(8) << setprecision(4) << fixed << wiersze[i][j];
		}
		cout << "  |" << setw(8) << setprecision(4) << wiersze[i][dlugosc_wiersza - 1] << endl;
	}
}

double& Macierz::element(int nrWiersza, int nrKolumny)
{
	if ((nrWiersza >= ile_wierszy) || (nrWiersza < 0) || (nrKolumny >= dlugosc_wiersza) || (nrKolumny < 0)) throw Blad("Nieprawidlowy numer elementu");
	return wiersze[nrWiersza][nrKolumny];
}

double& Macierz::wolny(int nrWiersza)
{
	if ((nrWiersza >= ile_wierszy) || (nrWiersza < 0)) throw Blad("Nieprawidlowy numer wyrazu wolnego");
	return wiersze[nrWiersza][dlugosc_wiersza - 1];
}*/