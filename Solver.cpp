/*#include "Solver.h"

void Solver::skalujWiersz(int ktory, double skala) {
  // mnozy kazdy element wiersza przez skalar
  for (int i = 0; i < n; ++i) {
   mat.element(ktory, i) *= skala;
  }
  mat.wolny(ktory) *= skala;
}

void Solver::addWiersze(int ktory, int do_ktorego, double skala) {
  // dodaje pierwszy rzad do drugiego, mnozac wczesniej jego wartosci przez skalar
  for (int i = 0; i < n; ++i) {
    mat.element(do_ktorego, i) += skala * mat.element(ktory, i);
  }
  mat.wolny(do_ktorego) += skala * mat.wolny(ktory);
}

void Solver::zamienWiersze(int ktory, int zKtorym)
{
	double* tymczasowyWiersz = new double[n]; // TEMPLATE double->T1
	double tymczasowyWyrazWolny;
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

void Solver::rozwiaz() {
  // rozwiazuj kazda kolumne z osobna
  for (int i = 0; i < n; ++i) {
    // znormalizuj dany wiersz (na diagonalnej musza byc same 1)
    double pierwszy = mat.element(i, i);
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
		if ((czyWyzerowany) && (mat.wolny(i) == 0)) throw Blad("Uklad tozsamosciowy");
		else if ((czyWyzerowany) && (mat.wolny(i) != 0)) throw Blad("Uklad sprzeczny");
		bool czyZamieniono = false;
		for (int j = 0; j < n; ++j) {
			if (mat.element(j, i) != 0)
			{
				zamienWiersze(i, j);
				pierwszy = mat.element(i, i);
				czyZamieniono = true;
				break;
			}
		}
		if (czyZamieniono == false) throw Blad("Kolumna sklada sie z samych zer");
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
}*/
