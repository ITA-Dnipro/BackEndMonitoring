#include "stdafx.h"

#include "Utils.h"

//in order to use ctime
#pragma warning(disable:4996)

bool Utils::TryGetCurrentDateAndTimeFormatted(std::string&
    date_time_var_to_save)
{
    //parse to format: dd.mm.yyyy hh:mm:ss
    std::time_t current_time = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now());
    date_time_var_to_save = ctime(&current_time);

    date_time_var_to_save.pop_back();
    date_time_var_to_save = date_time_var_to_save.substr(
        date_time_var_to_save.find_first_of(" ") + 1ULL);
    
    std::string buff_year = date_time_var_to_save.substr(
        date_time_var_to_save.find_last_of(" ") + 1ULL);
    date_time_var_to_save.erase(date_time_var_to_save.end() - buff_year.size(), 
        date_time_var_to_save.end());

    std::string buff_month = date_time_var_to_save.substr(0, 
        date_time_var_to_save.find_first_of(" "));
    date_time_var_to_save.erase(date_time_var_to_save.begin(), 
        date_time_var_to_save.begin() + buff_month.size() + 1ULL);

    if (!TrySetMonthAsNumber(buff_month))
    {
        return false;
    }
    
    date_time_var_to_save.insert(date_time_var_to_save.find_first_of(" "), 
        "." + buff_month);
    date_time_var_to_save.insert(date_time_var_to_save.find_first_of(" "), 
        "." + buff_year + " ");

    return true;
}

bool Utils::TrySetMonthAsNumber(std::string& p_month)
{
    constexpr size_t num_of_month_in_year = 12U;
    constexpr size_t num_of_letters = 4U;
    constexpr char c_name_of_all_months[][num_of_letters] = { 
        {'J', 'a', 'n', '\0'},
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

    for (size_t month_as_num = 0; month_as_num < num_of_month_in_year; 
         ++month_as_num)
    {
        if (!strcmp(p_month.c_str(),
            c_name_of_all_months[month_as_num - 1ULL]))
        {
            p_month = std::to_string(month_as_num);
            return true;
        }
    }

    return false;
}

bool Utils::TryGetFormattedDiskName(std::string& name_of_disk)
{
    if (name_of_disk.empty())
    {
        return false;
    }
    name_of_disk.replace(name_of_disk.begin() + 1ULL, name_of_disk.end(),
        std::string(":/"));

    return true;
}

bool Utils::IsFileEmpty(std::ifstream& file)
{ return file.peek() == std::ifstream::traits_type::eof(); }

bool Utils::IsFileEmpty(std::fstream& file)
{ return file.peek() == std::fstream::traits_type::eof(); }

