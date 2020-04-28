
#include "Interfejs.h"
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;



void menu()
{
	double czas, stop, start;
	char opcja;
	Graf *_Graf = NULL;
	fstream plik;
	plik.open("wyniki_casu.txt", ios_base::app);
	while (1)
	{
		cout << "W- Graf" << endl;
		cout << "O - Wczytaj" << endl;
		cout << "G - Generuj" << endl;
		cout << "D - Dijkstra macierz" << endl;
		cout << "L - Dijkstra lista" << endl;
		cout << "F - BellmanaForda lista" << endl;
		cout << "H - BellmanaForda macierz" << endl;
		cout << "K - Aby zakonczyc" << endl;

		cout << "podaj opcje" << endl;

		cin >> opcja;

		switch (opcja)
		{
		case 'K':
			return;
		case 'W':
			cout << "Macierz:" << endl;
			_Graf->wyswietl();

			cout << endl << "Lista:" << endl;
			_Graf->wyswietl_liste();
			break;
		case 'G':
			generuj();
			break;
		case 'O':
			Wczytaj(_Graf);
			break;
		case 'D':
		{
			start = clock();
			dane* tab = _Graf->Dijkstra();
			stop = clock();
			_Graf->zapisz(tab);
			czas = (double)(stop - start) / CLOCKS_PER_SEC;
			plik << "D tablica : " << czas;
		}
		break;
		case 'L':
		{
			start = clock();
			dane* tab = _Graf->Dijkstra_Lista();
			stop = clock();
			_Graf->zapisz(tab);
			czas = (double)(stop - start) / CLOCKS_PER_SEC;
			plik << "D lista : " << czas;
		}
		break;
		case 'F':
		{
			start = clock();
			_Graf->BellmanaForda_Lista();
			stop = clock();
			czas = (double)(stop - start) / CLOCKS_PER_SEC;
			plik << "BF Lista : " << czas;
		}
		break;
		case 'H':
		{
			start = clock();
			_Graf->BellmanaForda();
			stop = clock();
			czas = (double)(stop - start) / CLOCKS_PER_SEC;
			plik << "BF tablica : " << czas;
		}
		break;
		}
		
	}plik.close();
}
