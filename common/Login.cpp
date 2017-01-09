#include "Login.h"
#include "UserManager.h"
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
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD mode;
		GetConsoleMode(hStdin, &mode);
		if (!enableEcho)
			mode &= ~ENABLE_ECHO_INPUT;
		else
			mode |= ENABLE_ECHO_INPUT;
		SetConsoleMode(hStdin, mode);
        #endif
    }
}


namespace Login
{
    std::pair <std::string, std::string> promptUser()
    {
        std::string username, password;

        std::cout << "Username: ";
        std::getline(std::cin, username);

        std::cout << "Password: ";
        setEcho(false);

        std::getline(std::cin, password);
        setEcho(true);
		#if defined(_WIN32)
		std::cout << std::endl; // HACK: because '\n' gets hidden as well
		#endif

		return std::make_pair(username, password);
    }

	void tryLogin()
	{
		UserManager userManager;
		bool loggedIn;

		do
		{
			auto credentials = Login::promptUser();
			loggedIn = userManager.login(credentials.first, credentials.second);

			if (!loggedIn)
				std::cout << "Netacno korisnicko ime/sifra" << std::endl;
		} while (!loggedIn);

		std::cout << "Uspjesno logovanje na sistem." << std::endl << std::endl;
	}
}


