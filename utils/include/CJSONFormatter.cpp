#include "stdafx.h"

#include "Utils.h"
#include "CJSONFormatter.h"

bool CJSONFormatter::TryAddJSONFormattedData(const nlohmann::json& 
    p_formatted_data)
{
    if (p_formatted_data.is_null())
    { 
        return false;
    }

    if (m_date_and_time == std::nullopt)
    {
        std::string temp_date_and_time;
        if (!Utils::TryGetCurrentDateAndTimeFormatted(temp_date_and_time))
        {
            return false;
        }
        m_date_and_time = temp_date_and_time;
    }
    m_formatted_data[*m_date_and_time] += p_formatted_data;
   
    return true;
}

bool CJSONFormatter::TrySetJSONFormattedData(const nlohmann::json& 
    p_formatted_data)
{
    if (p_formatted_data.is_null())
    {
        return false;
    }
    if (m_date_and_time == std::nullopt)
    {
        std::string temp_date_and_time;
        if (!Utils::TryGetCurrentDateAndTimeFormatted(temp_date_and_time))
        {
            return false;
        }
        m_date_and_time = temp_date_and_time;
    }
    m_formatted_data[*m_date_and_time] = p_formatted_data;

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
    m_date_and_time.reset( );
    if (!m_formatted_data.is_null())
    {
        return false;
    }

    return true;
}

bool CJSONFormatter::TryReloadDateAndTime()
{
    // todo: check is work correct
    return Utils::TryGetCurrentDateAndTimeFormatted(m_date_and_time.value());
}
