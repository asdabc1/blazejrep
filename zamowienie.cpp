#include <iostream>
#include "zamowienie.h"

using namespace std;

fstream zamowienie::plik;

zamowienie::zamowienie(string date, sposobyPlatnosci payment, vector<przedmioty> list)
{
	float suma = 0;
	data = date;
	sp = payment;
	ID = time(NULL);
	tab = list;
	for (przedmioty q : tab)
		suma += q.zwrocCene() * q.zwrocIlosc();
}

zamowienie::zamowienie(int iden, string date, sposobyPlatnosci payment)
{
	data = date;
	sp = payment;
	ID = iden;
}

bool operator==(zamowienie x, int y) {
	return (x.zwrocID() == y);
}

void zamowienie::edytuj() {
	cout << "wybierz element zamowienia do edycji:" << endl
		<< "1 - sposob platnosci" << endl
		<< "2 - produkty" << endl;
	int temp;
	cin >> temp;
	switch (temp) {
	case 1:
		cout << endl << "wybierz metode platnosci (1 - gotowka, 2 - karta, 3 - raty, 4 - blik): _\b";
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
		break;
	case 2:
		int i = 0;
		for (przedmioty x : tab) {
			cout << "[" << i << "]" << " " << x.zwrocNazwe() << "(" << x.zwrocCene() << ")\t";
			i++;
		}
		cout << endl << "wybierz element do usuniecia: ";
		cin >> temp;
		tab.erase(tab.begin() + temp);
		break;
	}
}

int zamowienie::zwrocID() {
	return ID;
}

void zamowienie::dodajPrzedmiot(string linia) {
	przedmioty x = czytajPrzedmiot(linia);
	tab.push_back(x);
}

void zamowienie::zapisz(vector<zamowienie> lista) {
	plik.open("zamowienia.txt", ios::out);
	for (zamowienie q : lista) {
		int i = -1;
		plik << q.ID << " " << q.data << " " << q.sp << endl;
		for (przedmioty x : q.tab)
			plik << "%" << x.zwrocNazwe() << " " << x.zwrocCene() << " " << x.zwrocVAT() << " " << x.zwrocIlosc() << endl;
	}
	plik.close();
}

przedmioty czytajPrzedmiot(string wyrazenie) {
	string op, nazwa, cena, ilosc, vat;
	for (int i = 1; i < size(wyrazenie); i++)
		op += wyrazenie[i];
	stringstream linia;
	linia << op;
	linia >> nazwa;
	linia >> cena;
	linia >> vat;
	linia >> ilosc;
	przedmioty a(nazwa, stof(cena), stof(vat), stoi(ilosc));
	return a;
}

void zamowienie::wczytaj(vector<zamowienie>* lista) {
	plik.open("zamowienia.txt", ios::in);
	string t, ID, data, sposob;
	while (getline(plik, t)) {
		stringstream linia;
		linia << t;
		if (t[0] != '%') {
			linia >> ID;
			linia >> data;
			linia >> sposob;
			sposobyPlatnosci x;
			if (sposob == "0")
				x = gotowka;
			else if (sposob == "1")
				x = karta;
			else if (sposob == "2")
				x = raty;
			else
				x = blik;
			zamowienie a(stoi(ID), data, x);
			(*lista).push_back(a);
		}
		else {
			auto temp = (lista->end() - 1);
			temp->dodajPrzedmiot(t);
		}
	}
	plik.close();
}