#pragma once
#include "struktury.h"
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Graf
{

private:
	long long * d;
	int * p;
	int *droga;
	int **MacierzGrafu;
	Element *element;
	Element **Lista;
	int Wierzcholki;
	int Krawedzie; 
	int Start;
public:
	Graf() {};
	Graf(int Wierzcholki , int Krawedzie, int Start);
	~Graf();
	int dodaj_krawedz(int i, int j, int waga);
	void wyswietl();
	void wyswietl_liste();
	int Minimum(dane* tab);
	dane* Dijkstra();
	dane* Dijkstra_Lista();
	void zapisz( dane *tab);




	bool BF_L(int start)
	{
		int i, x;
		bool test;
		Element * pv;

		d[start] = 0;
		for (i = 1; i < Wierzcholki; i++)
		{
			test = true;
			for (x = 0; x < Wierzcholki; x++)
				for (pv = Lista[x]; pv; pv = pv->nastepny)
					if (d[pv->wezel] > d[x] + pv->waga)
					{
						test = false;
						d[pv->wezel] = d[x] + pv->waga;
						p[pv->wezel] = x;
					}
			if (test) return true;
		}

		for (x = 0; x < Wierzcholki; x++)
			for (pv = Lista[x]; pv; pv = pv->nastepny)
				if (d[pv->wezel] > d[x] + pv->waga)
					return false;

		return true;
	}


	bool BF(int start)
	{
		int i, x;
		bool test;

		d[start] = 0;
		for (i = 1; i < Wierzcholki; i++)
		{
			test = true;
			for (x = 0; x < Wierzcholki; x++)
				for (int j = 0; j < Wierzcholki; j++)
					if (d[j] > d[x] + MacierzGrafu[x][j] && MacierzGrafu[x][j] != 0)
					{
						test = false;
						d[j] = d[x] + MacierzGrafu[x][j];
						p[j] = x;
					}
			if (test) return true;
		}



		for (x = 0; x < Wierzcholki; x++)
			for (int j = 0; j < Wierzcholki; j++)
				if (d[j] > d[x] + MacierzGrafu[x][j] && MacierzGrafu[x][j] != 0) return false;

		return true;
	}

	void BellmanaForda_Lista() {

		int i, x, sptr, *S;
		bool czy_koniec;
		d = new long long[Wierzcholki];
		p = new int[Wierzcholki];
		for (i = 0; i < Wierzcholki; i++)
		{
			d[i] = INT_MAX;
			p[i] = -1;
		}

		czy_koniec = BF_L(Start);
		if (czy_koniec)
		{
			S = new int[Wierzcholki];
			sptr = 0;


			ofstream plik;
			plik.open("WynikiLista.txt");
			for (i = 0; i < Wierzcholki; i++)
			{
				plik << i << ": ";
				for (x = i; x != -1; x = p[x])
					S[sptr++] = x;

				while (sptr)
					plik << S[--sptr] << " ";

				plik << "koszt : " << d[i] << endl;
			}

			delete[] S;
		}
		else cout << "ujemna sciezka" << endl;
	}


	void BellmanaForda() {

		int i, x, sptr, *S;
		bool czy_koniec;
		d = new long long[Wierzcholki];
		p = new int[Wierzcholki];
		for (i = 0; i < Wierzcholki; i++)
		{
			d[i] = INT_MAX;
			p[i] = -1;
		}
		cout << endl;
		czy_koniec = BF(Start);

		if (czy_koniec)
		{
			S = new int[Wierzcholki];
			sptr = 0;


			ofstream plik;
			plik.open("WynikiTab.txt");
			for (i = 0; i < Wierzcholki; i++)
			{
				plik << i << ": ";
				for (x = i; x != -1; x = p[x])
					S[sptr++] = x;

				while (sptr)
					plik << S[--sptr] << " ";

				plik << "koszt : " << d[i] << endl;
			}

			delete[] S;
		}
		else cout << "ujemna sciezka" << endl;
	}

};




void Wczytaj(Graf *&_Graf);


void generuj();
