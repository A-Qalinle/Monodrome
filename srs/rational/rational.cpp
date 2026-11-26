#include "holo/rational.hpp"
#include <climits>
#include <numeric>
#include <ostream>
#include <stdexcept>


namespace holo {
    namespace{

        [[noreturn]] void overflow() {
            throw std::overflow_error(
                "holo::Rational: a number got too big for 64-bit integers"
                "(arbitrary precision arrives in a later milestone)");
        
        }

        long long checked_add(long long a, long long b) {
            if ((b>0 && a > LLONG_MAX - b) || (b < 0 && a < LLONG_MIN - b)) overflow();
            return a + b;
        }

        long long checked_mul(long long a, long long b){
            if (a == 0 || b == 0) return 0;
            if (a > 0) {
                if (b > 0 ? a > LLONG_MAX / b : b < LLONG_MIN / a) overflow();
            } else {
                if (b > 0 ? a < LLONG_MIN / b : b < LLONG_MAX / a) overflow();
            
            }
            return a * b;

        }

        long long checked_neg(long long a) {
            if ( a == LLONG_MIN) overflow();
            return -a;
        }

    } // namespace

    Rational::Rational(long long n) : n_(n), d_(1) { normalize (); }
    
    Rational::Rational(long long n, long long d) : n_(n), d_(d) {
        if (d == 0) throw std::domain_error("holo::Rational: division by zero");
        normalize();
    }

    void Rational::normalize() {
        // keeping LLONG_MIN out means negation and std::gcd are always safe.
        if (n_ == LLONG_MIN || d_ == LLONG_MIN) overflow();
        if (d_ < 0) {
            n_ = -n_;
            d_ = -d_;

        }
        if (n_ == 0) {
            d_ = 1;
            return;
        }

        const long long g = std::gcd(n_, d_);
        if(g > 1) {
            n_/= g;
            d_ /= g;

        }
    }

    double Rational::to_double() const { 
        return static_cast<double>(n_) / static_cast<double>(d_);
    }

    std::string Rational::str() const {
        return d_ == 1 ? std::to_string(n_) : std::to_string(n_) + "/" + std::to_string(d_);
    }

Rational Rational::operator-() const {
    Rational r;
    r.n_ = checked_neg(n_);
    r.d_ = d_;
    return r;
}

Rational& Rational::operator+=(const Rational& o) {
    // a/b + c/d = (a*(d/g) + c*(b/g)) / b*(d/g)), g = gcd(b, d)
    const long long g = std::gcd(d_, o.d_);
    const long long n = checked_add(checked_mul(n_, o.d_ / g), checked_mul(o.n_, d_ / g));
    const long long d = checked_mul(d_, o.d_ / g);
    n_ = n;
    d_ = d;
    normalize();
    return *this;

}

Rational& Rational::operator-=(const Rational& o) {return *this += -o;}

Rational& Rational::operator*=(const Rational& o) {
    //cancel common factors
    const long long g1 = std::gcd(n_, o.d_);
    const long long g2 = std::gcd(o.n_, d_);
    const long long n = checked_mul(n_ / g1, o.n_ / g2);
    const long long d = checked_mul(d_ / g2, o.d_ / g1);
    n_ = n;
    d_ = d;
    normalize();
    return *this;
}

Rational& Rational::operator/=(const Rational& o) {
    if (o.is_zero()) throw std::domain_error("holo::Rational: division by zero");
    return *this *= Rational(o.d_, o.n_);
}

std::ostream& operator<<(std::ostream& os, const Rational& r) { return os << r.str(); }

}
