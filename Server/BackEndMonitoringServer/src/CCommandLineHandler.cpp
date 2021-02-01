#include "stdafx.h"

#include "CCommandLineHandler.h"
#include "CServiceHandler.h"
// Chupakabra: unused header
#include "Utils.h"

// Chupakabra: maybe const method of class
Task CommandLineHandler::GetTask()
{ return task; }

// Chupakabra: maybe const method of class
bool CommandLineHandler::Parse(int argc, char** argv)
{
    bool success = false;
    CLOG_DEBUG_START_FUNCTION();
    ServiceParameters parameters;
    CLOG_TRACE_VAR_CREATION(parameters);
    auto service = std::make_unique<CService>(parameters);
    CLOG_TRACE_VAR_CREATION(service);
    // Chupakabra: maybe const var
    auto service_handler = std::make_unique<ServiceHandler>(std::move(service));
    CLOG_TRACE_VAR_CREATION(service_handler);
    success = true;
    CLOG_TRACE_VAR_CREATION(success);
	// Chupakabra: redundant parentheses in cases below
    switch(argc)
    {
    case (1):
        success = service_handler->Run();
        CLOG_TRACE_VAR_CREATION(success);
        break;

    case (2):
        if (strcmp(argv[1], "install") == 0)
        {
            success = service_handler->Install();
            CLOG_TRACE_VAR_CREATION(success);
            break;
        }

        if (strcmp(argv[1], "uninstall") == 0)
        {
            success = service_handler->Uninstall();
            CLOG_TRACE_VAR_CREATION(success);
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
    CLOG_DEBUG_END_FUNCTION();
    return success;
}
