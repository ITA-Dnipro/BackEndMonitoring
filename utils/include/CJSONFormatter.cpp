#include "stdafx.h"

#include "Utils.h"
#include "CJSONFormatter.h"
#include "CLogger/include/Log.h"

bool CJSONFormatter::TryAddJSONFormattedData(const nlohmann::json& 
    p_formatted_data)
{
    CLOG_DEBUG_START_FUNCTION();
    if (p_formatted_data.is_null())
    { 
        return false;
    }

    if (m_date_and_time == std::nullopt)
    {
        std::string temp_date_and_time;
        CLOG_TRACE_VAR_CREATION(temp_date_and_time);
        if (!Utils::TryGetCurrentDateAndTimeFormatted(temp_date_and_time))
        {
            return false;
        }
        m_date_and_time = temp_date_and_time;
        m_formatted_data["date"] = *m_date_and_time;
    }
    m_formatted_data["info"] += p_formatted_data;
    CLOG_DEBUG_END_FUNCTION();
    return true;
}

bool CJSONFormatter::TrySetJSONFormattedData(const nlohmann::json& 
    p_formatted_data)
{
    CLOG_DEBUG_START_FUNCTION();
    if (p_formatted_data.is_null())
    {
        return false;
    }
    if (m_date_and_time == std::nullopt)
    {
        std::string temp_date_and_time;
        CLOG_TRACE_VAR_CREATION(temp_date_and_time);
        if (!Utils::TryGetCurrentDateAndTimeFormatted(temp_date_and_time))
        {
            return false;
        }
        m_date_and_time = temp_date_and_time;
        m_formatted_data["date"] = *m_date_and_time;
    }
    m_formatted_data["info"] = p_formatted_data;
    CLOG_DEBUG_END_FUNCTION();
    return true;
}

const nlohmann::json* CJSONFormatter::GetJSONFormattedData() const
{
    CLOG_DEBUG_START_FUNCTION();
    if (m_formatted_data.is_null())
    {
        return nullptr;
    }
    CLOG_DEBUG_END_FUNCTION();
    return &m_formatted_data;
}

bool CJSONFormatter::TryGetJSONDataAsString(std::string& str_for_data)
{
    CLOG_DEBUG_START_FUNCTION();
    if (!m_formatted_data.empty())
    {
        str_for_data = m_formatted_data.dump();
        return true;
    }
    CLOG_DEBUG_END_FUNCTION();
    return false;
}

bool CJSONFormatter::TryEraseAllData()
{
    CLOG_DEBUG_START_FUNCTION();
    nlohmann::json empty_json;
    CLOG_TRACE_VAR_CREATION(empty_json);
    m_formatted_data = empty_json;
    m_date_and_time.reset( );
    if (!m_formatted_data.is_null())
    {
        return false;
    }
    CLOG_DEBUG_END_FUNCTION();
    return true;
}

bool CJSONFormatter::TryReloadDateAndTime()
{
    // todo: check is work correct
    return Utils::TryGetCurrentDateAndTimeFormatted(m_date_and_time.value());
}
