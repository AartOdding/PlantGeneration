/* Define functions to assert things at debug time.
 * If MB4_PREPROCESSOR_DEBUG is defined, assertion will run.
 * Else they will not.
*/

#pragma once

#include <stdexcept>

namespace Mb4
{

#ifdef MB4_PREPROCESSOR_DEBUG
    constexpr static bool MB4_DEBUG = true;
#else
    constexpr static bool MB4_DEBUG = false;
#endif

using AssertError = std::runtime_error;

void DebugPrint(std::string const &str);

}

#if __has_include(<experimental/source_location>)
    #include <experimental/source_location>

    #define Mb4_AssertEqual(a, b) Mb4::AssertEqual(a, b)
    #define Mb4_AssertLarger(a, b) Mb4::AssertLarger(a, b)
    #define Mb4_AssertLargerEqual(a, b) Mb4::AssertLargerEqual(a, b)
    #define Mb4_AssertSmaller(a, b) Mb4::AssertSmaller(a, b)
    #define Mb4_AssertSmallerEqual(a, b) Mb4::AssertSmallerEqual(a, b)

    namespace Mb4
    {

    void ThrowAssertFailure(std::experimental::source_location const &source_location);

    template <typename T1, typename T2>
    void AssertEqual(T1 const &a, T2 const &b, std::experimental::source_location source_location = std::experimental::source_location::current())
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
    void AssertLarger(T1 const &a, T2 const &b, std::experimental::source_location source_location = std::experimental::source_location::current())
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
    void AssertLargerEqual(T1 const &a, T2 const &b, std::experimental::source_location source_location = std::experimental::source_location::current())
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
    void AssertSmaller(T1 const &a, T2 const &b, std::experimental::source_location source_location = std::experimental::source_location::current())
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
    void AssertSmallerEqual(T1 const &a, T2 const &b, std::experimental::source_location source_location = std::experimental::source_location::current())
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
#else  // __has_include(<experimental/source_location>)
    #define Mb4_AssertEqual(a, b) Mb4::AssertEqual(a, b, __func__, __FILE__, __LINE__)
    #define Mb4_AssertLarger(a, b) Mb4::AssertLarger(a, b, __func__, __FILE__, __LINE__)
    #define Mb4_AssertLargerEqual(a, b) Mb4::AssertLargerEqual(a, b, __func__, __FILE__, __LINE__)
    #define Mb4_AssertSmaller(a, b) Mb4::AssertSmaller(a, b, __func__, __FILE__, __LINE__)
    #define Mb4_AssertSmallerEqual(a, b) Mb4::AssertSmallerEqual(a, b, __func__, __FILE__, __LINE__)

    namespace Mb4
    {

    void ThrowAssertFailure(std::string const& function, std::string const& file, int line);

    template <typename T1, typename T2>
    void AssertEqual(T1 const &a, T2 const &b, std::string const& function, std::string const& file, int line)
    {
        if constexpr (MB4_DEBUG)
        {
            if (!(a == b))
            {
                ThrowAssertFailure(function, file, line);
            }
        }
    }

    template <typename T1, typename T2>
    void AssertLarger(T1 const &a, T2 const &b, std::string const& function, std::string const& file, int line)
    {
        if constexpr (MB4_DEBUG)
        {
            if (!(a > b))
            {
                ThrowAssertFailure(function, file, line);
            }
        }
    }

    template <typename T1, typename T2>
    void AssertLargerEqual(T1 const &a, T2 const &b, std::string const& function, std::string const& file, int line)
    {
        if constexpr (MB4_DEBUG)
        {
            if (!(a >= b))
            {
                ThrowAssertFailure(function, file, line);
            }
        }
    }

    template <typename T1, typename T2>
    void AssertSmaller(T1 const &a, T2 const &b, std::string const& function, std::string const& file, int line)
    {
        if constexpr (MB4_DEBUG)
        {
            if (!(a < b))
            {
                ThrowAssertFailure(function, file, line);
            }
        }
    }

    template <typename T1, typename T2>
    void AssertSmallerEqual(T1 const &a, T2 const &b, std::string const& function, std::string const& file, int line)
    {
        if constexpr (MB4_DEBUG)
        {
            if (!(a <= b))
            {
                ThrowAssertFailure(function, file, line);
            }
        }
    }

    }
#endif // __has_include(<experimental/source_location>)