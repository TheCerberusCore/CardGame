#ifndef CARDGAME_HPP
#define CARDGAME_HPP

#include <iostream> 
#include <string>
#include <tuple>
#include <stack>
#include <set>
#include <random>
#include <vector>
#include <exception>

class DeckIsEmptyExcept : public std::exception {
public:
	virtual const char* what() const noexcept override {
		return "No more cards available!";
	}
};

enum class KartenAttribut { Farbe, Wert };
enum class Farbe { Herz, Karo, Kreuz, Pik };

struct Wert {
	enum { Ass = 1, Bube = 11, Dame, Koenig };
	int value;
	Wert(int v = 0) : value(v) {}
	bool operator<(const Wert& w) const { return this->value < w.value; }
	bool operator>(const Wert& w) const { return this->value > w.value; }
	bool operator==(const Wert& w) const { return this->value == w.value; }
};

inline std::ostream& operator<<(std::ostream& o, Farbe& f) {
	switch (f) {
	case Farbe::Herz:		o << "Herz"; break;
	case Farbe::Karo:		o << "Karo"; break;
	case Farbe::Kreuz:	o << "Kreuz"; break;
	case Farbe::Pik:		o << "Pik";
	} return o;
}

inline std::ostream& operator<<(std::ostream& o, Wert& w) {
	switch (w.value) {
	case Wert::Ass: o << "Ass"; break;
	case Wert::Koenig: o << "Koenig"; break;
	case Wert::Dame: o << "Dame"; break;
	case Wert::Bube: o << "Bube"; break;
	default: o << w.value;
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

typedef std::tuple<Farbe, Wert> Karte;
typedef std::set<Karte> Hand;

inline std::ostream& operator<<(std::ostream& o, Karte& karte) {
	return o << std::get<0>(karte) << " " << std::get<1>(karte);
}

inline std::ostream& operator<<(std::ostream& o, Hand& hand) {
	for (auto i : hand) o << i << std::endl;
	return o;
}

template <size_t MIN, size_t MAX>
class Deck {
	std::stack<Karte> deck;
public:
	Deck(void);
	Karte draw();
	void shuffle(void);
};

template <size_t MIN, size_t MAX>
Deck<MIN, MAX>::Deck() {
	std::vector<Karte> karten;
	for (int i = MIN; i <= MAX; ++i) {
		karten.push_back(Karte(Farbe::Herz, i));
		karten.push_back(Karte(Farbe::Karo, i));
		karten.push_back(Karte(Farbe::Kreuz, i));
		karten.push_back(Karte(Farbe::Pik, i));
	}
	for (auto i : karten) deck.push(i); 
}

template <size_t MIN, size_t MAX>
Karte Deck<MIN, MAX>::draw() {
	if (deck.empty()) throw DeckIsEmptyExcept();
	Karte next = deck.top();
	deck.pop();
	return next;
}

template <size_t MIN, size_t MAX>
void Deck<MIN, MAX>::shuffle() {
	std::vector<Karte> karten;
	while (deck.size()) karten.push_back(this->draw());
	while (karten.size()) {
		std::random_device rd;
		int rand = rd() % karten.size();
		deck.push(karten[rand]);
		karten.erase(karten.begin() + rand);
	}
}

#endif//CARDGAME_HPP