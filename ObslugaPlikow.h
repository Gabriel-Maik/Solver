#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include "Macierz.h"

using std::cout;
using std::endl;

template <typename T>
class ObslugaPlikow
{
	std::ifstream& plik;
	void usuwanieOdstepow(std::string& fraza);
	void wstepneFormatowanieRownaniaPro(std::string& fraza, std::vector<char>& zmienne);
	bool czyCyfra(char znak);
	T liczbaZFragmentu(std::string& fraza, int pozycja, char typ);
public:
	ObslugaPlikow(std::ifstream& _plik) : plik(_plik) {};
	~ObslugaPlikow() {};
	Macierz<T, T>* wczytywanieMacierzyTypu();
	Macierz<T, T>* wczytywanieZUkladuMacierzyTypu(std::vector<char>& zmienne);
	Macierz<T, T>* wczytywanieZUkladuProMacierzyTypu(std::vector<char>& zmienne);
	void wyznaczanieZmiennych(std::vector<char>& zmienne);
};

template <typename T>
Macierz<T, T>* ObslugaPlikow<T>::wczytywanieMacierzyTypu()
{
	int ile_wierszy = 0;
	T zmiennaPomocnicza;
	std::vector<T> wiersz;
	std::string linia;
	getline(plik, linia);
	std::istringstream s(linia);
	while (!s.eof())
	{
		s >> zmiennaPomocnicza;
		wiersz.push_back(zmiennaPomocnicza);
		ile_wierszy++;
	}
	ile_wierszy--;
	Macierz<T, T>* tworzonaMacierz = new Macierz<T, T>(ile_wierszy);
	for (int k = 0; k < ile_wierszy; k++)
	{
		tworzonaMacierz->element(0, k) = wiersz[k];
	}
	tworzonaMacierz->wolny(0) = wiersz[ile_wierszy];
	for (int w = 1; w < ile_wierszy; w++)
	{
		std::string linia2;
		getline(plik, linia2);
		std::istringstream s2(linia2);
		for (int k = 0; k < ile_wierszy; k++)
		{
			s2 >> zmiennaPomocnicza;
			tworzonaMacierz->element(w, k) = zmiennaPomocnicza;
		}
		s2 >> zmiennaPomocnicza;
		tworzonaMacierz->wolny(w) = zmiennaPomocnicza;
	}
	return tworzonaMacierz;
}

template <typename T>
Macierz<T, T>* ObslugaPlikow<T>::wczytywanieZUkladuMacierzyTypu(std::vector<char>& zmienne)
{
	std::vector<T> wierszWspolczynnikow;
	T zmiennaPomocnicza;
	char znak;
	int ile_wierszy = 0;
	std::string linia;
	getline(plik, linia);
	usuwanieOdstepow(linia);
	//cout << "linia: " << linia << endl;
	for (int i = 1; i < linia.length(); i++)
	{
		if ((linia[i] == '+') || (linia[i] == '-')) ile_wierszy++;
		if (linia[i] == 'e') linia[i] = '<'; // chyba nikt o zdrowych zmyslach nie uzyje < albo > jako zmiennej
		if (linia[i] == 'E') linia[i] = '>';
		if (linia[i] == '=') break;
	}
	std::istringstream s(linia);
	ile_wierszy++;
	for (int k = 0; k < ile_wierszy; k++)
	{
		s >> zmiennaPomocnicza;
		s >> znak;
		if (znak == '*') s >> znak;
		wierszWspolczynnikow.push_back(zmiennaPomocnicza);
		zmienne.push_back(znak);
	}
	s >> znak; // '='
	s >> zmiennaPomocnicza;
	wierszWspolczynnikow.push_back(zmiennaPomocnicza);
	Macierz<T, T>* zwracana = new Macierz<T, T>(ile_wierszy);
	for (int k = 0; k < ile_wierszy; k++)
	{
		zwracana->element(0, k) = wierszWspolczynnikow[k];
	}
	zwracana->wolny(0) = wierszWspolczynnikow[ile_wierszy];
	for (int w = 1; w < ile_wierszy; w++)
	{
		std::string linia2;
		getline(plik, linia2);
		usuwanieOdstepow(linia2);
		for (int i = 1; i < linia2.length(); i++)
		{
			if (linia2[i] == 'e') linia2[i] = '<';
			if (linia2[i] == 'E') linia2[i] = '>';
		}
		std::istringstream s2(linia2);
		for (int k = 0; k < ile_wierszy; k++)
		{
			s2 >> zmiennaPomocnicza;
			zwracana->element(w, k) = zmiennaPomocnicza;
			s2 >> znak;
			if (znak == '*') s2 >> znak;
		}
		s2 >> znak;
		s2 >> zmiennaPomocnicza;
		zwracana->wolny(w) = zmiennaPomocnicza;
	}
	//zwracana->pokaz(); // testowe wyswietlenie obrabianej macierzy
	for (int i = 0; i < ile_wierszy; i++)
	{
		if (zmienne[i] == '<') zmienne[i] = 'e';
		if (zmienne[i] == '>') zmienne[i] = 'E';
	}
	/*
	// kontrolne pokazywanie zmiennych
	for (int i = 0; i < ile_wierszy; i++)
	{
		cout << " " << zmienne[i];
	}*/
	return zwracana;
}

template <typename T>
Macierz<T, T>* ObslugaPlikow<T>::wczytywanieZUkladuProMacierzyTypu(std::vector<char>& zmienne)
{
	std::string linia1;
	std::getline(plik, linia1);
	char typ = linia1[0];
	Macierz<T, T>* zwracana = new Macierz<T, T>(zmienne.size());
	bool czyPrzedZnakiemRownosci;
	for (int w = 0; w < zmienne.size(); w++)
	{
		czyPrzedZnakiemRownosci = true;
		std::string linia;
		std::getline(plik, linia);
		//cout << "linia: " << linia  <<"koniec"<< endl;
		usuwanieOdstepow(linia);
		wstepneFormatowanieRownaniaPro(linia, zmienne);
		//cout << "sformatowane: " << linia << endl; // testowe wyswietlenie wstepnie sformatowanych linii
		for (int j = 0; j < linia.length(); j++)
		{
			if (linia[j] == '=')
			{
				czyPrzedZnakiemRownosci = false;
			}
			else if (linia[j] == '#')
			{
				if (czyPrzedZnakiemRownosci) zwracana->wolny(w) -= liczbaZFragmentu(linia, j - 1, typ);
				else zwracana->wolny(w) += liczbaZFragmentu(linia, j - 1, typ);
			}
			else
			{
				for (int i = 0; i < zmienne.size(); i++)
				{
					if (linia[j] == zmienne[i])
					{
						if (czyPrzedZnakiemRownosci) zwracana->element(w, i) += liczbaZFragmentu(linia, j - 1, typ);
						else zwracana->element(w, i) -= liczbaZFragmentu(linia, j - 1, typ);
						break;
					}
				}
			}
		}
	}
	return zwracana;
}

template <typename T>
void ObslugaPlikow<T>::usuwanieOdstepow(std::string& fraza)
{
	for (int i = 0; i < fraza.length(); i++)
	{
		if ((fraza[i] == ' ') || (fraza[i] == '\t') || (fraza[i] == '*')) // przy okazji mozna usunac znaki mnozenia
		{
			fraza.erase(fraza.begin() + i);
			i--;
		}
	}
}

template <typename T>
void ObslugaPlikow<T>::wyznaczanieZmiennych(std::vector<char>& zmienne)
{
	char znak;
	do
	{
		plik >> znak;
		switch (znak)
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '-':
		case '+':
		case '=':
		case '\t':
		case '\n':
		case ' ':
		case '.':
		case ',':
		case '*':
		case EOF:
			break;
		default:
			bool czyDodac = true;
			for (int i = 0; i < zmienne.size(); i++) // sprawdzanie, czy juz nie ma takiego znaku
			{
				if (zmienne[i] == znak)
				{
					czyDodac = false;
					break;
				}
			}
			if (czyDodac) zmienne.push_back(znak);
			break;
		}
	} while (plik.eof() == false);
}

template <typename T>
void ObslugaPlikow<T>::wstepneFormatowanieRownaniaPro(std::string& fraza, std::vector<char>& zmienne)
{
	for (int i = 0; i < fraza.length(); i++) // szukanie zmiennych i wstawianie 1 jezeli nie ma
	{
		for (int j = 0; j < zmienne.size(); j++)
		{
			if (zmienne[j] == fraza[i])
			{
				if (i == 0)
				{
					fraza.insert(i, "1");
					break;
				}
				else if ((fraza[i - 1] == '-') || (fraza[i - 1] == '+'))
				{
					fraza.insert(i, "1");
					break;
				}
			}
		}
		if (((fraza[i] == '+') || (fraza[i] == '-') || (fraza[i] == '=')) && (i != 0))
		{
			if (czyCyfra(fraza[i - 1]))
			{
				fraza.insert(i, "#"); // # oznacza wyraz wolny
			}
		}
	}
	if (czyCyfra(fraza[fraza.length() - 1]))
	{
		fraza.append("#");
	}
}

template <typename T>
bool ObslugaPlikow<T>::czyCyfra(char znak)
{
	switch(znak)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return true;
		break;
	default:
		return false;
		break;
	}
}

template <typename T>
T ObslugaPlikow<T>::liczbaZFragmentu(std::string& fraza, int pozycja, char typ)
{
	int i;
	for (i = pozycja - 1; i > 0; i--)
	{
		if ((fraza[i] == '+') || (fraza[i] == '-') || (fraza[i] == '=')) break;
	}
	std::string liczbaS = fraza.substr(i, pozycja - i + 1);
	if (liczbaS[0] == '=') liczbaS.erase(liczbaS.begin());
	//cout << "liczbaS: " << liczbaS << endl;
	T liczba;
	if (typ == 'F') liczba = std::stof(liczbaS);
	else if (typ == 'D') liczba = std::stod(liczbaS);
	//cout << "zwracam liczbe: " << liczba << endl;
	return liczba;
}