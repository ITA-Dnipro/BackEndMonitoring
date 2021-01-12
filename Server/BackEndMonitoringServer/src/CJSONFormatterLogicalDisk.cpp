#include "stdafx.h"

#include "CJSONFormatterLogicalDisk.h"

bool CJSONFormatterLogicalDisk::TryAddLogicalDiskData(
    const CLogicalDiskStatus& data_to_json, unsigned short disk_number)
{
    nlohmann::json json_format_data;
    constexpr size_t num_of_letter = 10;
    const std::string common_main_name = "disk";
    constexpr char all_field[][num_of_letter] = {
        {'n', 'a', 'm', 'e'},
        {'c', 'a', 'p', 'a', 'c', 'i', 't', 'y'},
        {'a', 'v', 'a', 'i', 'l', 'a', 'b', 'l', 'e'},
        {'f', 'r', 'e', 'e'} };

    json_format_data[common_main_name + std::to_string(disk_number)] = {
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

    return true;
}
