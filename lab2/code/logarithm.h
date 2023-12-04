 /*************************
 * Class Logarithm        *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <format>

#include "expression.h"

class Logarithm : public Expression {
    
public:
    double operator()(double x) const override;

    // write out a string
    explicit operator std::string() const override;

    Logarithm* clone() const override;

    // destructor
    ~Logarithm();

    // default constructor
    Logarithm();

    // constructor that given an expression e and constats c1 c2 and b>1 creates c1+c2 * logb(e)
    Logarithm(const Expression& arg1, double arg2, double arg3, int arg4);

    // copy constructor
    Logarithm(const Logarithm& arg);

    // assignment operator
    Logarithm& operator=(const Logarithm& rhs);

    // function  named set_base that modifies the base of the logarithm to a given iniger b' (b'>1)
    Logarithm set_base(int x);


private:
     
    double c1, c2;
    int b;
    Expression* E;
};
