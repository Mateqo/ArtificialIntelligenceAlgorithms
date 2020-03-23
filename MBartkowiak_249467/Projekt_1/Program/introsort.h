#pragma once


#pragma once

#include <algorithm>
#include <cmath>

using namespace std;

template < class  typ >

class intro
{

public:
	intro()
	{

	}

	intro(int n, typ *tablica)
	{
		this->n = n;
		this->tablica = tablica;

	}


	void wypisz()
	{
		for (int i = 0; i < n; i++)
		{

			cout << tablica[i] << endl;

		}
	}



	void Nowa_tablica(int i)
	{
		n = i;
		tablica = new typ[i];
	}

	typ &operator [](int i)
	{
		return tablica[i];
	}

	int podzial(int lewy, int prawy)
	{
		typ pivot = tablica[prawy];
		typ temp;
		int i = lewy;
		for (int j = lewy; j < prawy; ++j)
		{
			if (tablica[j] <= pivot)
			{
				temp = tablica[j];
				tablica[j] = tablica[i];
				tablica[i] = temp;
				i++;
			}
		}

		tablica[prawy] = tablica[i];
		tablica[i] = pivot;

		return i;
	}

	void Wstawianie()
	{
		typ tmp;
		int i;
		for (int j = n - 2; j >= 0; j--)
		{
			tmp = tablica[j];
			i = j + 1;
			while ((i < n) && (tmp > tablica[i]))
			{
				tablica[i - 1] = tablica[i];
				i++;
			}
			tablica[i - 1] = tmp;
		}

	}



	void MaksKopcowanie(int rozmiar, int index)
	{
		int lewy = (index + 1) * 2 - 1;
		int prawy = (index + 1) * 2;
		int najwiekszy = 0;

		if (lewy < rozmiar && tablica[lewy] > tablica[index])
			najwiekszy = lewy;
		else
			najwiekszy = index;

		if (prawy < rozmiar && tablica[prawy] > tablica[najwiekszy])
			najwiekszy = prawy;

		if (najwiekszy != index)
		{
			typ temp = tablica[index];
			tablica[index] = tablica[najwiekszy];
			tablica[najwiekszy] = temp;

			MaksKopcowanie(rozmiar, najwiekszy);
		}
	}

	void Kopcowanie()
	{
		int rozmiar = n;

		for (int p = (rozmiar - 1) / 2; p >= 0; --p)
			MaksKopcowanie(rozmiar, p);

		for (int i = rozmiar - 1; i > 0; --i)
		{
			typ temp = tablica[i];
			tablica[i] = tablica[0];
			tablica[0] = temp;

			--rozmiar;
			MaksKopcowanie(rozmiar, 0);
		}
	}

	void szybkie(int lewy, int prawy)
	{
		if (prawy <= lewy) return;
		typ tmp, pivot;
		int i = lewy - 1;
		int j = prawy + 1;
		pivot = tablica[(lewy + prawy) / 2];

		while (1)
		{
			while (pivot > tablica[++i]);
			while (pivot < tablica[--j]);

			if (i <= j)
			{
				tmp = tablica[i];
				tablica[i] = tablica[j];
				tablica[j] = tmp;

			}
			else
				break;
		}

		if (j > lewy)
			szybkie(lewy, j);
		if (i < prawy)
			szybkie(i, prawy);

	}

	void sortuj()
	{
		int rozmiarPodzialu = podzial(0, n - 1);

		if (rozmiarPodzialu < 16)
		{
			Wstawianie();
		}
		else if (rozmiarPodzialu > (2 * log(n)))
		{
			Kopcowanie();
		}
		else
		{
			szybkie(0, n - 1);
		}
	}


	~intro()
	{
		delete tablica;

	}
private:
	typ *tablica;
	unsigned int n;

};
