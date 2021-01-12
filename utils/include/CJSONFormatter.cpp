#include "stdafx.h"
#include "CJSONFormatter.h"

bool CJSONFormatter::TryAddJSONFormattedData(const nlohmann::json* 
    p_formatted_data)
{
    if(p_formatted_data->is_null())
    { 
        return false;
    }
    m_formatted_data_[Utilities::GetCurrentDateAndTimeFormatted()] 
        += *p_formatted_data;
   
    return true;
}

bool CJSONFormatter::TrySetJSONFormattedData(const nlohmann::json* 
    p_formatted_data)
{
    if (p_formatted_data->is_null())
    {
        return false;
    }
    m_formatted_data_[Utilities::GetCurrentDateAndTimeFormatted()] 
        = *p_formatted_data;

    return true;
}

nlohmann::json* CJSONFormatter::GetJSONFormattedData()
{
    if (m_formatted_data_.is_null())
    {
        return nullptr;
    }

    return &m_formatted_data_;
}
