#include "stdafx.h"
#include "IParser.h"

const SServer& IParser::GetServerConfiguration() const
{
    return server_;
}

const SComunicationSettings& IParser::GetComunicationConfiguration() const
{
    return comunication_settings_;
}

const SLogging& IParser::GetLoggingConfiguration() const
{
    return logging_;
}

const STime& IParser::GetTimeConfiguration() const
{
    return time_;
}

const SThreadPool& IParser::GetThreadPoolConfiguration() const
{
    return thread_pool_;
}

const SHDDInfo& IParser::GetHDDInfoConfiguration() const
{
    return hdd_info_;
}

const SProcessesInfo& IParser::GetProcessInfoConfiguration() const
{
    return processes_info_;
}
