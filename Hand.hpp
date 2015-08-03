#ifndef HAND_HPP
#define HAND_HPP

#include <deque>
#include "Karte.hpp"

class Hand {
	std::deque<Karte> hand;
public:
	Hand() = default;
	void take(const Karte&);
	bool play(const Karte& k);
	std::ostream& print(std::ostream& o) const;
};

void Hand::take(const Karte& karte) {
	hand.push_front(karte);
}

bool Hand::play(const Karte& k) {
	std::deque<Karte>::iterator i;
	for (i = hand.begin(); i != hand.end(); ++i) if (*i == k) break;
	if (i != hand.end()) {
		hand.erase(i); 
		return true;
	}
	return false;
}

std::ostream& Hand::print(std::ostream& o) const {
	for (Karte k : hand) o << k << std::endl;
	return o;
}

inline std::ostream& operator<<(std::ostream& o, const Hand& h) { return h.print(o); }

#endif//HAND_HPP