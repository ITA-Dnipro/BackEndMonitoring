#include "stdafx.h"

#include "CCommandLineHandler.h"

#include "CServiceHandler.h"
// Chupakabra: unused header
#include "Utils.h"

// Chupakabra: maybe const method of class
Task CommandLineHandler::GetTask()
{
    return task;
}

// Chupakabra: maybe const method of class
bool CommandLineHandler::Parse(int argc, char** argv)
{
    ServiceParameters parameters;
    auto service = std::make_unique<CService>(parameters);
    // Chupakabra: maybe const var
    auto service_handler = std::make_unique<ServiceHandler>(std::move(service));

    bool success = true;

	// Chupakabra: redundant parentheses in cases below
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
        // Chupakabra: no-need break
        // Show help
        break;
    }

    return success;
}
