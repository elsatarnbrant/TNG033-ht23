/*********************************************************
 * Class Polynomial member functions implementation       *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "polynomial.h"
#include <format>
// ADD implementation of the member functions for class Polynomial

Polynomial::Polynomial(double real) { // conversion form a real constant into a polynomial
	coeff.push_back(real);
}

Polynomial::Polynomial(const std::vector<double>& v) {
	for (double e : v) {
		coeff.push_back(e);
	}
}

Polynomial& Polynomial::operator=(const Polynomial& rhs) {
	if (this != &rhs) {
		coeff = rhs.coeff;
	}
	return *this;
}

double Polynomial::operator()(double x) const {

	double result = 0.0;
	
	for (int i = 0; i < std::ssize(coeff); i++) {
		result += coeff[i] * std::pow(x, i);
	}
	return result;
}

// add and assign operator
Polynomial& Polynomial::operator+=(const Polynomial& rhs) {

	for (std::size_t i = 0; i < rhs.coeff.size(); i++) { // börjar på i = 0, så länge i < storleken på rhs
		if (i >= this->coeff.size()) { // kollar om vektorn som skickas med har en size mindre eller lika med index e
			coeff.push_back(rhs.coeff[i]);
		}
		else {
			coeff[i] += rhs.coeff[i];
		}
	}
	return *this;
}

Polynomial operator+(const Polynomial& lhs, const Polynomial rhs) { // addition with two polynomials
	Polynomial result{ lhs };
	return result += rhs;
}

Polynomial operator+(const Polynomial& lhs, double rhs) {// addition of of a polynomial with a double
	return lhs + Polynomial(rhs);
}

double Polynomial::operator[](int index) const {
	return coeff[index];
}

double& Polynomial::operator[](int index) {
	return coeff[index];
}

Polynomial::operator std::string() const {
	std::string result = std::format("{:.2f}", coeff[0]);

	for (int i = 1; i < std::ssize(coeff); i++) {
		std::string sign = coeff[i] >= 0 ? "+" : "-";
		result += std::format(" {:s} {:.2f} * X^{:d}", sign, std::abs(coeff[i]), i);
	}
	return result;
}

Polynomial* Polynomial::clone() const {
	return new Polynomial{ *this };
}