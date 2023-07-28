#ifndef KLIENT_H
#define KLIENT_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include "zamowienie.h"

enum plec { inne, mezczyzna, kobieta };

std::string czytajDoSpacji(std::string);
int czytajID(std::string);

class klient {
private:
	std::string imie;
	std::string nazwisko;
	std::string adres;
	plec piec;
	std::vector<int> listaZamowien;
	std::string login;
	std::string haslo;
	static std::fstream plik;
public:
	klient(std::string, std::string, std::string, plec, std::string, std::string);
	void modyfikuj();
	static void zapisz(std::vector<klient>);
	static void wczytaj(std::vector<klient>*);
	bool logowanie(std::string, std::string);
	void dodajZam(int ID);
	void wyswListeZamow();
};

#endif // KLIENT_H
