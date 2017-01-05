#pragma once

#include <vector>
#include <utility> // std::pair
#include <string>
#include <functional>


class WWEntry
{

public:

    WWEntry();

    WWEntry(const WWEntry &) = delete;
    WWEntry(WWEntry &&) = delete;
    WWEntry &operator=(const WWEntry &) = delete;
    WWEntry &operator=(WWEntry &&) = delete;

    void run();


private:

    void initOptions();
    void generateEntryCard();
    void exit();

    void printOptions();
    bool validateSelection(std::istream &stream,int selection);


    using OptCallable = std::function <void()>;

    //Pair consisting of option string (eg. "Exit Program"), second is handler for the option
    using Option = std::pair <std::string,OptCallable>;



    std::vector <Option> options;
    bool programExit;

};
