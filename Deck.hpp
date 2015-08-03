#ifndef DECK_HPP
#define DECK_HPP

#include <deque>
#include <random>
#include "Karte.hpp"
#include "Exceptions.hpp"

template <size_t MIN, size_t MAX>
class Deck {
	std::deque<Karte> deck;
public:
	Deck();
	Karte& draw();
	void shuffle();
	bool empty() const { return deck.empty(); }
};

typedef Deck<Wert::Ass, Wert::Koenig> Deck_Default;

template <size_t MIN = Wert::Ass, size_t MAX = Wert::Koenig>
Deck<MIN, MAX>::Deck() {
	for (int i = MIN; i <= MAX; ++i) {
		deck.push_back(Karte(Farbe::Herz, i));
		deck.push_back(Karte(Farbe::Karo, i));
		deck.push_back(Karte(Farbe::Kreuz, i));
		deck.push_back(Karte(Farbe::Pik, i));
	}
}

template <size_t MIN, size_t MAX>
Karte& Deck<MIN, MAX>::draw() {
	if (deck.empty()) throw DeckIsEmptyExcept();
	Karte& next = deck.front();
	deck.pop_front();
	return next;
}

template <size_t MIN, size_t MAX>
void Deck<MIN, MAX>::shuffle() {
	std::deque<Karte> karten;
	std::random_device rd;
	swap(deck, karten);
	while (karten.size()) {
		int rand = rd() % karten.size();
		deck.push_back(karten[rand]);
		karten.erase(karten.begin() + rand);
	}
}

#endif//DECK_HPP