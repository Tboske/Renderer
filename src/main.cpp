#include "engine/Engine.h"


int main(int argc, const char** args)
{
    Tribe* pEngine{new Tribe()};
    pEngine->Run();
    SafeDelete(pEngine);

    return 0;
}