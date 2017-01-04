#pragma once

#include <string>
#include <unordered_map>
#include <cstddef>


class UserManager
{

public:

    UserManager(const UserManager &) = delete;
    UserManager(UserManager &&) = delete;
    UserManager& operator=(const UserManager &) = delete;
    UserManager& operator=(UserManager &&) = delete;

    bool login(const std::string &username,const std::string &password);

    static UserManager &getUserManager();

private:

    void initUserTable();
    UserManager();

    std::unordered_map <std::string,std::string> mUserTable;

    //File containing registered users
    static const std::string database;

};
