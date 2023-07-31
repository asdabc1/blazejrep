#include "przedmioty.h"

using namespace std;

fstream Przedmioty::plik;

Przedmioty::Przedmioty(string name, float price, float taxRate, int amount)
{
	nazwa = name;
	cena = price;
	stawkaVAT = taxRate;
	ilosc = amount;
}

void Przedmioty::zapisz(vector<Przedmioty> lista) {
	plik.open("Przedmioty.txt", ios::out);

	for (Przedmioty q : lista)
		plik << q.nazwa << " " << q.cena << " " << q.stawkaVAT << " " << q.ilosc << endl;

	plik.close();
}

float Przedmioty::zwrocCene() {
	return cena;
}

int Przedmioty::zwrocIlosc() {
	return ilosc;
}

float Przedmioty::zwrocVAT() {
	return stawkaVAT;
}

string Przedmioty::zwrocNazwe() {
	return nazwa;
}

void Przedmioty::wczytaj(vector<Przedmioty>* lista) {
	plik.open("Przedmioty.txt", ios::in);
	string t, name, price, taxR, quant;

	while (getline(plik, t)) {
		stringstream linia;
		linia << t;
		linia >> name;
		linia >> price;
		linia >> taxR;
		linia >> quant;
		Przedmioty a(name, stof(price), stof(taxR), stoi(quant));
		(*lista).push_back(a);
	}

	plik.close();
}

void Przedmioty::odejmij(int val) {
	ilosc -= val;
}