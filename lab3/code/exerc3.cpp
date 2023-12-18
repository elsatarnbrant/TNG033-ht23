/*********************************************
 * Lab 3: exercise 3                         *
 * Program to compute an approximation of pi *
 * STL-algorithms should be used             *
 *********************************************/

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <format>

double calculate(double k) {
    double const factor{ 8.0 * k };
    double const init{ 4.0 / (factor + 1.0) - 2.0 / (factor + 4.0) - 1.0/ (factor + 5.0) - 1.0 / (factor + 6.0)};
    return init;
}

int main() {
    std::cout << "Enter number of terms: ";
    int n;
    std::cin >> n;

    std::vector<double> terms(n); // vector with maximum slots of n
    std::iota(begin(terms), end(terms), 0.0); // fills the vector from first to last starting with value then increasing

    std::transform(begin(terms), end(terms), begin(terms), [](double& k) {
        return calculate(k);
        });

    std::vector<double> power_terms(n);

    std::transform(begin(terms), end(terms), begin(power_terms), [i = 0](double) mutable { // mutable tillåter i att ändras
        return std::pow(16.0, -i++);
    });

    double result = std::inner_product(begin(terms), end(terms), begin(power_terms), 0.0);

    std::cout << std::format("{:.15f} \n", result);
}
