#include <iostream>
#include "Scalanie.h"
#include "szybkie.h"
#include "introsort.h"
#include <time.h>
#include <fstream>
using namespace std;

int main()
{
	fstream plik, plik_w;
	int n;
	int *tab;
	char opcja;
	clock_t start;
	while (1)
	{
		cout << "**********************" << endl;
		cout << "|  w-wczytaj         |" << endl;
		cout << "|  z-zapisz          |" << endl;
		cout << "|  M-przez scalanie  |" << endl;
		cout << "|  S-Szybkie         |" << endl;
		cout << "|  I-intro           |" << endl;
		cout << "|  P-Procentowo      |" << endl;
		cout << "**********************" << endl;
		cin >> opcja;
		switch (opcja)
		{
		case 'w':
		{
			plik.open("dane.txt", std::ios::in);
			plik >> n;
			tab = new int[n];

			for (int i = 0; i < n; i++)
				plik >> tab[i];
			plik.close();
		}
		break;
		case 'z':
		{
			plik.open("dane.txt", std::ios::out);
			cout << "ile danych wylosowac?" << endl;
			cin >> n;
			plik << n;
			for (int i = 0; i < n; i++)
				plik << rand() % 1000 - 600 << endl;
			plik.close();
		}
		break;

		case 'M':
		{
			int m;
			plik_w.open("wynik_scalanie.txt", std::ios::out);
			cout << "ile razy posortowac?" << endl;
			cin >> m;
			for (int i = 0; i < m; i++)
			{
				plik.open("dane.txt", std::ios::in);

				plik >> n;
				tab = new int[n];

				for (int i = 0; i < n; i++)
					plik >> tab[i];
				plik.close();

				Scalenie<int> sortowanie(n, tab);
				start = clock();
				sortowanie.sortuj(0, n - 1);
				plik_w << ((1000 * (clock() - start)) / CLOCKS_PER_SEC) << "\n";
				// wyœwietlenie sortowania
				//sortowanie.wyswietl(); 

			}
			plik_w.close();
		}
		break;
		case 'S':
		{
			int m;
			plik_w.open("wynik_szybkie.txt", std::ios::out);
			cout << "ile razy posortowac?" << endl;
			cin >> m;
			for (int i = 0; i < m; i++)
			{
				plik.open("dane.txt", std::ios::in);

				plik >> n;
				tab = new int[n];

				for (int i = 0; i < n; i++)
					plik >> tab[i];
				plik.close();
				szybkie<int> sortowanie(n, tab);
				start = clock();
				sortowanie.sortuj(0, n - 1);
				plik_w << ((1000 * (clock() - start)) / CLOCKS_PER_SEC) << "\n";
				// wyœwietlenie sortowania
				//sortowanie.wyswietl(); 
			}
			plik_w.close();
		}
		break;
		case 'I':
		{   plik_w.open("wynik_insert.txt", std::ios::out);
		int m;

		cout << "ile razy posortowac?" << endl;
		cin >> m;
		for (int i = 0; i < m; i++)
		{
			plik.open("dane.txt", std::ios::in);

			plik >> n;
			tab = new int[n];

			for (int i = 0; i < n; i++)
				plik >> tab[i];
			plik.close();
			intro<int> sortowanie(n, tab);
			start = clock();
			sortowanie.sortuj();
			plik_w << ((1000 * (clock() - start)) / CLOCKS_PER_SEC) << "\n";
            // wyœwietlenie sortowania
			//sortowanie.wypisz();
		}
		plik_w.close();
		}
		break;
		case 'P':
		{
			plik.open("dane.txt", std::ios::in);
			double procent;
			cout << "ile procent posortowac?" << endl;
			cin >> procent; 
			n = (procent/ 100.0)*n;
			tab = new int[n];

			for (int i = 0; i < n; i++)
				plik >> tab[i];
			plik.close();
			szybkie<int> sortowanie(n, tab);

			sortowanie.sortuj(0, n - 1);

		}
		break;

		}
	}

	return 0;
}
