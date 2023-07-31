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
int czytajId(std::string);

class Klient {

	std::string imie;
	std::string nazwisko;
	std::string adres;
	plec piec;
	std::vector<int> listaZamowien;
	std::string login;
	std::string haslo;

	static std::fstream plik;

public:

	Klient(std::string, std::string, std::string, plec, std::string, std::string);
	void modyfikuj();
	static void zapisz(std::vector<Klient>);
	static void wczytaj(std::vector<Klient>*);
	bool logowanie(std::string, std::string);
	void dodajZam(int ID);
	void wyswListeZamow();
};

#endif
