#pragma once

#include <cstdint>

using f32 = float;
using f64 = double;
using u32 = std::uint32_t;

f32 operator"" _f32(long double x);

f64 operator"" _f64(long double x);