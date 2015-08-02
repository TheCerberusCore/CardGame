
#include "cardgame.hpp"
#include <string>

#ifdef WIN32
#define CLEAR "cls"
#else 
#define CLEAR "clear"
#endif

#include <string>
#include <sstream>
#include <chrono>
using namespace std::chrono;

class Command {
	std::string cmd, cmdline;
	std::stringstream cmdstream;
public:
	bool getcmd(std::istream& i = std::cin) { std::getline(i, cmdline); cmdstream << cmdline; return bool(cmdstream >> cmd); }
	template <typename T> bool getnext(T& next) { return bool(cmdstream >> next); }
	bool operator==(const std::string& str) { return (cmd == str); }
};

template <class time_type>
class Timer {
	time_point<system_clock, time_type> begin, end;
public:
	void start()	{ begin = time_point_cast<time_type>(system_clock::now()); }
	void stop()		{ end = time_point_cast<time_type>(system_clock::now()); }
	__int64 duration() { return (end - begin).count(); }
};

int main(int argc, const char* argv[]) {
	Deck<Wert::Ass, Wert::Koenig> deck;
	Hand hand;
	deck.shuffle();
	Timer<microseconds> t;

	while (true) {
		Command cmd;
		std::cout << "> ";
		if (cmd.getcmd()) {
			t.start();
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
					Hand::iterator it;
					for (it = hand.begin(); it != hand.end(); ++it) if (*it == karte) break;
					hand.erase(it);
					std::cout << karte << std::endl;
				}
			}
			else std::cout << "unknown command!\n";
			t.stop();
			std::cout << "\ttime: " << t.duration() << " microseconds" << std::endl;
		}
	}

#ifdef WIN32
	system("pause");
#endif
	return 0;
}