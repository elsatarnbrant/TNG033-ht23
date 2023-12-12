/*******************************
 * Lab 3: exercise 2            *
 * Polynomial class             *
 *******************************/

#include "polynomial.h"

Polynomial::Polynomial(int x) { // gör om int till en polynomial om det behövs :)), SLAAAAAY
	if (x != 0) {
		coeff[0] = x;
	}
}

Polynomial::Polynomial(int x, int y) {
	if (x != 0) {
		coeff[y] = x;
	}
}

Polynomial::Polynomial() : coeff{ {{0,0}} } {}

Polynomial::Polynomial(const std::vector<std::pair<int, int>>& terms) { // kopiera från verktorn till mappen
	std::copy(terms.begin(), terms.end(), std::inserter(coeff, end(coeff))); // itererar genom vektorn och stoppar in längst bak i coeff
}

Polynomial::Polynomial(const Polynomial& rhs) { // copy constructor

	coeff = rhs.coeff;
}

Polynomial& Polynomial::operator=(const Polynomial& rhs) { // assignment operator
	// om inte samma sätt lhs coeff till rhs coeff
	if (this != &rhs) {
		coeff = rhs.coeff;
	}
	return *this;
}

int Polynomial::degree() const { // returns the degree of the polynomial

	if (coeff.empty()) {
		return -1;
	}

	int degree = 0;

	for (const auto& e : coeff) {
		if (e.first > degree) {
			degree = e.first;
		}
	}

	return degree;
}

Polynomial::operator std::string() {// gör om polynom till string

	std::string result = "";

	bool first = true;



	for (std::pair p : coeff) {
		if (std::ssize(coeff) == 1 && p.second == 0) {
			return "0";
		}

		if (first) {
			result += std::format("{}X^{}", p.second, p.first);
			first = false;
		}
		else {	
			result += (p.second >= 0 ? " + " : " - ");
				result += std::format("{}X^{}", abs(p.second), p.first);
		}
	}
	return result;
}


Polynomial Polynomial::operator+=(const Polynomial& rhs) {
	for (const auto& e : rhs.coeff) {
		coeff[e.first] += e.second;

		if (coeff[e.first] == 0) {
			coeff.erase(e.first);
		}
	}

	return *this;
}

Polynomial Polynomial::operator-=(const Polynomial& rhs) {
	for (const auto& e : rhs.coeff) {
		coeff[e.first] -= e.second;

		if (coeff[e.first] == 0) {
			coeff.erase(e.first);
		}
	}

	return*this;
}


Polynomial Polynomial::operator*=(const Polynomial& rhs) {

	Polynomial result;

	if (this->coeff.empty() || rhs.coeff.empty()) {
		this->coeff.clear();
		return *this;
	}

	Polynomial rhs2 = rhs;

	for (auto e : coeff) {

		result += rhs2.multiply(e);
	}

	*this = result;

	return *this;
}


Polynomial Polynomial::multiply(std::pair<int, int> terms) {

	Polynomial result;

	for (std::pair<int, int> e : this->coeff) {
		int exponent = e.first + terms.first;
		int coefficient = e.second * terms.second;
		result.coeff[exponent] = coefficient;
	}

	return result;
}

bool operator==(const Polynomial& lhs, const Polynomial& rhs) {

	return lhs.coeff == rhs.coeff;

}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
	os << std::string(p);
	return os;
}
