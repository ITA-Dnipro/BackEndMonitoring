#include "stdafx.h"

#include "CService.h"
#include "CCommandLineHandler.h"
#include "CServiceHandler.h"
#include "Utils.h"

int main(int argc, char** argv)
{
    auto parser = std::make_unique<CommandLineHandler>();

    bool success = parser->Parse(argc, argv);

    if (!success)
    {
        Utils::DisplayMessage("Invalid parameters");
        return EXIT_FAILURE;
    }

    const int return_code = success ? 0 : 1;

    return return_code;
}


