
#include <vector>
#include <queue>
#include <ctime>
#include <algorithm>
#include <iostream>
#include "Graf.h"
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

Graf::Graf(int Wierzcholki, int Krawedzie, int Start)
{
	this->Wierzcholki = Wierzcholki;
	this->Krawedzie = Krawedzie;
	this->Start = Start;
	MacierzGrafu = new int*[Wierzcholki];
	for (int i = 0; i < Wierzcholki; i++)
		MacierzGrafu[i] = new int[Wierzcholki];
	for (int i = 0; i < Wierzcholki; i++)
		for (int j = 0; j < Wierzcholki; j++)
			MacierzGrafu[i][j] = 0;

	Lista = new Element*[Wierzcholki];

	for (int i = 0; i < Wierzcholki; i++)
		Lista[i] = NULL;



}




int Graf::Minimum(dane* tab) {
	int min = -1;
	int mindist = INT_MAX;
	for (int i = 0; i < Wierzcholki; i++) {
		if (!tab[i].odwiedzony && tab[i].dystans < mindist) {
			min = i;
			mindist = tab[i].dystans;
		}
	}
	return min;
}

dane* Graf::Dijkstra_Lista() {

	dane* tab = new dane[Wierzcholki];
	droga = new int[Wierzcholki];
	Element *pomocniczy;
	for (int i = 0; i < Wierzcholki; i++) {
		if (i == Start)
		{
			tab[i].dystans = 0;
		}
		else
		{
			tab[i].dystans = INT_MAX;
		}
		tab[i].odwiedzony = false;
		droga[i] = -1;
	}

	int min = Minimum(tab);

	while (min != -1) {
		tab[min].odwiedzony = true;
		pomocniczy = Lista[min];
		
		for (pomocniczy = Lista[min]; pomocniczy; pomocniczy = pomocniczy->nastepny)
		{
			if (tab[min].dystans + pomocniczy->waga < tab[pomocniczy->wezel].dystans) {
				tab[pomocniczy->wezel].dystans = tab[min].dystans + pomocniczy->waga;
				droga[pomocniczy->wezel] = min;
			}
			
		}
		cout << endl;
		min = Minimum(tab);

	}
	return tab;
}




dane* Graf::Dijkstra() {

	dane* tab = new dane[Wierzcholki];
	droga = new int[Wierzcholki];
	for (int i = 0; i < Wierzcholki; i++) {
		if (i == Start)
		{
			tab[i].dystans = 0;
		}
		else
		{
			tab[i].dystans = INT_MAX;
		}
		tab[i].odwiedzony = false;
		droga[i] = -1;
	}

	int min = Minimum(tab);
	while (min != -1) {
		tab[min].odwiedzony = true;
		for (int i = 0; i < Wierzcholki; i++) {
			if (MacierzGrafu[min][i] > 0 && tab[min].dystans + MacierzGrafu[min][i] < tab[i].dystans) {
				tab[i].dystans = tab[min].dystans + MacierzGrafu[min][i];
				droga[i] = min;
			}
		}
		cout << endl;
		min = Minimum(tab);
	}

	return tab;
}

int Graf::dodaj_krawedz(int i, int j, int waga)
{
	
	element = new Element;
	element->wezel = j;
	element->waga = waga;
	element->nastepny = Lista[i];
	Lista[i] = element;

	return MacierzGrafu[i][j] = waga;

	

}


void Graf::wyswietl()
{
	for (int i = 0; i < Wierzcholki; i++)
	{
		for (int j = 0; j < Wierzcholki; j++)
		{
			std::cout << MacierzGrafu[i][j] << "\t";
		}
		std::cout << endl;
	}
}

void Graf::wyswietl_liste()
{
	Element *tmp;
	for (int i = 0; i < Wierzcholki; i++)
	{
		tmp = Lista[i];
		cout << i << ":";
		while (tmp)
		{
			cout << tmp->wezel << " waga :" << tmp->waga<<" ";
			tmp = tmp->nastepny;
		}
		cout << endl;
	}
}

void Graf::zapisz( dane *tab) {
	int licznik = 0;
	int *Tab_drogi = new int[Wierzcholki];       
	ofstream plik;
	plik.open("Wyniki.txt");
	for (int i = 0; i < Wierzcholki; i++)
	{
		plik << i << ":" ;
		for (int j = i; j > -1; j = droga[j])
			Tab_drogi[licznik++] = j;
		while (licznik)
		plik << Tab_drogi[--licznik] << "->";
		plik << "( "<< tab[i].dystans << ") " << endl;
	}
	plik.close();
}


Graf::~Graf()
{
}


void Wczytaj(Graf *&_Graf)
{
	int Krawedzie;
	int Wierzcholki;
	int Start;
	int wierz_poccz;
	int wierz_kon;
	int waga;
	string nazwa_pliku;
	int warosc;
	ifstream plik;
	printf("podaj nazwe pliku \n");
	cin >> nazwa_pliku;


	plik.open(nazwa_pliku.c_str());

	if (plik.good())
	{
		plik >> Krawedzie;
		plik >> Wierzcholki;
		plik >> Start;
		_Graf = new Graf(Wierzcholki, Krawedzie, Start);
		while (!plik.eof())
		{
			plik >> wierz_poccz;
			plik >> wierz_kon;
			plik >> waga;

			_Graf->dodaj_krawedz(wierz_poccz, wierz_kon, waga);
		}

	}
	else
	{
		printf("zla nazwa pliku \n");
	}
	plik.close();


}

void generuj()
{
	int Krawedzie;
	int Wierzcholki;
	int Start;
	int licznik = 0;
	double gestosc;
	string nazwa_pliku;
	ofstream plik;
	int waga;
	printf("podaj nazwe pliku \n");
	cin >> nazwa_pliku;

	plik.open(nazwa_pliku.c_str());
	printf("podaj liczbe wierzcholkow , gestosc (0-1) np 0.2, wierzcholek startowy \n");
	cin >> Wierzcholki >> gestosc >> Start;
	Krawedzie = ((Wierzcholki*(Wierzcholki - 1)) / 2)*gestosc;

	plik << Krawedzie << " " << Wierzcholki << " " << Start << endl;

	for (int i = 0; i < Wierzcholki; i++)
		for (int j = i; j < Wierzcholki; j++)
		{

			if (i != j && licznik < Krawedzie)
			{
				waga = rand() % 50 + 1;
				plik << i << " " << j << " " << waga << endl;
				plik << j << " " << i << " " << waga << endl;
				licznik++;
			}
		}

	plik.close();

}