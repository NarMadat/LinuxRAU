#pragma once

#include <iostream>
#include <cmath>

class Complex {
public:
    Complex(double a = 0, double b = 0) : a(a), b(b) {}

    Complex operator+(const Complex &other) const;
    Complex operator-(const Complex &other) const;
    Complex operator*(double scalar) const;
    double abs() const;

    friend std::ostream &operator<<(std::ostream &out, const Complex &c);

private:
    double a, b;
};

