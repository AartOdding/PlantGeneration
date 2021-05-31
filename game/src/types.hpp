#pragma once

#include <cstdint>

using f32 = float;
using f64 = double;
using u32 = std::uint32_t;

constexpr f32 operator"" _f32(long double x)
{
	return x;
}

constexpr f64 operator"" _f64(long double x)
{
	return x;
}