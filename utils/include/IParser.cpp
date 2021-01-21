#include "stdafx.h"
#include "IParser.h"

SServer& IParser::GetDefaultServerConfiguration()
{
    return server_;
}

SComunicationSettings& IParser::GetDefaultComunicationConfiguration()
{
    return comunication_settings_;
}

SLogging& IParser::GetDefaultLoggingConfiguration()
{
    return logging_;
}

STime& IParser::GetDefaultTimeConfiguration()
{
    return time_;
}

SThreadPool& IParser::GetDefaultThreadPoolConfiguration()
{
    return thread_pool_;
}

SHDDInfo& IParser::GetDefaultHDDInfoConfiguration()
{
    return hdd_info_;
}

SProcessesInfo& IParser::GetDefaultProcessInfoConfiguration()
{
    return processes_info_;
}
