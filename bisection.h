// Bisection method for finding roots of a polynomial function

#ifndef BISECTION_H
#define BISECTION_H

#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>

// #include "Interval.h"

class Bisection {
public:
	Bisection()  = default;
	~Bisection() = default;

	// constructor
	Bisection(std::vector<double> coefficients, double a, double b,
			  double epsilon);
	// Find the root of a polynomial function f(x) in the interval [a, b]
	// f(a) and f(b) must have opposite signs
	// f must be continuous in [a, b]
	// f must be differentiable in (a, b)
	// f(a) and f(b) must not be 0
	// f must be monotonic in [a, b]
	double solve();

	// coefficients
	void push_coefficient(double coefficient);
	double pop_coefficient();
	void clear_coefficients();
	void unshift_coefficient(double coefficient);
	double shift_coefficient();

	// setter
	void set_coefficients(std::vector<double> coefficients);
	void set_a(double a);
	void set_b(double b);
	void set_epsilon(double epsilon);

	// getter
	int get_polynomial_degree();
	std::vector<double> get_coefficients();
	double get_a();
	double get_b();
	int get_degree();

private:
	std::vector<double> coefficients;
	double a;          // left endpoint of the interval
	double b;          // right endpoint of the interval
	double epsilon;    // tolerance
	double x;          // midpoint of the interval

	// f(x) = a_n * x^n + a_(n-1) * x^(n-1) + ... + a_1 * x + a_0
	double f(double x);
};

#endif    // !BISECTION_H