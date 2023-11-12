#include <cmath>

#include <gtest/gtest.h>

#include <gauss/gauss.hpp>

TEST(gauss_suite, check_equation_system_solution)
{
    const gauss::matrix_t m
    {
        { 7.0, 6.0, 1.0, 6.0 },
        { 3.0, 6.0, 5.0, 2.0 },
        { 1.0, 4.0, 5.0, 8.0 }
    };

    const std::vector<double> expected { 12.5, -15.5, 11.5 };

    const gauss::result_t r = gauss::elimination(m);

    ASSERT_TRUE(std::holds_alternative<std::vector<double>>(r));
    const auto &v = std::get<std::vector<double>>(r);

    for (std::size_t i = 0; i < v.size(); ++i)
        ASSERT_EQ(std::llround(2.0 * v[i]) / 2.0, expected[i]);
}

