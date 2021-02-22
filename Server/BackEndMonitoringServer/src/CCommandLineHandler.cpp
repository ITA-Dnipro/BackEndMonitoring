#include "stdafx.h"

#include "CCommandLineHandler.h"
#include "CServiceHandler.h"

#include "Utils.h"



CommandLineHandler::CommandLineHandler(int argc, char** argv)
    : m_argc(argc),
      m_argv(argv)
{ }

bool CommandLineHandler::Parse( )
{
#if defined(_WIN64) || defined(_WIN32)
    ServiceParameters parameters;
    auto service = std::make_unique<CWindowsService>(parameters);
    auto service_handler = std::make_unique<ServiceHandler>(std::move(service));

    bool success = true;

    do
    {
        if (m_argc == 1)
        {
            success = service_handler->Run( );
            break;
        }

        if (m_argc == 2)
        {
            if (strcmp(m_argv[1], "install") == 0)
            {
                success = service_handler->Install( );
                break;
            }

            if (strcmp(m_argv[1], "uninstall") == 0)
            {
                success = service_handler->Uninstall( );
                break;
            }

            if (strcmp(m_argv[1], "help") == 0)
            {
                Utils::DisplayHelp( );
                break;
            }
        }

        Utils::DisplayMessage("Invalid parameters");
        Utils::DisplayHelp( );
    } while (false);

    return success;
#elif __linux__
    auto service = std::make_unique<CLinuxService>( );
    bool success = true;

    do
    {
        if (m_argc == 1)
        {
            success = service->Run( );
            break;
        }

        if (m_argc == 2)
        {
            if (strcmp(m_argv[1], "help") == 0)
            {
                Utils::DisplayHelp( );
                break;
            }
        }

        Utils::DisplayMessage("Invalid parameters");
        Utils::DisplayHelp( );
    } while (false);

    return success;
#endif
}