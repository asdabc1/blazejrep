#include "klient.h"

using namespace std;

fstream Klient::plik;

Klient::Klient(string name, string lname, string adr, plec gen, string log, string has) {
	imie = name;
	nazwisko = lname;
	adres = adr;
	piec = gen;
	login = log;
	haslo = has;
}

void Klient::modyfikuj() {
	int temp;
	string nameAddress;

	cout << endl << "wybierz parametr do modyfikacji (1 - imie, 2 - nazwisko, 3 - adres, 4 - plec): ";
	cin >> temp;
	
	switch (temp) {
	case 1:
		cout << "podaj nowe imie: ";
		cin >> nameAddress;
		this->imie = nameAddress;
		cout << endl;
		break;
	case 2:
		cout << "podaj nowe nazwisko: ";
		cin >> nameAddress;
		this->nazwisko = nameAddress;
		cout << endl;
		break;
	case 3:
		cout << "podaj nowy adres: ";
		cin >> nameAddress;
		this->adres = nameAddress;
		cout << endl;
		break;
	case 4:
		cout << "1 - m, 2 - k, 3 - x: ";
		cin >> temp;

		switch (temp) {
		case 1:
			this->piec = mezczyzna;
			break;
		case 2:
			this->piec = kobieta;
			break;
		default:
			this->piec = inne;
			break;
		}

		cout << endl;
		break;
	default:
		cout << "wybrano nieodpowiednia opcje!" << endl;
		break;
	}
}

void Klient::zapisz(vector<Klient> lista) {
	plik.open("klienci.txt", ios::out);

	for (Klient x : lista) {
		plik << x.imie << " " << x.nazwisko << " " << x.adres << " " << x.piec << " " << x.login << " " << x.haslo << endl;
		for (int y : x.listaZamowien)
			plik << "%" << y << endl;
	}

	plik.close();
}

int czytajId(string wyrazenie) {
	string wynik;

	for (int i = 1; i < size(wyrazenie); i++)
		wynik += wyrazenie[i];

	int ret = stoi(wynik);

	return ret;
}

void Klient::wczytaj(vector<Klient>* lista) {
	plik.open("klienci.txt", ios::in);

	string t, name, lname, adr, gen, log, passwd;

	while (getline(plik, t)) {
		if (t[0] != '%') {
			stringstream linia;
			linia << t;
			linia >> name;
			linia >> lname;
			linia >> adr;
			linia >> gen;
			linia >> log;
			linia >> passwd;
			plec z;
			if (gen == "1")
				z = mezczyzna;
			else if (gen == "2")
				z = kobieta;
			else
				z = inne;
			Klient a(name, lname, adr, z, log, passwd);
			(*lista).push_back(a);
		}

		else {
			((*lista).end() - 1)->listaZamowien.push_back(czytajId(t));
		}
	}

	plik.close();
}

bool Klient::logowanie(string log, string passwd) {
	return (log == login && passwd == haslo);
}

void Klient::dodajZam(int ID) {
	listaZamowien.push_back(ID);
}

void Klient::wyswListeZamow() {
	for (int q : listaZamowien)
		cout << "zamowienie o ID: " << q << endl;
}