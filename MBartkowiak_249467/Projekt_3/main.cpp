#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#define ROZMIAR 60
using namespace std;

string **plansza_;
int rx,ry;
bool czl=true;
int star_max;





void plansza(sf::RenderWindow &okno)
{
    sf::Font font;
    font.loadFromFile("A_Font_with_Serifs.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(ROZMIAR);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Red);

    for(int i = 0; i < rx; i++)
        for(int j = 0; j < ry; j++)
        {
            text.setString(plansza_[i][j]);
            text.setPosition((ROZMIAR)*i,(ROZMIAR)*j);

            okno.draw(text);
        }





}

void czlowiek( sf::RenderWindow &okno)
{

    int x = sf::Mouse::getPosition(okno).x/ROZMIAR;
    int y = sf::Mouse::getPosition(okno).y/ROZMIAR;

if(x>=0 && x<rx &&y>=0 && y<ry )
        if(plansza_[x][y]==" ")
        {
            plansza_[x][y]="O";
            czl=false;
        }



}

bool wygrana(string gracz)
{
    int re=0;
    for(int i = 0; i < rx; i++)
    {
        re=0;
        for(int j = 0; j < ry; j++)
        {
            if(plansza_[i][j] == gracz)
            {
                re++;
                if(re==3)
                {
                    return true;
                }
            }
            else
            {
                re=0;
            }

        }
    }

    for(int i = 0; i < ry; i++)
    {
        re=0;
        for(int j = 0; j < rx; j++)
        {
            if(plansza_[j][i] == gracz)
            {
                re++;
                if(re==3)
                {
                    return true;
                }
            }
            else
            {
                re=0;
            }

        }
    }



    return false;
}

void nowa_plansza()
{
    for(int i = 0; i < rx; i++)
        for(int j = 0; j < ry; j++)
            plansza_[i][j] = " ";
}

bool wolne()
{
    for(int i = 0; i < rx; i++)
        for(int j = 0; j < ry; j++)
            if(plansza_[i][j] == " ")
                return true;
    return false;
}

int minimax(string gracz, int poziom)
{
    int suma = 0;
    int x,y, wartosc,wartosc_maksymalna;



    for(int i = 0; i < rx; i++)
        for(int j = 0; j < ry; j++)
            if(plansza_[i][j] == " ")
            {
                plansza_[i][j] = gracz;
                x = i;
                y = j;
                suma++;

                bool test = wygrana(gracz);

                plansza_[i][j] = " ";
                if(test)
                {
                    if(!poziom)
                        plansza_[i][j] = gracz;
                    if(gracz == "X" )
                        return -1;
                    else
                        return 1;
                }
            }

    if(suma == 1)
    {
        if(!poziom)
            plansza_[x][y] = gracz;
        return 0;
    }

    if(gracz == "X" )
        wartosc_maksymalna= star_max;
    else
        wartosc_maksymalna= -star_max;

    for(int i = 0; i < rx; i++)
        for(int j = 0; j < ry; j++)
            if(plansza_[i][j] == " ")
            {
                plansza_[i][j] = gracz;

                if(gracz == "X")
                {
                    wartosc = minimax("O",poziom+1);
                }
                else
                {
                    wartosc = minimax("X",poziom+1);
                }

                plansza_[i][j] = " ";

                if(((gracz == "X") && (wartosc < wartosc_maksymalna)) || ((gracz == "o") && (wartosc > wartosc_maksymalna)))
                {
                    wartosc_maksymalna = wartosc;
                    x = i;
                    y = j;
                }
            }

    if(!poziom)
        plansza_[x][y] = gracz;

    return wartosc_maksymalna;
}



main()
{
srand(time(NULL));
    cin>>rx>>ry;
    if(rx*ry<=16)
        star_max=2;
    else
        star_max=2;
    plansza_=new string*[rx];
    for(int i=0; i<rx; i++)
        plansza_[i]=new string[ry];

    sf::RenderWindow okno( sf::VideoMode( ROZMIAR*rx, ROZMIAR*ry ), "OiX" );
    okno.setFramerateLimit(1);
    sf::RectangleShape line1,line2;


    nowa_plansza();
    plansza(okno);
double pierwszy=true;
    do
    {
        sf::Event event;
        while( okno.pollEvent( event ) )
        {
            if( event.type == sf::Event::Closed )
                okno.close();

        }
        while(czl)
        {
            okno.clear();
            czlowiek(okno);
            plansza(okno);
            sf::Event event;
            while( okno.pollEvent( event ) )
            {
                if( event.type == sf::Event::Closed )
                    okno.close();

            }

            for(int i=1; i<ry; i++)
            {
                line1.setSize(sf::Vector2f(ROZMIAR*ry, 1));
                line1.setOutlineColor(sf::Color::Red);
                line1.setPosition( 0, ROZMIAR*i );
                okno.draw(line1);

            }

            for(int i=1; i<rx; i++)
            {


                line2.setSize(sf::Vector2f(1, ROZMIAR*rx));
                line2.setOutlineColor(sf::Color::Red);
                line2.setPosition( ROZMIAR*i, 0 );
                 okno.draw(line2);
            }


            okno.display();
        }
        okno.clear();
        if(wygrana("O"))
            break;

        if(wolne())
        {

if(pierwszy){
        while(1)
        {

        int x=rand()%rx;
        int y=rand()%ry;
        if(plansza_[x][y]==" ")
        {


                plansza_[x][y]="X";
                break;
        }

        }
            pierwszy=false;
}
else
{


            minimax("X",0);
            plansza(okno);
            if(wygrana("X"))
                break;
}
        }
        else
            break;

        czl=true;
            for(int i=1; i<ry; i++)
            {
                line1.setSize(sf::Vector2f(ROZMIAR*ry, 1));
                line1.setOutlineColor(sf::Color::Red);
                line1.setPosition( 0, ROZMIAR*i );
                okno.draw(line1);

            }

            for(int i=1; i<rx; i++)
            {


                line2.setSize(sf::Vector2f(1, ROZMIAR*rx));
                line2.setOutlineColor(sf::Color::Red);
                line2.setPosition( ROZMIAR*i, 0 );
                 okno.draw(line2);
            }
        okno.display();
    }
    while(true);

    do
    {
        sf::Event event;
        while( okno.pollEvent( event ) )
        {
            if( event.type == sf::Event::Closed )
                okno.close();

        }
        okno.display();
    }
    while(true);



}
