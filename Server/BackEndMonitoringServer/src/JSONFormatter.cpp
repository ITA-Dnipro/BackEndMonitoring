#include "stdafx.h"
#include "JSONFormatter.h"

JSONFormatter* JSONFormatter::FactoryJSONFormatter()
{
    // todo: ask where I should put func GetCurrentTimeAndDay
    std::time_t current_time = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now());
    std::string date_and_time = ctime(&current_time);
    date_and_time.pop_back();

    JSONFormatter* formatter = new JSONFormatter(date_and_time);

    return formatter;
}

bool JSONFormatter::AddNewPair(std::string key, nlohmann::json value)
{

    formatted_data_.push_back({ key, value });
    return true;
}

std::vector<nlohmann::json>* JSONFormatter::GetJSONFormattedData()
{
    if (formatted_data_.capacity() == 0)
    {
        return nullptr;
    }

    return &formatted_data_;
}
