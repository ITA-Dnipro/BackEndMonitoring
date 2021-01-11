#include "stdafx.h"
#include "JSONFormatter.h"

bool JSONFormatter::TryAddJSONFormattedData(const nlohmann::json* 
    formatted_data)
{
    if(formatted_data->is_null())
    { 
        return false;
    }
    formatted_data_[Utilities::GetCurrentDateAndTimeFormatted()] 
        += *formatted_data;
   
    return true;
}

bool JSONFormatter::TrySetJSONFormattedData(const nlohmann::json* 
    formatted_data)
{
    if (formatted_data->is_null())
    {
        return false;
    }
    formatted_data_[Utilities::GetCurrentDateAndTimeFormatted()] 
        = *formatted_data;

    return true;
}

nlohmann::json* JSONFormatter::GetJSONFormattedData()
{
    if (formatted_data_.is_null())
    {
        return nullptr;
    }

    return &formatted_data_;
}
