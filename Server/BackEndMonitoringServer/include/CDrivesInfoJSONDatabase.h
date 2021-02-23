#pragma once

#include "CMonitoringInfoJSONDatabase.h"
#include "CJSONFormatterLogicalDisk.h"

class CLogicalDiskInfo;

class CDrivesInfoJSONDatabase :
    public CMonitoringInfoJSONDatabase
{ 
public:
    CDrivesInfoJSONDatabase(const std::filesystem::path& path_to_file);
    CDrivesInfoJSONDatabase(const std::filesystem::path& path_to_file,
                            const std::string& date_format);

    CDrivesInfoJSONDatabase(const CDrivesInfoJSONDatabase&) = delete;
    CDrivesInfoJSONDatabase(CDrivesInfoJSONDatabase&&) = delete;

    ~CDrivesInfoJSONDatabase( ) = default;

    bool CommitDataAdd(const CLogicalDiskInfo& data_to_json);
    bool ClearCommitedData( );
    bool InsertCommitedData( );

private:
    CJSONFormatterLogicalDisk m_json_formatter;
};

