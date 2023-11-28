/*************************
 * Class Expression       *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>

constexpr double Epsilon = 1.0e-5;

class Expression {
public:
    // Destructor
    virtual ~Expression() {
        --count_expressions;
    }

    // ADD OTHER MEMBER FUNCTIONS

    bool isRoot(double x) const;

    explicit operator std::string() const; // fråga micke :))

    virtual double operator()(double x) const = 0; // define a base case for the function call operator

    friend std::ostream& operator<<(std::ostream& os, const Expression& expr); // va??
    
    virtual Expression* clone() const = 0;

    // Return number of existing instances of class Expression
    // Used only for debug purposes
    static std::size_t get_count_expressions();

protected:
    // Default constructor
    Expression() {
        ++count_expressions;
    }

    // Copy constructor
    Expression(const Expression&) {
        ++count_expressions;
    }

    // total number of existing expressions -- only to help to detect bugs in the code
    static std::size_t count_expressions;
};
