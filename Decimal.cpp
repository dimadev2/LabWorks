#include "Decimal.h"

Decimal::Decimal() :
	Value("0")
{}

Decimal::Decimal(const char* val) {
//	if (val == nullptr || strcmp(val, "")) {
//		throw std::invalid_argument("Bad const char* value");
//	}

	if (val[0] == '-') {
		Sign = true;
		Value = (val + 1);
	}
	else {
		Value = val;
	}
	Value = reverseValue(Value);
}

Decimal::Decimal(const std::string s) {
	if (s == "") {
		throw std::invalid_argument("Bad std::string value");
	}

	if (s[0] == '-') {
		Sign = true;
		Value = (s.c_str() + 1);
	}
	else {
		Value = s;
	}
	
	Value = reverseValue(Value);
}

Decimal::Decimal(const Decimal& other) :
	Value(other.Value),
	Sign(other.Sign)
{}

Decimal& Decimal::operator=(const Decimal& other) {
	Value = other.Value;
	Sign = other.Sign;

	return *this;
}

const Decimal Decimal::sum(const Decimal& other) const {
	std::string maxValue = Value.size() > other.Value.size() ? Value : other.Value;
	std::string minValue = Value.size() <= other.Value.size() ? Value : other.Value;

	unsigned int maxSize = maxValue.size();
	unsigned int minSize = minValue.size();

	std::string res;

	unsigned int carryFlag = 0;
	for (unsigned int i = 0; i < minSize; i++) {
		unsigned int tmp = toInt(Value[i]) + toInt(other.Value[i]) + carryFlag;
		if (tmp > 9) {
			carryFlag = 1;
		}
		else {
			carryFlag = 0;
		}
		res += toChar(tmp % 10);
	}

	for (unsigned int i = minSize; i < maxSize; i++) {
		unsigned int tmp = toInt(maxValue[i]) + carryFlag;
		if (tmp > 9) {
			carryFlag = 1;
		}
		else {
			carryFlag = 0;
		}
		res += toChar(tmp % 10);
	}

	if (carryFlag) {
		res += '1';
	}

	return static_cast<const Decimal>(Decimal(res));
}

std::string Decimal::reverseValue(const std::string& s) const {
	std::string res = "";

	int i = s.size() - 1;
	while (i >= 0) {
		res += s[i];
		i--;		
	}

	return res;
}

const Decimal operator+(const Decimal& d1, const Decimal& d2) {
	Decimal res;
	
	if (d1.Sign == d2.Sign) {
		res = d1.sum(d2);
		res.Sign = d1.Sign;
	}
	else {
//		res = d1.diff(d2);
//		res.Sign = d1 >= d2 ? false : true;
		;
	}

	return static_cast<const Decimal>(res);
}
