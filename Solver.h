#pragma once
#include "Macierz.h"

template <typename T1, typename T2>
class Solver {
  Macierz<T1, T2>& mat;
  const int n;

  void skalujWiersz(int ktory, double skala);
  void addWiersze(int ktory, int do_ktorego, double skala = 1.0);
  void zamienWiersze(int ktory, int zKtorym);

 public:
  Solver(Macierz<T1, T2>& mat_) : mat(mat_), n(mat.getIleWierszy()) {}

  void rozwiaz();
};

template <typename T1, typename T2>
void Solver<T1, T2>::skalujWiersz(int ktory, double skala) {
	// mnozy kazdy element wiersza przez skalar
	for (int i = 0; i < n; ++i) {
		mat.element(ktory, i) *= skala;
	}
	mat.wolny(ktory) *= skala;
}

template <typename T1, typename T2>
void Solver<T1, T2>::addWiersze(int ktory, int do_ktorego, double skala) {
	// dodaje pierwszy rzad do drugiego, mnozac wczesniej jego wartosci przez skalar
	for (int i = 0; i < n; ++i) {
		mat.element(do_ktorego, i) += skala * mat.element(ktory, i);
	}
	mat.wolny(do_ktorego) += skala * mat.wolny(ktory);
}

template <typename T1, typename T2>
void Solver<T1, T2>::zamienWiersze(int ktory, int zKtorym)
{
	T1* tymczasowyWiersz = new T1[n];
	T2 tymczasowyWyrazWolny;
	for (int i = 0; i < n; i++)
	{
		tymczasowyWiersz[i] = mat.element(ktory, i);

	}
	tymczasowyWyrazWolny = mat.wolny(ktory);
	for (int i = 0; i < n; i++)
	{
		mat.element(ktory, i) = mat.element(zKtorym, i);
		mat.element(zKtorym, i) = tymczasowyWiersz[i];
	}
	mat.wolny(ktory) = mat.wolny(zKtorym);
	mat.wolny(zKtorym) = tymczasowyWyrazWolny;
	delete[] tymczasowyWiersz;
}

template <typename T1, typename T2>
void Solver<T1, T2>::rozwiaz() {
	try
	{
		// rozwiazuj kazda kolumne z osobna
		for (int i = 0; i < n; ++i) {
			// znormalizuj dany wiersz (na diagonalnej musza byc same 1)
			T1 pierwszy = mat.element(i, i);
			// zabezpieczenie przed dzieleniem przez zero - proba zamiany wierszy, jezeli sie nie powiedzie to wyjatek
			if (pierwszy == 0)
			{
				// dodatkowe sprawdzenie czy wiersz nie jest wyzerowany - tozsamosc lub sprzecznosc
				bool czyWyzerowany = true;
				for (int j = 0; j < n; j++)
				{
					if (mat.element(i, j) != 0)
					{
						czyWyzerowany = false;
						break;
					}
				}
				if ((czyWyzerowany) && (mat.wolny(i) == 0)) throw Blad("Uklad jest tozsamosciowy");
				else if ((czyWyzerowany) && (mat.wolny(i) != 0)) throw Blad("Uklad jest sprzeczny");
				//bool czyZamieniono = false;
				for (int j = 0; j < n; ++j) {
					if (mat.element(j, i) != 0)
					{
						zamienWiersze(i, j);
						pierwszy = mat.element(i, i);
						//czyZamieniono = true;
						break;
					}
				}
				//if (czyZamieniono == false) throw Blad("Kolumna sklada sie z samych zer", i + 1);
			}
			skalujWiersz(i, 1.0 / pierwszy);
			// uzyj i-tego wiersza do wyeliminowania wszystkich pozostalych
			for (int j = 0; j < n; ++j) {
				if (i == j) continue; // nie wyeliminuj siebie
				// przemnoz wiersz przez te wartosc, by wyeliminowac element na i-tym miejscu
				double skala = -1.0 * mat.element(j, i);
				addWiersze(i, j, skala);
			}
		}
	}
	catch (Blad& wyjatek)
	{
		/*if (wyjatek.getKolumna() > 0)
		{
			std::cout << "Kolumna nr " << wyjatek.getKolumna() << " sklada sie z samych zer. ";
			std::cout << "Zmienna nr " << wyjatek.getKolumna() << " nie moze zostac wyznaczona." << std::endl;
		}
		else
		{*/
			std::cout << wyjatek.what() << ". Nie mozna go rozwiazac." << std::endl;
		//}
	}
	
}

// specjalizacja na dane typu int

template <typename T2>
class Solver<int, T2>
{
	Macierz<int, T2>& mat;
	const int n;

	void skalujWiersz(int ktory, int skala, bool czyMnozenie);
	void addWiersze(int ktory, int do_ktorego, int skala, bool czyMnozenieSkala);
	void zamienWiersze(int ktory, int zKtorym);
	int NWD(int a, int b);
	int NWDWiersza(int ktory);
	void uprosc();

public:
	Solver(Macierz<int, T2>& mat_) : mat(mat_), n(mat.getIleWierszy()) {}

	void rozwiaz();
};

template <typename T2>
int Solver<int, T2>::NWD(int a, int b)
{
	int c;
	while (b != 0) {
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}

template <typename T2>
int Solver<int, T2>::NWDWiersza(int ktory)
{
	int nwd = mat.element(ktory, 0);
	for (int i = 1; i < n; i++)
	{
		nwd = NWD(nwd, mat.element(ktory, i));
	}
	return nwd;
}

template <typename T2>
void Solver<int, T2>::skalujWiersz(int ktory, int skala, bool czyMnozenie)
{
	if (czyMnozenie)
	{
		for (int i = 0; i < n; ++i) {
			mat.element(ktory, i) *= skala;
		}
		mat.wolny(ktory) *= skala;
	}
	else
	{
		for (int i = 0; i < n; ++i) {
			mat.element(ktory, i) /= skala;
		}
		mat.wolny(ktory) /= skala;
	}
	
}

template <typename T2>
void Solver<int, T2>::addWiersze(int ktory, int do_ktorego, int skala, bool czyMnozenieSkala)
{
	if (czyMnozenieSkala)
	{
		for (int i = 0; i < n; ++i) {
			mat.element(do_ktorego, i) += skala * mat.element(ktory, i);
		}
		mat.wolny(do_ktorego) += skala * mat.wolny(ktory);
	}
	else
	{
		for (int i = 0; i < n; ++i) {
			mat.element(do_ktorego, i) += mat.element(ktory, i) / skala;
		}
		mat.wolny(do_ktorego) += mat.wolny(ktory) / skala;
	}
}

template <typename T2>
void Solver<int, T2>::zamienWiersze(int ktory, int zKtorym)
{
	int* tymczasowyWiersz = new int[n];
	T2 tymczasowyWyrazWolny;
	for (int i = 0; i < n; i++)
	{
		tymczasowyWiersz[i] = mat.element(ktory, i);

	}
	tymczasowyWyrazWolny = mat.wolny(ktory);
	for (int i = 0; i < n; i++)
	{
		mat.element(ktory, i) = mat.element(zKtorym, i);
		mat.element(zKtorym, i) = tymczasowyWiersz[i];
	}
	mat.wolny(ktory) = mat.wolny(zKtorym);
	mat.wolny(zKtorym) = tymczasowyWyrazWolny;
	delete[] tymczasowyWiersz;
}

template <typename T2>
void Solver<int, T2>::rozwiaz()
{
	try
	{
		// rozwiazuj kazda kolumne z osobna
		for (int i = 0; i < n; ++i) {
			// znormalizuj dany wiersz (na diagonalnej musza byc same 1)
			int pierwszy = mat.element(i, i);
			// zabezpieczenie przed dzieleniem przez zero - proba zamiany wierszy, jezeli sie nie powiedzie to wyjatek
			if (pierwszy == 0)
			{
				// dodatkowe sprawdzenie czy wiersz nie jest wyzerowany - tozsamosc lub sprzecznosc
				bool czyWyzerowany = true;
				for (int j = 0; j < n; j++)
				{
					if (mat.element(i, j) != 0)
					{
						czyWyzerowany = false;
						break;
					}
				}
				if ((czyWyzerowany) && (mat.wolny(i) == 0)) throw Blad("Uklad jest tozsamosciowy");
				else if ((czyWyzerowany) && (mat.wolny(i) != 0)) throw Blad("Uklad jest sprzeczny");
				//bool czyZamieniono = false;
				for (int j = 0; j < n; ++j) {
					if (mat.element(j, i) != 0)
					{
						zamienWiersze(i, j);
						pierwszy = mat.element(i, i);
						//czyZamieniono = true;
						break;
					}
				}
				//if (czyZamieniono == false) throw Blad("Kolumna sklada sie z samych zer", i + 1);
			}
			//skalujWiersz(i, pierwszy, 0);
			// uzyj i-tego wiersza do wyeliminowania wszystkich pozostalych
			for (int j = 0; j < n; ++j) {
				if (i == j) continue; // nie wyeliminuj siebie
				// przemnoz wiersz przez te wartosc, by wyeliminowac element na i-tym miejscu
				if (mat.element(j, i) != 0)
				{
					skalujWiersz(i, mat.element(j, i), 1);
					skalujWiersz(j, pierwszy, 1);
					mat.pokaz();
					std::cout << std::endl;
					addWiersze(i, j, -1, 1);
					mat.pokaz();
					std::cout << std::endl;
					uprosc();
					mat.pokaz();
					std::cout << std::endl;
				}
				
			}
		}
		for (int i = 0; i < n; i++)
		{
			skalujWiersz(i, mat.element(i, i), 0);
		}
	}
	catch (Blad& wyjatek)
	{
		/*
		if (wyjatek.getKolumna() > 0)
		{
			std::cout << "Kolumna nr " << wyjatek.getKolumna() << " sklada sie z samych zer. ";
			std::cout << "Zmienna nr " << wyjatek.getKolumna() << " nie moze zostac wyznaczona." << std::endl;
		}
		else
		{*/
			std::cout << wyjatek.what() << ". Nie mozna go rozwiazac." << std::endl;
		//}
	}

}

template <typename T2>
void Solver<int, T2>::uprosc()
{
	for (int i = 0; i < n; i++)
	{
		int nwd = NWDWiersza(i);
		if(nwd != 0) skalujWiersz(i, nwd, 0);
	}
}
