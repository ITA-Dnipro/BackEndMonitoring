#include "stdafx.h"
#include "CConfiguration.h"

CConfiguration::CConfiguration(std::unique_ptr<IParser> p_parser) : p_parser_(std::move(p_parser))
{
	
}

SServer& CConfiguration::GetDefaultServerConfiguration()
{
    return p_parser_->GetDefaultServerConfiguration();
}

SComunicationSettings& CConfiguration::GetDefaultComunicationConfiguration()
{
    return p_parser_->GetDefaultComunicationConfiguration();
}

SLogging& CConfiguration::GetDefaultLoggingConfiguration()
{
    return p_parser_->GetDefaultLoggingConfiguration();
}

STime& CConfiguration::GetDefaultTimeConfiguration()
{
    return p_parser_->GetDefaultTimeConfiguration();
}

SThreadPool& CConfiguration::GetDefaultThreadPoolConfiguration()
{
    return p_parser_->GetDefaultThreadPoolConfiguration();
}

SHDDInfo& CConfiguration::GetDefaultHDDInfoConfiguration()
{
    return p_parser_->GetDefaultHDDInfoConfiguration();
}

SProcessesInfo& CConfiguration::GetDefaultProcessInfoConfiguration()
{
    return p_parser_->GetDefaultProcessInfoConfiguration();
}

SServer& CConfiguration::TryToGetServerConfigurationFromFile()
{
    return p_parser_->TryToGetServerConfigurationFromFile();
}

SComunicationSettings& CConfiguration::TryToGetComunicationConfigurationFromFile()
{
    return p_parser_->TryToGetComunicationConfigurationFromFile();
}

SLogging& CConfiguration::TryToGetLoggingConfigurationFromFile()
{
    return p_parser_->TryToGetLoggingConfigurationFromFile();
}

STime& CConfiguration::TryToGetTimeConfigurationFromFile()
{
    return p_parser_->TryToGetTimeConfigurationFromFile();
}

SThreadPool& CConfiguration::TryToGetThreadPoolConfigurationFromFile()
{
    return p_parser_->TryToGetThreadPoolConfigurationFromFile();
}

SHDDInfo& CConfiguration::TryToGetHDDInfoConfigurationFromFile()
{
    return p_parser_->TryToGetHDDInfoConfigurationFromFile();
}

SProcessesInfo& CConfiguration::TryToGetProcessInfoConfigurationFromFile()
{
    return p_parser_->TryToGetProcessInfoConfigurationFromFile();
}
