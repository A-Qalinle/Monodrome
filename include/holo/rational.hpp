#pragma once

#include <iosfwd>
#include <string>

namespace holo {



class Rational {

public:
    Rational(long long n = 0); // implicit so 3 * P works
    Rational(long long n, long long d);

    long long num() const {return n_; }
    long long den() const {return d_; }
    bool is_zero() const {return n_ == 0;}
    bool is_integer() const { return d_ == 1;}
    double to_double() const;
    std::string str() const; // "3", "-1/2"

    Rational operator-() const;
    Rational& operator+=(const Rational& o);
    Rational& operator-=(const Rational& o);
    Rational& operator*=(const Rational& o);
    Rational& operator/=(const Rational& o);

    friend Rational operator+(Rational a, const Rational& b) { return a += b; }
    friend Rational operator-(Rational a, const Rational& b) { return a -= b; }
    friend Rational operator*(Rational a, const Rational& b) { return a *= b; }
    friend Rational operator/(Rational a, const Rational& b) { return a /= b; }
    friend bool operator==(const Rational& a, const Rational& b) {
        return a.n_ == b.n_ && a.d_ == b.d_;
    }
    friend bool operator!=(const Rational& a, const Rational& b) { return !(a==b);}

private:
    long long n_ = 0;
    long long d_ = 1;
    void normalize();
};

std::ostream& operator<<(std::ostream& os, const Rational& r);

} 