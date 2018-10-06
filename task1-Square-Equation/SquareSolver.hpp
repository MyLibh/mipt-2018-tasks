#pragma once

#ifndef __SQUARESOLVER_HPP_INCLUDED__
#define __SQUARESOLVER_HPP_INCLUDED__

#include <variant>
#include <utility>
#include <complex>

using ld_t = long double;

constexpr ld_t EPSILON = 1.e-5; 

using no_roots      = std::monostate;
using real_roots    = std::pair<ld_t, ld_t>;
using real_root     = ld_t;
using complex_roots = std::pair<std::complex<ld_t>, std::complex<ld_t>>;
using roots_t       = std::variant<no_roots, real_root, real_roots, complex_roots>;

roots_t SolveSquare(ld_t a, ld_t b, ld_t c) noexcept;
void PrintQuadResults(const roots_t &crRoots);

#endif /* __SQUARESOLVER_HPP_INCLUDED__ */