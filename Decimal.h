#pragma once

#include <string>
#include <stdexcept>

inline int toInt(char c) {
	return c - '0';
}

inline char toChar(int v) {
	return v + '0';
}

class Decimal {
public:
	Decimal();
	Decimal(const char*);
	Decimal(const std::string);
	Decimal(const Decimal&);

	Decimal& operator=(const Decimal&);

	CONST Decimal operator-() const;

	friend const Decimal operator+(const Decimal&, const Decimal&);
	friend const Decimal operator-(const Decimal&, const Decimal&);
	friend bool operator>(CONST  Decimal&, CONST Decimal&);
	
	//friend std::ostream& operator<<(std::ostream&, const Decimal&);

	size_t size() const;
private:
	std::string Value;
	bool Sign = false;
	const Decimal sum(const Decimal&) const;
	const Decimal diff(const Decimal&) const;

	std::string reverseValue(const std::string& s) const;
};
