#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;
struct kontakt
{
    string imie, nazwisko, email, adres, telefon;
};

int wczytanieKsiazki(kontakt ksiazkaVector[]);
bool czyTakiIstnieje(kontakt ksiazkaVector[], string email, int iloscKontaktow);
int zapisywanieKontaktu(kontakt ksiazkaVector[], kontakt dane, int iloscKontaktow);
void wyswietlanieKontaktu(kontakt dane);
void szukajImienia(kontakt ksiazkaVector[], string imie, int iloscKontaktow);
void szukajNazwiska(kontakt ksiazkaVector[], string nazwisko, int iloscKontaktow);

int main()
{
    int nrKontaktu=1, linia, iloscKontaktow=0, wyszukiwanie=0;
    char wybor;
    string dane;
    kontakt osoba;
    kontakt ksiazkaVector[1000];

    iloscKontaktow = wczytanieKsiazki(ksiazkaVector);

    while(1)
    {
        if(wyszukiwanie==0)
        {
            system("cls");
            cout<<"1. Wyswietl wszystkich."<<endl;
            cout<<"2. Zapisz kontakt."<<endl;
            cout<<"3. Wyszukaj kontakt."<<endl;
            cout<<"9. Zakoncz program"<<endl;
            cin>>wybor;

            if(wybor=='1')
            {
                while(wybor!='8')
                {
                    for(int i=0; i<iloscKontaktow; ++i)
                    {
                        wyswietlanieKontaktu(ksiazkaVector[i]);
                    }
                    cout<<"Aby zakonczyc wyswietlanie wybierz 8."<<endl;
                    cin>>wybor;
                }
            }
            else if(wybor=='2')
            {
                cout<<"Podaj email: ";
                cin>>dane;
                if(czyTakiIstnieje(ksiazkaVector, dane, iloscKontaktow))
                {
                    cout<<"Ten kontakt juz jest w ksiazce."<<endl;
                    Sleep(3000);
                }
                else
                {
                    osoba.email=dane;
                    cout<<"Podaj imie: ";
                    cin>>dane;
                    osoba.imie=dane;
                    cout<<"Podaj nazwisko: ";
                    cin>>dane;
                    osoba.nazwisko=dane;
                    cin.ignore();
                    cout<<"Podaj adres: ";
                    getline(cin,dane);
                    osoba.adres=dane;
                    cout<<"Podaj telefon: ";
                    getline(cin,dane);
                    osoba.telefon=dane;

                    iloscKontaktow = zapisywanieKontaktu(ksiazkaVector, osoba, iloscKontaktow);
                }
            }
            else if(wybor=='3')
            {
                wyszukiwanie=1;
            }
            else if(wybor=='9')
            {
                exit(0);
            }
        }
        else
        {
            system("cls");
            cout<<"1. Wyszukiwanie po imieniu"<<endl;
            cout<<"2. Wyszukiwanie po nazwisku"<<endl;
            cin>>wybor;

            if(wybor=='1')
            {
                while(wybor!='8')
                {
                    cout<<"Podaj imie: "<<endl;
                    cin>>dane;
                    szukajImienia(ksiazkaVector, dane, iloscKontaktow);

                    cout<<"Aby zakonczyc wyswietlanie wybierz 8."<<endl;
                    cin>>wybor;
                }
            }
            else if(wybor=='2')
            {
                while(wybor!='8')
                {
                    cout<<"Podaj nazwisko: "<<endl;
                    cin>>dane;
                    szukajNazwiska(ksiazkaVector, dane, iloscKontaktow);

                    cout<<"Aby zakonczyc wyswietlanie wybierz 8."<<endl;
                    cin>>wybor;
                }
            }
            wyszukiwanie=0;
        }
    }
    return 0;
}
int wczytanieKsiazki(kontakt ksiazkaVector[])
{
    string dane;
    kontakt temp;
    int i=1, id=0, j=0;
    fstream plik;

    plik.open("KsiazkaAdresowa.txt",ios::in);

    if(plik.good() == true)
    {
        while(getline(plik, dane))
        {
            switch(i)
            {
                case 1:
                    ksiazkaVector[j].imie = dane;
                    break;
                case 2:
                    ksiazkaVector[j].nazwisko = dane;
                    break;
                case 3:
                    ksiazkaVector[j].email = dane;
                    break;
                case 4:
                    ksiazkaVector[j].adres = dane;
                    break;
                case 5:
                    ksiazkaVector[j].telefon = dane;
                    break;
            }
            if(i>=5)
            {
                i=1;
                ++j;
            }
            else
            {
                ++i;
            }
        }

        plik.close();
        return j;
    }
}
bool czyTakiIstnieje(kontakt ksiazkaVector[], string email, int iloscKontaktow)
{
    for(int i=0; i<iloscKontaktow; ++i)
    {
        if(ksiazkaVector[i].email == email)
        {
            return 1;
        }
    }
    return 0;
}
int zapisywanieKontaktu(kontakt ksiazkaVector[], kontakt dane, int iloscKontaktow)
{
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);
    plik<<dane.imie<<endl;
    plik<<dane.nazwisko<<endl;
    plik<<dane.email<<endl;
    plik<<dane.adres<<endl;
    plik<<dane.telefon<<endl;
    plik.close();

    ksiazkaVector[iloscKontaktow].imie = dane.imie;
    ksiazkaVector[iloscKontaktow].nazwisko = dane.nazwisko;
    ksiazkaVector[iloscKontaktow].email = dane.email;
    ksiazkaVector[iloscKontaktow].adres = dane.adres;
    ksiazkaVector[iloscKontaktow].telefon = dane.telefon;

    return iloscKontaktow+1;
}
void wyswietlanieKontaktu(kontakt dane)
{
    cout<<dane.imie<<" "<<dane.nazwisko<<endl;
    cout<<dane.adres<<endl;
    cout<<dane.email<<endl;
    cout<<dane.telefon<<endl<<endl;
}
void szukajImienia(kontakt ksiazkaVector[], string imie, int iloscKontaktow)
{
    for(int i=0; i<iloscKontaktow; ++i)
    {
        if(ksiazkaVector[i].imie == imie)
        {
            wyswietlanieKontaktu(ksiazkaVector[i]);
        }
    }
}
void szukajNazwiska(kontakt ksiazkaVector[], string nazwisko, int iloscKontaktow)
{
    for(int i=0; i<iloscKontaktow; ++i)
    {
        if(ksiazkaVector[i].nazwisko == nazwisko)
        {
            wyswietlanieKontaktu(ksiazkaVector[i]);
        }
    }
}
