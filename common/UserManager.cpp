#include "UserManager.h"
#include <fstream>
#include <stdexcept>
#include <sstream>

const std::string UserManager::database = "database.txt";
bool UserManager::initialized = false;


UserManager::UserManager()
{

    if(initialized)
        throw std::logic_error("Only one instance allowed");

    initUserTable();
    initialized = true;

}


bool UserManager::login(const std::string &username,const std::string &password)
{

    auto end = userTable.end();
    auto userEntry = userTable.find(username);
    return userEntry != end && userEntry->second == password;

}


void UserManager::initUserTable()
{

    std::ifstream dbFile(database);

    if(!dbFile.is_open())
        throw std::runtime_error("Could not open database file: " + database);  // Custom exeption?

    std::string username;
    std::string password;

    while(dbFile >> username >> password)
        userTable[username] = password;


    if(userTable.size() == 0 )
        throw std::runtime_error("No users defined in database file: " + database); // Custom exeption?

}



