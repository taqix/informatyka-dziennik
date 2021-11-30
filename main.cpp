#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <sstream>
#include <cstdlib>

using namespace std;

class Klasa;
class Przedmiot
{
private:
    string _nazwa;
    vector<float> oceny;
    float _srednia;
    float _suma;
    int _ilosc;

public:
    Przedmiot()
    {
        _srednia = 0.0f;
        _suma = 0.0f;
        _ilosc = 0;
    }
    Przedmiot(string nazwa)
    {
        _srednia = 0.0f;
        _suma = 0.0f;
        _ilosc = 0;
        _nazwa = nazwa;
    }
    void setNazwa(string nazwa)
    {
        _nazwa = nazwa;
    }
    string getNazwa()
    {
        return _nazwa;
    }
    float getSuma()
    {
        return _suma;
    }
    int getIlosc()
    {
        return _ilosc;
    }
    void dodajOcene(float ocena)
    {
        oceny.push_back(ocena);
        _suma += ocena;
        _ilosc++;
    }
    float sredniaOcen()
    {
        return _ilosc == 0 ? 0 : _suma / _ilosc;
    }
    friend ostream &operator<<(ostream &os, const Przedmiot &przedmiot);
};

ostream &operator<<(ostream &os, const Przedmiot &przedmiot)
{
    cout << "Oceny z przedmiotu " << przedmiot._nazwa << ": ";
    if (przedmiot.oceny.size() == 0)
        cout << "Brak ocen!";
    else
    {

        for (float a : przedmiot.oceny)
        {
            cout << a << " - ";
        }
        cout << "Srednia: " << przedmiot._suma / przedmiot.oceny.size();
    }
}

class Uczen
{
private:
    string _imie, _nazwisko;
    int _id;
    string _klasa;

public:
    vector<Przedmiot> przedmioty; // w code blocksie musi być public
    Uczen(string imie, string nazwisko, int id)
    {
        _imie = imie;
        _nazwisko = nazwisko;
        _id = id;
    }
    void setImie(string imie)
    {
        _imie = imie;
    }
    void setNazwisko(string nazwisko)
    {
        _nazwisko = nazwisko;
    }
    void setId(int id)
    {
        _id = id;
    }
    void setKlasa(Klasa klasa);
    void setKlasa(string klasa)
    {
        _klasa = klasa;
    }
    void dodajPrzedmiot(Przedmiot &przedmiot)
    {
        przedmioty.push_back(przedmiot);
    }
    void pokazOceny()
    {
        cout << "Uczen " << _nazwisko << " " << _imie << "(nr " << _id << ")" << endl;
        if (przedmioty.size() == 0)
            cout << "Brak przedmiotow!" << endl;
        else
        {
            for (Przedmiot a : przedmioty)
                cout << a << endl;
        }
    }

    string getImie()
    {
        return _imie;
    }
    string getNazwisko()
    {
        return _nazwisko;
    }
    int getId()
    {
        return _id;
    }
    string getKlasa()
    {
        return _klasa;
    }
    float sredniaOcen()
    {
        float avg = 0;
        int i = 0;
        for (Przedmiot a : przedmioty)
        {
            avg += a.getSuma();
            i += a.getIlosc();
        }
        return avg / i;
    }
    friend ostream &operator<<(ostream &os, const Uczen &uczen);
};

ostream &operator<<(ostream &os, const Uczen &uczen)
{
    os << uczen._id << ", " << uczen._imie << " " << uczen._nazwisko;
}

class Klasa
{
private:
    string _nazwa;
    vector<Uczen> uczniowie;

public:
    Klasa()
    {
        _nazwa = "Domyslna";
    }
    Klasa(string nazwa)
    {
        _nazwa = nazwa;
    }
    void setNazwa(string nazwa)
    {
        _nazwa = nazwa;
    }
    string getNazwa()
    {
        return _nazwa;
    }
    void dodajUcznia(Uczen &uczen)
    {
        uczen.setKlasa(_nazwa);
        uczniowie.push_back(uczen);
    }
    void wyswietlUczniow()
    {
        cout << "Lista uczniow klasy " + _nazwa + ": " << endl;
        for (Uczen a : uczniowie)
        {
            cout << a << endl;
        }
    }
    void zapiszKlase(string nazwa_pliku)
    {
        ofstream plik;
        plik.open(nazwa_pliku);
        plik << "Klasa " << _nazwa << endl;
        for (Uczen a : uczniowie)
            plik << a << endl;
        plik.close();
    }
    void zmianDoCSV(string nazwa_pliku)
    {
        const char sep=',';
        string line,word;
        ifstream in(nazwa_pliku);
        if (!in)
        {
            cout << "Can't open file";
            exit(0);
        }
        ofstream out("file.csv");
        while (getline(in, line)) // get successive line of text
        {
            stringstream ss(line);
            bool first = true;
            while (ss >> word) // get successive words per line
            {
                if (!first)
                    out << sep; // second and later words need a separator
                out << word;
                first = false;
            }
            out << '\n'; // end of line of output
        }
        in.close();
        out.close();
    }
    friend ostream &operator<<(ostream &os, const Klasa &klasa);
};

ostream &operator<<(ostream &os, const Klasa &klasa)
{
    cout << "Lista uczniow klasy " << klasa._nazwa << ":" << endl;
    for (Uczen a : klasa.uczniowie)
    {
        cout << a << endl;
    }
}

void Uczen::setKlasa(Klasa klasa)
{
    _klasa = klasa.getNazwa();
}

int main()
{
    Klasa kl2p("2P");
    Uczen tomasz("Tomasz", "Wilk", 27);
    Uczen wiktor("Wiktor", "Lemanski", 12);
    Uczen wojtus("Wojtek", "Bednarowski", 1);
    Przedmiot infa("informatyka");
    Przedmiot matematyka("matematyka");
    kl2p.dodajUcznia(tomasz);
    kl2p.dodajUcznia(wiktor);
    kl2p.dodajUcznia(wojtus);
    infa.dodajOcene(4);
    matematyka.dodajOcene(3);
    tomasz.dodajPrzedmiot(infa);
    tomasz.dodajPrzedmiot(matematyka);
    tomasz.pokazOceny();
    infa.dodajOcene(6);
    wiktor.dodajPrzedmiot(infa);
    wiktor.dodajPrzedmiot(matematyka);
    wiktor.pokazOceny();
    matematyka.dodajOcene(2);
    wojtus.dodajPrzedmiot(infa);
    wojtus.dodajPrzedmiot(matematyka);
    wojtus.pokazOceny();
    cout << infa.sredniaOcen();
    kl2p.wyswietlUczniow();
    kl2p.zapiszKlase("isk.txt");
    kl2p.zmianDoCSV("isk.txt");

    return 0;
}