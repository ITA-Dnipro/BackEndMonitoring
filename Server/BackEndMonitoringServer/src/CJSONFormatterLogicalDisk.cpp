#include "stdafx.h"

#include "CJSONFormatter.h"
#include "CLogicalDiskInfo.h"
#include "CJSONFormatterLogicalDisk.h"
#include "CLogger/include/Log.h"

CJSONFormatterLogicalDisk::CJSONFormatterLogicalDisk() : CJSONFormatter()
{ };

bool CJSONFormatterLogicalDisk::TryAddLogicalDiskData(
    const CLogicalDiskInfo& data_to_json)
{
    CLOG_TRACE_START_FUNCTION();
    nlohmann::json json_format_data;
    CLOG_TRACE_VAR_CREATION(json_format_data);
    constexpr size_t num_of_letter = 10ULL;
    CLOG_TRACE_VAR_CREATION(num_of_letter);
    constexpr char all_field[][num_of_letter] = {
        {'n', 'a', 'm', 'e'},
        {'c', 'a', 'p', 'a', 'c', 'i', 't', 'y'},
        {'a', 'v', 'a', 'i', 'l', 'a', 'b', 'l', 'e'},
        {'f', 'r', 'e', 'e'} };
    CLOG_TRACE_VAR_CREATION(all_field);
    json_format_data = {
        CreatePair<std::string>(all_field[0], data_to_json.GetDiskName()),
        CreatePair<long double>(all_field[1], 
        data_to_json.GetCapacityOfDisk()),
        CreatePair<long double>(all_field[2], 
        data_to_json.GetAvailableOfDisk()),
        CreatePair<long double>(all_field[3], 
        data_to_json.GetFreeSpaceOfDisk()) };
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
