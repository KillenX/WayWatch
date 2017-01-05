#include "Login.h"
#include <iostream>
#include <termios.h>
#include <unistd.h>


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

        std::cout << "Korisnicko ime: ";
        std::getline(std::cin,username);

        std::cout << "Sifra: ";
        setEcho(false);

        std::getline(std::cin,password);

        setEcho(true);
        std::cout << "\n";

        return std::make_pair(username,password);

    }

}


