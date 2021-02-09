#include "stdafx.h"

#include "CProcessInfo.h"
#include "CJSONFormatterProcess.h"
#include "CLogger/include/Log.h"

CJSONFormatterProcess::CJSONFormatterProcess() : CJSONFormatter()
{};

bool CJSONFormatterProcess::TryAddProcessData(
    const CProcessInfo& process_to_json)
{
    CLOG_TRACE_START_FUNCTION();
    nlohmann::json json_format_data;
    CLOG_TRACE_VAR_CREATION(json_format_data);
    unsigned PID;
    CLOG_TRACE_VAR_CREATION(PID);
    double cpu_usage;
    CLOG_TRACE_VAR_CREATION(cpu_usage);
    long double ram_usage;
    CLOG_TRACE_VAR_CREATION(ram_usage);
    long double pagefile_usage;
    CLOG_TRACE_VAR_CREATION(pagefile_usage);
    if (!process_to_json.GetPID(PID) ||
        !process_to_json.GetCpuUsage(cpu_usage) ||
        !process_to_json.GetRamUsage(ram_usage) ||
        !process_to_json.GetPagefileUsage(pagefile_usage))
    {
        return false;
    }
    json_format_data["PID " + std::to_string(PID)] = {
        CreatePair<double>("CPU_usage", cpu_usage),
        CreatePair<long double>("RAM_usage", ram_usage),
        CreatePair<long double>("Pagefile_usage",pagefile_usage)
    };
    if (json_format_data.is_null())
    {
        return false;
    }
    if (!TryAddJSONFormattedData(json_format_data))
    {
        return false;
    }
    CLOG_TRACE_END_FUNCTION();
    return true;
}
