#include "Login.h"
#include "UserManager.h"
#include "Console.h"
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

    std::pair <std::string, std::string> promptUser()
    {
        std::string username, password;

        std::cout << "Username: ";
        std::getline(std::cin, username);

        std::cout << "Password: ";
        setEcho(false);

        std::getline(std::cin, password);
        setEcho(true);

		std::cout << std::endl;

		return std::make_pair(username, password);
    }

    //UserManager userManager;

}


namespace Login
{

	void tryLogin()
	{

		UserManager userManager;
		bool loggedIn;

		do
		{
			auto credentials = promptUser();
			loggedIn = userManager.login(credentials.first, credentials.second);

			if (!loggedIn)
				std::cout << "Netacno korisnicko ime/sifra" << std::endl;
		} while (!loggedIn);

		std::cout << "Uspjesno logovanje na sistem." << std::endl << std::endl;
	}

	//Returns false if user wants to exit, true login successful
	/*bool loginPrompt()
	{




	}*/

	LoginUI::LoginUI():exit(false){}

	bool LoginUI::show()
	{

	    int selection;

	    do
        {

            printOptions();
            std::cout << "Izaberite opciju: ";

            std::cin >> selection;
            std::cin.clear();
            std::cin.ignore();

            Console::clear();

            bool validSelection = validateSelection(std::cin,selection);

            if(!validSelection)
                std::cout << "Greska! opcija ne postoji\n";

            else
            {

                switch(selection)
                {

                case 1:

                    tryLogin();
                    Console::clear();

                    if(!exit)
                        std::cout << "Neuspjesno logovanje\n";

                    break;

                case 2:

                    exit = true;

                    break;

                default:
                    break;

                }

            }

        }
        while(!exit);

        //User wants to exit
        return selection != 2;

	}


	void LoginUI::setEcho(bool enableEcho)
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

	LoginUI::Credentials LoginUI::promptUser()
	{

	    std::string username, password;

        std::cout << "Username: ";
        std::getline(std::cin, username);

        std::cout << "Password: ";
        setEcho(false);

        std::getline(std::cin, password);
        setEcho(true);

		std::cout << std::endl;

		return std::make_pair(username, password);

	}

	void LoginUI::printOptions()
	{

	    std::cout << "1. Prijava na sistem\n";
	    std::cout << "2. Izlaz\n";

	}

	bool LoginUI::validateSelection(std::istream &stream,int selection)
	{

	    return !stream.fail() && selection >= 1 && selection <=2;

	}

	void LoginUI::tryLogin()
	{

	    auto credentials = promptUser();
	    //If user logs in succcesfully then exit from ui
	    exit = userManager.login(credentials.first,credentials.second);

	}





}


