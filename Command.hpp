#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <string>
#include <sstream>

class Command {
	std::string cmd, cmdline;
	std::stringstream cmdstream;
public:
	Command() = default;
	~Command() = default;
	bool get(std::istream& i = std::cin) { std::getline(i, cmdline); cmdstream << cmdline; return (cmdstream >> cmd) ? true : false; }
	template <typename T>
	bool next(T& next) { return (cmdstream >> next) ? true : false; }
	bool operator==(const std::string& str) { return (cmd == str) ? true : false; }
};

#endif//COMMAND_HPP