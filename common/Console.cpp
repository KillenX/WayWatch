#include "Console.h"
#include <iostream>

#if defined(_WIN32)

#include <windows.h>

#endif


namespace Console
{

    void clear()
    {

        #if defined(__linux__)

        std::cout << "\033[2J\033[1;1H"; // Magic

        #elif defined(_WIN32)

        auto consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD topLeft = {0,0};
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        DWORD written;

        auto bufferSize = consoleInfo.dwSize.X * consoleInfo.dwSize.Y;

        FillConsoleOutputCharacter(consoleHandle,' ',bufferSize,topLeft,&written);
        SetConsoleCursorPosition(consoleHandle,topLeft);

        #endif
    }

}

