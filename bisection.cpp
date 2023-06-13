// Bisection method for finding roots of a polynomial function

#include "bisection.h"

/**
 * This is a constructor for the Bisection class that initializes its member
 * variables.
 *
 * @param coefficients A vector of coefficients of a polynomial function in
 * descending order of degree. For example, if the polynomial is 3x^2 + 2x + 1,
 * the coefficients vector would be {3, 2, 1}.
 * @param a The lower bound of the interval in which we want to find a root of
 * the polynomial.
 * @param b The parameter "b" represents the upper bound of the interval in
 * which the bisection method will search for a root of the polynomial function
 * defined by the given coefficients.
 * @param epsilon Epsilon is the tolerance level or the maximum allowable error
 * in the solution. It is used as a stopping criterion for the bisection
 * algorithm. The algorithm stops when the absolute difference between the upper
 * and lower bounds of the interval is less than or equal to epsilon.
 * @param max_iterations The maximum number of iterations allowed for the
 * bisection algorithm to converge to a solution. If the algorithm does not
 * converge within this number of iterations, it will stop and return an error
 * message.
 */
Bisection::Bisection(std::vector<double> coefficients, double a, double b,
					 double epsilon, long long max_iterations) {
	this->coefficients   = coefficients;
	this->a              = a;
	this->b              = b;
	this->epsilon        = epsilon;
	this->max_iterations = max_iterations;
}

// Find the root of a polynomial function f(x) in the interval [a, b]
// f(a) and f(b) must have opposite signs
// f must be continuous in [a, b]
// f must be differentiable in (a, b)
// f(a) and f(b) must not be 0
// f must be monotonic in [a, b]
double Bisection::solve(short* error_code) {
	// check if error_code is nullptr
	if (error_code == nullptr) {
		std::cout << "error_code is nullptr" << std::endl;
		return std::numeric_limits<double>::quiet_NaN();
	}
	// check if coefficients is empty
	if (coefficients.empty()) {
		std::cout << "coefficients are empty" << std::endl;
		*error_code = 1;
		return std::numeric_limits<double>::quiet_NaN();
	}
	// check if epsilon is empty
	if (epsilon == 0) {
		std::cout << "epsilon is empty" << std::endl;
		*error_code = 2;
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
		*error_code = 4;
		return std::numeric_limits<double>::quiet_NaN();
	}
	// check if f(a) and f(b) are 0
	if (f(a) == 0) {
		*error_code = 0;
		return a;
	}
	if (f(b) == 0) {
		*error_code = 0;
		return b;
	}

	// bisection method
	long long iterations = 0;
	std::cout << "f(x) = ";
	for (int i = 0; i < this->coefficients.size() - 1; i++) {
		std::cout << this->coefficients[i] << " * x^"
				  << this->coefficients.size() - 1 - i << " + ";
	}
	std::cout << this->coefficients.back() << std::endl;

	while (true) {
		double c = (a + b) / 2;
		iterations++;
		if (iterations > max_iterations) {
			std::cout << "max_iterations exceeded" << std::endl;
			*error_code = 55;
			return c;
		}
		if (f(c) == 0) {
			*error_code = 0;
			return c;
		}
		if (f(a) * f(c) < 0) {
			b = c;
		} else {
			a = c;
		}
		if (b - a < epsilon) {
			*error_code = 0;
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
double Bisection::f(const double x) {
	double result = double(0);
	for (int i = 0; i < coefficients.size(); i++) {
		long power         = coefficients.size() - 1 - i;
		double coefficient = coefficients[i];
		result += double(coefficient * pow(x, power));
	}
	return result;
}

/**
 * The function initializes a bisection interval object with given coefficients,
 * interval bounds, and convergence criteria.
 *
 * @param leftCoefficients A vector of coefficients for the left interval value
 * of a coefficient. Each element of the vector represents the coefficient of a
 * term in the polynomial, starting with the constant term and increasing in
 * degree.
 * @param rightCoefficients A vector of coefficients for the right interval
 * value of a coefficient. Each element of the vector represents the coefficient
 * of a term in the polynomial, starting with the constant term and increasing
 * in degree.
 * @param aLeft The left endpoint of the interval for the left variable in the
 * bisection method.
 * @param bLeft The left endpoint of the interval for the right variable in the
 *  bisection interval.
 * @param aRight The right endpoint of the interval for the left variable in the
 * bisection method.
 * @param bRight The right endpoint of the interval for the right variable in
 * the bisection method.
 * @param epsilon The tolerance level for the bisection method. It determines
 * the maximum allowable difference between the upper and lower bounds of the
 * interval. If the difference is less than epsilon, the algorithm stops and
 * returns the midpoint of the interval as the solution.
 * @param max_iterations The maximum number of iterations allowed for the
 * bisection algorithm to converge to a solution.
 */
BisectionInterval::BisectionInterval(std::vector<double> leftCoefficients,
									 std::vector<double> rightCoefficients,
									 double aLeft, double bLeft, double aRight,
									 double bRight, double epsilon,
									 long long max_iterations) {
	this->a.a            = aLeft;
	this->a.b            = aRight;
	this->b.a            = bLeft;
	this->b.b            = bRight;
	this->epsilon        = epsilon;
	this->max_iterations = max_iterations;
	for (int i = 0; i < leftCoefficients.size(); i++) {
		this->coefficients.push_back(interval_arithmetic::Interval(
			leftCoefficients[i], rightCoefficients[i]));
	}
}

/**
 * The function calculates the value of the polynomial function at a given
 * point.
 *
 * @param x The input parameter `x` is an interval of type
 * `interval_arithmetic::Interval<double>`. It represents the interval on which
 * the function `f` is evaluated. The function `f` takes an interval as input
 * and returns an interval as output.
 *
 * @return The function `f` returns an interval arithmetic `Interval<double>`
 * object, which represents the range of possible values of the polynomial
 * function evaluated over the input interval `x`.
 */
interval_arithmetic::Interval<double> BisectionInterval::f(
	const interval_arithmetic::Interval<double> x) {
	// f([x1,x2]) = [min(f(x1),f(x2)), max(f(x1),f(x2))]
	interval_arithmetic::Interval<double> result =
		interval_arithmetic::Interval<double>(0, 0);
	for (int i = 0; i < coefficients.size(); i++) {
		long power = coefficients.size() - 1 - i;
		interval_arithmetic::Interval<double> coefficient = coefficients[i];

		interval_arithmetic::Interval<double> x_val;
		double x_minabs = std::min(abs(x.a), abs(x.b));
		double x_maxabs = std::max(abs(x.a), abs(x.b));

		if (power % 2) {
			x_val = interval_arithmetic::Interval<double>(
				double(pow(x.a, power)), double(pow(x.b, power)));
		} else {
			if (x.a < 0 && x.b > 0) {
				x_val = interval_arithmetic::Interval<double>(
					0, double(pow(x_maxabs, power)));
			} else {
				x_val = interval_arithmetic::Interval<double>(
					double(pow(x_minabs, power)), double(pow(x_maxabs, power)));
			}
		}
		result = result + (coefficient * x_val);
	}

	return result;
}

/**
 * The function implements the bisection method to find the root of a polynomial
 * function with interval coefficients.
 *
 * @param error_code A pointer to a short integer that will be used to return an
 * error code indicating the success or failure of the function. If the pointer
 * is null, an error message will be printed and the function will return NaN.
 *
 * @return an interval of type `interval_arithmetic::Interval<double>` which
 * represents the root of a function obtained using the bisection method. If
 * there is an error, the function returns
 * `std::numeric_limits<interval_arithmetic::Interval<double>>::quiet_NaN()`.
 * The function also sets an error code which is passed as a pointer to the
 * function.
 */
interval_arithmetic::Interval<double> BisectionInterval::solve(
	short* error_code) {
	// check if error_code is nullptr
	/* The code is checking if the pointer `error_code` is `nullptr` (i.e.,
	pointing to nothing). If it is `nullptr`, it prints a message to the console
	and returns a `NaN` (Not a Number) value of type
	`interval_arithmetic::Interval<double>`. */
	if (error_code == nullptr) {
		std::cout << "error_code is nullptr" << std::endl;
		return std::numeric_limits<
			interval_arithmetic::Interval<double>>::quiet_NaN();
	}
	// check if coefficients is empty
	/* The below code is checking if a vector called "coefficients" is empty. If
	it is empty, it prints a message saying "coefficients are empty", sets an
	error code to 1, and returns a NaN (Not a Number) value of type
	"interval_arithmetic::Interval<double>". */
	if (coefficients.empty()) {
		std::cout << "coefficients are empty" << std::endl;
		*error_code = 1;
		return std::numeric_limits<
			interval_arithmetic::Interval<double>>::quiet_NaN();
	}
	// check if epsilon is empty
	/* The code is checking if the variable `epsilon` is equal to zero. If it
	is, it prints a message saying that `epsilon` is empty, sets an error code
	to 2, and returns a NaN (Not a Number) value of type
	`interval_arithmetic::Interval<double>`. */
	if (epsilon == 0) {
		std::cout << "epsilon is empty" << std::endl;
		*error_code = 2;
		return std::numeric_limits<
			interval_arithmetic::Interval<double>>::quiet_NaN();
	}

	// check if f(a) and f(b) have opposite signs
	std::string leftInv;
	std::string rightInv;
	f(a).IEndsToStrings(leftInv, rightInv);
	std::cout << "f(a) = "
			  << "[" << leftInv << " , " << rightInv << "]" << std::endl;
	f(b).IEndsToStrings(leftInv, rightInv);
	std::cout << "f(b) = "
			  << "[" << leftInv << " , " << rightInv << "]" << std::endl;

	// check if f(a) or f(b)  go through 0
	/* The below code is checking if the product of the values of `f(a).a` and
	`f(a).b` is less than zero, and if so, setting the value of `error_code` to
	0 and returning the value of `a`. It then checks if the product of the
	values of `f(b).a` and `f(b).b` is less than zero, and if so, sets the value
	of `error_code` to 0 and returns the value of `b`.
	*/
	if (f(a).a * f(a).b < 0) {
		*error_code = 0;
		return a;
	}
	if (f(b).a * f(b).b < 0) {
		std::cout << "f(b) = " << f(b).a << " , " << f(b).b << std::endl;
		std::cout << "f(b) sign = " << f(b).a * f(b).b << std::endl;
		*error_code = 0;
		return b;
	}

	/* The below code is checking if the function f evaluated at two input
	values a and b have opposite signs. If they do not have opposite signs, it
	prints an error message, sets an error code to 4, and returns a NaN (Not a
	Number) value. This code is likely part of a larger algorithm for finding
	the root of a function using interval arithmetic. */
	if (f(a).a * f(b).a > 0) {
		std::cout << "f(a) and f(b) must have opposite signs" << std::endl;
		*error_code = 4;
		return std::numeric_limits<
			interval_arithmetic::Interval<double>>::quiet_NaN();
	}
	if (f(a).b * f(b).b > 0) {
		std::cout << "f(a) and f(b) must have opposite signs" << std::endl;
		*error_code = 4;
		return std::numeric_limits<
			interval_arithmetic::Interval<double>>::quiet_NaN();
	}

	// bisection method
	long long iterations = 0;
	interval_arithmetic::Interval<double> inv0 =
		interval_arithmetic::Interval<double>(0, 0);
	interval_arithmetic::Interval<double> inv2 =
		interval_arithmetic::Interval<double>(2, 2);

	std::cout << "f(x) = ";
	for (int i = 0; i < this->coefficients.size() - 1; i++) {
		std::cout << "[" << this->coefficients[i].a << " , "
				  << this->coefficients[i].b << "]"
				  << " * x^" << this->coefficients.size() - 1 - i << " + ";
	}
	std::cout << "[" << this->coefficients.back().a << " , "
			  << this->coefficients.back().b << "]" << std::endl;

	interval_arithmetic::Interval<double> c;
	interval_arithmetic::Interval<double> f_c;

	/* The below code is implementing the bisection method for finding the root
	of a function. It repeatedly bisects an interval [a,b] and checks if the
	midpoint of the interval contains the root. If the midpoint contains the
	root, it returns the midpoint as the root. If not, it updates the interval
	by setting either a or b to the midpoint, depending on which subinterval
	contains the root. The process continues until the difference between b and
	a is less than a specified tolerance (epsilon) or the maximum number of
	iterations is reached. */
	while (abs(b.a - a.a) > epsilon && abs(b.b - a.b) > epsilon) {
		// set c to interval midpoint of two intervals
		c = (a + b) / inv2;
		iterations++;
		// if iterations > max_iterations end computation
		if (iterations > max_iterations) {
			std::cout << "max_iterations exceeded" << std::endl;
			*error_code = 55;
			return c;
		}

		f_c = f(c);

		// check if f(c) contains 0
		if (f_c.a * f_c.b < 0) {
			*error_code = 0;
			return c;
		}

		// if left interval contains 0
		// else a = c
		if (f(a).b * f_c.a < 0) {
			b = c;
		} else {
			a = c;
		}
	}
	*error_code = 0;
	return (a + b) / inv2;
}