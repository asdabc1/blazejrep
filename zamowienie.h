#ifndef ZAMOWIENIE_H
#define ZAMOWIENIE_H
#include <string>
#include <sstream>
#include <ctime>
#include <vector>
#include "przedmioty.h"

enum sposobyPlatnosci { gotowka, karta, raty, blik };

Przedmioty czytajPrzedmiot(std::string);

class Zamowienie {

	std::string data;
	float wartoscCalkowita;
	sposobyPlatnosci sp;
	std::vector<Przedmioty> tab;
	int ID;
	static std::fstream plik;

	void setPaymentMethod();

public:

	Zamowienie(std::string date, sposobyPlatnosci payment, std::vector<Przedmioty> list);
	Zamowienie(int ident, std::string date, sposobyPlatnosci payment);
	void edytuj();
	int zwrocID();
	void dodajPrzedmiot(std::string linia);
	static void zapisz(std::vector<Zamowienie> lista);
	static void wczytaj(std::vector<Zamowienie>* lista);
};

#endif
