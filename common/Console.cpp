#include "Console.h"
#include <iostream>


namespace Console
{

    void clear()
    {

        #if defined(__linux__)

        std::cout << "\033[2J\033[1;1H"; // Magic

        #elif defined(_WIN32)

        //Port to windows

        #endif // defined
    }

}

