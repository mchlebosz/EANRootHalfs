// Bisection method for finding roots of a polynomial function

#include "bisection.h"

Bisection::Bisection(std::vector<double> coefficients, double a, double b,
					 double epsilon) {
	this->coefficients = coefficients;
	this->a            = a;
	this->b            = b;
	this->epsilon      = epsilon;
}

// Find the root of a polynomial function f(x) in the interval [a, b]
// f(a) and f(b) must have opposite signs
// f must be continuous in [a, b]
// f must be differentiable in (a, b)
// f(a) and f(b) must not be 0
// f must be monotonic in [a, b]
double Bisection::solve() {
	// check if coefficients is empty
	if (coefficients.empty()) {
		std::cout << "coefficients is empty" << std::endl;
		return std::numeric_limits<double>::quiet_NaN();
	}
	// check if epsilon is empty
	if (epsilon == 0) {
		std::cout << "epsilon is empty" << std::endl;
		return std::numeric_limits<double>::quiet_NaN();
	}
	// check if polynomial_degree is negative
	if (coefficients.size() - 1 < 0) {
		std::cout << "polynomial_degree must be non-negative" << std::endl;
		return std::numeric_limits<double>::quiet_NaN();
	}
	// check if a is greater than b
	// if so, swap a and b
	if (a > b) {
		double temp = a;
		a           = b;
		b           = temp;
	}
	// check if f(a) and f(b) have opposite signs
	std::cout << "f(a) = " << f(a) << std::endl;
	std::cout << "f(b) = " << f(b) << std::endl;
	if (f(a) * f(b) >= 0) {
		std::cout << "f(a) and f(b) must have opposite signs" << std::endl;
		return std::numeric_limits<double>::quiet_NaN();
	}
	// check if f(a) and f(b) are 0
	if (f(a) == 0) {
		return a;
	}
	if (f(b) == 0) {
		return b;
	}

	// bisection method
	std::cout << "f(x) = ";
	for (int i = 0; i < this->coefficients.size() - 1; i++) {
		std::cout << this->coefficients[i] << " * x^"
				  << this->coefficients.size() - 1 - i << " + ";
	}
	std::cout << this->coefficients.back() << std::endl;

	while (true) {
		double c = (a + b) / 2;
		if (f(c) == 0) {
			return c;
		}
		if (f(a) * f(c) < 0) {
			b = c;
		} else {
			a = c;
		}
		if (b - a < epsilon) {
			return c;
		}
	}
}

// setter
void Bisection::set_coefficients(std::vector<double> coefficients) {
	this->coefficients = coefficients;
}
void Bisection::set_a(double a) {
	this->a = a;
}
void Bisection::set_b(double b) {
	this->b = b;
}

// getter
int Bisection::get_degree() {
	return this->coefficients.size() - 1;
}
std::vector<double> Bisection::get_coefficients() {
	return coefficients;
}
double Bisection::get_a() {
	return a;
}
double Bisection::get_b() {
	return b;
}

void Bisection::push_coefficient(double coefficient) {
	this->coefficients.push_back(coefficient);
}
double Bisection::pop_coefficient() {
	double coefficient = this->coefficients.back();
	this->coefficients.pop_back();
	return coefficient;
}
void Bisection::clear_coefficients() {
	this->coefficients.clear();
}
void Bisection::unshift_coefficient(double coefficient) {
	this->coefficients.insert(this->coefficients.begin(), coefficient);
}
double Bisection::shift_coefficient() {
	double coefficient = this->coefficients.front();
	this->coefficients.erase(this->coefficients.begin());
	return coefficient;
}

// f(x) = a_n * x^n + a_(n-1) * x^(n-1) + ... + a_1 * x + a_0
double Bisection::f(double x) {
	double result = 0;
	for (int i = 0; i < this->coefficients.size(); i++) {
		result +=
			this->coefficients[i] * pow(x, this->coefficients.size() - 1 - i);
	}
	return result;
}