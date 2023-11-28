/*********************************************************
 * Class Polynomial member functions implementation       *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "polynomial.h"

// ADD implementation of the member functions for class Polynomial

Polynomial::Polynomial(double real) : Expression{} { // conversion form a real constant into a polynomial
	coeff.push_back(real);
}

Polynomial::Polynomial(const std::vector<double>& v) {
	for (double e : v) {
		coeff.push_back(e);
	}
}

Polynomial& operator=(const Polynomial& rhs) {
	
	
	return *this;
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

Polynomial operator+(const Polynomial& lhs, const Polynomial rhs); { // addition with two polynomials
	Polynomial result(*this);
	return result += rhs;
}
Polynomial operator+(const Polynomial& lhs, double rhs); {// addition of of a polynomial with a double
	return lhs + Polynomial(rhs);
}

const double& operator[](int index) const; // fattar noll
double& operator[](int index); // bara accepteptera det

operator std::string() const; // qué?