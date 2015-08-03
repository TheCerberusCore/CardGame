#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>

class DeckIsEmptyExcept : public std::exception {
public:
	virtual const char* what() const noexcept override {
		return "No more cards available!";
	}
};

#endif//EXCEPTIONS_HPP