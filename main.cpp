#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Macierz.h"
#include "Solver.h"
#include "Blad.h"
#include "Koordynator.h"

using std::cout;
using std::endl;

void demo3(Macierz<double, double>& m) {
	m.element(0, 0) = 2.2;
	m.element(0, 1) = -1.5;
	m.element(0, 2) = 0.6;
	m.wolny(0) = 1.3;
	m.element(1, 0) = -0.7;
	m.element(1, 1) = 1.2;
	m.element(1, 2) = 1.8;
	m.wolny(1) = 1.85;
	m.element(2, 0) = 1.2;
	m.element(2, 1) = 0.8;
	m.element(2, 2) = -2.1;
	m.wolny(2) = -4.55;
}

void demo4(Macierz<double, double>& m) {
  m.element(0, 0) = -0.2;
  m.element(0, 1) =  1.1;
  m.element(0, 2) =  0.1;
  m.element(0, 3) =  0.9;
  m.wolny(0) = 1.95;
  m.element(1, 0) = -1.2;
  m.element(1, 1) =  3.5;
  m.element(1, 2) = -2.6;
  m.element(1, 3) =  1.9;
  m.wolny(1) = 5.43;
  m.element(2, 0) =  0.8;
  m.element(2, 1) = -2.3;
  m.element(2, 2) =  1.2;
  m.element(2, 3) = -0.8;
  m.wolny(2) = -3.28;
  m.element(3, 0) =  0.2;
  m.element(3, 1) = -1.7;
  m.element(3, 2) =  1.9;
  m.element(3, 3) =  1.3;
  m.wolny(3) = -0.05;
}

/*
void demo4x4(Macierz<double, double>& m) {
	m.element(0, 0) = 0;
	m.element(0, 1) = 1.1;
	m.element(0, 2) = 0.1;
	m.element(0, 2) = 0.9;
	m.wolny(0) = 1.95;
	m.element(1, 0) = 5;
	m.element(1, 1) = 0.23;
	m.element(1, 2) = -2.6;
	m.element(1, 2) = 1.9;
	m.wolny(1) = 5.43;
	m.element(2, 0) = 7;
	m.element(2, 1) = -2.3;
	m.element(2, 2) = 1.2;
	m.element(2, 3) = -0.8;
	m.wolny(2) = -3.28;
	m.element(3, 0) = 9;
	m.element(3, 1) = -1.7;
	m.element(3, 2) = 1.9;
	m.element(3, 2) = 1.3;
	m.wolny(3) = -0.05;
}

void demo2(Macierz<double, double>& m)
{
	m.element(0, 0) = 2;
	m.element(0, 1) = 4;
	m.wolny(0) = 6;
	m.element(1, 0) = 1;
	m.element(1, 1) = 2;
	m.wolny(1) = 3;
}

void demo1(Macierz<double, double>& m)
{
	m.element(0, 0) = 1.26;
	m.wolny(0) = 1.38;
}
*/
/*
void usuwanieOdstepow(std::string& fraza)
{
	for (int i = 0; i < fraza.length(); i++)
	{
		if ((fraza[i] == ' ') || (fraza[i] == '\t'))
		{
			fraza.erase(fraza.begin() + i);
			i--;
		}
		
	}
}

template <typename T>
Macierz<T, T>* wczytywanieMacierzyTypu(std::fstream& plik)
{
	int ile_wierszy = 0;
	T zmiennaPomocnicza;
	std::vector<T> wiersz;
	std::string linia;
	getline(plik, linia);
	std::stringstream s(linia);
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
		std::stringstream s2(linia2);
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
Macierz<T, T>* wczytywanieZUkladuMacierzyTypu(std::fstream& plik, std::vector<char>& zmienne)
{
	std::vector<T> wierszWspolczynnikow;
	T zmiennaPomocnicza;
	char znak;
	int ile_wierszy = 0;
	std::string linia;
	getline(plik, linia);
	usuwanieOdstepow(linia);
	for (int i = 1; i < linia.length(); i++)
	{
		if ((linia[i] == '+') || (linia[i] == '-')) ile_wierszy++;
		if (linia[i] == 'e') linia[i] = '<'; // chyba nikt o zdrowych zmyslach nie uzyje < albo > jako zmiennej
		if (linia[i] == 'E') linia[i] = '>';
		if (linia[i] == '=') break;
	}
	std::stringstream s(linia);
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
		std::stringstream s2(linia2);
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
	zwracana->pokaz();
	for (int i = 0; i < ile_wierszy; i++)
	{
		if (zmienne[i] == '<') zmienne[i] = 'e';
		if (zmienne[i] == '>') zmienne[i] = 'E';
	}
	for (int i = 0; i < ile_wierszy; i++)
	{
		cout << " " << zmienne[i];
	}
	return zwracana;
}
*/

void demo2I(Macierz<int, double>& m)
{
	m.element(0, 0) = 1;
	m.element(0, 1) = 2;
	m.wolny(0) = 3;
	m.element(1, 0) = 4;
	m.element(1, 1) = 6;
	m.wolny(1) = 7;
}

void demo4I(Macierz<int, double>& m) {
	m.element(0, 0) = 2;
	m.element(0, 1) = 2;
	m.element(0, 2) = 3;
	m.element(0, 3) = 3;
	m.wolny(0) = 4;
	m.element(1, 0) = 1;
	m.element(1, 1) = 5;
	m.element(1, 2) = -3;
	m.element(1, 2) = -2;
	m.wolny(1) = -5;
	m.element(2, 0) = 1;
	m.element(2, 1) = 4;
	m.element(2, 2) = 1;
	m.element(2, 3) = 0;
	m.wolny(2) = 2;
	m.element(3, 0) = 1;
	m.element(3, 1) = 0;
	m.element(3, 2) = 2;
	m.element(3, 2) = -1;
	m.wolny(3) = -1;
}

void demo2Ik0(Macierz<int, double>& m)
{
	m.element(0, 0) = 1;
	m.element(0, 1) = 1;
	m.element(0, 2) = 0;
	m.wolny(0) = 1;
	m.element(1, 0) = 1;
	m.element(1, 1) = 2;
	m.element(1, 2) = 0;
	m.wolny(1) = 2;
	m.element(2, 0) = 1;
	m.element(2, 1) = 0;
	m.element(2, 2) = 0;
	m.wolny(2) = 0;
}

void demo2Is(Macierz<int, double>& m)
{
	m.element(0, 0) = 1;
	m.element(0, 1) = 2;
	m.wolny(0) = 7;
	m.element(1, 0) = 2;
	m.element(1, 1) = 4;
	m.wolny(1) = 15;
}

void demo2It(Macierz<int, double>& m)
{
	m.element(0, 0) = 1;
	m.element(0, 1) = 2;
	m.wolny(0) = 7;
	m.element(1, 0) = 2;
	m.element(1, 1) = 4;
	m.wolny(1) = 14;
}

/*
void zaladujPrzykladoweMacierze(Macierz<int, double>** macierze)
{
	macierze = new Macierz<int, double>*[5];
	macierze[0] = new Macierz<int, double>(2);
	macierze[1] = new Macierz<int, double>(4);
	macierze[2] = new Macierz<int, double>(2);
	macierze[3] = new Macierz<int, double>(2);
	macierze[4] = new Macierz<int, double>(2);
	macierze[0]->element(0, 0) = 1;
	macierze[0]->element(0, 1) = 2;
	macierze[0]->wolny(0) = 3;
	macierze[0]->element(1, 0) = 4;
	macierze[0]->element(1, 1) = 6;
	macierze[0]->wolny(1) = 7;
	macierze[1]->element(0, 0) = 2;
	macierze[1]->element(0, 1) = 2;
	macierze[1]->element(0, 2) = 3;
	macierze[1]->element(0, 3) = 3;
	macierze[1]->wolny(0) = 4;
	macierze[1]->element(1, 0) = 1;
	macierze[1]->element(1, 1) = 5;
	macierze[1]->element(1, 2) = -3;
	macierze[1]->element(1, 2) = -2;
	macierze[1]->wolny(1) = -5;
	macierze[1]->element(2, 0) = 1;
	macierze[1]->element(2, 1) = 4;
	macierze[1]->element(2, 2) = 1;
	macierze[1]->element(2, 3) = 0;
	macierze[1]->wolny(2) = 2;
	macierze[1]->element(3, 0) = 1;
	macierze[1]->element(3, 1) = 0;
	macierze[1]->element(3, 2) = 2;
	macierze[1]->element(3, 2) = -1;
	macierze[1]->wolny(3) = -1;
	macierze[2]->element(0, 0) = 1;
	macierze[2]->element(0, 1) = 0;
	macierze[2]->wolny(0) = 3;
	macierze[2]->element(1, 0) = 4;
	macierze[2]->element(1, 1) = 0;
	macierze[2]->wolny(1) = 7;
	macierze[3]->element(0, 0) = 1;
	macierze[2]->element(0, 1) = 2;
	macierze[2]->wolny(0) = 7;
	macierze[2]->element(1, 0) = 1;
	macierze[2]->element(1, 1) = 3;
	macierze[2]->wolny(1) = 7;
	macierze[3]->element(0, 0) = 1;
	macierze[3]->element(0, 1) = 2;
	macierze[3]->wolny(0) = 7;
	macierze[3]->element(1, 0) = 2;
	macierze[3]->element(1, 1) = 4;
	macierze[3]->wolny(1) = 14;
}
*/

void demoInt()
{
	cout << "Rozwiazywanie macierzy 2x2 typu Int" << endl;
	try
	{
		Macierz<int, double> m2(2);
		demo2I(m2);
		m2.pokaz();
		cout << endl;
		Solver<int, double> s1(m2);
		s1.rozwiaz();
		m2.pokaz();
	}
	catch (Blad& wyjatek)
	{
		cout << wyjatek.what();
	}
	system("pause");
	system("cls");

	cout << "Rozwiazywanie macierzy 4x4 typu Int" << endl;
	try
	{
		Macierz<int, double> m4(4);
		demo4I(m4);
		m4.pokaz();
		cout << endl;
		Solver<int, double> s2(m4);
		s2.rozwiaz();
		m4.pokaz();
	}
	catch (Blad& wyjatek)
	{
		cout << wyjatek.what();
	}
	system("pause");
	system("cls");
	/*
	cout << "Rozpoznanie bledu w macierzy - kolumna sklada sie z zer" << endl;
	try
	{
		Macierz<int, double> m2k0(3);
		demo2Ik0(m2k0);
		m2k0.pokaz();
		cout << endl;
		Solver<int, double> sk0(m2k0);
		sk0.rozwiaz();
		m2k0.pokaz();
	}
	catch (Blad& wyjatek)
	{
		cout << wyjatek.what();
	}
	system("pause");
	system("cls");
	*/
	cout << "Rozpoznanie bledu w macierzy - uklad sprzeczny" << endl;
	try
	{
		Macierz<int, double> m2s(2);
		demo2Is(m2s);
		m2s.pokaz();
		cout << endl;
		Solver<int, double> ss(m2s);
		ss.rozwiaz();
		m2s.pokaz();
	}
	catch (Blad& wyjatek)
	{
		cout << wyjatek.what();
	}
	system("pause");
	system("cls");

	cout << "Rozpoznanie bledu w macierzy - uklad tozsamosciowy" << endl;
	try
	{
		Macierz<int, double> m2t(2);
		demo2It(m2t);
		m2t.pokaz();
		cout << endl;
		Solver<int, double> st(m2t);
		st.rozwiaz();
		m2t.pokaz();
	}
	catch (Blad& wyjatek)
	{
		cout << wyjatek.what();
	}
	system("pause");
	system("cls");
	
}

int main() 
{
	Koordynator koordynator;
	demoInt();
	koordynator.prezentacja();
	return 0;
}
