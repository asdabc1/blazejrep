#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

class Przedmioty {

	float stawkaVAT;
	int ilosc;
	std::string nazwa;
	float cena;
	static std::fstream plik;

public:

	Przedmioty(std::string name, float price, float taxRate, int amount);
	static void zapisz(std::vector<Przedmioty>);
	static void wczytaj(std::vector<Przedmioty>*);
	float zwrocVAT();
	int zwrocIlosc();
	std::string zwrocNazwe();
	float zwrocCene();
	void odejmij(int);
};
