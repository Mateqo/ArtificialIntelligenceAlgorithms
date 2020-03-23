
#include <iostream>
using namespace std;
template <class typ>

class Scalenie
{
public:

	Scalenie()
	{
	}
	Scalenie(int n, typ *t)
	{
		this->n = n;
		tablica = t;
		pomocnicza = new typ[n];
	}

	void scalanie(int i_podzb_1, int i_podzb_2, int i_podzb_2_koniec)
	{
		int i, i1, i2;
		i = i1 = i_podzb_1;
		i2 = i_podzb_2;
		for (;i <= i_podzb_2_koniec; i++)
		{
			if (i1 == i_podzb_2)
			{
				pomocnicza[i] = tablica[i2];
				i2++;
			}
			else if (i2 > i_podzb_2_koniec)
			{
				pomocnicza[i] = tablica[i1];
				i1++;
			}
			else if (tablica[i1] > tablica[i2])
			{
				pomocnicza[i] = tablica[i2];
				i2++;
			}
			else
			{
				pomocnicza[i] = tablica[i1];
				i1++;
			}
		}
		for (i = i_podzb_1;i <= i_podzb_2_koniec; i++)
		{
			tablica[i] = pomocnicza[i];
		}
	}


	void sortuj(int i_podzb_1, int i_podzb_2_koniec)
	{
		int i_podzb_2 = (i_podzb_1 + i_podzb_2_koniec + 1) / 2;
		if (i_podzb_2 - i_podzb_1 > 1)
		{
			sortuj(i_podzb_1, i_podzb_2 - 1);
		}
		if (i_podzb_2_koniec - i_podzb_2 > 0)
		{
			sortuj(i_podzb_2, i_podzb_2_koniec);
		}
		scalanie(i_podzb_1, i_podzb_2, i_podzb_2_koniec);

	}
	void wyswietl()
	{
		for (int i = 0;i < n;i++)
		{
			cout << tablica[i] << endl;
		}
	}
	~Scalenie()
	{


	}



private:
	typ *tablica;
	typ *pomocnicza;
	int n;
};

