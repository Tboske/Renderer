#include "engine/Engine.h"


int main(int argc, const char** args)
{
    Engine* pEngine{new Engine()};
    pEngine->Run();
    SafeDelete(pEngine);

    return 0;
}
