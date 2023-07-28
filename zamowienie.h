#ifndef ZAMOWIENIE_H
#define ZAMOWIENIE_H
#include <string>
#include <sstream>
#include <ctime>
#include <vector>
#include "przedmioty.h"

enum sposobyPlatnosci { gotowka, karta, raty, blik };

przedmioty czytajPrzedmiot(std::string);

class zamowienie {
private:
	std::string data;
	float wartoscCalkowita;
	sposobyPlatnosci sp;
	std::vector<przedmioty> tab;
	int ID;
	static std::fstream plik;
public:
	zamowienie(std::string date, sposobyPlatnosci payment, std::vector<przedmioty> list);
	zamowienie(int ident, std::string date, sposobyPlatnosci payment);
	void edytuj();
	int zwrocID();
	void dodajPrzedmiot(std::string linia);
	static void zapisz(std::vector<zamowienie> lista);
	static void wczytaj(std::vector<zamowienie>* lista);
};

#endif // ZAMOWIENIE_H
