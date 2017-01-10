#pragma once

#include <string>
#include <unordered_map>
#include <cstddef>


class UserManager
{

public:

    UserManager();

    UserManager(const UserManager &) = delete;
    UserManager(UserManager &&) = delete;
    UserManager& operator=(const UserManager &) = delete;
    UserManager& operator=(UserManager &&) = delete;

    bool login(const std::string &username,const std::string &password);

private:

    void initUserTable();

    std::unordered_map <std::string,std::string> userTable;

    //File containing registered users
    static const std::string database;
    static bool initialized;

};
