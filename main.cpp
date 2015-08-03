#include "Command.hpp"
#include "Karte.hpp"
#include "Deck.hpp"
#include "Hand.hpp"

int main(int argc, const char* argv[]) {
	int cmdcount = 0;
	Karte karte(Farbe::Herz, Wert::Dame);
	Deck_Default deck;
	deck.shuffle();
	Hand hand;

	/* MAIN LOOP */
	while (true) {
		std::cout << ++cmdcount << "> ";
		Command cmd;
		if (cmd.get()) {
			if (cmd == "quit") break;
			if (cmd == "karte") std::cout << karte << std::endl;
			if (cmd == "draw") {
				Karte& k = deck.draw();
				hand.take(k);
				std::cout << k << std::endl;
			}
			if (cmd == "hand") std::cout << hand;
			else if (cmd == "play") {
				Farbe farbe;
				Wert wert;
				if (cmd.next(farbe) && cmd.next(wert)) {
					Karte karte(farbe, wert);
					if(hand.play(karte)) std::cout << karte << std::endl;
				}
			}
			if (cmd == "shuffle") deck.shuffle();
		}
	}
	return 0;
}