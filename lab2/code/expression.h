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

    bool isRoot(double x) const;

    // viritual används när andra klasser ska kunna override funktionen
    virtual explicit operator std::string() const = 0; 

    virtual double operator()(double x) const = 0; // define a base case for the function call operator
    
    virtual Expression* clone() const = 0;

    // kan access private och protected men används för att göra funtionen till non-member function 
    friend std::ostream& operator<<(std::ostream& os, const Expression& expr);

    Expression& operator=(const Expression& ) const = delete; // define a base case for the function call operator

 
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
