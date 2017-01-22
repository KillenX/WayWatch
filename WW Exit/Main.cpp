#include <iostream>
#include <exception>
#include "WWExit.h"



int main()
{


    try
    {

        WWExit app;
        app.run();

    }
    catch(const std::exception &ex)
    {

        std::cout << "\nFatal error: " << ex.what();

    }


}
