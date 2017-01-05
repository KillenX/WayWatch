#pragma once


#include <utility>
#include <string>

namespace Login
{

    //First template parameter is username, second is password
    std::pair <std::string,std::string> promptUser();

}
