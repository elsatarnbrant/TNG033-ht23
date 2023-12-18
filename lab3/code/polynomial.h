/*******************************
 * Lab 3: exercise 2            *
 * Polynomial class             *
 * Header file                  *
 *******************************/

#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>
#include <format>
#include <string>

class Polynomial {

public:
	Polynomial(int x); // gör om int till en polynomial om det behövs :)), SLAAAAAY

	Polynomial(int x, int y);

	Polynomial(); // default constructor

	Polynomial(const std::vector<std::pair<int, int>>& terms);

	Polynomial multiply(std::pair<int, int>);

	Polynomial(const Polynomial& rhs); // copy constructor

	Polynomial& operator=(const Polynomial& rhs); // assignment operator

	int degree() const; // returns the degree of the polynomial

	explicit operator std::string() const; // gör om polynom till string

	
	Polynomial operator+=(const Polynomial& rhs);
	Polynomial operator-=(const Polynomial& rhs);
	Polynomial operator*=(const Polynomial& rhs);

	friend Polynomial operator+(Polynomial lhs, const Polynomial& rhs);

	friend Polynomial operator+(Polynomial& lhs, const int rhs);

	friend Polynomial operator-(Polynomial lhs, const Polynomial& rhs);

	friend Polynomial operator*(Polynomial& lhs, const Polynomial& rhs);

	friend Polynomial operator*(int lhs, const Polynomial& rhs);

	friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);

	friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);



private:
	std::map<int, int> coeff;
};
 