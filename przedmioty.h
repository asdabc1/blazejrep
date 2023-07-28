#ifndef PRZEDMIOTY_H
#define PRZEDMIOTY_H
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

class przedmioty {
private:
	float stawkaVAT;
	int ilosc;
	std::string nazwa;
	float cena;
	static std::fstream plik;
public:
	przedmioty(std::string name, float price, float taxRate, int amount);
	static void zapisz(std::vector<przedmioty>);
	static void wczytaj(std::vector<przedmioty>*);
	float zwrocVAT();
	int zwrocIlosc();
	std::string zwrocNazwe();
	float zwrocCene();
	void odejmij(int);
};

#endif // PRZEDMIOTY_H
