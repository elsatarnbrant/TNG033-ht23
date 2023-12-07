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

Polynomial::Polynomial() : coeff{{{0,0}}} {}

// vi försökte med for_each och skit men funka ej HUUUUUUR????? :((((
// går igenom vektor med par av koffecinter och exponenter, ex. {2,3} => 2x^3
// lägger in koefficinten i vektor på platsen för exponenten ex. {2,3} sätter in 2 på index 3 :D))))
Polynomial::Polynomial(const std::vector<std::pair<int, int>>& terms) {
	for (const auto& e : terms) {
		if (e.second != 0) {
			coeff[e.first] = e.second;
		}
	}
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

Polynomial::operator std::string() const {// gör om polynom till string
	//HEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEELP PLS 

	if (coeff.empty()) {
		return "-1";
	}

	std::string result;

	bool first = true;

	for (const auto& e : coeff) {
		if (!first) {
			result += (e.second >= 0 ? " + " : " - ");
		}
		else {
			first = false;
		}

		result += std::to_string(std::abs(e.second)) + "X^" + std::to_string(e.first);
	}
	if (result == "") {
		return "0";
	}
	else {

		return result;
	}
}

#if 0
Polynomial::operator std::string() const {// gör om polynom till string

	std::string result = "";

	for (std::pair p : coeff) {
		if (p.first == 0) {
			result += p.second;
		} 
		else {
			if (p.second < 0) {
				result += std::format(" - {}X^{}", abs(p.second), p.first);
			}
			else {
				result += std::format(" + {}X^{}", abs(p.second), p.first);
			}
			
		}
	}
	return result;
}
#endif

#if 0
Polynomial operator+=(const Polynomial& rhs);
Polynomial operator-=(const Polynomial& rhs);
Polynomial operator*=(const Polynomial& rhs);

Polynomial operator+=(int rhs);
Polynomial operator-=(int rhs);
Polynomial operator*=(int rhs);

friend Polynomial operator+(Polynomial& lhs, const Polynomial& rhs);
friend Polynomial operator-(Polynomial& lhs, const Polynomial& rhs);
friend Polynomial operator*(Polynomial& lhs, const Polynomial& rhs);

friend Polynomial operator+(Polynomial& lhs, int rhs);
friend Polynomial operator-(Polynomial& lhs, int rhs);
friend Polynomial operator*(Polynomial& lhs, int rhs);

friend Polynomial operator+(int lhs, const Polynomial& rhs);
friend Polynomial operator-(int lhs, const Polynomial& rhs);
friend Polynomial operator*(int lhs, const Polynomial& rhs);

friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);

#endif