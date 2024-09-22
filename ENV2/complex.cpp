#include "complex.h"

Complex Complex::operator+(const Complex &other) const {
	return Complex(a + other.a, b + other.b);
}

Complex Complex::operator-(const Complex &other) const {
	return Complex(a - other.a, b - other.b);
}

Complex Complex::operator*(double scalar) const {
	return Complex(a * scalar, b * scalar);
}

double Complex::abs() const {
	return std::sqrt(a * a + b + b);
}


std::ostream &operator<<(std::ostream &out, const Complex &c) {
	out << c.a << " + " << c.b << "i";
	return out;
}



