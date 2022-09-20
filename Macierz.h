#pragma once
#include <iomanip>
#include <iostream>
#include <vector>
#include "Blad.h"

template <typename T1, typename T2>
class Macierz {
	const int ile_wierszy;
	//T1* dane;
	//T1** wiersze;
	//T2* wyrazyWolne;
	std::vector<std::vector<T1>> wiersze;
	std::vector<T2> wyrazyWolne;
public:
	Macierz(const int iloscRownan = 3);
	// Usuniety konstruktor kopiujacy i operator przypisania powoduje,
	// ze obiektow tej klasy nie da sie przekazywac przez wartosc.
	// Jest to rowniez sposob dotrzymania zasady trzech.
	void operator=(const Macierz& other_) = delete;
	Macierz(const Macierz& other_) = delete;
	~Macierz();

	void alokuj();
	void zeruj();
	void pokaz() const;

	int getIleWierszy() const { return ile_wierszy; }
	T1& element(int nrWiersza, int nrKolumny);
	T2& wolny(int nrWiersza);
};

template <typename T1, typename T2>
Macierz<T1, T2>::Macierz(const int iloscRownan) : ile_wierszy(iloscRownan) {
	alokuj();
	zeruj();
}
/*
template <typename T1, typename T2>
Macierz<T1, T2>::Macierz(const Macierz& other_)
	: ile_wierszy(other_.getIleWierszy())
{
	alokuj();
	for (int w = 0; w < ile_wierszy; w++)
	{
		for (int k = 0; k < ile_wierszy; k++)
		{
			element(w, k) = other_.element(w, k);
		}
		wolny(w) = other_.wolny(w);
	}
}
*/
template <typename T1, typename T2>
Macierz<T1, T2>::~Macierz()
{
	//delete[] wiersze;
	//delete[] dane;
	//delete[] wyrazyWolne;
}

template <typename T1, typename T2>
void Macierz<T1, T2>::alokuj()
{
	if (ile_wierszy < 1) throw Blad("Nieprawidlowy rozmiar macierzy");
	/*dane = new T1[ile_wierszy*ile_wierszy];
	wiersze = new T1*[ile_wierszy];
	wyrazyWolne = new T2[ile_wierszy];
	for (int i = 0; i < ile_wierszy; ++i) {
		wiersze[i] = &(dane[i*ile_wierszy]);
	}*/
	wiersze.reserve(ile_wierszy);
	for (int i = 0; i < ile_wierszy; ++i) {
		std::vector<T1> pusty;
		wiersze.push_back(pusty);
		wiersze[i].reserve(ile_wierszy);
	}
	wyrazyWolne.reserve(ile_wierszy);
}

template <typename T1, typename T2>
void Macierz<T1, T2>::zeruj() {
	/*for (int i = 0; i < ile_wierszy*ile_wierszy; ++i) {
		dane[i] = 0;
	}*/
	for (int w = 0; w < ile_wierszy; w++)
	{
		for (int k = 0; k < ile_wierszy; k++)
		{
			wiersze[w].push_back(0);
		}
	}
	for (int i = 0; i < ile_wierszy; i++)
	{
		wyrazyWolne.push_back(0);
	}
}

template <typename T1, typename T2>
void Macierz<T1, T2>::pokaz() const {
	using std::cout;
	using std::endl;
	using std::setw;
	using std::fixed;
	using std::setprecision;
	for (int i = 0; i < ile_wierszy; ++i) {
		for (int j = 0; j < ile_wierszy; ++j) {
			cout << setw(8) << setprecision(4) << fixed << wiersze[i][j];
		}
		cout << "  |" << setw(8) << setprecision(4) << wyrazyWolne[i] << endl;
	}
}

template <typename T1, typename T2>
T1& Macierz<T1, T2>::element(int nrWiersza, int nrKolumny)
{
	if ((nrWiersza >= ile_wierszy) || (nrWiersza < 0) || (nrKolumny >= ile_wierszy) || (nrKolumny < 0)) throw Blad("Nieprawidlowy numer elementu");
	return wiersze[nrWiersza][nrKolumny];
}

template <typename T1, typename T2>
T2& Macierz<T1, T2>::wolny(int nrWiersza)
{
	if ((nrWiersza >= ile_wierszy) || (nrWiersza < 0)) throw Blad("Nieprawidlowy numer wyrazu wolnego");
	return wyrazyWolne[nrWiersza];
}
