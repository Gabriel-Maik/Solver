#include "Koordynator.h"

Koordynator::Koordynator()
	: macierzF(nullptr), macierzD(nullptr), /*macierzI(nullptr),*/ rodzajPliku(0), nrPliku(0), typ(0)
{
	zaladujNazwy();
}

Koordynator::~Koordynator()
{
	if (macierzF != nullptr) delete macierzF;
	if (macierzD != nullptr) delete macierzD;
	//if (macierzI != nullptr) delete macierzI;
}

void Koordynator::wyswietlPliki() const
{
	cout << "macierze " << endl;
	for (int j = 0; j < 4; j++) cout << j + 1 << ".\t" << macierze[j] << endl;
	cout << "rownania " << endl;
	for (int j = 0; j < 9; j++) cout << j + 1 << ".\t" << rownania[j] << endl;
	cout << "rownaniaPro " << endl;
	for (int j = 0; j < 2; j++) cout << j + 1 << ".\t" << rownaniaPro[j] << endl;
}

void Koordynator::zaladujNazwy()
{
	macierze[0] = "macierz_1.txt";
	macierze[1] = "macierz_2.txt";
	macierze[2] = "macierz_3.txt";
	macierze[3] = "macierz_5.txt";
	for (int i = 0; i < 9; i++)
	{
		std::string pomocniczy("uklad_");
		pomocniczy.append(std::to_string(i)).append(".txt");
		rownania[i] = pomocniczy;
	}
	rownaniaPro[0] = "pro_uklad_1.txt";
	rownaniaPro[1] = "pro_uklad_2.txt";
}

void Koordynator::wczytajMacierz(int ktora)
{
	if ((ktora > 3) || (ktora < 0)) throw Blad("Nieprawidlowy numer macierzy");
	plik.open(macierze[ktora], std::ifstream::in);
	if (plik.good() == 0) throw Blad(string("Nie odnaleziono pliku " + macierze[ktora]).c_str());
	std::string linia;
	std::getline(plik, linia);
	typ = linia[0];
	if (typ == 'F')
	{
		if (macierzF != nullptr) delete macierzF;
		ObslugaPlikow<float> wczytywarka(plik);
		macierzF = wczytywarka.wczytywanieMacierzyTypu();
		cout << "Wczytano " << macierze[ktora] << endl;
		macierzF->pokaz();
	}
	else if (typ == 'D')
	{
		if (macierzD != nullptr) delete macierzD;
		ObslugaPlikow<double> wczytywarka(plik);
		macierzD = wczytywarka.wczytywanieMacierzyTypu();
		cout << "Wczytano " << macierze[ktora] << endl;
		macierzD->pokaz();
	}
	plik.close();
}

void Koordynator::wczytajRownanie(int ktore)
{
	if ((ktore > 9) || (ktore < 0)) throw Blad("Nieprawidlowy numer rownania");
	plik.open(rownania[ktore], std::ifstream::in);
	if (plik.good() == 0) throw Blad(string("Nie odnaleziono pliku " + rownania[ktore]).c_str());
	std::string linia;
	std::getline(plik, linia);
	typ = linia[0];
	if (zmienne.size() > 0) zmienne.erase(zmienne.begin(), zmienne.end());
	if (typ == 'F')
	{
		if (macierzF != nullptr) delete macierzF;
		ObslugaPlikow<float> wczytywarka(plik);
		macierzF = wczytywarka.wczytywanieZUkladuMacierzyTypu(zmienne);
		cout << "Wczytano " << rownania[ktore] << endl;
		macierzF->pokaz();
	}
	else if (typ == 'D')
	{
		if (macierzD != nullptr) delete macierzD;
		ObslugaPlikow<double> wczytywarka(plik);
		macierzD = wczytywarka.wczytywanieZUkladuMacierzyTypu(zmienne);
		cout << "Wczytano " << rownania[ktore] << endl;
		macierzD->pokaz();
	}
	plik.close();
}

void Koordynator::wczytajRownaniePro(int ktore)
{
	if ((ktore > 1) || (ktore < 0)) throw Blad("Nieprawidlowy numer rownania pro");
	plik.open(rownaniaPro[ktore], std::ifstream::in);
	if (plik.good() == 0) throw Blad(string("Nie odnaleziono pliku " + rownaniaPro[ktore]).c_str());
	string linia;
	std::getline(plik, linia);
	std::stringstream s(linia);
	typ = linia[0];
	if (zmienne.size() > 0) zmienne.erase(zmienne.begin(), zmienne.end());
	wyznaczZmienne();
	plik.close();
	plik.open(rownaniaPro[ktore], std::ifstream::in);
	if (typ == 'F')
	{
		if (macierzF != nullptr) delete macierzF;
		ObslugaPlikow<float> wczytywarka(plik);
		macierzF = wczytywarka.wczytywanieZUkladuProMacierzyTypu(zmienne);
		cout << "Wczytano " << rownaniaPro[ktore] << endl;
		macierzF->pokaz();
	}
	else if (typ == 'D')
	{
		if (macierzD != nullptr) delete macierzD;
		ObslugaPlikow<double> wczytywarka(plik);
		macierzD = wczytywarka.wczytywanieZUkladuProMacierzyTypu(zmienne);
		cout << "Wczytano " << rownaniaPro[ktore] << endl;
		macierzD->pokaz();
	}
	plik.close();
}

void Koordynator::rozwiazMacierz() const
{
	if (typ == 'F')
	{
		Solver<float, float> rozwiazywacz(*macierzF);
		rozwiazywacz.rozwiaz();
		cout << "Po rozwiazaniu" << endl;
		macierzF->pokaz();
	}
	else if (typ == 'D')
	{
		Solver<double, double> rozwiazywacz(*macierzD);
		rozwiazywacz.rozwiaz();
		cout << "Po rozwiazaniu" << endl;
		macierzD->pokaz();
	}
}

void Koordynator::rozwiazRownanie() const
{
	if (typ == 'F')
	{
		Solver<float, float> analizator(*macierzF);
		analizator.rozwiaz();
		cout << "Po rozwiazaniu" << endl;
		macierzF->pokaz();
		cout << endl << "Wynik w postaci naturalnej" << endl;
		for (int w = 0; w < macierzF->getIleWierszy(); w++)
		{
			cout << zmienne[w] << " = " << macierzF->wolny(w) << endl;
		}
	}
	else if (typ == 'D')
	{
		Solver<double, double> analizator(*macierzD);
		analizator.rozwiaz();
		cout << "Po rozwiazaniu" << endl;
		macierzD->pokaz();
		cout << endl << "Wynik w postaci naturalnej" << endl;
		for (int w = 0; w < macierzD->getIleWierszy(); w++)
		{
			cout << zmienne[w] << " = " << macierzD->wolny(w) << endl;
		}
	}
}

void Koordynator::wyznaczZmienne()
{
	if (typ == 'F')
	{
		ObslugaPlikow<float> sprawdzacz(plik);
		sprawdzacz.wyznaczanieZmiennych(zmienne);
	}
	else if (typ == 'D')
	{
		ObslugaPlikow<double> sprawdzacz(plik);
		sprawdzacz.wyznaczanieZmiennych(zmienne);
	}
}

void Koordynator::prezentacja()
{
	system("cls");
	cout << "Baza plikow" << endl << endl;
	wyswietlPliki();
	cout << endl;
	system("pause");
	system("cls");
	cout << "Wczytywanie i rozwiazywanie macierzy" << endl;
	system("pause");
	for (int i = 0; i < 4; i++)
	{
		system("cls");
		try
		{
			wczytajMacierz(i);
			rozwiazMacierz();
		}
		catch (Blad& wyjatek)
		{
			cout << wyjatek.what();
		}
		cout << endl;
		system("pause");
		
	}
	system("cls");
	cout << "Wczytywanie i rozwiazywanie ukladow" << endl;
	system("pause");
	for (int i = 0; i < 9; i++)
	{
		system("cls");
		try
		{
			wczytajRownanie(i);
			rozwiazRownanie();
		}
		catch (Blad& wyjatek)
		{
			cout << wyjatek.what();
		}
		cout << endl;
		system("pause");
	}
	system("cls");
	cout << "Wczytywanie i rozwiazywanie ukladow pro" << endl;
	system("pause");
	for (int i = 0; i < 2; i++)
	{
		system("cls");
		try
		{
			wczytajRownaniePro(i);
			rozwiazRownanie();
		}
		catch (Blad& wyjatek)
		{
			cout << wyjatek.what();
		}
		cout << endl;
		system("pause");
	}
}