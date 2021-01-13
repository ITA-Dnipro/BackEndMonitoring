#include "stdafx.h"

#include "CJSONFormatterProcess.h"

bool CJSONFormatterProcess::TryAddProcessData(const CProcess& process_to_json)
{
    nlohmann::json json_format_data;

    json_format_data["PID " + std::to_string(process_to_json.GetPID())] = {
        CreatePair<unsigned>("CPU_usage", process_to_json.GetCpuUsage()),
        CreatePair<unsigned>("RAM_usage", process_to_json.GetRamUsage()),
        CreatePair<unsigned>("Pagefile_usage", process_to_json.GetPagefileUsage())
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
