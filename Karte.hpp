#ifndef KARTE_HPP
#define KARTE_HPP

#include <iostream>
#include <string>
#include <tuple>

enum class Farbe { Herz, Karo, Kreuz, Pik };
struct Wert {
	enum { Ass = 1, Bube = 11, Dame, Koenig };
	int value;
	Wert(int v = 0) : value(v) {}
	bool operator<(const Wert& w) const { return this->value < w.value; }
	bool operator>(const Wert& w) const { return this->value > w.value; }
	bool operator==(const Wert& w) const { return this->value == w.value; }
};

class Karte {
	std::tuple<Farbe, Wert> karte;
public:
	Karte(Farbe farbe, Wert wert) : karte(farbe, wert) { }
	Farbe& farbe() { return std::get<0>(karte); }
	Wert& wert() { return std::get<1>(karte); }
	bool operator==(const Karte& k) { return (karte == k.karte); }
	std::ostream& print(std::ostream& o) const;
};

/* I/O - Farbe */

inline std::ostream& operator<<(std::ostream& o, const Farbe& f) {
	switch (f) {
	case Farbe::Herz: o << "Herz"; break;
	case Farbe::Karo: o << "Karo"; break;
	case Farbe::Kreuz: o << "Kreuz"; break;
	case Farbe::Pik: o << "Pik";
	} return o;
}

inline std::istream& operator>>(std::istream& i, Farbe& f) {
	std::string farbe;
	i >> farbe;
	if (farbe == "Herz" || farbe == "herz") f = Farbe::Herz;
	else if (farbe == "Karo" || farbe == "karo") f = Farbe::Karo;
	else if (farbe == "Kreuz" || farbe == "kreuz") f = Farbe::Kreuz;
	else if (farbe == "Pik" || farbe == "pik") f = Farbe::Pik;
	return i;
}

/* I/O - Wert */

inline std::ostream& operator<<(std::ostream& o, const Wert& w) {
	switch (w.value) {
	case Wert::Ass: o << "Ass"; break;
	case Wert::Koenig: o << "Koenig"; break;
	case Wert::Dame: o << "Dame"; break;
	case Wert::Bube: o << "Bube"; break;
	default: o << w.value;
	} return o;
}

inline std::istream& operator>>(std::istream& i, Wert& w) {
	std::string wert;
	i >> wert;
	if (wert == "Ass" || wert == "ass") w = Wert::Ass;
	else if (wert == "Koenig" || wert == "koenig") w = Wert::Koenig;
	else if (wert == "Dame" || wert == "dame") w = Wert::Dame;
	else if (wert == "Bube" || wert == "bube") w = Wert::Bube;
	else w = std::stoi(wert);
	return i;
}

/* O - Karte */

std::ostream& Karte::print(std::ostream& o) const {
	return o << std::get<0>(karte) << " " << std::get<1>(karte);
}

inline std::ostream& operator<<(std::ostream& o, const Karte& k) { return k.print(o); }

#endif//KARTE_HPP