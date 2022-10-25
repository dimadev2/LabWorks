#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "Decimal.h"

int main() {
	Decimal d1 = Decimal("123");
	Decimal d2 = Decimal("-123");
	Decimal d3 = Decimal(std::string("29"));

	d1 = d1 + d3;
	d1 = d2 + d3;
	d1 = d2 - d3;
	d1 = d3 - d2;
	d1 = Decimal("132") - Decimal("32");

	return 0;
}