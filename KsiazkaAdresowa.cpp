#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <cstdio>
#include <fstream>
#include <string> 
using namespace std;

struct Adresat 
{
int id;
string imie, nazwisko, nrTelefonu, email, adres;
};

string wczytajLinie()
{
  string wejscie = "";
  getline(cin, wejscie);
  return wejscie;
}

char wczytajZnak() 
{
  string wejscie = "";
  char znak = {0};
  while (true)
  {
    getline(cin, wejscie);
    if (wejscie.length() == 1)
    {
      znak = wejscie[0];
      break;
    }
    cout << "To nie jest pojedynczy znak. Wpisz ponownie" << endl;
  }
  return znak;
}

void wyswietlKontakt(Adresat adresat)
{
    cout << adresat.id << endl;
    cout << adresat.imie << endl;
    cout << adresat.nazwisko << endl;
    cout << adresat.nrTelefonu << endl;
    cout << adresat.email << endl;
    cout << adresat.adres << endl;
}

void zapisanieKsiazkiDoPliku(const vector <Adresat> &adresaci)
{
    fstream plik;
    plik.open("Ksiazka_adresowa.txt", ios::out);
    if (plik.good() == false) // sprawdzanie czy plik istnieje
    {
        cout << "Plik z Twoją książką adresową nie istnieje!" << endl;
        system("read"); // dla Linux i Mac
    }  
    else //if (plik.good() == true)
    {
        for (int i = 0; i < adresaci.size(); ++i)
        {
        plik << adresaci[i].id << "|";
        plik << adresaci[i].imie << "|";
        plik << adresaci[i].nazwisko << "|";
        plik << adresaci[i].nrTelefonu << "|";
        plik << adresaci[i].email << "|";
        plik << adresaci[i].adres << "|" << endl;
        }
    plik.close();
  }
}

int dodanieOsobyDoKsiazkiAdresowej(vector <Adresat> &adresaci, int idOstatniejOsoby)
{
  Adresat adresat;
  string imie, nazwisko, nrTelefonu, email, adres;

  cout << "Podaj imię: "; 
  adresat.imie = wczytajLinie();
  cout << "Podaj nazwisko: "; 
  adresat.nazwisko = wczytajLinie();
  cout << "Podaj nr telefonu: "; 
  adresat.nrTelefonu = wczytajLinie();
  cout << "Podaj adres email: "; 
  adresat.email = wczytajLinie();
  cout << "Podaj adres: "; 
  adresat.adres = wczytajLinie();
  adresat.id = idOstatniejOsoby + 1;

  adresaci.push_back(adresat);

  zapisanieKsiazkiDoPliku(adresaci);
  
  cout << "Dodano do ksiazki adresowej" << endl;
  system("read");
  return (idOstatniejOsoby + 1);
}

void wczytywanieZnajomychDoStruktury(vector <Adresat> &adresaci, const string& nazwaPliku)
{
  Adresat adresat;
  string liniaZDanymi = "";
  string pojedynczaDanaAdresata = "";
  int numerPojedynczejDanejAdresata = 1;
  
  fstream plik;

  plik.open(nazwaPliku, ios::in | ios::app);
  if(plik.good() == true)
  {
    while (getline (plik, liniaZDanymi)) 
    {
        for (int pozycjaZnaku = 0; pozycjaZnaku < liniaZDanymi.length(); pozycjaZnaku++)
        {
            if (liniaZDanymi[pozycjaZnaku] != '|')
            {
                pojedynczaDanaAdresata += liniaZDanymi[pozycjaZnaku];
            }
            else
            {
                switch (numerPojedynczejDanejAdresata)
                {
                case 1:
                    adresat.id = atoi(pojedynczaDanaAdresata.c_str()); //stoi(linia) nie działa
                    break;
                case 2:
                    adresat.imie = pojedynczaDanaAdresata;
                    break;
                case 3:
                    adresat.nazwisko = pojedynczaDanaAdresata;
                    break;
                case 4:
                    adresat.nrTelefonu = pojedynczaDanaAdresata;
                    break;
                case 5:
                    adresat.email = pojedynczaDanaAdresata;
                    break;
                case 6:
                    adresat.adres = pojedynczaDanaAdresata;
                    break;
                }
                pojedynczaDanaAdresata = "";
                numerPojedynczejDanejAdresata++;
            }
        }
    adresaci.push_back(adresat);
    }
    plik.close();
  }
}

void wyszukajOsobe(vector <Adresat> &adresaci)
{
    int idOsoby = 0;
    string imie, nazwisko;
    char wybor;

    system("cls");
      cout << "Wyszukiwanie osob" << endl << endl;
      cout << "1. Wyszukiwanie osób po imieniu" << endl;
      cout << "2. Wyszukiwanie osób po nazwisku" << endl << endl;
      cout << "Wybierz numer i wciśnij ENTER" << endl;
      cin >> wybor;
    if (wybor == '1')
    {
        system ("cls");
        cout << "Podaj imię: ";
        cin >> imie;

        for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr -> imie == imie)
            {
                cout << "Znalazlem osobę o imieniu " << imie << endl;
                sleep(1);
                cout << "Oto dane z ksiazki adresowej: " << endl;
                wyswietlKontakt(*itr);
                
                system("read");
                
                idOsoby = itr -> id;
            }
            if (itr == adresaci.end())
            {
                break;
            }
        }
        
        if (idOsoby == 0)
        {
          cout << "Nie ma osoby o takim imieniu" << endl;
          system("read");
        }
        
    }

    else if (wybor == '2')
    {
        system ("cls");
        cout << "Podaj nazwisko: ";
        cin >> nazwisko;
        
        for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr -> nazwisko == nazwisko)
            {
                cout << "Znalazlem osobę o nazwisku " << nazwisko << endl;
                sleep(1);
                cout << "Oto dane z ksiazki adresowej: " << endl;
                wyswietlKontakt(*itr);
                
                system("read");
                
                idOsoby = itr -> id;
            }
            if (itr == adresaci.end())
            {
                break;
            }
        }
        if (idOsoby == 0)
        {
          cout << "Nie ma osoby o takim nazwisku" << endl;
          system("read");
        }
    }
}

void wyswietlKsiazkeAdresowa(const vector <Adresat> &adresaci)
{
  system ("cls");

  if (adresaci.empty()) 
    {
        cout << "Brak znajomych w ksiazce adresowej." << endl;
        system("read");
        return;
    }
    cout << "Ksiazka adresowa:" << endl;
    for (int i = 0; i < adresaci.size(); ++i) 
    {
        cout << adresaci[i].id << endl;
        cout << "Imie: " << adresaci[i].imie << endl;
        cout << "Nazwisko: " << adresaci[i].nazwisko << endl;
        cout << "Numer telefonu: " << adresaci[i].nrTelefonu << endl;
        cout << "Email: " << adresaci[i].email << endl;
        cout << "Adres: " << adresaci[i].adres << endl << endl;    
    }
  system("read");
}

void usunAdresataOPodanymId(vector <Adresat> &adresaci)
{
    int id;
    cout << "Podaj ID adresata, ktory ma zostac usuniety: ";
    cin >> id;
    for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr -> id == id)
        {
            adresaci.erase(itr);
        }
        if (itr == adresaci.end())
        {
            break;
        }
    }
    zapisanieKsiazkiDoPliku(adresaci);
    cout << "Adresat zostal usuniety. Nacisnij dowolny klawisz.";
    system("read");
}

void edytujAdresata(vector <Adresat> &adresaci)
{
    int id;
    char wybor;
    cout << "Podaj ID adresata, ktory ma zostac edytowany: ";
    cin >> id;

        system("cls");
        cout << "Edycja wybranego adresata. Wybierz co edytowac:" << endl << endl;
        cout << "1. Imie." << endl;
        cout << "2. Nazwisko" << endl;
        cout << "3. Numer telefonu" << endl;
        cout << "4. Email" << endl;
        cout << "5. Adres" << endl;
        cout << "9. Powrot do menu" << endl << endl;
        cout << "Wybierz numer i wciśnij ENTER" << endl;
      
        wybor = wczytajZnak();

            switch (wybor)
            {
            case '1':
                cout << "Podaj nowe imie: ";
                cin >> adresaci[id - 1].imie;
                break;
            case '2':
                cout << "Podaj nowe nazwisko: ";
                cin >> adresaci[id - 1].nazwisko;
                break;
            case '3':
                cout << "Podaj nowy numer telefonu: ";
                cin >> adresaci[id - 1].nrTelefonu;
                break;
            case '4':
                cout << "Podaj nowy email: ";
                cin >> adresaci[id - 1].email;
                break;
            case '5':
                cout << "Podaj nowy adres zamieszkania: ";
                cin >> adresaci[id - 1].adres;
                break;
            case '6':
                cout << endl << "Powrot do menu uzytkownika" << endl << endl;
                break;
            default:
                cout << endl << "Nie ma takiej opcji w menu! Powrot do menu uzytkownika." << endl << endl;
                break;
            }
    zapisanieKsiazkiDoPliku(adresaci);
    cout << "Zmiany zostaly dokonane. Nacisnij dowolny klawisz.";
    system("read");
        
}

int main()
{
  vector <Adresat> adresaci;
  int idOsoby = 0;
  int idOstatniejOsoby = 0;
  char wybor;
  string nazwaPliku = "Ksiazka_adresowa.txt";
  
  wczytywanieZnajomychDoStruktury(adresaci, nazwaPliku); 
//   idOstatniejOsoby = adresaci.back().id;


  while(true)
    {
      system("cls");
      cout << "Ksiazka adresowa" << endl << endl;
      cout << "1. Dodaj nowa osobe" << endl;
      cout << "2. Wyszukaj" << endl;
      cout << "3. Wyswietl wszystkie zapisane kontakty" << endl;
      cout << "4. Usun adresata" << endl;
      cout << "5. Edytuj adresata" << endl;
      cout << "9. Zakoncz program" << endl << endl;
      cout << "Wybierz numer i wciśnij ENTER" << endl;
      
      wybor = wczytajZnak();

      switch (wybor)
      {
        case '1':
            idOstatniejOsoby = dodanieOsobyDoKsiazkiAdresowej(adresaci, idOstatniejOsoby);
            break;
        case '2':
            wyszukajOsobe(adresaci);
            break;
        case '3':
            wyswietlKsiazkeAdresowa(adresaci);
            break;
        case '4':
            usunAdresataOPodanymId(adresaci);
            break;
        case '5':
            edytujAdresata(adresaci);
            break;
        case '9':
            exit(0);
            break;
      }
    }

  return 0;
}
