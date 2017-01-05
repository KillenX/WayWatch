#include "Login.h"
#include <iostream>

#if defined(linux)
#include <termios.h>
#include <unistd.h>

#elif defined(_WIN32)
#include <windows.h>
#endif
   

namespace
{

    void setEcho(bool enableEcho)
    {

        #if defined(__linux__)

        termios tty;

        tcgetattr(STDIN_FILENO,&tty);

        if(enableEcho)
            tty.c_lflag |= ECHO;

        else
            tty.c_lflag &= ~ECHO;

        tcsetattr(STDIN_FILENO,TCSANOW,&tty);

        #elif defined(_WIN32)

        //Port to windows

        #endif

    }

}


namespace Login
{

    std::pair <std::string,std::string> promptUser()
    {


        std::string username,password;

        std::cout << "Username: ";
        std::getline(std::cin,username);

        std::cout << "Password: ";
        setEcho(false);

        std::getline(std::cin,password);

        setEcho(true);

        return std::make_pair(username,password);

    }

}


