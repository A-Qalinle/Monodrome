#pragma once

#include "holo/rational.hpp"

#include <iosfwd>
#include <string>
#include <vector>
#include <map>

namespace holo {
    using Exponent = std::vector<int>;


class Polynomial {

 public:
   
 using Terms = std::map<Exponent, Rational>;
 explicit Polynomial(std::vector<std::string> names);

 const std::vector<std::string>& names() const { return names_;}
 std::size_t nums_vars() const { return names_.size();}
 const Terms& terms() const { return terms_;}


 void add_term(const Exponent& e, const Rational& c);

 bool is_zero() const { return terms_.empty(); }
 int total_degree() const;
 Polynomial derivative(std::size_t i) const;
 std::string str() const;

 Polynomial operator-() const;
 Polynomial& operator+=(const Polynomial& o);
 Polynomial& operator-=(const Polynomial& o);
 Polynomial& operator*=(const Polynomial& o);
 friend Polynomial operator+(Polynomial a, const Polynomial& b) {return a += b;}
 friend Polynomial operator-(Polynomial a, const Polynomial& b) {return a -= b;}
 friend Polynomial operator*(Polynomial a, const Polynomial& b) {return a *= b;}
 friend bool operator==(const Polynomial& a, const Polynomial& b) {
    return a.names_ == b.names_ && a.terms_ == b.terms_;
 }
 friend bool operator!=(const Polynomial& a, const Polynomial& b) { return !(a == b); }


 private:
 
 std::vector<std::string> names_;
 Terms terms_;
 void require_same_ring(const Polynomial& o) const;
};

std::ostream& operator<<(std::ostream& os, const Polynomial& p);

}


