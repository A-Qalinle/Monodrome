#pragma once

#include "holo/rational.hpp"
#include <string>
#include <utility>
#include <vector>

namespace holo::detail {

    std::string format_power(const std::string& name, int power);
    std::string join_function(const std::vector<std::string>& factors);
    std::string format_sums(const std::vector<std::pair<Rational, std::string>>& terms);

}
