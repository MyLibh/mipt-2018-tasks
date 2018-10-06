#include "SquareSolver.hpp"

#include <limits>   
#include <iostream> // std::cout

namespace Detail
{
	static constexpr ld_t sqrtNewtonRaphson(ld_t x, ld_t curr, ld_t prev) noexcept
	{
		return curr == prev ? curr : sqrtNewtonRaphson(x, .5l * (curr + x / curr), curr);
	}

	static inline ld_t constexpr sqrt(ld_t x) noexcept
	{
		return (x >= 0.l && x < std::numeric_limits<ld_t>::infinity() ? Detail::sqrtNewtonRaphson(x, x, 0.l) : std::numeric_limits<ld_t>::quiet_NaN());
	}

	static inline ld_t constexpr sqr(ld_t x) noexcept
	{
		return (x * x);
	}

	static inline constexpr bool isZero(ld_t x, ld_t eps = EPSILON) noexcept
	{
		return (x > -eps && x < eps);
	}

	template<class... Args> 
	struct helper : Args... { using Args::operator()...; };

	template<class... Args> 
	helper(Args...)->helper<Args...>;
}

roots_t SolveSquare(ld_t a, ld_t b, ld_t c) noexcept
{
	if (Detail::isZero(a))
		return std::monostate();

	using namespace std::complex_literals;

	// TODO: Remove repeated calculations
	if (register auto diskr = Detail::sqr(b) - 4.l * a * c; diskr > 0.l)
		return std::pair{ (-b + Detail::sqrt(diskr)) / (2.l * a), (-b - Detail::sqrt(diskr)) / (2.l * a) };
	else if (auto tmp = -b / (2. * a); Detail::isZero(diskr))
		return tmp;
	else
		return std::pair{ std::complex{ (-b + 1il * sqrt(-diskr)) / (2.l * a) }, std::complex{ (-b - 1il * std::sqrt(-diskr)) / (2.l * a) } };
}

void PrintQuadResults(const roots_t &crRoots)
{
	std::visit(Detail::helper{ 
				[](no_roots) { std::cout << "No roots"; },
				[](const real_root x) { std::cout << "Real root: " << x; },
		        [](const real_roots &roots) { std::cout << "Real roots: " << roots.first << ", " << roots.second; },
			    [](const complex_roots &roots) { std::cout << "Complex roots: " << roots.first << ", " << roots.second; }, }, 
				crRoots);

	std::cout << std::endl;
}

