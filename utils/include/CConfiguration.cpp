#include "stdafx.h"
#include "CConfiguration.h"

CConfiguration::CConfiguration(std::unique_ptr<IParser> p_parser) : p_parser_(std::move(p_parser))
{
	
}

void CConfiguration::ReadConfigFromFile()
{
    if(IsParserInitialized() && p_parser_->IsFileInitialized())
        p_parser_->ReadConfigFromFile();

}

const SServer& CConfiguration::GetServerConfiguration() const
{
    return p_parser_->GetServerConfiguration();
}

const SComunicationSettings& CConfiguration::GetComunicationConfiguration() const
{
    return p_parser_->GetComunicationConfiguration();
}

const SLogging& CConfiguration::GetLoggingConfiguration() const
{
    return p_parser_->GetLoggingConfiguration();
}

const STime& CConfiguration::GetTimeConfiguration() const
{
    return p_parser_->GetTimeConfiguration();
}

const SThreadPool& CConfiguration::GetThreadPoolConfiguration() const
{
    return p_parser_->GetThreadPoolConfiguration();
}

const SHDDInfo& CConfiguration::GetHDDInfoConfiguration() const
{
    return p_parser_->GetHDDInfoConfiguration();
}

const SProcessesInfo& CConfiguration::GetProcessInfoConfiguration() const
{
    return p_parser_->GetProcessInfoConfiguration();
}

bool CConfiguration::IsParserInitialized() const
{
    if (nullptr == p_parser_)
    {
        // write to logger: parser isn't initialized
        return false;
    }
    return true;
}
