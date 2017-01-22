#pragma once

#include <utility>
#include <string>
#include <istream>
#include "../common/UserManager.h"

namespace Login
{

	class LoginUI
	{

    public:

        LoginUI();
        LoginUI(const LoginUI &) = delete;
        LoginUI(LoginUI &&) = delete;
        LoginUI &operator=(const LoginUI &) = delete;
        LoginUI &operator=(LoginUI &&) = delete;

        bool show();

    private:

        using Credentials = std::pair<std::string,std::string>;

        void setEcho(bool enableEcho);
        Credentials promptUser();
        void printOptions();
        bool validateSelection(std::istream &str,int selection);
        void tryLogin();


        UserManager userManager;
        bool exit;

	};
}
