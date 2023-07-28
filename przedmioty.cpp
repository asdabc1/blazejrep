#include "przedmioty.h"

using namespace std;

fstream przedmioty::plik;

przedmioty::przedmioty(string name, float price, float taxRate, int amount)
{
	nazwa = name;
	cena = price;
	stawkaVAT = taxRate;
	ilosc = amount;
}

void przedmioty::zapisz(vector<przedmioty> lista) {
	plik.open("przedmioty.txt", ios::out);
	for (przedmioty q : lista)
		plik << q.nazwa << " " << q.cena << " " << q.stawkaVAT << " " << q.ilosc << endl;
	plik.close();
}

float przedmioty::zwrocCene() {
	return cena;
}

int przedmioty::zwrocIlosc() {
	return ilosc;
}

float przedmioty::zwrocVAT() {
	return stawkaVAT;
}

string przedmioty::zwrocNazwe() {
	return nazwa;
}

void przedmioty::wczytaj(vector<przedmioty>* lista) {
	plik.open("przedmioty.txt", ios::in);
	string t, name, price, taxR, quant;
	while (getline(plik, t)) {
		stringstream linia;
		linia << t;
		linia >> name;
		linia >> price;
		linia >> taxR;
		linia >> quant;
		przedmioty a(name, stof(price), stof(taxR), stoi(quant));
		(*lista).push_back(a);
	}
	plik.close();
}

void przedmioty::odejmij(int val) {
	ilosc -= val;
}