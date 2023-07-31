#include <iostream>
#include "zamowienie.h"

using namespace std;

fstream Zamowienie::plik;

Zamowienie::Zamowienie(string date, sposobyPlatnosci payment, vector<Przedmioty> list)
{
	float suma = 0;
	data = date;
	sp = payment;
	ID = time(NULL);
	tab = list;

	for (Przedmioty q : tab)
		suma += q.zwrocCene() * q.zwrocIlosc();
}

Zamowienie::Zamowienie(int iden, string date, sposobyPlatnosci payment)
{
	data = date;
	sp = payment;
	ID = iden;
}

bool operator==(Zamowienie x, int y) {
	return (x.zwrocID() == y);
}

void Zamowienie::setPaymentMethod() {
	cout << endl << "wybierz metode platnosci (1 - gotowka, 2 - karta, 3 - raty, 4 - blik): _\b";
	int temp;
	cin >> temp;

	switch (temp) {
	case 1:
		this->sp = gotowka;
		break;
	case 2:
		this->sp = karta;
		break;
	case 3:
		this->sp = raty;
		break;
	case 4:
		this->sp = blik;
		break;
	}
}

void Zamowienie::edytuj() {
	cout << "wybierz element zamowienia do edycji:" << endl
		<< "1 - sposob platnosci" << endl
		<< "2 - produkty" << endl;
	int temp;
	cin >> temp;

	switch (temp) {
	case 1:
		this->setPaymentMethod();
		break;
	case 2:
		int i = 0;

		for (Przedmioty x : tab) {
			cout << "[" << i << "]" << " " << x.zwrocNazwe() << "(" << x.zwrocCene() << ")\t";
			i++;
		}

		cout << endl << "wybierz element do usuniecia: ";
		cin >> temp;
		tab.erase(tab.begin() + temp);
		break;
	}
}

int Zamowienie::zwrocID() {
	return ID;
}

void Zamowienie::dodajPrzedmiot(string linia) {
	Przedmioty x = czytajPrzedmiot(linia);
	tab.push_back(x);
}

void Zamowienie::zapisz(vector<Zamowienie> lista) {
	plik.open("zamowienia.txt", ios::out);

	for (Zamowienie q : lista) {
		int i = -1;
		plik << q.ID << " " << q.data << " " << q.sp << endl;
		for (Przedmioty x : q.tab)
			plik << "%" << x.zwrocNazwe() << " " << x.zwrocCene() << " " << x.zwrocVAT() << " " << x.zwrocIlosc() << endl;
	}

	plik.close();
}

Przedmioty czytajPrzedmiot(string wyrazenie) {
	string op, nazwa, cena, ilosc, vat;

	for (int i = 1; i < size(wyrazenie); i++)
		op += wyrazenie[i];

	stringstream linia;
	linia << op;
	linia >> nazwa;
	linia >> cena;
	linia >> vat;
	linia >> ilosc;

	Przedmioty a(nazwa, stof(cena), stof(vat), stoi(ilosc));

	return a;
}

void Zamowienie::wczytaj(vector<Zamowienie>* lista) {
	plik.open("zamowienia.txt", ios::in);
	string t, ID, data, sposob;

	while (getline(plik, t)) {
		stringstream linia;
		linia << t;

		if (t[0] == '%') {
			auto temp = (lista->end() - 1);
			temp->dodajPrzedmiot(t);

			return;
		}
		linia >> ID;
		linia >> data;
		linia >> sposob;
		sposobyPlatnosci x;

		switch (stoi(sposob)) {
		case 0:
			x = gotowka;
			break;
		case 1:
			x = karta;
			break;
		case 2:
			x = raty;
			break;
		default:
			x = blik;
			break;
		}
		Zamowienie a(stoi(ID), data, x);
		(*lista).push_back(a);
	}

	plik.close();
}