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
			  double epsilon, long long max_iterations = 100000);
	// Find the root of a polynomial function f(x) in the interval [a, b]
	// f(a) and f(b) must have opposite signs
	// f must be continuous in [a, b]
	// f must be differentiable in (a, b)
	// f(a) and f(b) must not be 0
	// f must be monotonic in [a, b]
	double solve(short *error_code);

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

	// f(x) = a_n * x^n + a_(n-1) * x^(n-1) + ... + a_1 * x + a_0
	double f(const double x);

private:
	std::vector<double> coefficients;
	double a;          // left endpoint of the interval
	double b;          // right endpoint of the interval
	double epsilon;    // tolerance
	double x;          // midpoint of the interval
	long long max_iterations;
};
#include "Interval.h"
// Bisection method for finding roots of a polynomial function using Interval
// arithmetic
class BisectionInterval {
public:
	BisectionInterval()  = default;
	~BisectionInterval() = default;

	// constructor
	BisectionInterval(std::vector<double> leftCoefficients,
					  std::vector<double> rightCoefficients, double aLeft,
					  double bLeft, double aRight, double bRight,
					  double epsilon, long long max_iterations = 10000);

	// Find the root of a polynomial function f(x) in the interval [ [aL,aR],
	// [bL,bR] ] f(a) and f(b) must have opposite signs continuously f must be
	// continuous in [a, b] f must be differentiable in (a, b) f(a) and f(b)
	// must not be 0

	interval_arithmetic::Interval<double> solve(short *error_code);
	interval_arithmetic::Interval<double> f(
		const interval_arithmetic::Interval<double> x);

private:
	std::vector<interval_arithmetic::Interval<double>> coefficients;
	interval_arithmetic::Interval<double> a;    // left endpoint of the interval
	interval_arithmetic::Interval<double>
		b;             // right endpoint of the interval
	double epsilon;    // tolerance
	interval_arithmetic::Interval<double> x;    // midpoint of the interval
	long long max_iterations;
};

#endif    // !BISECTION_H