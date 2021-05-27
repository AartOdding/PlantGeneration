#include "debug.hpp"
#include <iostream>

void Mb4::DebugPrint(std::string const& str)
{
    if constexpr (MB4_DEBUG)
    {
        std::cout << str << std::endl;
    }
}

#if __has_include(<experimental/source_location>)
    void Mb4::ThrowAssertFailure(std::experimental::source_location const& source_location)
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
#else // __has_include(<experimental/source_location>)
    #include <string>

    void Mb4::ThrowAssertFailure(std::string const& function, std::string const& file, int line)
    {
        std::string errstr = "Assert failed!\nFunction: ";
        errstr.append(function);
        errstr.append("\nFile: ");
        errstr.append(file);
        errstr.append("\nLine: ");
        errstr.append(std::to_string(line));
        
        throw AssertError(errstr);
    }
#endif // __has_include(<experimental/source_location>)