#pragma once

namespace Console
{
    void clear();
    //Use this function to clear stdin flags when there is parse error (e.g. std::cin >> number)
    void resetStdin();
}
