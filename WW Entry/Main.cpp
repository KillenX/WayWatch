#include "WWEntry.h"
#include <exception>
#include <iostream>


int main()
{

    try
    {

        WWEntry app;
        app.run();

    }
    catch(const std::exception &ex)
    {

        std::cout << "\nFatal Error: " << ex.what();

    }

}
