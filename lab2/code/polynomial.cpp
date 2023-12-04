/*********************************************************
 * Class Polynomial member functions implementation       *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "polynomial.h"
#include <format>

 // Constructor: Converts a real number to a constant polynomial
Polynomial::Polynomial(double real) {
	coeff.push_back(real);
}

// Same as over except vector and vector
// Constructor: Creates a polynomial from a vector of coefficients
Polynomial::Polynomial(const std::vector<double>& v) {
	for (double e : v) {
		coeff.push_back(e);
	}
}


//assignment operator
// kollar ifall lhs = rhs
Polynomial& Polynomial::operator=(const Polynomial& rhs) {
	// om inte samma s�tt lhs coeff till rhs coeff
	if (this != &rhs) {
		coeff = rhs.coeff;
	}
	return *this;
}

double Polynomial::operator()(double x) const { // skickar med en variabel f�r att ber�kna polynomet

	double result = 0.0;
	
	for (int i = 0; i < std::ssize(coeff); i++) {
		// r�knar ut polynomen
		result += coeff[i] * std::pow(x, i);
	}
	return result;
}

// add and assign operator, �ndrar nuvararande polynom
Polynomial& Polynomial::operator+=(const Polynomial& rhs) {

	for (std::size_t i = 0; i < rhs.coeff.size(); i++) { // b�rjar p� i = 0, s� l�nge i < storleken p� rhs
		if (i >= this->coeff.size()) { // kollar om vektorn som skickas med har en size mindre eller lika med index i
			coeff.push_back(rhs.coeff[i]); // om x^i inte finns l�gg i vektorn
		}
		else {
			coeff[i] += rhs.coeff[i]; // annars addera till existerande
		}
	}
	return *this;
}

// skapar ett nytt polynom utan att �ndra de gamla genom att addera ihop dem
Polynomial operator+(const Polynomial& lhs, const Polynomial rhs) { // addition with two polynomials
	Polynomial result{ lhs }; // kopierar lhs
	return result += rhs; // adderar med rhs
}

Polynomial operator+(const Polynomial& lhs, double rhs) {// addition of of a polynomial with a double
	return lhs + Polynomial(rhs); // converts a double to a polynomial and adds together
}

double Polynomial::operator[](int index) const { // tar framm ett viss koefficient, read only
	return coeff[index];
}

double& Polynomial::operator[](int index) {// tar framm ett viss koefficient, kan �ndra koefficient
	return coeff[index];
}

// g�r polynom till string
Polynomial::operator std::string() const {
	std::string result = std::format("{:.2f}", coeff[0]); // b�rjar med konstanten

	for (int i = 1; i < std::ssize(coeff); i++) {
		std::string sign = coeff[i] >= 0 ? "+" : "-"; // best�mmer tecken f�r varje
		result += std::format(" {:s} {:.2f} * X^{:d}", sign, std::abs(coeff[i]), i); // skriver ut
	}
	return result;
}

// klonar polynomen med hj�lp av copy constructorn (default)
Polynomial* Polynomial::clone() const {
	return new Polynomial{ *this };
}