/*********************************************************
 * Class Logarithm member functions implementation        *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "logarithm.h"
#include "polynomial.h"

// ADD implementation of the member functions for class Logarithm

double Logarithm::operator()(double x) const {

	double polyValue = (*E)(x);

	return c1 + c2 * std::log(polyValue) / std::log(b);
}

// write out a string
Logarithm::operator std::string() const {

	std::string result = std::format("{:.2f}", c1);

	std::string sign = c2 < 0.0 ? "-" : "+";
	result += std::format(" {} {:.2f} * Log_{}( {} )",sign ,std::abs(c2) ,b ,std::string{ *E }); // static_cast säger till compiler 'lyssna på mig'. tvingar till att converta

	return result;
}

Logarithm* Logarithm::clone() const {
	return new Logarithm{ *this };
}

// destructor
Logarithm::~Logarithm() {

	delete E;
	b = 0;
	c1 = 0;
	c2 = 0;
}

// default constructor
Logarithm::Logarithm() {

	c1 = 0.0;
	c2 = 1.0;
	b = 2;

	std::vector<double> coeff{ 0,1 };

	E = new Polynomial{coeff};
}

// constructor that given an expression e and constats c1 c2 and b>1 creates c1+c2 * logb(e)
Logarithm::Logarithm(const Expression& arg1, double arg2, double arg3, int arg4) {
	
	E = arg1.clone();
	c1 = arg2;
	c2 = arg3;
	b = arg4;
}

// copy constructor
Logarithm::Logarithm(const Logarithm& arg) {

	c1 = arg.c1;
	c2 = arg.c2;
	b = arg.b;
	E = arg.E->clone(); // klonar E??
}

// assignment operator
Logarithm& Logarithm::operator=(const Logarithm& rhs) {

	b = rhs.b;
	c1 = rhs.c1;
	c2 = rhs.c2;
	delete E;
	E = rhs.E->clone();

	return *this;
}

// function  named set_base that modifies the base of the logarithm to a given iniger b' (b'>1)
Logarithm Logarithm::set_base(int x) {

	b = x;
	return *this;
}