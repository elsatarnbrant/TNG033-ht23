/*******************************
 * Lab 3: exercise 2            *
 * Polynomial class             *
 *******************************/

#include "polynomial.h"

Polynomial::Polynomial(int x) { // g�r om int till en polynomial om det beh�vs :)), SLAAAAAY
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

Polynomial::Polynomial(const std::vector<std::pair<int, int>>& terms) { // kopiera fr�n verktorn till mappen
	std::copy(terms.begin(), terms.end(), std::inserter(coeff, end(coeff))); // itererar genom vektorn och stoppar in l�ngst bak i coeff
}

Polynomial::Polynomial(const Polynomial& rhs) { // copy constructor

	coeff = rhs.coeff;
}

Polynomial& Polynomial::operator=(const Polynomial& rhs) { // assignment operator
	// om inte samma s�tt lhs coeff till rhs coeff
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

Polynomial::operator std::string() const {// g�r om polynom till string

	std::string result = "";

	bool first = true;



	for (std::pair p : coeff) { // g�r igenom varje par i coeff
		if (std::ssize(coeff) == 1 && p.second == 0) { // om ett element eller exponent �r noll 
			return "0";
		}

		if (first) { // om f�rsta elementet
			result += std::format("{}X^{}", p.second, p.first);
			first = false;
		}
		else {	
			result += (p.second >= 0 ? " + " : " - "); // best�m tecken som ska ara framf�r
				result += std::format("{}X^{}", abs(p.second), p.first);
		}
	}
	return result;
}


Polynomial Polynomial::operator+=(const Polynomial& rhs) {
	for (const auto& e : rhs.coeff) {
		coeff[e.first] += e.second; // adderar ihop koeff med samma exponent

		if (coeff[e.first] == 0) {
			coeff.erase(e.first); 
		}
	}

	return *this;
}

Polynomial Polynomial::operator-=(const Polynomial& rhs) {
	for (const auto& e : rhs.coeff) {
		coeff[e.first] -= e.second; // subrtaherar koeff med samma exponent

		if (coeff[e.first] == 0) {
			coeff.erase(e.first);
		}
	}

	return *this;
}


Polynomial Polynomial::operator*=(const Polynomial& rhs) {

	Polynomial result;

	if (this->coeff.empty() || rhs.coeff.empty()) { // retunerar tom coeff
		this->coeff.clear();
		return *this;
	}

	Polynomial rhs2 = rhs;

	for (auto e : coeff) { // 

		result += rhs2.multiply(e); // multiplicerar en term med 
	}

	*this = result;

	return *this;
}


Polynomial Polynomial::multiply(std::pair<int, int> terms) {

	Polynomial result;

	for (std::pair<int, int> e : this->coeff) { // f�r varje term i Polynomial this (rhs2), multiplicerar med pair

		int exponent = e.first + terms.first; // adderar exponeterna
		int coefficient = e.second * terms.second; // multiplicerar koeff
		result.coeff[exponent] = coefficient; // l�gger in p� r�tt plats, exp �r index
	}

	return result;
}

bool operator==(const Polynomial& lhs, const Polynomial& rhs) { // kollar om lika
	return lhs.coeff == rhs.coeff;
}

Polynomial operator+(Polynomial lhs, const Polynomial& rhs) { // tv� polynom
	return lhs += rhs;
}

Polynomial operator+(Polynomial& lhs, const int rhs) { // polynom och int
	return lhs += Polynomial(rhs);
}


Polynomial operator-(Polynomial lhs, const Polynomial& rhs) { // tv� polynom
	return lhs -= rhs;
}

// var�fr funkade inte f�rra multiply and assign funktionen????
Polynomial operator*(Polynomial& lhs, const Polynomial& rhs) { 
	Polynomial result = 1; // multiplicerar lhs med 1 f�r att int �ndra lhs
	result *= lhs;
	result *= rhs;
	return result;
}

Polynomial operator*(int lhs, const Polynomial& rhs) { // int, polynomial
	return Polynomial(lhs) *= rhs;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) { // skriver ut polynom med string funktion
	os << std::string(p);
	return os;
}