#include "debug.hpp"
#include <iostream>

void Mb4::DebugPrint(std::string const& str)
{
    if constexpr (MB4_DEBUG)
    {
        std::cout << str << std::endl;
    }
}

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
