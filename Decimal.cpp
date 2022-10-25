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
		res = d1.diff(d2);
		res.Sign = d1 >= d2 ? false : true;
	}

	return static_cast<const Decimal>(res);
}

bool operator>(CONST Decimal& d1, CONST Decimal& d2) {
	if (d1.Value.size() > d2.Value.size()) {
		return true;
	}
	else if (d1.Value.size() < d2.Value.size()) {
		return false;
	}

	for (int i = d1.Value.size() - 1; i >= 0; i--) {
		if (d1.Value[i] > d2.Value[i]) {
			return true;
		}
	}

	return false;
}

const Decimal Decimal::diff(const Decimal& other) {
	std::string maxValue = (*this) > other ? Value : other.Value;
	std::string minValue = (*this) > other ? other.Value : Value;

	std::string res = "";

	for (int i = 0; i < minValue.size(); i++) {
		int tmp = toInt(maxValue[i]) - toInt(minValue[i]);
		if (tmp < 0) {
			tmp += 10;
			maxValue[i+1] -= 1;
		}
		res += toChar(tmp);
	}

	for (int i = minValue.size(); i < maxValue.size(); i++) {
		if (maxValue[i] < '0') {
			maxValue[i+1] -= 1;
			maxValue[i] += 10;
		}
		res += maxValue[i];
	}

	while (!res.empty() && res[res.size() - 1] == '0') {
		res.pop_back();
	}

	Decimal Res = Decimal(res);

	return static_cast<const Decimal>(Res);
}

const Decimal Decimal::operator-() const {
	Decimal res = *this;
	res.Sign = !res.Sign;

	return static_cast<const Decimal> (res);
}

size_t Decimal::size() const {
	return Value.size();
}

const Decimal operator-(const Decimal& d1, const Decimal d2) {
	return d1 + (-d2);
}
