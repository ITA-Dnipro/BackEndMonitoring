#include "stdafx.h"

#include "json.hpp"

#include "CJSONFormatter.h"
#include "Utils.h"

bool CJSONFormatter::TryAddJSONFormattedData(const nlohmann::json& 
    p_formatted_data)
{
    if (p_formatted_data.is_null())
    { 
        return false;
    }
    std::string date_and_time;

    if (!Utils::TryGetCurrentDateAndTimeFormatted(date_and_time))
    {
        return false;
    }
    m_formatted_data[date_and_time] += p_formatted_data;
   
    return true;
}

bool CJSONFormatter::TrySetJSONFormattedData(const nlohmann::json& 
    p_formatted_data)
{
    if (p_formatted_data.is_null())
    {
        return false;
    }
    std::string date_and_time;

    if (!Utils::TryGetCurrentDateAndTimeFormatted(date_and_time))
    {
        return false;
    }
    m_formatted_data[date_and_time] = p_formatted_data;

    return true;
}

nlohmann::json* CJSONFormatter::GetJSONFormattedData()
{
    if (m_formatted_data.is_null())
    {
        return nullptr;
    }

    return &m_formatted_data;
}

bool CJSONFormatter::TryGetJSONDataAsString(std::string& str_for_data)
{
    str_for_data = m_formatted_data.dump();
    if (str_for_data.empty())
    {
        return false;
    }

    return true;
}

bool CJSONFormatter::TryEraseAllData()
{
    nlohmann::json empty_json;
    m_formatted_data = empty_json;
    
    if (!m_formatted_data.is_null())
    {
        return false;
    }

    return true;
}
