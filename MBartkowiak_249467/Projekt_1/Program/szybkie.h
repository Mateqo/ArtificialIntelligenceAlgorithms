
#include <iostream>
using namespace std;
template <class typ>

class szybkie
{

public:
	szybkie()
	{

	}

	szybkie(int n, typ *tablica)
	{
		this->n = n;
		this->tablica = tablica;

	}

	~szybkie() {

		delete (tablica);
	};

	void sortuj(int lewy, int prawy)
	{
		typ piwot;
		int j, i = (lewy + prawy) / 2;
		piwot = tablica[i];
		tablica[i] = tablica[prawy];
		j = lewy;
		for (i = lewy;i < prawy;i++)
		{
			if (tablica[i] < piwot) // zmiana znaku, sortowanie w drug¹ stronê
			{
				swap(tablica[i], tablica[j]);
				j++;
			}
		}
		tablica[prawy] = tablica[j];
		tablica[j] = piwot;
		if (lewy < j - 1)
		{
			sortuj(lewy, j - 1);
		}
		if (j + 1 < prawy)
		{
			sortuj(j + 1, prawy);
		}



	}

	void wyswietl()
	{
		for (int i = 0;i < n;i++)
		{
			cout << tablica[i]<<endl;
		}
	}

private:
	typ *tablica;
	int n;
};



