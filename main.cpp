#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;

class Klasa;
class Przedmiot {
private:
    string _nazwa;
    vector<float> oceny;
    float _srednia;
    float _suma;
    int _ilosc;
public:
    Przedmiot() {
        _srednia = 0.0f;
        _suma = 0.0f;
        _ilosc = 0;
    }
    Przedmiot(string nazwa) {
        _srednia = 0.0f;
        _suma = 0.0f;
        _ilosc = 0;
        _nazwa = nazwa;
    }
    void setNazwa(string nazwa) {
        _nazwa = nazwa;
    }
    string getNazwa(){
        return _nazwa;
    }
    float getSuma(){
        return _suma;
    }
    int getIlosc(){
        return _ilosc;
    }
    void dodajOcene(float ocena) {
        oceny.push_back(ocena);
        _suma += ocena;
        _ilosc++;
    }
    float sredniaOcen(){
        return _ilosc == 0 ? 0 : _suma/_ilosc;
    }
    friend ostream& operator <<(ostream &os, const Przedmiot &przedmiot);
};

ostream& operator <<(ostream &os, const Przedmiot &przedmiot) {
    cout << "Oceny z przedmiotu " << przedmiot._nazwa << ": ";
    if(przedmiot.oceny.size() == 0)
        cout << "Brak ocen!";
    else {
        cout << "| ";
        for(float a : przedmiot.oceny) {
            cout << a << " | ";
        }
        cout << "Srednia: " << przedmiot._suma/przedmiot.oceny.size();
    }
}

class Uczen {
private:
    string _imie,_nazwisko;
    int _id;
    string _klasa;
public:
    vector<Przedmiot> przedmioty; // w code blocksie musi być public
    Uczen(string imie, string nazwisko, int id) {
        _imie = imie;
        _nazwisko = nazwisko;
        _id = id;
    }
    void setImie(string imie) {
        _imie = imie;
    }
    void setNazwisko(string nazwisko) {
        _nazwisko = nazwisko;
    }
    void setId(int id) {
        _id = id;
    }
    void setKlasa(Klasa klasa);
    void setKlasa(string klasa) {
        _klasa = klasa;
    }
    void dodajPrzedmiot(Przedmiot &przedmiot) {
        przedmioty.push_back(przedmiot);
    }
    void pokazOceny() {
        cout << "Uczen " << _nazwisko  << " " << _imie << "(nr " << _id << ")" << endl;
        if(przedmioty.size() == 0 )
            cout << "Brak przedmiotow!" << endl;
        else {
            for(Przedmiot a : przedmioty)
                cout << a << endl;
        }
    }

    string getImie() {
        return _imie;
    }
    string getNazwisko() {
        return _nazwisko;
    }
    int getId() {
        return _id;
    }
    string getKlasa() {
        return _klasa;
    }
    float sredniaOcen() {
        float avg=0;
        int i=0;
        for(Przedmiot a : przedmioty) {
            avg += a.getSuma();
            i += a.getIlosc();
        }
        return avg/i;
    }
    friend ostream& operator <<(ostream &os, const Uczen &uczen);
};

ostream& operator <<(ostream &os, const Uczen &uczen) {
    os << uczen._id << ", " <<uczen._imie << " " << uczen._nazwisko;
}

class Klasa {
private:
    string _nazwa;
    vector<Uczen> uczniowie;
public:
    Klasa() {
        _nazwa = "Domyslna";
    }
    Klasa(string nazwa) {
        _nazwa = nazwa;
    }
    void setNazwa(string nazwa) {
        _nazwa = nazwa;
    }
    string getNazwa() {
        return _nazwa;
    }
    void dodajUcznia(Uczen &uczen) {
        uczen.setKlasa(_nazwa);
        uczniowie.push_back(uczen);
    }
    void wyswietlUczniow() {
        cout << "Lista uczniow klasy " + _nazwa + ": ";
        for(Uczen a : uczniowie) {
            cout << a;
        }
    }
    void zapiszKlase(string nazwa_pliku) {
        ofstream plik;
        plik.open(nazwa_pliku);
        plik << "Klasa " << _nazwa << endl;
        for(Uczen a : uczniowie)
            plik << a << endl;
        plik.close();

    }
    friend ostream& operator <<(ostream &os, const Klasa &klasa);
};

ostream& operator <<(ostream &os, const Klasa &klasa) {
    cout << "Lista uczniow klasy " << klasa._nazwa << ":" << endl;
    for(Uczen a : klasa.uczniowie) {
        cout  << a << endl;
    }
}

void Uczen::setKlasa(Klasa klasa) {
    _klasa = klasa.getNazwa();
}

int main() {
    do
    {
      cout<<"Jaką operację chcesz wykonać? \n 1.Dodać ucznia \n 2. Utworzyć klase \n 3. Dodać przedmiot \n 4.Dodać oceny ucznia \n 5. Dodać Ucznia do Klasy \n 6. Wyświetlić oceny ucznia oraz średnią \n 7. Wyswietlic uczniow w klasie \n 8.Zapisac klase do pliku \n"<<endl;
      int n;
      cin>>n;
      switch(n)
      {
        case 1:
          cout << "Wpisz imie i nazwisko ucznia oraz id";
          string imie,nazwisko;
          int id;
          cin>>imie>>nazwisko>>id;
          Uczen uczen1(imie,nazwisko,id);
        break;
        case 2:
          cout << "Wpisz nazwe klasy";
          string nazwa;
          cin>>nazwa;
          Klasa klasa1(nazwa);
        break;
        case 3:
            cout<<"Wpisz nazwe przedmiotu";
            string naz;
            cin>>naz;
            Przedmiot przedmiot1(naz);
        break;
        case 4:
        break;
      }

    } while (true);

    return 0;
}
