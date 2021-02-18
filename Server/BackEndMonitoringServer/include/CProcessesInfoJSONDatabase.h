#pragma once
#include "CMonitoringInfoJSONDatabase.h"
#include "CJSONFormatterProcess.h"
class CProcessesInfoJSONDatabase :
    public CMonitoringInfoJSONDatabase
{
public:
    CProcessesInfoJSONDatabase(const std::filesystem::path& path_to_file);
    CProcessesInfoJSONDatabase(const std::filesystem::path& path_to_file,
                               const std::string& date_format);

    CProcessesInfoJSONDatabase(const CProcessesInfoJSONDatabase&) = delete;
    CProcessesInfoJSONDatabase(CProcessesInfoJSONDatabase&&) = delete;
    
    ~CProcessesInfoJSONDatabase( ) = default;

    bool CommitDataAdd(const CProcessInfo& data_to_json);
    bool ClearCommitedData();
    bool InsertCommitedData();

private:
    CJSONFormatterProcess m_json_formatter;
};

