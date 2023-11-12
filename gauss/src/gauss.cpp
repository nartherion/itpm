#include <gauss/gauss.hpp>

#include <cmath>

#include <optional>

namespace gauss
{

namespace 
{

std::optional<std::size_t> forward_elimination(matrix_t &m)
{
    const std::size_t h = m.size();
    const std::size_t l = m.front().size();

    for (std::size_t i = 0; i < h; ++i)
    {
        std::size_t i_max = i;
        double e_max = m[i][i];

        for (std::size_t j = i + 1; j < h; ++j)
        {
            if (std::abs(m[j][i]) > e_max)
            {
                i_max = j;
                e_max = m[j][i];
            }
        }

        if (m[i][i_max] == 0)
            return i;

        if (i_max != i)
            std::swap(m[i], m[i_max]);

        for (std::size_t j = i + 1; j < h; ++j)
        {
            const double f = m[j][i] / m[i][i];

            for (std::size_t k = i + 1; k < l; ++k)
                m[j][k] -= m[i][k] * f;

            m[j][i] = 0;
        }
    }

    return std::nullopt;
}

std::vector<double> backward_substitution(matrix_t &m)
{
    const std::size_t n = m.size();

    std::vector<double> b(n);

    for (auto a = static_cast<int>(n) - 1; a >= 0; --a)
    {
        const auto i = static_cast<std::size_t>(a);

        b[i] = m[i].back();

        for (std::size_t j = i + 1; j < n; ++j)
            b[i] -= m[i][j] * b[j];

        b[i] /= m[i][i];
    }

    return b;
}

} // namespace

result_t elimination(matrix_t m)
{
    if (const std::optional<std::size_t> sf = forward_elimination(m))
    {
        if (m[sf.value()][m.size()] != 0)
            return error_code::inconsistent_system;

        return error_code::infinite_solutions;
    }

    return backward_substitution(m);

}

} // namespace gauss

