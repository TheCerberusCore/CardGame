
#include "cardgame.hpp"
#include <string>

#ifdef WIN32
#define CLEAR "cls"
#else 
#define CLEAR "clear"
#endif

#include <string>
#include <sstream>

class Command {
	std::string cmd, cmdline;
	std::stringstream cmdstream;
public:
	bool getcmd(std::istream& i = std::cin) { std::getline(i, cmdline); cmdstream << cmdline; return bool(cmdstream >> cmd); }
	template <typename T> bool getnext(T& next) { return bool(cmdstream >> next); }
	bool operator==(const std::string& str) { return (cmd == str); }
};

int main(int argc, const char* argv[]) {
	Deck<Wert::Ass, Wert::Koenig> deck;
	Hand hand;
	deck.shuffle();

	while (true) {
		Command cmd;
		std::cout << "> ";
		if (cmd.getcmd()) {
			if (cmd == "quit") break;
			else if (cmd == "draw") { Karte draw = deck.draw(); hand.insert(draw); std::cout << draw << std::endl; }
			else if (cmd == "shuffle") deck.shuffle();
			else if (cmd == "hand") std::cout << hand;
			else if (cmd == "clear") system(CLEAR);
			else if (cmd == "play") {
				Farbe farbe;
				Wert wert;
				if (cmd.getnext(farbe) && cmd.getnext(wert)) {
					Karte karte(farbe, wert);
					hand.erase(karte);
					std::cout << karte << std::endl;
				}
			}
			else std::cout << "unknown command!\n";
		}
	}

#ifdef WIN32
	system("pause");
#endif
	return 0;
}