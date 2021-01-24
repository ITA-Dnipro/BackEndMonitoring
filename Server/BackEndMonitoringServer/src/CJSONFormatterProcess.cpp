#include "stdafx.h"

#include "CProcessInfo.h"
#include "CJSONFormatterProcess.h"

CJSONFormatterProcess::CJSONFormatterProcess() : CJSONFormatter()
{};

bool CJSONFormatterProcess::TryAddProcessData(
    const CProcessInfo& process_to_json)
{
    nlohmann::json json_format_data;

    unsigned PID;
    double cpu_usage;
    long double ram_usage;
    long double pagefile_usage;
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

    return true;
}
