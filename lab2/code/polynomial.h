/*************************
 * Class Polynomial       *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>
#include <vector>

#include "expression.h"

class Polynomial : public Expression {

public:
    Polynomial(double real); // conversion form a real constant into a polynomial

    Polynomial(const std::vector<double>& v);

    Polynomial(const Polynomial& poly) = default; // copy constructor

    // assignment operator
    Polynomial& operator=(const Polynomial& rhs);

    // add and assign operator
    Polynomial& operator+=(const Polynomial& rhs);

    // frend ger tillåtelse att ändra i private vektor
    friend Polynomial operator+(const Polynomial& lhs, const Polynomial rhs); // addition with two polynomials
    friend Polynomial operator+(const Polynomial& lhs, double rhs); // addition of of a polynomial with a double

    double operator[](int index) const; 
    double& operator[](int index); 

    // override från expression.h, för att 
    double operator()(double x) const override;

    explicit operator std::string() const override;

    Polynomial* clone() const override;

private:
    std::vector<double> coeff;
};
