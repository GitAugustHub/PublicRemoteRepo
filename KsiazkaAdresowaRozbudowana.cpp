#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <cstdio>
#include <fstream>
#include <string> 
#include <sstream>
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

void czyscEkran() 
{
    cout << "\033[2J\033[1;1H"; // Sekwencja czyszczaca ANSI
}

void czekajNaWcisniecieKlawisza() 
{
    cout << "Nacisnij klawisz ENTER by kontynuowac...";
    cin.ignore(numeric_limits <streamsize> :: max(), '\n');
}

void wyswietlKontakt(Adresat adresat)
{ 
    cout << adresat.id << endl;
    cout << "Imie: " << adresat.imie << endl;
    cout << "Nazwisko: " << adresat.nazwisko << endl;
    cout << "Numer telefonu: " << adresat.nrTelefonu << endl;
    cout << "Email: " << adresat.email << endl;
    cout << "Adres: " << adresat.adres << endl;
}

void zapisanieKsiazkiDoPliku(const vector <Adresat> &adresaci)
{
    fstream plik;
    plik.open("Ksiazka_adresowa.txt", ios::out);
    if (plik.good() == false) 
    {
        cout << "Plik z Twoja ksiazka adresowa nie istnieje!" << endl;
        czekajNaWcisniecieKlawisza();
    }  
    else 
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

void dodanieOsobyDoKsiazkiAdresowej(vector <Adresat> &adresaci)
{
  Adresat adresat;
  string imie, nazwisko, nrTelefonu, email, adres;
  czyscEkran();

  if (adresaci.empty() == true)
  {
    adresat.id = 1;
  }
  else
  {
    adresat.id = adresaci.back().id + 1;
  }

  cout << "Podaj imie: "; 
  adresat.imie = wczytajLinie();
  cout << "Podaj nazwisko: "; 
  adresat.nazwisko = wczytajLinie();
  cout << "Podaj nr telefonu: "; 
  adresat.nrTelefonu = wczytajLinie();
  cout << "Podaj adres email: "; 
  adresat.email = wczytajLinie();
  cout << "Podaj adres: "; 
  adresat.adres = wczytajLinie();

  adresaci.push_back(adresat);

  zapisanieKsiazkiDoPliku(adresaci); 
  
  cout << "Dodano do ksiazki adresowej" << endl;
  czekajNaWcisniecieKlawisza();
}

vector <Adresat> wczytywanieZnajomychDoStruktury(const string nazwaPliku)
{
  vector <Adresat> adresaci;
  Adresat adresat;
  string id;
  string liniaZDanymi = "";
  string pojedynczaDanaAdresata = "";
  int numerPojedynczejDanejAdresata = 1;
  
  ifstream plik(nazwaPliku);

  // plik.open(nazwaPliku, ios::in | ios::app);
  if (!plik.is_open()) 
    {
        cerr << "Nie udalo sie otworzyc pliku " << nazwaPliku << endl;
        return adresaci; // Zwrocenie pustego wektora w przypadku błedu
    }

    while (getline (plik, liniaZDanymi)) 
    {
        stringstream ss(liniaZDanymi);
        getline(ss, id, '|');
        adresat.id = atoi(id.c_str());
        getline(ss, adresat.imie, '|');
        getline(ss, adresat.nazwisko, '|');
        getline(ss, adresat.nrTelefonu, '|');
        getline(ss, adresat.email, '|');
        getline(ss, adresat.adres, '|');
        
    adresaci.push_back(adresat);
    }
    plik.close();
    return adresaci;
}

void wyszukajOsobePoImieniu(vector <Adresat> &adresaci)
{
    string imie;
    bool osobaOdnaleziona = false;
        
        czyscEkran();
        cout << "Podaj imie: ";
        cin >> imie;

        for (const Adresat adresat : adresaci) 
        {
            if (adresat.imie == imie) 
            {
                cout << "Znalazlem osobe o imieniu " << imie << endl;
                sleep(1);
                cout << "Oto dane z ksiazki adresowej: " << endl;
                wyswietlKontakt(adresat);
                sleep(3);
                osobaOdnaleziona = true;
            }
        }
        if (!osobaOdnaleziona) 
        {
        cout << "Osoby o imieniu: " << imie << " nie ma w ksiazce adresowej." << endl;
        sleep(3);
        }
}

void wyszukajOsobePoNazwisku(vector <Adresat> &adresaci)
{
    string nazwisko;
    bool osobaOdnaleziona = false;
    
        czyscEkran();
        cout << "Podaj nazwisko: ";
        cin >> nazwisko;
        
        for (const Adresat adresat : adresaci) 
        {
            if (adresat.nazwisko == nazwisko) 
            {
                cout << "Znalazlem osobe o nazwisku " << nazwisko << endl;
                sleep(1);
                cout << "Oto dane z ksiazki adresowej: " << endl;
                wyswietlKontakt(adresat);
                sleep(3);
                osobaOdnaleziona = true;
            }
        }
        if (osobaOdnaleziona == false) 
        {
        cout << "Osoby o nazwisku: " << nazwisko << " nie ma w ksiazce adresowej." << endl;
        sleep(3);
        }
}

void wyswietlKsiazkeAdresowa(vector <Adresat> &adresaci)
{
  czyscEkran();

  if (adresaci.empty()) 
    {
        cout << "Brak znajomych w ksiazce adresowej." << endl;
        czekajNaWcisniecieKlawisza();
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
  czekajNaWcisniecieKlawisza();
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
            zapisanieKsiazkiDoPliku(adresaci);
            cout << "Adresat zostal usuniety. Nacisnij dowolny klawisz.";
            czekajNaWcisniecieKlawisza();
        }
        if (itr == adresaci.end())
        {
            break;
        }
    }
    
}

void edytujAdresata(vector <Adresat> &adresaci)
{
    int idWybranegoAdresata;
    char wybor;
    cout << "Podaj ID adresata, ktory ma zostac edytowany: ";
    cin >> idWybranegoAdresata;

    for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr -> id == idWybranegoAdresata)
        {
        czyscEkran();
        cout << "Edycja wybranego adresata. Wybierz dane do aktualizacji:" << endl << endl;
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
                itr -> imie =  wczytajLinie();
                zapisanieKsiazkiDoPliku(adresaci);
                break;
            case '2':
                cout << "Podaj nowe nazwisko: ";
                itr -> nazwisko =  wczytajLinie();
                zapisanieKsiazkiDoPliku(adresaci);
                break;
            case '3':
                cout << "Podaj nowy numer telefonu: ";
                itr -> nrTelefonu =  wczytajLinie();
                zapisanieKsiazkiDoPliku(adresaci);
                break;
            case '4':
                cout << "Podaj nowy email: ";
                itr -> email =  wczytajLinie();
                zapisanieKsiazkiDoPliku(adresaci);
                break;
            case '5':
                cout << "Podaj nowy adres zamieszkania: ";
                itr -> adres =  wczytajLinie();
                zapisanieKsiazkiDoPliku(adresaci);
                break;
            case '6':
                cout << endl << "Powrot do menu uzytkownika" << endl << endl;
                break;
            default:
                cout << endl << "Nie ma takiej opcji w menu! Powrot do menu uzytkownika." << endl << endl;
                break;
            }
        }
    }
    cout << "Zmiany zostaly dokonane.";
    czekajNaWcisniecieKlawisza();
        
}

int main()
{
  int idOsoby = 0;
  char wybor;
  string nazwaPliku = "Ksiazka_adresowa.txt";
  vector <Adresat> adresaci = wczytywanieZnajomychDoStruktury(nazwaPliku); 

  while(true)
    {
      czyscEkran();
      cout << "Ksiazka adresowa" << endl << endl;
      cout << "1. Dodaj nowa osobe" << endl;
      cout << "2. Wyszukaj osobe po imieniu" << endl;
      cout << "3. Wyszukaj osobe po nazwisku" << endl;
      cout << "4. Wyswietl wszystkie zapisane kontakty" << endl;
      cout << "5. Usun adresata" << endl;
      cout << "6. Edytuj adresata" << endl;
      cout << "9. Zakoncz program" << endl << endl;
      cout << "Wybierz numer i wciśnij ENTER" << endl;
      
      wybor = wczytajZnak();

      switch (wybor)
      {
        case '1':
            dodanieOsobyDoKsiazkiAdresowej(adresaci);
            break;
        case '2':
            wyszukajOsobePoImieniu(adresaci);
            break;
        case '3':
            wyszukajOsobePoNazwisku(adresaci);
            break;
        case '4':
            wyswietlKsiazkeAdresowa(adresaci);
            break;
        case '5':
            usunAdresataOPodanymId(adresaci);
            break;
        case '6':
            edytujAdresata(adresaci);
            break;
        case '9':
            exit(0);
            break;
      }
    }

  return 0;
}
