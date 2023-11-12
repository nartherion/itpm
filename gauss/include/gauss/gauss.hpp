#include <vector>
#include <variant>

#pragma once

namespace gauss
{

using matrix_t = std::vector<std::vector<double>>;

enum class error_code { inconsistent_system, infinite_solutions };

using result_t = std::variant<error_code, std::vector<double>>;

[[nodiscard]] result_t elimination(matrix_t m);

} // namespace gauss

