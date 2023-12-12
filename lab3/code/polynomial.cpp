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

Polynomial::operator std::string() {// gör om polynom till string

	std::string result = "";

	bool first = true;

	for (std::pair p : coeff) {

		if (!first) {
			result += (p.second >= 0 ? " + " : " - ");
		}

		if (std::ssize(coeff) == 1 && p.second == 0) {
			return "0";
		}

		if (p.first == 0) {
			result += std::format("{}X^{}", p.second, 0);
		} 

		else {
			result += std::format("{}X^{}", abs(p.second), p.first);
		}
		first = false;
	}
	return result;
}

#if 1
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

	return* this;
}
Polynomial Polynomial::operator*=(const Polynomial& rhs) {

}

Polynomial Polynomial::operator+=(int rhs) {

}

Polynomial Polynomial::operator-=(int rhs) {

}

Polynomial Polynomial::operator*=(int rhs) {

}

Polynomial Polynomial::operator+(Polynomial& lhs, const Polynomial& rhs) {

}
Polynomial Polynomial::operator-(Polynomial& lhs, const Polynomial& rhs) {

}
Polynomial Polynomial::operator*(Polynomial& lhs, const Polynomial& rhs) {

}

Polynomial Polynomial::operator+(Polynomial& lhs, int rhs) {

}
Polynomial Polynomial::operator-(Polynomial& lhs, int rhs) {

}
Polynomial Polynomial::operator*(Polynomial& lhs, int rhs) {

}

Polynomial Polynomial::operator+(int lhs, const Polynomial& rhs) {

}
Polynomial Polynomial::operator-(int lhs, const Polynomial& rhs) {

}
Polynomial Polynomial::operator*(int lhs, const Polynomial& rhs) {

}

bool operator==(const Polynomial& lhs, const Polynomial& rhs);
std::ostream& operator<<(std::ostream& os, const Polynomial& p);

#endif