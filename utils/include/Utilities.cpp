#include "stdafx.h"
#include "Utilities.h"

std::string Utilities::GetCurrentDateAndTimeFormatted()
{
    //parse to format: dd.mm.yyyy hh:mm:ss
    std::time_t current_time = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now());
    std::string date_and_time = ctime(&current_time);

    date_and_time.pop_back();
    date_and_time = date_and_time.substr(date_and_time.find_first_of(" ") + 1);
    
    std::string buff_year = date_and_time.substr(
        date_and_time.find_last_of(" ") + 1);
    date_and_time.erase(date_and_time.end() - buff_year.size(), 
        date_and_time.end());

    std::string buff_month = date_and_time.substr(0, 
        date_and_time.find_first_of(" "));
    date_and_time.erase(date_and_time.begin(), date_and_time.begin() + 
        buff_month.size() + 1);

    if (!HelperDateAndTime::TrySetMonthAsNumber(&buff_month))
    {
        return std::string("Couln't parse month to number!");
    }
    
    date_and_time.insert(date_and_time.find_first_of(" "), "." + buff_month);
    date_and_time.insert(date_and_time.find_first_of(" "), 
        "." + buff_year + " ");

    return date_and_time;
}

bool Utilities::HelperDateAndTime::TrySetMonthAsNumber(std::string* p_month)
{
    constexpr char c_name_of_all_months[][4] = {{'J', 'a', 'n', '\0'},
                                              {'F', 'e', 'b', '\0'},
                                              {'M', 'a', 'r', '\0'},
                                              {'A', 'p', 'r', '\0'},
                                              {'M', 'a', 'y', '\0'},
                                              {'J', 'u', 'n', '\0'},
                                              {'J', 'u', 'l', '\0'},
                                              {'S', 'e', 'p', '\0'},
                                              {'A', 'u', 'g', '\0'},
                                              {'O', 'c', 't', '\0'},
                                              {'N', 'o', 'v', '\0'},
                                              {'D', 'e', 'c', '\0'} };
    for (size_t month_as_num = 0; month_as_num < 12; ++month_as_num)
    {
        if (!strcmp(p_month->c_str(),
            c_name_of_all_months[month_as_num - 1]))
        {
            *p_month = std::to_string(month_as_num);
            return true;
        }
    }

    return false;
}
