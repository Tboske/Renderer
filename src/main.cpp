#include "Tribe.h"
#include <exception>
#include <spdlog/spdlog.h>
#include <string>


int main(int argc, const char** args)
{
    try
    {
        Tribe* pEngine{new Tribe()};
        pEngine->Run();
        SafeDelete(pEngine);
    }
    catch(std::exception& e)
    {
        spdlog::error(e.what());
    }

    return 0;
}