#include <iostream>
#include <algorithm>
#include "klient.h"
#include "przedmioty.h"
#include "zamowienie.h"

Klient nowyKlient();
void zapisPlikowy(std::vector<Klient> listaKlientow, std::vector<Przedmioty> listaPrzedmiotow, std::vector<Zamowienie> listaZamowien);
void login(std::vector<Klient>* listaKlientow, Klient** aktualny);
void obslugaZamowien(std::vector<Przedmioty>* listaPrzedmiotow, std::vector<Zamowienie>* listaZamowien, Klient** aktualny, std::vector<Przedmioty>& tempList, std::vector<Klient> listaKlientow);

int main() {
	using std::vector;
	using std::cout;
	using std::cin;
	using std::endl;

	vector<Klient> listaKlientow;
	vector<Przedmioty> listaPrzedmiotow;
	vector<Zamowienie> listaZamowien;

	Klient* aktualny = nullptr;

	Klient::wczytaj(&listaKlientow);
	Zamowienie::wczytaj(&listaZamowien);
	Przedmioty::wczytaj(&listaPrzedmiotow);

	while (aktualny == nullptr) {
		int x, y;
		vector<Przedmioty> tempList;

		cout << "1 - wyswietl dostepne produkty" << endl
			<< "2 - zaloguj sie" << endl
			<< "3 - zarejestruj sie" << endl
			<< "4 - wyjscie z programu" << endl;
		cin >> x;

		switch (x) {
		case 1:
			obslugaZamowien(&listaPrzedmiotow, &listaZamowien, &aktualny, tempList, listaKlientow);
			break;
		case 2:
			login(&listaKlientow, &aktualny);
			break;
		case 3:
			listaKlientow.push_back(nowyKlient());
			system("cls");
			break;
		case 4:
			zapisPlikowy(listaKlientow, listaPrzedmiotow, listaZamowien);
			return 0;
		default:
			break;

	}
}

	while (aktualny != nullptr) {
		int x, y, z;
		vector<Przedmioty> tempList;
		vector<int> qu;

		cout << "1 - wyswietl dostepne produkty" << endl
			<< "2 - poglad konta" << endl
			<< "3 - przeloguj sie" << endl
			<< "4 - wyjscie z programu" << endl;
		cin >> x;
		
		switch (x) {
		case 1:
			system("cls");

			for (Przedmioty q : listaPrzedmiotow)
				cout << q.zwrocNazwe() << " (" << q.zwrocCene() << ") x " << q.zwrocIlosc() << endl;

			cout << endl << endl << "(1)dokonaj zamowienia" << endl
				<< "(2)anuluj" << endl;
			cin >> y;
			
			switch (y) {
			case 1:
				obslugaZamowien(&listaPrzedmiotow, &listaZamowien, &aktualny, tempList, listaKlientow);
				break;
			case 2:
				system("cls");
				break;
			}

			break;
		case 2:
			cout << "(1)historia zamowien, (2)edycja konta";
			cin >> x;
			
			switch (x) {
			case 1:
				aktualny->wyswListeZamow();
				cout << "(1)edycja zamowien (2)wyjscie ";
				cin >> x;

				if (x == 1) {
					cout << "wpisz ID zamowienia do edycji: __________\b\b\b\b\b\b\b\b\b\b";
					cin >> y;
					z = -1;

					for (int i = 0; i < size(listaZamowien); i++) {
						if (listaZamowien[i].zwrocID() == y) {
							listaZamowien[i].edytuj();
							break;
						}
					}

					system("cls");
					break;
				}

				else {
					system("cls");
					break;
				}
				break;
			case 2:
				aktualny->modyfikuj();
				break;
			}

			break;
		case 3:
			login(&listaKlientow, &aktualny);
			break;
		case 4:
			zapisPlikowy(listaKlientow, listaPrzedmiotow, listaZamowien);
			return 0;
		}
	}
}

Klient nowyKlient() {
	using std::string;
	using std::cout;
	using std::cin;
	using std::endl;

	string imie;
	string nazwisko;
	string adres;
	string login;
	string haslo;
	plec pl;
	int temp;

	cout << "podaj imie: ";
	cin >> imie;
	cout << endl << "podaj nazwisko: ";
	cin >> nazwisko;
	cout << endl << "podaj adres: ";
	cin >> adres;
	cout << endl << "wybierz plec (1 - m, 2 - k, 3 - x): ";
	cin >> temp;

	if (temp == 1)
		pl = mezczyzna;
	else if (temp == 2)
		pl = kobieta;
	else
		pl = inne;

	cout << endl << "podaj login: ";
	cin >> login;
	cout << endl << "podaj haslo: ";
	cin >> haslo;

	Klient nowy(imie, nazwisko, adres, pl, login, haslo);

	return nowy;
}

void zapisPlikowy(std::vector<Klient> listaKlientow, std::vector<Przedmioty> listaPrzedmiotow, std::vector<Zamowienie> listaZamowien) {
	Klient::zapisz(listaKlientow);
	Przedmioty::zapisz(listaPrzedmiotow);
	Zamowienie::zapisz(listaZamowien);
}

void login(std::vector<Klient>* listaKlientow, Klient** aktualny) {
	std::string login, password;

	system("cls");
	std::cout << "podaj login: ";
	std::cin >> login;
	std::cout << std::endl << "podaj haslo: ";
	std::cin >> password;

	for (int i = 0; i < size(*listaKlientow); i++) {
		if ((*listaKlientow)[i].logowanie(login, password)) {
			*aktualny = &(*listaKlientow)[i];
			break;
		}
	}

	if (aktualny == nullptr)
		std::cout << "logowanie nieudane" << std::endl;
}

void obslugaZamowien(std::vector<Przedmioty>* listaPrzedmiotow, std::vector<Zamowienie>* listaZamowien, Klient** aktualny, std::vector<Przedmioty>& tempList, std::vector<Klient> listaKlientow) {
	using std::string;
	using std::vector;
	using std::stringstream;
	using std::cout;
	using std::cin;
	using std::endl;

	int x, y;
	string linia, el, data;
	stringstream a;
	vector<int> indList;

	system("cls");

	for (Przedmioty q : *listaPrzedmiotow)
		cout << q.zwrocNazwe() << " (" << q.zwrocCene() << ") x " << q.zwrocIlosc() << endl;

	cout << endl << endl << "(1)dokonaj zamowienia" << endl
		<< "(2)anuluj" << endl;
	cin >> y;

	switch (y) {
	case 1:
		cout << "podaj numer(y) artykulu(ow), jesli zamawiany jest wiecej niz jeden artykul, ich numery oddziel spacja: ";
		cin.ignore();
		getline(cin, linia);
		a << linia;

		while (getline(a, el, ' ')) {
			indList.push_back(stoi(el));
		}

		sort(indList.begin(), indList.end(), std::greater<int>());

		for (int q : indList) {
			cout << "podaj ilosc przedmiotu: " << (*listaPrzedmiotow)[q].zwrocNazwe() << ": ";

			do {
				cin >> x;
			} while (x > (*listaPrzedmiotow)[q].zwrocIlosc());

			tempList.push_back(*(new Przedmioty((*listaPrzedmiotow)[q].zwrocNazwe(), (*listaPrzedmiotow)[q].zwrocCene(), (*listaPrzedmiotow)[q].zwrocVAT(), x)));

			if (x == (*listaPrzedmiotow)[q].zwrocIlosc())
				(*listaPrzedmiotow).erase((*listaPrzedmiotow).begin() + q);

			else
				(*listaPrzedmiotow)[q].odejmij(x);
		}
	}

	if (*aktualny == nullptr) {
		system("cls");
		cout << "(1)zaloguj sie lub (2)zarejestruj!" << endl;
		cin >> y;

		switch (y) {
		case 1:
			login(&listaKlientow, aktualny);
			break;
		case 2:
			listaKlientow.push_back(nowyKlient());
			system("cls");
			cout << "zaloguj sie przy uzyciu nowo zalozonego konta" << endl;
			login(&listaKlientow, aktualny);
			system("cls");
			break;
		}
	}

	cout << "dzisiejsza data: ";
	cin >> data;
	cout << endl << "sposob platnosci: (1)gotowka, (2)karta, (3)raty, (4)blik: ";
	cin >> x;

	sposobyPlatnosci spos;
	if (x == 1)
		spos = gotowka;
	else if (x == 2)
		spos = karta;
	else if (x == 3)
		spos = raty;
	else
		spos = blik;

	(*listaZamowien).push_back(*(new Zamowienie(data, spos, tempList)));
	(*aktualny)->dodajZam(((*listaZamowien).end() - 1)->zwrocID());
}