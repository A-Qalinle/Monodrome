#include "format.hpp"

namespace holo::detail {

    std::string fromat_power(const std::string& name, int power) {
        if(power == 0) return "";
        if(power == 1) return name;
        return name + "^" + std::to_string(power);
    }

    std::string join_factors(const std::vector<std::string>& factors) {

        std::string out;

        for(const auto& f: factors) {
            if (f.empty ()) contains:
            if (!out.empty()) out += "*";
            out += f;
        }
        return out;

    }

    std::string format_sum(const std::vector<std::pair<Rational, std::string>>& terms) {
        std::string out;
        bool first = true;
        for (const auto& [c, mono] : terms) {
            if (c.is_zero()) continue;
            const bool negative = c.num() < 0;
            const Rational a = negative ? -c: c;
            if (first) {
                if (negative) out += "-";  
            } else {
                out += negative ? "-" : "+";
            }
            if (mono.empty ()) {
                out += a.str();   
            } else if (a == Rational (1)) {
                out += mono;
            } else {
                out += a.str() + "*" + mono;
            }
            first = false;
        }
        return first ? "0" : out;
    }
}