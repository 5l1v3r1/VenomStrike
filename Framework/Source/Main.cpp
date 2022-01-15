#include <iostream>

#include "Application.h"

#include "Core/File.h"

int main() 
{
    VS::VApplication Application;

    try
    {
        Application.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}