/* Define functions to assert things at debug time.
 * If MB4_PREPROCESSOR_DEBUG is defined, assertion will run.
 * Else they will not.
*/

#pragma once

#include <stdexcept>
#include <experimental/source_location>

namespace Mb4 {

#ifdef MB4_PREPROCESSOR_DEBUG
    constexpr static bool MB4_DEBUG = true;
#else
    constexpr static bool MB4_DEBUG = false;
#endif

using AssertError = std::runtime_error;

void ThrowAssertFailure(std::experimental::source_location const& source_location)
{
    std::string errstr = "Assert failed!\nFile: ";
    errstr.append(source_location.file_name());
    errstr.append("\nFunction: ");
    errstr.append(source_location.function_name());
    errstr.append("\nLine: ");
    errstr.append(std::to_string(source_location.line()));
    errstr.append("\nColumn: ");
    errstr.append(std::to_string(source_location.column()));
    
    throw AssertError(errstr);
}

template <typename T1, typename T2>
void AssertEqual(T1 const& a, T2 const& b, std::experimental::source_location source_location = std::experimental::source_location::current())
{
    if constexpr (MB4_DEBUG)
    {
        if (!(a == b))
        {
            ThrowAssertFailure(source_location);
        }
    }
}

template <typename T1, typename T2>
void AssertLarger(T1 const& a, T2 const& b, std::experimental::source_location source_location = std::experimental::source_location::current())
{
    if constexpr (MB4_DEBUG)
    {
        if (!(a > b))
        {
            ThrowAssertFailure(source_location);
        }
    }
}

template <typename T1, typename T2>
void AssertLargerEqual(T1 const& a, T2 const& b, std::experimental::source_location source_location = std::experimental::source_location::current())
{
    if constexpr (MB4_DEBUG)
    {
        if (!(a >= b))
        {
            ThrowAssertFailure(source_location);
        }
    }
}

template <typename T1, typename T2>
void AssertSmaller(T1 const& a, T2 const& b, std::experimental::source_location source_location = std::experimental::source_location::current())
{
    if constexpr (MB4_DEBUG)
    {
        if (!(a < b))
        {
            ThrowAssertFailure(source_location);
        }
    }
}

template <typename T1, typename T2>
void AssertSmallerEqual(T1 const& a, T2 const& b, std::experimental::source_location source_location = std::experimental::source_location::current())
{
    if constexpr (MB4_DEBUG)
    {
        if (!(a <= b))
        {
            ThrowAssertFailure(source_location);
        }
    }
}

}