#include "stdafx.h"

#include "CCommandLineHandler.h"
#include "CServiceHandler.h"
#include "Utils.h"

Task CommandLineHandler::GetTask()
{ return task; }

bool CommandLineHandler::Parse(int argc, char** argv)
{
    ServiceParameters parameters;
    auto service = std::make_unique<CService>(parameters);
    auto service_handler = 
        std::make_unique<ServiceHandler>(std::move(service));

    bool success = true;

    switch(argc)
    {
    case (1):
        success = service_handler->Run();
        break;

    case (2):
        if (strcmp(argv[1], "install") == 0)
        {
            success = service_handler->Install();
            break;
        }

        if (strcmp(argv[1], "uninstall") == 0)
        {
            success = service_handler->Uninstall();
            break;
        }

        if (strcmp(argv[1], "help") == 0)
        {
            // Show help
            break;
        }

    default :
        // Show help
        break;
    }

    return success;
}
