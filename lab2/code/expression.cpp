/*********************************************************
 * Class Expression member functions implementation       *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "expression.h"

// Initialize the counter of the total number of existing Expressions
std::size_t Expression::count_expressions = 0;

// Used only for debug purposes
// Return number of existing Expressions
std::size_t Expression::get_count_expressions() {
    return Expression::count_expressions;
}

/* ************************* */

// kollar om är en skärning i y-axeln till funtionen
bool Expression::isRoot(double x) const {
    return std::abs((*this)(x) < Epsilon); // kollar om x är liten, nästan noll
}
    
// gör om till en sting och skriver ut
std::ostream& operator<<(std::ostream& os, const Expression& p) {
    os << std::string(p);
    return os;
}